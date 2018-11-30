#pragma once

#include "frontmatter.hpp"
#include "frontmatter_type.hpp"
#include "util.hpp"

#include <fstream>
#include <iostream>

int post_write(std::string __file_path, frontmatter __frontmatter, std::string __frontmatter_type = "YAML") {
	std::ofstream __output_file;

	 frontmatter_type __f = init(__frontmatter_type);
	
	__output_file.open(__file_path);

	if (!(__output_file.is_open()))
		return return_error_code(3, "Can't open file at \"" + __file_path + "\".");

	// Writing the frontmatter in the file
	__output_file << __f.__open_divider << std::endl;
	__output_file << __f.__tab << isJSON("layout", __frontmatter_type) << __f.__assigner << " " << isJSON(__frontmatter.layout, __frontmatter_type) << std::endl;
	__output_file << __f.__tab << isJSON("title", __frontmatter_type) << __f.__assigner << " " << encloseQuote(__frontmatter.title) << std::endl;
	__output_file << __f.__tab << isJSON("date", __frontmatter_type) << __f.__assigner << " " << isJSON(__frontmatter.date, __frontmatter_type) << std::endl;
	__output_file << __f.__tab << isJSON("author", __frontmatter_type) << __f.__assigner << " " << isJSON(__frontmatter.author, __frontmatter_type) << std::endl;

	if (__frontmatter.categories_length > 0)
		__output_file << __f.__tab << isJSON("categories", __frontmatter_type) << __f.__assigner << " " << encloseQuote_arr(__frontmatter.categories, __frontmatter.categories_length) << std::endl;
	if (__frontmatter.tags_length > 0)
		__output_file << __f.__tab << isJSON("tags", __frontmatter_type) << __f.__assigner << " " << encloseQuote_arr(__frontmatter.tags, __frontmatter.tags_length) << std::endl;

	__output_file << __f.__close_divider << std::endl;

	std::cout << "\n\n" + __file_path + " was successfully created." << std::endl;

	__output_file.close();
	return 0;
}
