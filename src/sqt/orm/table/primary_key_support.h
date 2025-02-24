#pragma once

#include <sqt/orm/table/primary_key.h>

#define SQT_DEFINE_PRIMARY_KEY(AUTO_INC, ...) \
private: \
    using PrimaryKeyBaseType = decltype(sqt::MakePrimaryKey(__VA_ARGS__)); \
public: \
    class PrimaryKeyType : public PrimaryKeyBaseType { \
    public: \
        using PrimaryKeyBaseType::PrimaryKeyBaseType; \
        constexpr bool IsAutoInc() const noexcept override { \
            return AUTO_INC; \
        } \
    }; \
    PrimaryKeyType PrimaryKey{ __VA_ARGS__ }; \
    constexpr const sqt::AbstractPrimaryKey* GetAbstractPrimaryKey() const noexcept override { \
        return &PrimaryKey; \
    }