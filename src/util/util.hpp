#pragma once

#include <ctime>
#include <iostream>
#include <regex>
#include <string>

#include "util_bool.hpp"
#include "util_string.hpp"
#include "util_prompt.hpp"

static void exit_error_code(int error_num, std::string description) {
    std::cerr << "Error " << error_num << ": " << description << std::endl;
    exit(error_num);
}
