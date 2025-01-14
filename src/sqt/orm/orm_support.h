#pragma once

#include <array>
#include <sqt/orm/abstract_table.h>
#include <sqt/orm/column.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/value_type/primitive_value_type.h>
#include <sqt/orm/value_type/nullable_value_type.h>

#define SQT_TABLE_BEGIN(TABLE_NAME, ENTITY_CLASS) \
namespace __sqt_table_##TABLE_NAME { \
using EntityType = ENTITY_CLASS; \
class TableType : public sqt::AbstractTable { \
public: \
    static constexpr const TableType& GetInstance() noexcept; \
    constexpr std::string_view GetName() const noexcept override { \
        return #TABLE_NAME; \
    } \
    constexpr sqt::ColumnsView<EntityType> GetColumns() const noexcept; \
    sqt::AbstractColumnsView GetAbstractColumns() const noexcept override; \
private: \
    constexpr TableType() noexcept = default; \
    class BaseColumn : public sqt::Column<EntityType> { \
    public: \
        constexpr explicit BaseColumn(const BaseColumn*& last) noexcept : previous_(last) { \
            last = this; \
        } \
    private: \
        friend class TableType; \
        const BaseColumn* const previous_{}; \
    }; \
    const BaseColumn* last_column_{}; \


#define SQT_COLUMN(COLUMN_NAME, CLASS_FIELD) \
public: \
    class COLUMN_NAME##Type : public BaseColumn { \
    private: \
        using ThisType = COLUMN_NAME##Type; \
    public: \
        using ValueType = decltype(((EntityType*)nullptr)->CLASS_FIELD); \
        using ValueTypeTraits = sqt::ValueTypeTraits<ValueType>; \
        constexpr explicit COLUMN_NAME##Type(const BaseColumn*& last) : BaseColumn(last) { } \
        constexpr std::string_view GetName() const noexcept override { \
            return #COLUMN_NAME; \
        } \
        constexpr sqt::DataType GetDataType() const noexcept override { \
            return ValueTypeTraits::DataType; \
        } \
        constexpr bool IsNullable() const noexcept override { \
            return ValueTypeTraits::IsNullable; \
        } \
        void BindValueToStatement( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) const override { \
        } \
        void GetValueFromStatement( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) const override { \
        } \
    }; \
    COLUMN_NAME##Type COLUMN_NAME{ last_column_ };


#define SQT_TABLE_END \
    class Insider; \
}; \
class TableType::Insider { \
public: \
    static constexpr TableType TableInstance; \
    static constexpr std::size_t ColumnCount = []() { \
        std::size_t result{}; \
        auto current = TableInstance.last_column_; \
        while (current) { \
            ++result; \
            current = current->previous_; \
        } \
        return result; \
    }(); \
    template<std::size_t Count> \
    static constexpr void FillColumnArray( \
        std::array<const sqt::Column<EntityType>*, Count>& array, \
        std::size_t index, \
        const sqt::Column<EntityType>* column) { \
        if (index >= array.size()) { \
            return; \
        } \
        array[Count - index - 1] = column; \
        FillColumnArray<Count>( \
            array, ++index, static_cast<const BaseColumn*>(column)->previous_); \
    } \
    template<std::size_t Count> \
    static constexpr std::array<const sqt::Column<EntityType>*, Count> MakeColumns() { \
        std::array<const sqt::Column<EntityType>*, Count> result; \
        FillColumnArray<Count>(result, 0, TableInstance.last_column_); \
        return result; \
    } \
    static constexpr std::array<const sqt::Column<EntityType>*, ColumnCount> Columns = \
        MakeColumns<ColumnCount>(); \
}; \
constexpr const TableType& TableType::GetInstance() noexcept { \
    return Insider::TableInstance; \
} \
constexpr sqt::ColumnsView<EntityType> TableType::GetColumns() const noexcept { \
    return TableType::Insider::Columns; \
} \
inline sqt::AbstractColumnsView TableType::GetAbstractColumns() const noexcept { \
    return { \
        reinterpret_cast<const sqt::AbstractColumn* const*>(GetColumns().data()), \
        GetColumns().size() \
    }; \
} \
};


#define SQT_REGISTER(NAMESPACE, TABLE_NAME) \
namespace sqt { \
template<> \
struct Table<NAMESPACE::__sqt_table_##TABLE_NAME::EntityType> { \
    using type = NAMESPACE::__sqt_table_##TABLE_NAME::TableType; \
}; \
}