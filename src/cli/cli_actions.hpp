#include <fstream>
#include <iostream>
#include <string>

#include "../functions/file_io.hpp"
#include "../functions/util.hpp"
#include "cli_help.hpp"

int create(std::string __title, std::string __publish_date = "0", std::string __output_path = "./", std::string __fm_type = "YAML") {
	frontmatter __file;

    if (__title.length() > MAX_TITLE_LENGTH)
        return return_error_code(2, "Title exceeds character limit of " + std::to_string(MAX_TITLE_LENGTH) +  " characters.");
	
	int publish_date;
	if (hasNondigits(__publish_date))
		return return_error_code(3, "@param \"publish_date\" contains invalid characters for conversion.");
	publish_date = stoi(__publish_date);
	std::string full_iso_date_string = getFormattedDateString(publish_date);
	std::string iso_date_string = getFormattedDateString(publish_date, "%F");

	std::string output_path;
	if (!_begin_isDir(__output_path))
		output_path = "./" + __output_path;
	else
		output_path = __output_path;

	if (!_end_isDir(__output_path))
		output_path += "/";

	// Filling up the frontmatter with the necessary data
	__file.layout = prompt("What is the post layout in the frontmatter?");
	__file.author = prompt("Who is the author of the post?");
	
	__file.categories_length = prompt_int("How many categories for this post?", 1, MAX_ARR_LENGTH);
	__file.categories = prompt_arr("Categories", __file.categories_length);

	__file.date = full_iso_date_string;

	__file.tags_length = prompt_int("How many tags for this post?", 1, MAX_ARR_LENGTH);
	__file.tags = prompt_arr("Tags", __file.tags_length);

	__file.title = __title;
	
    std::string __file_name = output_path + iso_date_string + "-" + slugize_str(__title) + ".md";

	return post_write(__file_name, __file, __fm_type);
}

// TODO: Complete the remaining functions
// TODO: Complete update()
int update(std::string __file_path, std::string __updated_title = nullptr, std::string __fm_type = nullptr) {
	if (__updated_title.empty() && __fm_type.empty())
		return return_error_code(4, "Command \"update\" needs at least one option parameter.");
	
	return post_parse(__file_path);
}

// TODO: Complete reset()
int reset(std::string __file_path) {
	if (__file_path.empty())
		return return_error_code(5, "Command \"reset\" needs the file path.");
}

// TODO: Complete extract()
int extract(std::string __file_path, std::string __part = "frontmatter") {
	if (__part.empty() || !(__part.compare("frontmatter") || __part.compare("FRONTMATTER")) || !(__part.compare("content") || __part.compare("CONTENT")))
		return return_error_code(6, "Command \"extract\" needs the file path.");

	if (__part.compare("frontmatter") || __part.compare("FRONTMATTER"))
		return post_extract(__file_path, __part);
	
	return 0;
}
