#pragma once

#include <mutex>
#include <sqt/foundation/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/expression/value_operand.h>
#include <sqt/orm/querier/inserter/entity_inserter.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/table_initializer.h>

namespace sqt {

template<typename E>
class DataContext {
public:
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeInserter() noexcept {
        return EntityInserter<CONFLICT_ACTION, Operand<Placeholder<E>>>{
            Operand<Placeholder<E>>{}
        };
    }

    static constexpr auto MakeAutoIncInserter() noexcept {

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