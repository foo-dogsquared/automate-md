#pragma once

#include "frontmatter.hpp"
#include "frontmatter_type.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>

frontmatter extract_frontmatter(std::string __file_path) {
	frontmatter _output;
	frontmatter_type _fm_type_obj;
	std::ifstream _input_file;

	_input_file.open(__file_path);

	if (!_input_file.is_open())
		return _output;

	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false;

	std::string _line;
	std::vector<std::string> _contents;
	std::regex _val("(" + _fm_type_obj.__tab + ")(.+)(" + _fm_type_obj.__assigner + ")(.+)");
	while (!_is_opening_tag_parse || !_is_closing_tag_parse) {
		getline(_input_file, _line);

		if (_line == "+++" || _line == "---" || _line == "{" || _line == "}") {
			_fm_type_obj.__type = detect_type(_line);
			_fm_type_obj = init(_fm_type_obj.__type);

			if (!_is_opening_tag_parse)
				_is_opening_tag_parse = true;
			else if (!_is_closing_tag_parse)
				_is_closing_tag_parse = true;
		}


		std::smatch _matches;
		if (_is_opening_tag_parse && std::regex_search(_line, _matches, _val)) {
			if (removeQuote(_matches[2]) == "author")
				_output.author = _matches[4];
			else if (removeQuote(_matches[2]) == "layout")
				_output.layout = _matches[4];
			else if (removeQuote(_matches[2]) == "title")
				_output.title = _matches[4];
			else if (removeQuote(_matches[2]) == "categories")
				_output.categories = arr_extract(_matches[4]);
			else if (removeQuote(_matches[2]) == "tags")
				_output.tags = arr_extract(_matches[4]);
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
	__output_file << __f.__tab << is_json("layout", __frontmatter_type) << __f.__assigner << " " << encloseQuote(__frontmatter.layout) << std::endl;
	__output_file << __f.__tab << is_json("title", __frontmatter_type) << __f.__assigner << " " << encloseQuote(__frontmatter.title) << std::endl;
	__output_file << __f.__tab << is_json("date", __frontmatter_type) << __f.__assigner << " " << encloseQuote(__frontmatter.date) << std::endl;
	__output_file << __f.__tab << is_json("author", __frontmatter_type) << __f.__assigner << " " << encloseQuote(__frontmatter.author) << std::endl;

	if (__frontmatter.categories_length > 0)
		__output_file << __f.__tab << is_json("categories", __frontmatter_type) << __f.__assigner << " " << encloseQuote_arr(__frontmatter.categories, __frontmatter.categories_length) << std::endl;
	if (__frontmatter.tags_length > 0)
		__output_file << __f.__tab << is_json("tags", __frontmatter_type) << __f.__assigner << " " << encloseQuote_arr(__frontmatter.tags, __frontmatter.tags_length) << std::endl;

	__output_file << __f.__close_divider << std::endl;

	std::cout << "\n\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}

int post_parse(std::string __file_path) {

}

int post_extract(std::string __file_path, std::string __part = "frontmatter") {
	frontmatter _fm = extract_frontmatter(__file_path);

	std::cout << _fm.author << std::endl;

	return 0;
}
