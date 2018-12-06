#include <iostream>
#include <regex>
#include <string>

bool _begin_isDir(std::string __path)
{
	std::regex _begin__dir_regex("^\\.\\.?/.*");

	if (regex_match(__path, _begin__dir_regex))
		return true;
	else
		return false;
}

bool _end_isDir(std::string __path) {
	std::regex _end__dir_regex(".*/$");

	if (std::regex_match(__path, _end__dir_regex))
		return true;
	else
		return false;
}

bool hasNondigits(std::string __str) {
	std::regex __digit_regex("\\d+");

	if (!std::regex_match(__str, __digit_regex))
		return true;
	else
		return false;
}
