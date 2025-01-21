#pragma once

#include <sqt/foundation/statement.h>

namespace sqt {

template<typename E>
class EntityBinder {
public:
    using ValueType = E;

public:
    constexpr explicit EntityBinder(int index) : index_(index) {

    }

    void Bind(Statement& statement, const ValueType& entity) {

    }

private:
    int index_{};
};

}