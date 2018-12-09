#include <fstream>
#include <iostream>
#include <string>

#include "../file_io/file_io.hpp"
#include "../util/util.hpp"
#include "cli_help.hpp"

void create(std::string __title, std::map<std::string, std::string> __optional_params) {
	frontmatter __file;
	std::string _output_path;

	if (!__optional_params.empty()) {
		std::map<std::string, std::string>::iterator _trav = __optional_params.begin();

		std::string _key, _value;
		while (_trav != __optional_params.end()) {
			_key = _trav->first;
			_value = _trav->second;

			if (_key == "fm_type") {
				__file.type = _value;
				continue;
			}
			else if (_key == "output_path") {
				_output_path = _value;
				continue;
			}

			__file.list.insert(std::make_pair(_key, _value));
			_trav++;
		}
	}

    if (__title.length() > MAX_TITLE_LENGTH) {
        exit_error_code(10, "Title exceeds character limit of " + std::to_string(MAX_TITLE_LENGTH) +  " characters.");
	}
	
	// default parameters for the publish date
	int publish_date;
	if (__file.list.at("date").empty() || hasNondigits(__file.list.at("date")))
		publish_date = 0;
	else
		publish_date = stoi(__file.list["date"]);
	
	// default parameters for the frontmatter format
	if (__file.type.empty())
		__file.type = "YAML";
	
	// default parameters for the path
	if (_output_path.empty())
		_output_path = "./";

	if (__file.list.find("layout") == __file.list.end())
		__file.list.insert(std::make_pair("layout", prompt("What is the post layout in the frontmatter?")));

	if (__file.list.find("author") == __file.list.end())
		__file.list.insert(std::make_pair("author", prompt("Who is the author in the post?") ) );

	std::string full_iso_date_string = getFormattedDateString(publish_date);
	__file.list.at("date") = full_iso_date_string;

	std::string iso_date_string = getFormattedDateString(publish_date, "%F");
	_output_path = check_dir_path(_output_path);
	// Filling up the frontmatter with the necessary data
	
	__file.categories_length = prompt_int("How many categories for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("categories", prompt_arr("Categories", __file.categories_length) ));

	__file.list.insert(std::make_pair("date", full_iso_date_string));

	__file.tags_length = prompt_int("How many tags for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("tags", prompt_arr("Tags", __file.tags_length)));

	__file.list.insert(std::make_pair("title", encloseQuote(__title)));
	
    std::string __file_name = _output_path + iso_date_string + "-" + slugize_str(__title) + ".md";

	post_write(__file_name, __file, __file.type);
	exit(0);
}

// TODO: Complete the remaining functions
// TODO: Complete update()
void update(std::string __file_path, std::string __options...) {
	if (__options.empty())
		exit_error_code(20, "Command \"update\" needs at least one option parameter.");
	
	exit(post_update(__file_path, __options));
}

void reset(std::string __file_path) {
	if (__file_path.empty())
		exit_error_code(30, "Command \"reset\" needs the file path.");

	frontmatter _fm = extract_frontmatter(__file_path);

	exit(post_write(__file_path, _fm));
}

void extract(std::string __file_path, std::string __output_path, std::string __part = "frontmatter") {
	if (__output_path.empty())
		exit_error_code(40, "Command \"extract\" needs an output path");
	
	exit(post_extract(__file_path, __output_path, __part));
}
