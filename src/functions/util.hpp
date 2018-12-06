#pragma once

#include <ctime>
#include <iostream>
#include <regex>
#include <string>

#include "util/util_bool.hpp"
#include "util/util_string.hpp"
#include "util/util_prompt.hpp"

#define INVALID_CHARS " !@#$%^&*()_+={}[]:;\"'<,>.?/|\\~`"

int return_error_code(int error_num, std::string description) {
    std::cerr << "Error " << error_num << ": " << description << std::endl;
    return error_num;
}

int prompt_int(std::string __question, int __minimum = 0, int __maximum = INT8_MAX)
{
	std::string _out;
	int _num = 0;
	do {
		_out = prompt(__question);

		if (hasNondigits(_out))
			continue;

		_num = stoi(_out);

		if (_num < __minimum || _num > __maximum)
			std::cout << "Value can only range from " << std::to_string(__minimum) << " to " << std::to_string(__maximum) << std::endl;
	} while (_num < __minimum || _num > __maximum);

	return _num;
}

std::string check_dir_path(std::string __file_path) {
	std::string _output;

	if (!_begin_isDir(__file_path))
		_output = "./" + __file_path;
	else
		_output = __file_path;

	if (!_end_isDir(__file_path))
		_output += "/";

	return _output;
}