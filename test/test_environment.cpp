#include "test_environment.h"

std::filesystem::path MakeTempFilePath(std::string_view file_name) {

    auto directory = std::filesystem::current_path() / "temp";
    std::filesystem::create_directories(directory);
    return directory / file_name;
}