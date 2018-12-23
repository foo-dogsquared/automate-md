#pragma once

#include "file_io_extract.hpp"

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

namespace file_io {
	/** It will write a markdown file with the frontmatter and returns an integer for the exit code
	*
	* @param __file_path
	* @param __frontmatter - the instance of the frontmatter struct
	* @param __frontmatter_type - the format of the frontmatter to be written in the file
	* @param __operation - the protocol to be followed when writing the file; possible values are "write", "append", and "replace"
	*
	**/
	int post_fm_write(std::string __file_path, frontmatter __frontmatter, std::string __frontmatter_type = "YAML", std::string __operation = "write") {
		std::ofstream __output_file;
		
		init_fm_format_data(__frontmatter);  // defensive mechanism in case the struct frontmatter has no initialized data to get

		if (!is_valid_file(__file_path))
			__file_path += ".md";

		if (__operation == "write")
			__output_file.open(__file_path, std::ios::out);
		else if (__operation == "append") 
			__output_file.open(__file_path, std::ios::out | std::ios::app);
		else if (__operation == "replace")
			__output_file.open(__file_path, std::ios::out | std::ios::trunc);

		// Writing the frontmatter in the file
		__output_file << __frontmatter.__open_divider << std::endl;

		std::string _comma = ",";
		for (std::map<std::string, std::string>::iterator _trav = __frontmatter.list.begin(); _trav != __frontmatter.list.end(); _trav++) {
			__output_file << __frontmatter.__tab << string_format(__frontmatter.type, _trav->first, "key") << __frontmatter.__space << __frontmatter.__assigner << " " << string_format(__frontmatter.type, _trav->second, "value");

			if ((__frontmatter_type == "JSON" || __frontmatter_type == "json") && std::next(_trav) != __frontmatter.list.end())
				__output_file << ", " << NEWLINE;
			else
				__output_file << NEWLINE;
		}

		__output_file << __frontmatter.__close_divider << std::endl;

		__output_file.flush();
		__output_file.close();
		return 0;
	}

	/** It will write a markdown file with the content and returns an integer for the exit code
	*
	* @param __output_path - path of file to be written (but not overwritten)
	* @param __content - the string to be written on the file
	* @param __operation - the type of output file stream operation for the file; possible values are "write", "append", and "replace"
	*
	**/
	int post_content_write(std::string __output_path, std::string __content, std::string __operation = "write") {
		if (!is_valid_file(__output_path))
			__output_path += ".md";
		
		std::ofstream _output;
		if (__operation == "write")
			_output.open(__output_path, std::ios::out);
		else if (__operation == "append") {
			_output.open(__output_path, std::ios::out | std::ios::app);
			_output << "\n";
		}
		else if (__operation == "replace")
			_output.open(__output_path, std::ios::out | std::ios::trunc);

		_output << __content;
		_output.close();
		return 0;
	}

	/** It will update the specified markdown file with the new data
	*
	* @param __file_path - path of file to be updated
	* @param __fm - a frontmatter struct that contains the data 
	* @param __fm_type - the frontmatter format to be written down onto the markdown file
	* @param __content - the content of the input file
	*
	**/
	int post_update(std::string __file_path, frontmatter __fm, std::string __fm__type = "YAML", std::string __content = "") {
		std::fstream __file(__file_path);
		if (!__file.is_open())
			exit_error_code(3, "Cannot open file at " + __file_path);

		int _exit_code = 0;
		
		_exit_code = post_fm_write(__file_path, __fm, __fm.type);
		std::cout.flush();
		std::cout << "Frontmatter has been written in the file..." << std::endl;
		
		_exit_code += post_content_write(__file_path, __content, "append");
		std::cout << "Content has been copied on the file..." << std::endl;

		return _exit_code;
	}

}
