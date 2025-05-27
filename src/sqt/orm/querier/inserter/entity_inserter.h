#pragma once

/**
@file
    Defines the `sqt::EntityInserter<>` class template.
*/

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/operand/entity_value_operand_type.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

/**
A primary inserter that inserts entities into the table.

@tparam CONFLICT_ACTION
    The conflict action to be used when a unique constraint violation occurs.

@tparam VALUE_OPERAND
    The value operand type that the inserter uses for insertion. It must satisfy the 
    `sqt::EntityValueOperandType` concept.

@details
    This primary inserter inserts entities into the table. The columns to be inserted are specified
    by the `VALUE_OPERAND` type.

    To create instances of this inserter, use the `sqt::DataContext::MakeInserter()` method.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::ConflictAction
@see sqt::DataContext<>::MakeInserter()
@see sqt::EntityValueOperandType
@see sqt::QuerierType
*/
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