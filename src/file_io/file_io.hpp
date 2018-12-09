#pragma once

#include "../frontmatter/frontmatter.hpp"
#include "file_io_util.hpp"

#include <fstream>
#include <iostream>
#include <regex>

#define FILE_IO_ERROR_NUM 3

// OS-dependent newlines
#ifdef _WIN32
#define NEWLINE "\r\n" // Windows-styled newline
#else
#define NEWLINE "\n" // Unix-styled newline
#endif

/**
 * Returns a frontmatter struct (hopefully filled with the values) 
 * by reading the file
 * 
 * @param file_path - self-explanatory
 **/
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
	std::regex _key_values_regex;
	std::smatch _matches;
	std::ssub_match _key, _value;
	while (std::getline(_input_file, _line) && (!_is_closing_tag_parse || !_is_opening_tag_parse)) {
		// first line is most likely be the frontmatter opening tag
		if (is_frontmatter_tag(_line) && !_is_opening_tag_parse) {
			_is_opening_tag_parse = true;
			_output.type = detect_type(_line);
			init_fm_format_data(_output);
			_key_values_regex = "^\\s*\"?([A-Za-z0-9!@#$%^&*()_+-]+)\"?\\s*" + _output.__assigner + "\\s*(.+)\\s*";
		}

		else if (_is_opening_tag_parse && !_is_closing_tag_parse && std::regex_match(_line, _matches, _key_values_regex)) {
			_key = _matches[1];
			_value = _matches[2];
			_output.list.insert(std::make_pair(_key.str(), _value.str()));
		}

		else if (is_frontmatter_tag(_line) && _is_opening_tag_parse && !_is_closing_tag_parse) {
			_is_closing_tag_parse = true;
			_input_file.close();
			break;
		}

		else {
			continue;
		}
	}
	
	return _output;
}

/**
 * Returns a string by reading the file and skipping the frontmatter 
 * until it gets to the first non-whitespace character
 * 
 * @param file_path
 **/
std::string extract_content(std::string __file_path) {
	std::string _output;
	std::ifstream _input_file;
	open_file_i(_input_file, __file_path);

	std::regex _whitespace("\\s+");
	bool _is_opening_tag_parse = false, _is_closing_tag_parse = false, _content_start = false;
	for (std::string _line; std::getline(_input_file, _line);) {
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

/** It will write a markdown file with the frontmatter and returns an integer for the exit code
*
* @param file_path
* @param frontmatter - the instance of the frontmatter struct
* @param frontmatter_type - the format of the frontmatter to be written in the file
*
**/
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
		__output_file << __frontmatter.__tab << is_json(__frontmatter_type, encloseQuote(_trav->first), _trav->first) << __frontmatter.__space << __frontmatter.__assigner << " " << _trav->second << is_json(__frontmatter_type, ",", "") << NEWLINE;
		_trav++;
	}

	__output_file << __frontmatter.__close_divider << std::endl;

	std::cout << "\n" + __file_path + " was successfully created." << std::endl;

	__output_file.flush();
	__output_file.close();
	return 0;
}

/** It will write a markdown file with the content and returns an integer for the exit code
*
* @param output_path
* @param content - the string to be written on the file
*
**/
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

int post_update(std::string __file_path, std::string __options) {


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
