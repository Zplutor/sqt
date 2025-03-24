#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment_type.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<AssignmentType... ASSIGNMENT>
class ColumnUpdater : public WhereCapability<ColumnUpdater<ASSIGNMENT...>> {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = (ASSIGNMENT::ParameterCount + ... + 0);

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
            (build_set_clause(ASSIGNMENT::BuildSQL()), ...);

            using First = std::tuple_element_t<0, std::tuple<ASSIGNMENT...>>;
            constexpr auto& table = Table<typename First::LHSOperand::EntityType>;
            return std::format("update {} set {}", table.GetName(), set_clause);
        }();
        return sql;
    }

    static auto BuildPlaceholderBinders() {
        int index = ParameterIndex;
        return std::tuple_cat(ASSIGNMENT::BuildPlaceholderBinders(index++)...);
    }

public:
    constexpr explicit ColumnUpdater(ASSIGNMENT... assignments) noexcept : 
        assignments_(std::move(assignments)...) {

    }

    void BindInlineParameters(Statement& statement) const {

        int index = ParameterIndex;
        auto bind = [&statement, &index](const auto& assignment) {
            assignment.BindInlineParameters(statement, index);
            index += assignment.ParameterCount;
        };

        std::apply(
            [&bind](const auto&... values) {
                (bind(values), ...);
            },
            assignments_);
    }

private:
    std::tuple<ASSIGNMENT...> assignments_;
};

}