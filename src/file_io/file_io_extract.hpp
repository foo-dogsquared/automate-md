#include <iostream>
#include <regex>
#include <fstream>

#include "../frontmatter/frontmatter.hpp"
#include "file_io_util.hpp"

namespace file_io {
    /**
     * Returns a frontmatter struct (hopefully filled with the values) 
     * by reading the file
     * 
     * @param file_path - path of file to be read
     *  
     **/
    frontmatter extract_frontmatter(std::string __file_path) {
        frontmatter _output;
        std::ifstream _input_file(__file_path);
        std::cout << "Extracting frontmatter from: " << __file_path << std::endl;
        if (!_input_file.is_open())
            exit_error_code(3, "Cannot open file at: " + __file_path);		

        std::string _line;
        bool _is_opening_tag_parse = false;
        bool _is_closing_tag_parse = false;
        std::regex _key_values_regex;
        std::smatch _matches;
        std::string _key, _value;
        while (std::getline(_input_file, _line) && (!_is_closing_tag_parse || !_is_opening_tag_parse)) {
            // first line is most likely be the frontmatter opening tag
            if (is_frontmatter_tag(_line) && !_is_opening_tag_parse) {
                _is_opening_tag_parse = true;
                _output.type = detect_type(_line);
                init_fm_format_data(_output);
                _key_values_regex = "^\\s*\"?([A-Za-z0-9!@#$%^&*()_+-]+)\"?\\s*" + _output.__assigner + "\\s*(.+)\\s*,?\\s*";
            }

            else if (_is_opening_tag_parse && !_is_closing_tag_parse && std::regex_match(_line, _matches, _key_values_regex)) {
                _key = _matches[1].str();
                _value = util::trim_both(util::trim_right(util::trim_right(_matches[2].str()), ","));
                _output.list.insert(std::make_pair(_key, _value ) );
            }

            else if (is_frontmatter_tag(_line) && _is_opening_tag_parse && !_is_closing_tag_parse) {
                _is_closing_tag_parse = true;
                _input_file.close();
                break;
            }

            else {
                continue;
            }
        }
        
        _input_file.close();
        return _output;
    }

    /**
     * Returns a string by reading the file and skipping the frontmatter
     * until it gets to the first non-whitespace character
     *
     * @param file_path - path of file to be read
     * 
     **/
    std::string extract_content(std::string __file_path) {
        std::string _output;
        std::ifstream _input_file(__file_path);
        std::cout << "Extracting content from: " << __file_path << std::endl;
        if (!_input_file.is_open())
            exit_error_code(3, "Cannot open file at: " + __file_path);		

        std::regex _whitespace("\\s+");
        bool _is_opening_tag_parse = false, _is_closing_tag_parse = false, _content_start = false;
        for (std::string _line; std::getline(_input_file, _line);) {
            if (is_frontmatter_tag(_line) && !_is_opening_tag_parse)
                _is_opening_tag_parse = true;
            else if (is_frontmatter_tag(_line) && _is_opening_tag_parse && !_is_closing_tag_parse)
                _is_closing_tag_parse = true;
            else if ((_is_opening_tag_parse && !_is_closing_tag_parse) || ((regex_match(_line, _whitespace) || _line.empty()) && !_content_start))
                continue;
            else {
                _output += _line + "\n";
                _content_start = true;
            }
        }

        _input_file.close();
        return _output;
    }
}
