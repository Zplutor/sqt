#pragma once

/**
@file
    Defines the `sqt::ColumnUpdater<>` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment_type.h>
#include <sqt/orm/internal/assignment_helper.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

/**
A primary updater that updates values of specific columns in the table.

@tparam CONFLICT_ACTION
    The conflict action to be used when a unique constraint violation occurs.

@tparam ASSIGNMENTS
    The assignment types that the updater uses for updating. Each assignment type must satisfy
    the `sqt::AssignmentType` concept.

@details
    This primary updater updates values of specific columns in the table without any condition. The
    columns to be updated are specified by the `ASSIGNMENTS` types.

    To create instances of this updater, use the 
    `sqt::DataContext::MakeUpdater(ASSIGNMENTS&&... assignments)` method.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::AssignmentType
@see sqt::ConflictAction
@see sqt::DataContext<>::MakeUpdater(ASSIGNMENTS&&... assignments)
@see sqt::QuerierType
*/
template<ConflictAction CONFLICT_ACTION, AssignmentType... ASSIGNMENTS>
class ColumnUpdater : public WhereCapability<ColumnUpdater<CONFLICT_ACTION, ASSIGNMENTS...>> {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = (ASSIGNMENTS::ParameterCount + ... + 0);

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            
            std::string set_clause;
            int index{};
            auto build_set_clause = [&set_clause, &index](const std::string& sql) {
                if (index != 0) {
                    set_clause += ',';
                }
                set_clause += sql;
                ++index;
            };
            (build_set_clause(ASSIGNMENTS::BuildSQL()), ...);

            using First = std::tuple_element_t<0, std::tuple<ASSIGNMENTS...>>;
            constexpr auto& table = Table<typename First::LHSOperand::EntityType>;
            return std::format(
                "update or {} {} set {}", 
                ConflictActionEnum::ToString(CONFLICT_ACTION),
                table.GetName(), 
                set_clause);
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        int index = ParameterIndex;
        return std::tuple_cat(ASSIGNMENTS::BuildPlaceholderBinders(index++)...);
    }

public:
    constexpr explicit ColumnUpdater(ASSIGNMENTS... assignments) noexcept : 
        assignments_(std::move(assignments)...) {

    }

    void BindInlineParameters(Statement& statement) const {
        internal::BindAssignmentInlineParameters(statement, ParameterIndex, assignments_);
    }

private:
    std::tuple<ASSIGNMENTS...> assignments_;
};

}