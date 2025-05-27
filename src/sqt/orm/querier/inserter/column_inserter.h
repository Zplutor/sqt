#pragma once

/**
@file
    Defines the `sqt::ColumnInserter<>` class template.
*/

#include <format>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment_type.h>
#include <sqt/orm/internal/assignment_helper.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

/**
A primary inserter that inserts values to specific columns in the table.

@tparam CONFLICT_ACTION
    The conflict action to be used when a unique constraint violation occurs.

@tparam ASSIGNMENTS
    The assignment types that the inserter uses for insertion. Each assignment type must satisfy 
    the `sqt::AssignmentType` concept.

@details
    This primary inserter inserts values to specific columns in the table. The columns to be 
    inserted are specified by the `ASSIGNMENTS` types.

    To create instances of this inserter, use the 
    `sqt::DataContext::MakeInserter(ASSIGNMENTS&&... assignments)` method.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::AssignmentType
@see sqt::ConflictAction
@see sqt::DataContext<>::MakeInserter(ASSIGNMENTS&&... assignments)
@see sqt::QuerierType
*/
template<ConflictAction CONFLICT_ACTION, AssignmentType... ASSIGNMENTS>
class ColumnInserter {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = (ASSIGNMENTS::ParameterCount + ... + 0);

    static std::string_view BuildSQL() {
        static const std::string sql = []() {

            std::string column_names;
            int index{};
            auto build_column_names = [&column_names, &index](const std::string& name) {
                if (index != 0) {
                    column_names += ',';
                }
                column_names += name;
                ++index;
            };
            (build_column_names(ASSIGNMENTS::LHSOperand::BuildSQL()), ...);

            constexpr auto conflict_action = ConflictActionEnum::ToString(CONFLICT_ACTION);

            using First = std::tuple_element_t<0, std::tuple<ASSIGNMENTS...>>;
            constexpr auto& table = Table<typename First::LHSOperand::EntityType>;
            constexpr auto table_name = table.GetName();

            return std::format(
                "insert or {} into {} ({}) values ({})",
                conflict_action,
                table_name,
                column_names,
                internal::JoinPlaceholders(ParameterCount));
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        int index = ParameterIndex;
        return std::tuple_cat(ASSIGNMENTS::BuildPlaceholderBinders(index++)...);
    }

public:
    constexpr explicit ColumnInserter(ASSIGNMENTS... assignments) noexcept :
        assignments_(std::move(assignments)...) {

    }

    void BindInlineParameters(Statement& statement) const {
        internal::BindAssignmentInlineParameters(statement, ParameterIndex, assignments_);
    }

private:
    std::tuple<ASSIGNMENTS...> assignments_;
};

}