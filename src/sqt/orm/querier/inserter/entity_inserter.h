#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/operand/entity_value_operand_type.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<ConflictAction CONFLICT_ACTION, EntityValueOperandType VALUE_OPERAND>
class EntityInserter {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = VALUE_OPERAND::ParameterCount;

    static std::string_view BuildSQL() {

        static const std::string sql = []() {

            constexpr auto conflict_action = ConflictActionEnum::ToString(CONFLICT_ACTION);

            constexpr auto& table = Table<typename VALUE_OPERAND::ValueType>;
            constexpr auto table_name = table.GetName();

            return std::format(
                "insert or {} into {} ({}) values ({})", 
                conflict_action, 
                table_name, 
                internal::JoinColumnNames(VALUE_OPERAND::ValueTraits::ManipulatingColumns),
                VALUE_OPERAND::BuildSQL());
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        return VALUE_OPERAND::BuildPlaceholderBinders(ParameterIndex);
    }

public:
    constexpr explicit EntityInserter(VALUE_OPERAND value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement) const {
        value_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    VALUE_OPERAND value_;
};

}