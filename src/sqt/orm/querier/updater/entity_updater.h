#pragma once

/**
@file
    Defines the `sqt::EntityUpdater<>` class template.
*/

#include <sqt/orm/expression/operand/entity_value_operand_type.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/querier/where_capability.h>

namespace sqt {

/**
A primary updater that updates values of entities in the table.

@tparam CONFLICT_ACTION
    The conflict action to be used when a unique constraint violation occurs.

@tparam VALUE_OPERAND
    The value operand type that the updater uses for updating. It must satisfy the
    `sqt::EntityValueOperandType` concept.

@details
    This primary updater updates values of entities in the table without any condition. The columns
    to be updated are specified by the `VALUE_OPERAND` type.

    To create instances of this updater, use the `sqt::DataContext::MakeUpdater()` and 
    `sqt::DataContext::MakeNoPrimaryKeyUpdater()` methods.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::ConflictAction
@see sqt::DataContext<>::MakeNoPrimaryKeyUpdater()
@see sqt::DataContext<>::MakeUpdater()
@see sqt::EntityValueOperandType
@see sqt::QuerierType
*/
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
                ConflictActionEnum::ToString(CONFLICT_ACTION),
                table.GetName(), 
                set_clause);
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
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