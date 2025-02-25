#pragma once

#include <mutex>
#include <sqt/foundation/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/expression/operand/value_operand.h>
#include <sqt/orm/querier/inserter/entity_inserter.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table/table_initializer.h>
#include <sqt/orm/value/auto_inc_entity_value_traits.h>
#include <sqt/orm/value/entire_entity_value_traits.h>
#include <sqt/orm/value/entity_value_type.h>

namespace sqt {

template<EntityValueType E>
class DataContext {
public:
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeInserter() noexcept {
        using ValueTraits = EntireEntityValueTraits<E>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeReplacer() noexcept {
        return MakeInserter<ConflictAction::Replace>();
    }

    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeAutoIncInserter() noexcept requires AutoIncEntityValueType<E> {
        using ValueTraits = AutoIncEntityValueTraits<E>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeAutoIncReplacer() noexcept requires AutoIncEntityValueType<E> {
        return MakeAutoIncInserter<ConflictAction::Replace>();
    }

    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<E>{};
    }

public:
    explicit DataContext(std::shared_ptr<Database> db) noexcept : init_once_guard_(std::move(db)) {

    }

    DataContext(const DataContext&) = delete;
    DataContext& operator=(const DataContext&) = delete;

    template<typename Q>
    auto Prepare(const Q& querier) {
        auto statement = init_once_guard_.DB().PrepareStatement(querier.BuildSQL());
        querier.BindInlineParameters(statement);
        return Executor{ querier, std::move(statement) };
    }

    void Insert(const E& entity) {
        constexpr auto inserter = MakeInserter();
        ExecuteEntityInserter(inserter, entity);
    }

    void AutoIncInsert(const E& entity) {
        constexpr auto inserter = MakeAutoIncInserter();
        ExecuteEntityInserter(inserter, entity);
    }

    void Replace(const E& entity) {
        constexpr auto replacer = MakeReplacer();
        ExecuteEntityInserter(replacer, entity);
    }

    void AutoIncReplace(const E& entity) {
        constexpr auto replacer = MakeAutoIncReplacer();
        ExecuteEntityInserter(replacer, entity);
    }

private:
    template<typename INSERTER>
    void ExecuteEntityInserter(const INSERTER& inserter, const E& entity) {
        auto executer = Prepare(inserter);
        executer.BeginBind().Bind(entity);
        executer.Execute();
    }

private:
    class InitOnceGuard {
    public:
        InitOnceGuard(std::shared_ptr<Database> db) noexcept : db_(std::move(db)) {

        }

        InitOnceGuard(const InitOnceGuard&) = delete;
        InitOnceGuard& operator=(const InitOnceGuard&) = delete;

        Database& DB() {
            std::call_once(init_once_flag_, [this]() {
                TableInitializer::Initialize(TableV<E>, *db_);
            });
            return *db_;
        }

    private:
        std::shared_ptr<Database> db_;
        std::once_flag init_once_flag_;
    };

private:
    InitOnceGuard init_once_guard_;
};

}