#pragma once

#include <format>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment_type.h>
#include <sqt/orm/internal/assignment_helper.h>
#include <sqt/orm/querier/conflict_action.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/utility/utility.h>

namespace sqt {

template<ConflictAction CONFLICT_ACTION, AssignmentType... ASSIGNMENT>
class ColumnInserter {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = (ASSIGNMENT::ParameterCount + ... + 0);

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
            (build_column_names(ASSIGNMENT::LHSOperand::BuildSQL()), ...);

            constexpr auto conflict_action = ConflictActionEnum::ToString(CONFLICT_ACTION);

            using First = std::tuple_element_t<0, std::tuple<ASSIGNMENT...>>;
            constexpr auto& table = Table<typename First::LHSOperand::EntityType>;
            constexpr auto table_name = table.GetName();

            return std::format(
                "insert or {} into {} ({}) values ({})",
                conflict_action,
                table_name,
                column_names,
                JoinPlaceholders(ParameterCount));
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        int index = ParameterIndex;
        return std::tuple_cat(ASSIGNMENT::BuildPlaceholderBinders(index++)...);
    }

public:
    constexpr explicit ColumnInserter(ASSIGNMENT... assignments) noexcept :
        assignments_(std::move(assignments)...) {

    }

    void BindInlineParameters(Statement& statement) const {
        internal::BindAssignmentInlineParameters(statement, ParameterIndex, assignments_);
    }

private:
    std::tuple<ASSIGNMENT...> assignments_;
};

}