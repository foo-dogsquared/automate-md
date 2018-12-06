#pragma once

#include "frontmatter.hpp"
#include "frontmatter_type.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>
#include <regex>

#define FILE_IO_ERROR_NUM 3

int open_file_i(std::ifstream &__input_file, std::string __input_path) {
	__input_file.open(__input_path);

	if (!__input_file.is_open())
		return return_error_code(3, "Cannot open file at: " + __input_path);

	return 0;
}

int open_file_o(std::ofstream &__output_file, std::string __output_path) {
	__output_file.open(__output_path);

	if (!__output_file.is_open())
		return return_error_code(3, "Cannot open file at: " + __output_path);

	return 0;
}

frontmatter extract_frontmatter(std::string __file_path) {
	frontmatter _output;
	frontmatter_type _fm_type_obj;
	std::ifstream _input_file;
	if (open_file_i(_input_file, __file_path) == FILE_IO_ERROR_NUM)
		return _output;

	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false;

	std::string _line;
	std::regex _key_value_regex;
	std::smatch _matches;
	std::ssub_match _key, _value;
	while (!_is_opening_tag_parse || !_is_closing_tag_parse) {
		getline(_input_file, _line);

		if (_line == "+++" || _line == "---" || _line == "{" || _line == "}") {
			_fm_type_obj.__type = detect_type(_line);
			_fm_type_obj = init(_fm_type_obj.__type);
			_key_value_regex = "^\\s*\"?(\\w+)\"?" + _fm_type_obj.__assigner + "\\s*(.+)";

			if (!_is_opening_tag_parse)
				_is_opening_tag_parse = true;
			else if (!_is_closing_tag_parse) {
				_is_closing_tag_parse = true;
				_input_file.close();
				break;
			}
		}
		else if (_is_opening_tag_parse && std::regex_match(_line, _matches, _key_value_regex)) {
			_key = _matches[1];
			_value = _matches[2];
			_output.list.insert(std::make_pair(_key.str(), _value.str()));
		}
	}

	return _output;
}

int post_write(std::string __file_path, frontmatter __frontmatter, std::string __frontmatter_type = "YAML") {
	std::ofstream __output_file;
	std::regex _file_ext_md(".+\\.md$");

	if (!std::regex_match(__file_path, _file_ext_md))
		__file_path += ".md";

	frontmatter_type __f = init(__frontmatter_type);
	if (open_file_o(__output_file, __file_path) == FILE_IO_ERROR_NUM)
		return FILE_IO_ERROR_NUM;

	// Writing the frontmatter in the file
	__output_file << __f.__open_divider << std::endl;
	std::map<std::string, std::string>::iterator _trav = __frontmatter.list.begin();

	while (_trav != __frontmatter.list.end()) {
		__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote(_trav->first), _trav->first) << __f.__assigner << " " << is_json(__frontmatter_type, encloseQuote(_trav->second), _trav->second) << is_json(__frontmatter_type, ",", "") << std::endl;
		_trav++;
	}

	__output_file << __f.__close_divider << std::endl;

	std::cout << "\n\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}

int post_parse(std::string __file_path) {
	return 0;
}

int post_extract(std::string __file_path, std::string __output_path, std::string __part = "frontmatter") {
	frontmatter _fm = extract_frontmatter(__file_path);

	std::ofstream _output_file;
	if (open_file_o(_output_file, __output_path) == FILE_IO_ERROR_NUM)
		return FILE_IO_ERROR_NUM;
	
	_output_file.close();
	return 0;
}
