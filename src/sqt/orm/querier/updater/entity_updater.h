#pragma once

#include <sqt/orm/expression/operand/entity_value_operand_type.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/querier/where_capability.h>

namespace sqt {

template<ConflictAction CONFLICT_ACTION, EntityValueOperandType VALUE_OPERAND>
class EntityUpdater : public WhereCapability<EntityUpdater<CONFLICT_ACTION, VALUE_OPERAND>> {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = VALUE_OPERAND::ParameterCount;

    static std::string_view BuildSQL() {

        static const std::string sql = []() {

            using TableType = typename VALUE_OPERAND::ValueTraits::TableType;
            constexpr auto& table = TableType::GetInstance();
            constexpr auto columns = VALUE_OPERAND::ValueTraits::ManipulatingColumns;

            std::string set_clause;
            for (std::size_t index = 0; index < columns.size(); ++index) {
                if (index != 0) {
                    set_clause += ',';
                }
                set_clause += std::format("{}=?", columns[index]->GetName());
            }

            return std::format(
                "update or {} {} set {}", 
                ConvertConflictActionToString(CONFLICT_ACTION),
                table.GetName(), 
                set_clause);
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        return VALUE_OPERAND::BuildPlaceholderBinders(ParameterIndex);
    }

public:
    constexpr explicit EntityUpdater(VALUE_OPERAND value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement) const {
        value_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    VALUE_OPERAND value_;
};

}