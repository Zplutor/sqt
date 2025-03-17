#pragma once

#include <sqt/orm/utility/macro_utility.h>

#define SQT_MAKE_INDEX_BASE_TYPE_NAME(NAME) IndexBaseType_##NAME 
#define SQT_INDEX_BASE_TYPE_NAME_(NAME) SQT_MAKE_INDEX_BASE_TYPE_NAME(NAME)
#define SQT_INDEX_BASE_TYPE_NAME(...) SQT_INDEX_BASE_TYPE_NAME_(SQL_UTILITY_JOIN(__VA_ARGS__))

#define SQT_MAKE_INDEX_TYPE_NAME(NAME) IndexType_##NAME 
#define SQT_INDEX_TYPE_NAME_(NAME) SQT_MAKE_INDEX_TYPE_NAME(NAME)
#define SQT_INDEX_TYPE_NAME(...) SQT_INDEX_TYPE_NAME_(SQL_UTILITY_JOIN(__VA_ARGS__))

#define SQT_MAKE_INDEX_NAME(NAME) Index_##NAME 
#define SQT_INDEX_NAME_(NAME) SQT_MAKE_INDEX_NAME(NAME)
#define SQT_INDEX_NAME(...) SQT_INDEX_NAME_(SQL_UTILITY_JOIN(__VA_ARGS__))

#define SQT_INDEX_NAME_STRING_(NAME) SQT_UTILITY_STRINGIZE(NAME)
#define SQT_INDEX_NAME_STRING(...) SQT_INDEX_NAME_STRING_(SQT_INDEX_NAME(__VA_ARGS__))


#define SQT_DEFINE_INDEX(UNIQUE, ...) \
private: \
    using SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__) = decltype(MakeBaseIndex(__VA_ARGS__)); \
public: \
    class SQT_INDEX_TYPE_NAME(__VA_ARGS__) : public SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__) { \
    private: \
        static constexpr std::string_view IndexName = SQT_INDEX_NAME_STRING(__VA_ARGS__); \
        static constexpr std::size_t FullNameLength = UserTableName.size() + IndexName.size() + 1;\
        static constexpr std::array<char, FullNameLength> FullName = \
            sqt::MakeIndexFullName<FullNameLength>(UserTableName, IndexName); \
    public: \
        using SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__)::SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__); \
        std::string_view GetName() const noexcept override { \
            return std::string_view{ FullName.data(), FullName.size() }; \
        } \
        constexpr bool IsUnique() const noexcept override { \
            return UNIQUE; \
        } \
    }; \
    SQT_INDEX_TYPE_NAME(__VA_ARGS__) SQT_INDEX_NAME(__VA_ARGS__){ \
        index_linked_list_.Last(), __VA_ARGS__ };


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