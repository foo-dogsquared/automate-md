#include <regex>
#include <iostream>
#include <fstream>

#include "../util/util.hpp"

namespace file_io {
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
		std::regex __frontmatter_tags("^\\s*(?:---|\\+\\+\\+|\\{|\\})\\s*$");
		if (std::regex_match(__line, __frontmatter_tags))
			return true;
		else
			return false;
	}

	bool is_valid_file(std::string __file_path) {
		std::regex _file_ext_md(".+\\.(md|markdown|mdown|mkdn|mkd|html|htm)$");

		if (std::regex_match(__file_path, _file_ext_md))
			return true;
		else
			return false;
	}

	std::string string_format(std::string __fm_type, std::string __str, std::string __type = "value") {
		if (__type == "key") {
			if (__fm_type == "JSON" || __fm_type == "json")
				return util::enclose_str(__str);
		}
		else if (__type == "value") {
			if (util::str_is_array(__str) || __fm_type == "YAML" || __fm_type == "yaml")
				return __str;
			else
				return util::enclose_str(__str);
		}

		return __str;
	}
	
    /**
     * Returns a string of the file's extension
     *
     * @param file_path - path of file to be read
     * 
     **/
    std::string extract_file_extension(std::string __file_path) {
        std::vector<std::string> _words = util::split(__file_path, "\\.");
        std::string _file_ext = _words[_words.size() - 1];

        if (_file_ext.empty())
            throw "Cannot find file extension";
        
        return _file_ext;
    }
}

