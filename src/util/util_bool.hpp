#include <iostream>
#include <regex>
#include <string>

namespace util {
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

	bool has_non_digits(std::string __str) {
		std::regex __digit_regex("\\d+");

		if (!std::regex_match(__str, __digit_regex))
			return true;
		else
			return false;
	}

	bool str_is_array(std::string __str) {
		if (__str.front() == '[' && __str.back() == ']')
			return true;
		else
			return false;
	}

	bool is_quoted(std::string __str) {
		if (__str.front() == '\"' && __str.back() == '\"')
			return true;
		else
			return false;
	}

	bool is_not_valid_fm_format(std::string __str) {
		if (__str != "YAML" || __str != "yaml" || __str != "JSON" || __str != "json" || __str != "TOML" || __str != "toml")
			return false;
		else
			return true;
	}
}
