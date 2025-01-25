#pragma once

#include <mutex>
#include <sqt/foundation/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/table_initializer.h>

namespace sqt {

template<typename E>
class DataContext {
public:
    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<E>{};
    }

public:
    explicit DataContext(std::shared_ptr<Database> db) noexcept : init_once_guard_(std::move(db)) {

    }

    template<typename Q>
    auto Prepare(const Q& querier) {

        auto statement = init_once_guard_.DB().PrepareStatement(querier.BuildSQL());
        querier.BindInlineParameters(statement);

        return Executor{ querier, std::move(statement) };
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