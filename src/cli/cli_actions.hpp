#include <fstream>
#include <iostream>
#include <string>

#include "../functions/file_io.hpp"
#include "../functions/util.hpp"
#include "cli_help.hpp"

int create(std::string __title, std::string __publish_date = "0", std::string __output_path = "./", std::string __fm_type = "YAML") {
	frontmatter __file;

    if (__title.length() > MAX_TITLE_LENGTH) {
        return return_error_code(10, "Title exceeds character limit of " + std::to_string(MAX_TITLE_LENGTH) +  " characters.");
	}
	
	int publish_date;

	if (hasNondigits(__publish_date))
		return return_error_code(11, "@param \"publish_date\" contains invalid characters for conversion.");
	
	publish_date = stoi(__publish_date);
	std::string full_iso_date_string = getFormattedDateString(publish_date);
	std::string iso_date_string = getFormattedDateString(publish_date, "%F");

	std::string output_path = check_dir_path(__output_path);

	// Filling up the frontmatter with the necessary data
	__file.type = __fm_type;

	__file.list.insert(std::make_pair("layout", prompt("What is the post layout in the frontmatter?")));
	__file.list.insert(std::make_pair("author", prompt("Who is the author in the post?") ) );
	
	__file.categories_length = prompt_int("How many categories for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("categories", prompt_arr("Categories", __file.categories_length) ));

	__file.list.insert(std::make_pair("date", full_iso_date_string));

	__file.tags_length = prompt_int("How many tags for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("tags", prompt_arr("Tags", __file.tags_length)));

	__file.list.insert(std::make_pair("title", encloseQuote(__title)));
	
    std::string __file_name = output_path + iso_date_string + "-" + slugize_str(__title) + ".md";

	return post_write(__file_name, __file, __fm_type);
}

// TODO: Complete the remaining functions
// TODO: Complete update()
int update(std::string __file_path, std::string __updated_title = nullptr, std::string __fm_type = nullptr) {
	if (__updated_title.empty() && __fm_type.empty())
		return return_error_code(20, "Command \"update\" needs at least one option parameter.");
	
	return post_parse(__file_path);
}

// TODO: Complete reset()
int reset(std::string __file_path) {
	if (__file_path.empty())
		return return_error_code(30, "Command \"reset\" needs the file path.");

	frontmatter _fm = extract_frontmatter(__file_path);

	return post_write(__file_path, _fm);
}

// TODO: Complete extract()
int extract(std::string __file_path, std::string __output_path, std::string __part = "frontmatter") {
	if (__output_path.empty())
		return return_error_code(40, "Command \"extract\" needs an output path");

	if (__part.compare("frontmatter") || __part.compare("FRONTMATTER"))
		return post_extract(__file_path, __output_path, __part);
	
	return 0;
}
