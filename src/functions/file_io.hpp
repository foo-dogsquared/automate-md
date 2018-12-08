#pragma once

#include "frontmatter.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>
#include <regex>

#define FILE_IO_ERROR_NUM 3

void open_file_i(std::ifstream &__input_file, std::string __input_path) {
	__input_file.open(__input_path);

	std::cout << "Opening file at " << __input_path << std::endl;
	if (!__input_file.is_open())
		exit_error_code(3, "Cannot open file at: " + __input_path);
}

void open_file_o(std::ofstream &__output_file, std::string __output_path) {
	__output_file.open(__output_path);

	std::cout << "Writing file at " << __output_path << std::endl;
	if (!__output_file.is_open())
		exit_error_code(3, "Cannot open file at: " + __output_path);
}

bool is_frontmatter_tag(std::string __line) {
	std::regex __frontmatter_tags("\\+\\+\\+|---|{|}\\s*");
	if (std::regex_match(__line, __frontmatter_tags))
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
	std::ifstream _input_file(__file_path, std::ios::in | std::ios::binary);

	if (_input_file.good())
		std::cout << "K" << std::endl;
	else
		std::cout << "Mbad" << std::endl;

	std::string _line;
	bool _is_opening_tag_parse = false;
	bool _is_closing_tag_parse = false;
	while (getline(_input_file, _line) && (!_is_closing_tag_parse || !_is_opening_tag_parse)) {
		if (is_frontmatter_tag(_line))
			std::cout << _line << std::endl;
	}
	

	return _output;
}

std::string extract_content(std::string __file_path) {
	std::string _output;
	std::ifstream _input_file;
	open_file_i(_input_file, __file_path);

	std::regex _whitespace("\\s+");
	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false, _content_start = false;
	for (std::string _line; std::getline(_input_file, _line);) {
		std::cout << is_frontmatter_tag(_line) << "---"  << std::endl;
		if (!_is_opening_tag_parse)
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

	open_file_o(__output_file, __file_path);

	// Writing the frontmatter in the file
	__output_file << __frontmatter.__open_divider << std::endl;
	std::map<std::string, std::string>::iterator _trav = __frontmatter.list.begin();

	while (_trav != __frontmatter.list.end()) {
		__output_file << __frontmatter.__tab << is_json(__frontmatter_type, encloseQuote(_trav->first), _trav->first) << __frontmatter.__space << __frontmatter.__assigner << " " << _trav->second << is_json(__frontmatter_type, ",", "") << "\n";
		_trav++;
	}

	__output_file << __frontmatter.__close_divider << std::endl;

	std::cout << "\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}

int post_write_text(std::string __output_path, std::string __content) {
	if (__content.empty()) 
		exit_error_code(41, "Content from file is empty");
	
	if (!is_markdown(__output_path))
		__output_path += ".md";
	
	std::ofstream _output;
	open_file_o(_output, __output_path);

	_output << __content;
	std::cout << "\n" << __output_path << " was successfully created.";

	return 0;
}

int post_parse(std::string __file_path) {
	return 0;
}

int post_extract(std::string __file_path, std::string __output_path, std::string __part = "frontmatter") {
	std::cout << "Extracting " << __part << " from " << __file_path << std::endl;
	if (__part == "frontmatter" || __part == "FRONTMATTER") {
		frontmatter _fm = extract_frontmatter(__file_path);
		return post_write(__output_path, _fm, _fm.type);
	} else if (__part == "content" || __part == "CONTENT") {
		std::string _content = extract_content(__file_path);
		return post_write_text(__output_path, _content);
	}
}
