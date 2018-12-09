#include <fstream>
#include <iostream>
#include <string>

#include "../file_io/file_io.hpp"
#include "../util/util.hpp"
#include "cli_help.hpp"

// optional action specifiers (command-specific)
#define FM_TYPE "%fm_type"

// for create()
#define OUTPUT_PATH "%output_path"

// for update()
#define DELETE_KEYS "%delete_key"

// for extract()
#define MARKDOWN_PART "%part"

void create(std::string __title, std::map<std::string, std::string> __optional_params) {
	frontmatter __file;
	std::string _output_path;

	// parsing through the options (--OPTION=VALUE)
	if (!__optional_params.empty()) {
		std::map<std::string, std::string>::iterator _trav = __optional_params.begin();

		std::string _key, _value;
		while (_trav != __optional_params.end()) {
			_key = _trav->first;
			_value = _trav->second;

			if (_key == FM_TYPE && !is_not_valid_fm_format(_value)) {
				__file.type = _value;
				_trav++;
				continue;
			}
			else if (_key == OUTPUT_PATH) {
				_output_path = _value;
				_trav++;
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
	if (__file.list["date"].empty())
		publish_date = 0;
	else
		publish_date = stoi(__file.list["date"]);
	
	// default parameters for the frontmatter format
	if (__file.type.empty())
		__file.type = "JSON";
	
	// default parameters for the path
	if (_output_path.empty())
		_output_path = "./";

	// prompting for layout when no given option
	if (__file.list.find("layout") == __file.list.end())
		__file.list.insert(std::make_pair("layout", prompt("What is the post layout in the frontmatter?")));

	// prompting for author when no given option
	if (__file.list.find("author") == __file.list.end())
		__file.list.insert(std::make_pair("author", prompt("Who is the author in the post?") ) );

	std::string full_iso_date_string = get_current_formatted_date_string(publish_date);
	__file.list.at("date") = full_iso_date_string;

	std::string iso_date_string = get_current_formatted_date_string(publish_date, "%F");
	_output_path = check_dir_path(_output_path);
	// Filling up the frontmatter with the necessary data
	
	__file.categories_length = prompt_int("How many categories for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("categories", prompt_arr("Categories", __file.categories_length) ));

	__file.list.insert(std::make_pair("date", full_iso_date_string));

	__file.tags_length = prompt_int("How many tags for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("tags", prompt_arr("Tags", __file.tags_length)));

	__file.list.insert(std::make_pair("title", __title));
	
    std::string __file_name = _output_path + iso_date_string + "-" + slugize_str(__title) + ".md";

	int _exit_code = post_write(__file_name, __file, __file.type);
	if (_exit_code == 0)
		std::cout << "\n" + __file_name + " successfully created." << std::endl;
	exit(_exit_code);
}

void update(std::string __file_path, std::map<std::string, std::string> __options) {
	if (__options.empty())
		exit_error_code(20, "Command \"update\" needs at least one optional parameter.");
	
	frontmatter _fm = extract_frontmatter(__file_path);
	std::string _content = extract_content(__file_path);

	for (std::map<std::string, std::string>::iterator _trav = __options.begin(); _trav != __options.end(); _trav++) {
		std::string _key = _trav->first, _value = _trav->second;
		// since optional command specifiers are also in there, we have to search for it
		if (_key == DELETE_KEYS) {
			std::vector<std::string> _delete_list = arr_extract(_value);
			
			for (int index = 0; index < _delete_list.size(); index++) {
				_fm.list.erase(_delete_list[index]);
			}
			continue;
		}
		else if (_key == FM_TYPE) {
			_fm.type = _value;
			continue;
		}

		// either adding or replacing values that are already in the _fm struct
		if (_fm.list.find(_key) == _fm.list.end()) {
			_fm.list.insert(std::make_pair(_key, _value));
		}
		else if (_value != _fm.list.find(_key)->second)
			_fm.list[_key] = _value;
	}

	int _exit_code = post_update(__file_path, _fm, _fm.type, _content);
	if (_exit_code == 0)
		std::cout << "\n" << __file_path << " was successfully created.";
	exit(_exit_code);
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
