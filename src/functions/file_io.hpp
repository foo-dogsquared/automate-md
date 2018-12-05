#pragma once

#include "frontmatter.hpp"
#include "frontmatter_type.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>
#include <regex>

frontmatter extract_frontmatter(std::string __file_path) {
	frontmatter _output;
	frontmatter_type _fm_type_obj;
	std::ifstream _input_file;

	_input_file.open(__file_path);

	if (!_input_file.is_open())
		return _output;

	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false;

	std::string _line;
	std::regex _key_value_regex;
	std::smatch _matches;
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
			std::ssub_match _key = _matches[1];
			std::ssub_match _value = _matches[2];
			std::cout << _matches[2]  << std::endl;
			if (removeQuote(_key) == "author")
				_output.author = _value;
			else if (removeQuote(_key) == "layout")
				_output.layout = _value;
			else if (removeQuote(_key) == "date")
				_output.date = _value;
			else if (removeQuote(_key) == "title")
				_output.title = _value;
			else if (removeQuote(_key) == "categories")
				_output.categories = arr_extract(_value);
			else if (removeQuote(_key) == "tags")
				_output.tags = arr_extract(_value);
			else
				_output.others.insert(std::make_pair(_key.str(), _value.str()));
		}
	}

	return _output;
}

int post_write(std::string __file_path, frontmatter __frontmatter, std::string __frontmatter_type = "YAML") {
	std::ofstream __output_file;

	 frontmatter_type __f = init(__frontmatter_type);
	
	__output_file.open(__file_path);

	if (!(__output_file.is_open()))
		return return_error_code(3, "Can't open file at \"" + __file_path + "\".");

	// Writing the frontmatter in the file
	__output_file << __f.__open_divider << std::endl;
	__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("layout"), "layout") << __f.__assigner << " " << is_json(__frontmatter_type, encloseQuote(__frontmatter.layout), __frontmatter.layout) << is_json(__frontmatter_type, ",", "") << std::endl;
	__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("title"), "title") << __f.__assigner << " " << is_json(__frontmatter_type, encloseQuote(__frontmatter.title), __frontmatter.title) << is_json(__frontmatter_type, ",", "") << std::endl;
	__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("date"), "date") << __f.__assigner << " " << is_json(__frontmatter_type, encloseQuote(__frontmatter.date), __frontmatter.date) << is_json(__frontmatter_type, ",", "") << std::endl;
	__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("author"), "author") << __f.__assigner << " " << is_json(__frontmatter_type, encloseQuote(__frontmatter.author), __frontmatter.author) << is_json(__frontmatter_type, ",", "") << std::endl;

	if (__frontmatter.categories_length > 0)
		__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("categories"), "categories") << __f.__assigner << " " << encloseQuote_arr(__frontmatter.categories, __frontmatter.categories_length) << is_json(__frontmatter_type, ",", "") << std::endl;
	if (__frontmatter.tags_length > 0)
		__output_file << __f.__tab << is_json(__frontmatter_type, encloseQuote("tags"), "tags") << __f.__assigner << " " << encloseQuote_arr(__frontmatter.tags, __frontmatter.tags_length) << std::endl;

	__output_file << __f.__close_divider << std::endl;

	std::cout << "\n\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}

int post_parse(std::string __file_path) {
	return 0;
}

int post_extract(std::string __file_path, std::string __part = "frontmatter") {
	frontmatter _fm = extract_frontmatter(__file_path);

	std::cout << _fm.date << std::endl;

	return 0;
}
