#pragma once

#include <sqt/orm/internal/macro_utility.h>

#define __SQT_MAKE_INDEX_BASE_TYPE_NAME(NAME) IndexBaseType_##NAME 
#define __SQT_INDEX_BASE_TYPE_NAME_(NAME) __SQT_MAKE_INDEX_BASE_TYPE_NAME(NAME)
#define __SQT_INDEX_BASE_TYPE_NAME(...) __SQT_INDEX_BASE_TYPE_NAME_(__SQT_JOIN(__VA_ARGS__))

#define __SQT_MAKE_INDEX_TYPE_NAME(NAME) IndexType_##NAME 
#define __SQT_INDEX_TYPE_NAME_(NAME) __SQT_MAKE_INDEX_TYPE_NAME(NAME)
#define __SQT_INDEX_TYPE_NAME(...) __SQT_INDEX_TYPE_NAME_(__SQT_JOIN(__VA_ARGS__))

#define __SQT_MAKE_INDEX_NAME(NAME) Index_##NAME 
#define __SQT_INDEX_NAME_(NAME) __SQT_MAKE_INDEX_NAME(NAME)
#define __SQT_INDEX_NAME(...) __SQT_INDEX_NAME_(__SQT_JOIN(__VA_ARGS__))

#define __SQT_INDEX_NAME_STRING_(NAME) __SQT_STRINGIZE(NAME)
#define __SQT_INDEX_NAME_STRING(...) __SQT_INDEX_NAME_STRING_(__SQT_INDEX_NAME(__VA_ARGS__))


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
        static constexpr std::string_view IndexName = __SQT_INDEX_NAME_STRING(__VA_ARGS__); \
        static constexpr std::size_t FullNameLength = TableName.size() + IndexName.size() + 1; \
        static constexpr std::array<char, FullNameLength> FullName = \
            sqt::MakeIndexFullName<FullNameLength>(TableName, IndexName); \
    public: \
        std::string_view GetName() const noexcept override { \
            return std::string_view{ FullName.data(), FullName.size() }; \
        }


#define __SQT_INDEX_CUSTOM_NAME(NAME) \
        std::string_view GetName() const noexcept override { \
            return #NAME; \
        }


#define __SQT_INDEX_UNIQUE(IS_UNIQUE) \
        constexpr bool IsUnique() const noexcept override { \
            return IS_UNIQUE; \
        }


#define __SQT_INDEX_END(FILED_NAME) \
    } FILED_NAME{ index_linked_list_.Last() };


#define __SQT_DEFINE_INDEX_AUTO_NAME(IS_UNIQUE, ...) \
__SQT_INDEX_BEGIN( \
    __SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__), \
    __SQT_INDEX_TYPE_NAME(__VA_ARGS__), \
    __VA_ARGS__) \
__SQT_INDEX_AUTO_NAME(__VA_ARGS__) \
__SQT_INDEX_UNIQUE(IS_UNIQUE) \
__SQT_INDEX_END(__SQT_INDEX_NAME(__VA_ARGS__))


#define __SQT_DEFINE_INDEX_CUSTOM_NAME(NAME, IS_UNIQUE, ...) \
__SQT_INDEX_BEGIN(IndexBaseType_##NAME, IndexType_##NAME, __VA_ARGS__) \
__SQT_INDEX_CUSTOM_NAME(NAME) \
__SQT_INDEX_UNIQUE(IS_UNIQUE) \
__SQT_INDEX_END(Index_##NAME)


namespace sqt {

template<std::size_t LENGTH>
inline constexpr auto MakeIndexFullName(std::string_view table_name, std::string_view index_name) {

    std::array<char, LENGTH> result{};

    std::size_t index{};

    for (auto ch : table_name) {
        result[index++] = ch;
    }

    result[index++] = '_';

    for (auto ch : index_name) {
        result[index++] = ch;
    }

    return result;
}

}