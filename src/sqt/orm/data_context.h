#pragma once

#include <mutex>
#include <optional>
#include <vector>
#include <sqt/foundation/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/querier/deleter/deleter.h>
#include <sqt/orm/querier/inserter/entity_inserter.h>
#include <sqt/orm/querier/selecter/column_selecter.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/querier/updater/column_updater.h>
#include <sqt/orm/querier/updater/entity_updater.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/internal/table_initializer.h>
#include <sqt/orm/value/entity/entire_entity_value_traits.h>
#include <sqt/orm/value/entity/entity_value_type.h>
#include <sqt/orm/value/entity/no_primary_key_entity_value_traits.h>

namespace sqt {

template<EntityValueType ENTITY>
class DataContext {
public:
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeInserter() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeReplacer() noexcept {
        return MakeInserter<ConflictAction::Replace>();
    }

    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeAutoIncInserter() noexcept requires AutoIncEntityValueType<ENTITY> {
        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeAutoIncReplacer() noexcept requires AutoIncEntityValueType<ENTITY> {
        return MakeAutoIncInserter<ConflictAction::Replace>();
    }

    static constexpr auto MakeUpdater() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<Operand>{ Operand{} };
    }

    static constexpr auto MakeNoPrimaryKeyUpdater() noexcept
        requires PrimaryKeyEntityValueType<ENTITY> {

        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<Operand>{ Operand{} };
    }

    template<AssignmentType... ASSIGNMENT>
    static constexpr auto MakeUpdater(ASSIGNMENT... assignments) noexcept {
        return ColumnUpdater<ASSIGNMENT...>{ std::move(assignments)... };
    }

    static constexpr auto MakeDeleter() noexcept {
        return Deleter<ENTITY>{};
    }

    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<ENTITY>{};
    }

    template<ColumnType... COLUMN>
    static constexpr auto MakeSelecter(const COLUMN&... columns) noexcept {
        return ColumnSelecter<COLUMN...>{};
    }

public:
    explicit DataContext(sqt::Database database) : 
        DataContext(std::make_shared<sqt::Database>(std::move(database))) {

    }

    explicit DataContext(std::shared_ptr<sqt::Database> database) noexcept :
        init_once_guard_(std::move(database)) {

    }

    DataContext(const DataContext&) = delete;
    DataContext& operator=(const DataContext&) = delete;

    template<QuerierType QUERIER>
    auto Prepare(const QUERIER& querier) {
        auto db = init_once_guard_.DB();
        auto sql = querier.BuildSQL();
        auto statement = db->PrepareStatement(sql);
        querier.BindInlineParameters(statement);
        return Executor{ querier, std::move(db), std::move(statement) };
    }

    std::int64_t Insert(const ENTITY& entity) {
        constexpr auto inserter = MakeInserter();
        return ExecuteEntityInserter(inserter, entity);
    }

    std::int64_t AutoIncInsert(const ENTITY& entity) {
        constexpr auto inserter = MakeAutoIncInserter();
        return ExecuteEntityInserter(inserter, entity);
    }

    std::int64_t Replace(const ENTITY& entity) {
        constexpr auto replacer = MakeReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }

    std::int64_t AutoIncReplace(const ENTITY& entity) {
        constexpr auto replacer = MakeAutoIncReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }

    template<typename E = ENTITY>
    bool Update(const E& entity) requires PrimaryKeyEntityValueType<E> {
        constexpr auto updater = MakeNoPrimaryKeyUpdater().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(updater);
        executor.BeginBind().Bind(entity).BindFromEntity(entity);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    std::size_t DeleteAll() {
        constexpr auto deleter = MakeDeleter();
        auto executor = Prepare(deleter);
        executor.Execute();
        return executor.LastChanges();
    }

    template<typename E = ENTITY>
    bool Delete(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) 
        requires PrimaryKeyEntityValueType<E> {

        constexpr auto deleter = MakeDeleter().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(deleter);
        executor.BeginBind().Bind(primary_key);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    std::vector<ENTITY> SelectAll() {
        constexpr auto selecter = MakeSelecter();
        auto executor = Prepare(selecter);
        auto result = executor.Execute();
        return std::vector<ENTITY>{ result.begin(), result.end() };
    }

    template<typename E = ENTITY>
    std::optional<E> Select(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) 
        requires PrimaryKeyEntityValueType<E> {

        constexpr auto selecter = MakeSelecter().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(selecter);
        executor.BeginBind().Bind(primary_key);
        auto result = executor.Execute();
        auto begin = result.begin();
        if (begin != result.end()) {
            return *begin;
        }
        return std::nullopt;
    }

    void InitializeTable() {
        init_once_guard_.DB();
    }

    const std::shared_ptr<sqt::Database>& Database() const noexcept {
        return init_once_guard_.DB();
    }

private:
    template<typename INSERTER>
    std::int64_t ExecuteEntityInserter(const INSERTER& inserter, const ENTITY& entity) {
        auto executor = Prepare(inserter);
        executor.BeginBind().Bind(entity);
        executor.Execute();
        return executor.LastInsertRowID();
    }

private:
    class InitOnceGuard {
    public:
        InitOnceGuard(std::shared_ptr<sqt::Database> db) noexcept : db_(std::move(db)) {

        }

        InitOnceGuard(const InitOnceGuard&) = delete;
        InitOnceGuard& operator=(const InitOnceGuard&) = delete;

        const std::shared_ptr<sqt::Database>& DB() const {
            return db_;
        }

        const std::shared_ptr<sqt::Database>& DB() {
            std::call_once(init_once_flag_, [this]() {
                internal::TableInitializer::Initialize(Table<ENTITY>, *db_);
            });
            return db_;
        }

    private:
        std::shared_ptr<sqt::Database> db_;
        std::once_flag init_once_flag_;
    };

private:
    InitOnceGuard init_once_guard_;
};

}