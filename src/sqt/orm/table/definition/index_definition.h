#pragma once

#include <sqt/orm/internal/macro_utility.h>

#define __SQT_INDEX_BASE_TYPE_NAME_IMPL_2(NAME) IndexBaseType_##NAME 
#define __SQT_INDEX_BASE_TYPE_NAME_IMPL_1(NAME) __SQT_INDEX_BASE_TYPE_NAME_IMPL_2(NAME)
#define __SQT_INDEX_BASE_TYPE_NAME(...) __SQT_INDEX_BASE_TYPE_NAME_IMPL_1(__SQT_JOIN(__VA_ARGS__))

#define __SQT_INDEX_TYPE_NAME_IMPL_2(NAME) IndexType_##NAME 
#define __SQT_INDEX_TYPE_NAME_IMPL_1(NAME) __SQT_INDEX_TYPE_NAME_IMPL_2(NAME)
#define __SQT_INDEX_TYPE_NAME(...) __SQT_INDEX_TYPE_NAME_IMPL_1(__SQT_JOIN(__VA_ARGS__))

#define __SQT_INDEX_INSTANCE_NAME_IMPL_2(NAME) Index_##NAME 
#define __SQT_INDEX_INSTANCE_NAME_IMPL_1(NAME) __SQT_INDEX_INSTANCE_NAME_IMPL_2(NAME)
#define __SQT_INDEX_INSTANCE_NAME(...) __SQT_INDEX_INSTANCE_NAME_IMPL_1(__SQT_JOIN(__VA_ARGS__))


#define __SQT_INDEX_BEGIN(BASE_TYPE_NAME, TYPE_NAME, ...) \
private: \
    using BASE_TYPE_NAME = decltype(sqt::MakeCompositeColumn(__VA_ARGS__)); \
public: \
    class TYPE_NAME : public BASE_TYPE_NAME, public IndexLinkedList::Node { \
    public: \
        constexpr TYPE_NAME(const IndexLinkedList::Node*& last_index) : \
            IndexLinkedList::Node(last_index) { } \
        sqt::AbstractColumnsView GetAbstractColumns() const noexcept override { \
            return BASE_TYPE_NAME::GetAbstractColumns(); \
        }


#define __SQT_INDEX_AUTO_NAME(...) \
    private: \
        static constexpr std::string_view ColumnNames = __SQT_JOIN_AS_STRING(__VA_ARGS__); \
        static constexpr std::size_t AutoNameLength = \
            sqt::internal::IndexAutoNamePrefix.length() + \
            TableName.length() + ColumnNames.length() + 1; \
        static constexpr std::array<char, AutoNameLength> AutoName = \
            sqt::internal::MakeIndexAutoName<AutoNameLength>(TableName, ColumnNames); \
    public: \
        std::string_view GetName() const noexcept override { \
            return std::string_view{ AutoName.data(), AutoName.size() }; \
        }


#define __SQT_INDEX_CUSTOM_NAME(NAME) \
        std::string_view GetName() const noexcept override { \
            return #NAME; \
        }


#define __SQT_INDEX_UNIQUE(IS_UNIQUE) \
        constexpr bool IsUnique() const noexcept override { \
            return IS_UNIQUE; \
        }


#define __SQT_INDEX_END(INSTANCE_NAME) \
    } INSTANCE_NAME{ index_linked_list_.Last() };


#define __SQT_DEFINE_INDEX_AUTO_NAME(IS_UNIQUE, ...) \
__SQT_INDEX_BEGIN( \
    __SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__), \
    __SQT_INDEX_TYPE_NAME(__VA_ARGS__), \
    __VA_ARGS__) \
__SQT_INDEX_AUTO_NAME(__VA_ARGS__) \
__SQT_INDEX_UNIQUE(IS_UNIQUE) \
__SQT_INDEX_END(__SQT_INDEX_INSTANCE_NAME(__VA_ARGS__))


#define __SQT_DEFINE_INDEX_CUSTOM_NAME(INDEX_NAME, INSTANCE_NAME, IS_UNIQUE, ...) \
__SQT_INDEX_BEGIN(IndexBaseType_##INSTANCE_NAME, IndexType_##INSTANCE_NAME, __VA_ARGS__) \
__SQT_INDEX_CUSTOM_NAME(INDEX_NAME) \
__SQT_INDEX_UNIQUE(IS_UNIQUE) \
__SQT_INDEX_END(INSTANCE_NAME)


namespace sqt::internal {

constexpr std::string_view IndexAutoNamePrefix = "SQTIndex_";

template<std::size_t LENGTH>
inline constexpr auto MakeIndexAutoName(
    std::string_view table_name,
    std::string_view column_names) {

    std::array<char, LENGTH> result{};

    std::size_t index{};

    for (auto ch : IndexAutoNamePrefix) {
        result[index++] = ch;
    }

    for (auto ch : table_name) {
        result[index++] = ch;
    }

    result[index++] = '_';

    for (auto ch : column_names) {
        result[index++] = ch;
    }

    return result;
}

}