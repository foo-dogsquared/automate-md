#include <regex>
#include <iostream>
#include <fstream>

#include "../util/util.hpp"

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
	std::regex __frontmatter_tags("^\\+\\+\\+\\s*$|^---\\s*$|^\\{\\s*$|^\\}\\s*$");
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
