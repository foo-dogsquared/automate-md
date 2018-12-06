#pragma once

#include "frontmatter.hpp"
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

bool is_frontmatter_tag(std::string __line) {
	if (__line == "+++" || __line == "---" || __line == "{" || __line == "}")
		return true;
	else
		return false;
}

bool is_markdown(std::string __file_path) {
	std::regex _file_ext_md(".+\\.md|\\.markdown$");

	if (std::regex_match(__file_path, _file_ext_md))
		return true;
	else
		return false;
}

frontmatter extract_frontmatter(std::string __file_path) {
	frontmatter _output;
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
		std::cout << _is_opening_tag_parse << _is_closing_tag_parse << std::endl;

		if (is_frontmatter_tag(_line)) {
			_output.type = detect_type(_line);
			init_fm_format_data(_output);
			_key_value_regex = "^\\s*\"?([A-Za-z0-9!@#$%^&*()_+-]+)\"?" + _output.__assigner + "\\s*(.+)";

			if (!_is_opening_tag_parse && !_is_closing_tag_parse)
				_is_opening_tag_parse = true;
			else if (_is_opening_tag_parse && !_is_closing_tag_parse) {
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

std::string extract_content(std::string __file_path) {
	std::string _output;
	std::ifstream _input_file;
	_input_file.open(__file_path);
	
	if (!_input_file.is_open())
		return "";
	
	std::string _line;
	std::regex _whitespace("\\s+");
	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false, _content_start = false;
	while(getline(_input_file, _line)) {
		if (is_frontmatter_tag(_line) && !_is_opening_tag_parse)
			_is_opening_tag_parse = true;
		else if (is_frontmatter_tag(_line) && _is_opening_tag_parse && !_is_closing_tag_parse)
			_is_closing_tag_parse = true;
		else if ((_is_opening_tag_parse && !_is_closing_tag_parse) || ((regex_match(_line, _whitespace) || _line.empty()) && !_content_start))
			continue;
		else {
			_output += _line + "\n";
			_content_start = true;
		}
	}

	return _output;
}

int post_write(std::string __file_path, frontmatter __frontmatter, std::string __frontmatter_type = "YAML") {
	std::ofstream __output_file;
	
	init_fm_format_data(__frontmatter);  // defensive mechanism in case the struct frontmatter has no initialized data to get

	if (!is_markdown(__file_path))
		__file_path += ".md";

	if (open_file_o(__output_file, __file_path) == FILE_IO_ERROR_NUM)
		return FILE_IO_ERROR_NUM;

	// Writing the frontmatter in the file
	__output_file << __frontmatter.__open_divider << std::endl;
	std::map<std::string, std::string>::iterator _trav = __frontmatter.list.begin();

	while (_trav != __frontmatter.list.end()) {
		__output_file << __frontmatter.__tab << is_json(__frontmatter_type, encloseQuote(_trav->first), _trav->first) << __frontmatter.__assigner << " " << is_yaml(__frontmatter_type, _trav->second, encloseQuote(_trav->second)) << is_json(__frontmatter_type, ",", "") << std::endl;
		_trav++;
	}

	__output_file << __frontmatter.__close_divider << std::endl;

	std::cout << "\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}

int post_write_text(std::string __output_path, std::string __content) {
	if (__content.empty()) 
		return return_error_code(41, "Content from file is empty");
	
	if (!is_markdown(__output_path))
		__output_path += ".md";
	
	std::ofstream _output;
	_output.open(__output_path);
	if (!_output.is_open())
		return 3;

	_output << __content;
	std::cout << "\n" << __output_path << " was successfully created.";

	return 0;
}

int post_parse(std::string __file_path) {
	return 0;
}

int post_extract(std::string __file_path, std::string __output_path, std::string __part = "frontmatter") {
	if (__part == "frontmatter" || __part == "FRONTMATTER") {
		frontmatter _fm = extract_frontmatter(__file_path);
		return post_write(__output_path, _fm, _fm.type);
	} else if (__part == "content" || __part == "CONTENT") {
		std::string _content = extract_content(__file_path);
		return post_write_text(__output_path, _content);
	}
}
