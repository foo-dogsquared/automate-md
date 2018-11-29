#pragma once

#include "frontmatter.h"
#include "frontmatter_type.h"
#include "util.h"

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
	__output_file << __f.__close_divider << std::endl;

	__output_file.close();
	return 0;
}
