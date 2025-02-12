#pragma once

namespace sqt {

template<typename T, typename = void>
class Operand;


/*
//Used for composite columns such as primary key and index.
template<typename T>
class Operand<T, std::enable_if_t<IsCompositeColumnBasedV<T>>> {
public:
    explicit Operand(const T& composite_column) : composite_column_(&composite_column) {

    }

    std::string BuildSQL() const {
        return std::format("({})", JoinColumnNames(composite_column_->GetAbstractColumns()));
    }

    int BindParameters(Statement& statement, int begin_index) const {
        return begin_index;
    }

private:
    const T* composite_column_{};
};
*/

}
