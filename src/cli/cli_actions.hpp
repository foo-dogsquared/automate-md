#include <fstream>
#include <iostream>
#include <string>

#include "../file_io/file_io.hpp"
#include "../util/util.hpp"
#include "cli_help.hpp"

// optional action specifiers (command-specific)
#define FM_TYPE "%fm_type"
#define FORCE_PROMPT "%force"

// for create()
#define OUTPUT_PATH "%output_path"

// for update()
#define DELETE_KEYS "%delete_keys"
#define UPDATE_DATE "%update_date"

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

			if (_key == FM_TYPE && !util::is_not_valid_fm_format(_value)) {
				__file.type = _value;
				_trav++;
				continue;
			}
			else if (_key == OUTPUT_PATH) {
				_output_path = _value;
				_trav++;
				continue;
			}
			else if (_key.front() == '%') {
				std::cout << _key + " is not an optional command parameter." << std::endl;
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
		__file.type = "YAML";
	
	// default parameters for the path
	if (_output_path.empty())
		_output_path = "./";

	// prompting for layout when no given option
	if (__file.list.find("layout") == __file.list.end())
		__file.list.insert(std::make_pair("layout", util::prompt("What is the post layout in the frontmatter?")));

	// prompting for author when no given option
	if (__file.list.find("author") == __file.list.end())
		__file.list.insert(std::make_pair("author", util::prompt("Who is the author in the post?") ) );

	std::string full_iso_date_string = util::get_current_formatted_date_string(publish_date);
	__file.list.at("date") = full_iso_date_string;

	std::string iso_date_string = util::get_current_formatted_date_string(publish_date, "%F");
	_output_path = util::check_dir_path(_output_path);
	// Filling up the frontmatter with the necessary data
	
	__file.categories_length = util::prompt_int("How many categories for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("categories", util::prompt_arr("Categories", __file.categories_length) ));

	__file.list.insert(std::make_pair("date", full_iso_date_string));

	__file.tags_length = util::prompt_int("How many tags for this post?", 1, MAX_ARR_LENGTH);
	__file.list.insert(std::make_pair("tags", util::prompt_arr("Tags", __file.tags_length)));

	__file.list.insert(std::make_pair("title", __title));
	
    std::string __file_name = _output_path + iso_date_string + "-" + util::slugize_str(__title) + ".md";

	int _exit_code = file_io::post_fm_write(__file_name, __file, __file.type);
	if (_exit_code == 0)
		std::cout << "\n" + __file_name + " successfully created." << std::endl;
	exit(_exit_code);
}

void update(std::string __file_path, std::map<std::string, std::string> __options) {
	if (__options.empty())
		exit_error_code(20, "Command \"update\" needs at least one optional parameter.");

	if (__options.find(FORCE_PROMPT) == __options.end() || __options.find(FORCE_PROMPT)->second != "true")
		util::confirm_prompt();
	else
		__options.erase(FORCE_PROMPT);
	
	frontmatter _fm = file_io::extract_frontmatter(__file_path);
	std::string _content = file_io::extract_content(__file_path);

	for (std::map<std::string, std::string>::iterator _trav = __options.begin(); _trav != __options.end(); _trav++) {
		std::string _key = _trav->first, _value = _trav->second;
		// since optional command specifiers are also in there, we have to search for it
		if (_key == DELETE_KEYS) {
			std::vector<std::string> _delete_list = util::arr_extract(_value);
			std::cout << std::endl;

			for (int index = 0; index < _delete_list.size(); index++) {
				if (_fm.list.find(_delete_list[index]) == _fm.list.end())
					std::cout << "Cannot detect key \"" + _delete_list[index] + "\" in the frontmatter." << std::endl;
				else
					_fm.list.erase(_delete_list[index]);
			}
			std::cout << std::endl;
			continue;
		}
		else if (_key == UPDATE_DATE) {
			if (util::has_non_digits(_value))
				std::cout << "%update_date optional command parameter has a non-digit character" << std::endl;
			
			if (_fm.list.find("date") == _fm.list.end())
				_fm.list.insert(std::make_pair("date", util::get_current_formatted_date_string(stoi(_value)) ));
			else
				_fm.list["date"] = util::get_current_formatted_date_string(stoi(_value));

			continue;
		}
		else if (_key == FM_TYPE) {
			_fm.type = _value;
			continue;
		}
		else if (_key.front() == '%') {
			std::cout << _key + " is not an optional command parameter." << std::endl;
			continue;
		}

		// either adding or replacing values that are already in the _fm struct
		if (_fm.list.find(_key) == _fm.list.end()) {
			_fm.list.insert(std::make_pair(_key, _value));
		}
		else if (_value != _fm.list.find(_key)->second)
			_fm.list[_key] = _value;
	}

	int _exit_code = file_io::post_update(__file_path, _fm, _fm.type, _content);
	if (_exit_code == 0)
		std::cout << "\n" << __file_path << " was successfully updated.";
	exit(_exit_code);
}

void reset(std::string __file_path) {
	if (__file_path.empty())
		exit_error_code(30, "Command \"reset\" needs the file path.");

	util::confirm_prompt();

	frontmatter _fm = file_io::extract_frontmatter(__file_path);

	int _exit_code = file_io::post_fm_write(__file_path, _fm);
	std::cout << "File has been reset." << std::endl;
	exit(_exit_code);
}

void extract(std::string __file_path, std::map<std::string, std::string> __options) {
	std::string _output_path;
	std::string _part;
	int _exit_code = 0;

	if ((__options.find(MARKDOWN_PART) != __options.end()) && (__options.find(MARKDOWN_PART)->second == "frontmatter" || __options.find(MARKDOWN_PART)->second == "content"))
		_part = __options.find(MARKDOWN_PART)->second;
	else
		_part = "frontmatter";

	if (__options.find(OUTPUT_PATH) != __options.end())
		_output_path = __options.find(OUTPUT_PATH)->second;
	else
		_output_path = __file_path;

	if (_part == "frontmatter" || _part == "FRONTMATTER") {
		frontmatter _fm = file_io::extract_frontmatter(__file_path);
		_exit_code = file_io::post_fm_write(__file_path, _fm, _fm.type);
	} else if (_part == "content" || _part == "CONTENT") {
		std::string _content = file_io::extract_content(__file_path);
		if (_content.empty()) 
			exit_error_code(41, "Content from file is empty");
		_exit_code = file_io::post_content_write(__file_path, _content);
	}
	
	exit(_exit_code);
}
