#pragma once

#include <filesystem>
#include <string_view>

std::filesystem::path MakeTempFilePath(std::string_view file_name);