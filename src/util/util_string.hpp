#include <iostream>
#include <string>
#include <regex>
#include <vector>

#define MAX_DATE_STRING 64

std::string enclose_str(std::string __word, std::string __start = "\"", std::string __end = "\"") {
	return __start + __word + __end;
}

std::string remove_quote(std::string __word, std::string __start = "\"", std::string __end = "\"") {
	std::string _output;
	_output.assign(__word);

	if (__word.substr(0, __start.length()) == __start && __word.substr(__word.length() - __end.length(), __end.length()) == __end) {
		_output.erase(0, __start.length());
		_output.erase(__word.length() - __end.length());
	}

	return _output;
}

std::string trim_both(std::string __str, std::string __start = "\"", std::string __end = "\"") {
	std::string _output = __str;
	while (_output.substr(0, __start.length()) == __start && _output.substr(_output.length() - __end.length(), __end.length()) == __end) {
		_output.erase(0, __start.length());
		_output.erase(_output.length() - __end.length(), __end.length());
	}

	return _output;
}

std::string trim_right(std::string __str, std::string __keychars = " \r\n\t") {
	return __str.erase(__str.find_last_not_of(__keychars) + 1);
}

/** Returns a string that returns a formatted date string based on current time
*
* @param __num - the numbers of days relative to current day
* @param __format - a string that denotes the format with the specifiers; refer to link for the specifiers
*
* LINK: https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
**/
std::string get_current_formatted_date_string(int __num = 0, const char *__format = "%F %T %z") {
	time_t _now = time(0);
	char iso_string[MAX_DATE_STRING];

	tm *_local_time = localtime(&_now);

	_local_time->tm_mday += __num;

	mktime(_local_time);

	strftime(iso_string, sizeof(iso_string), __format, _local_time);

	return iso_string;
}

/** Returns a vector of strings that has been delimited by programmer-specified characters, 
* similar to JavaScript's split (https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/split)
*
* @param __str - the string to be split
* @param __delimiters - a string that contains a regex string; refer to link for the regex syntax 
*
* LINK: http://www.cplusplus.com/reference/regex/ECMAScript/
**/
std::vector<std::string> split(std::string __str, std::string __delimiters) {
	const std::regex __invalid_chars(__delimiters);
	const std::vector<std::string> _arr{ 
		std::sregex_token_iterator(__str.begin(), __str.end(), __invalid_chars, -1), 
		std::sregex_token_iterator() 
	};
	return  _arr;
}

/** Returns a vector of strings that has been extract from a JSON array which means 
 * it has to be delimited by a comma; 
 * returns a vector with one element if the string does not start with the opening square bracket ('[')
 * or does not end with the closing square bracket (']') 
*
* @param __arr_str - the string to be split
*
**/
std::vector<std::string> arr_extract(std::string __arr_str) {

	std::vector<std::string> _arr;

	if (__arr_str.front() != '[' || __arr_str.back() != ']') {
		_arr.push_back(__arr_str);
		return _arr;
	}

	std::regex _vector_elem("\"?\\w+\"?");
	
	for (std::sregex_iterator _match = std::sregex_iterator(__arr_str.begin(), __arr_str.end(), _vector_elem); _match != std::sregex_iterator(); ++_match) {
		std::smatch _word = *_match;
		if (_word.empty())
			continue;

		_arr.push_back(remove_quote(_word.str())); 
	}
	
	return _arr;
}

std::string slugize_str(std::string __str) {
	std::string _slug;
	std::vector<std::string> _words = split(__str, "[^A-Za-z0-9]");

	if (_words.empty())
		return __str;
	
	for (int _word_index = 0; (unsigned int) _word_index < _words.size(); _word_index++) {
		for (int _char_index = 0; _words[_word_index][_char_index]; _char_index++)
			_words[_word_index][_char_index] = tolower(_words[_word_index][_char_index]);

		if (_words[_word_index].empty())
			continue;
		else if ((_words.at(_word_index) == _words.front() && _words.size() == 1) || _words.at(_word_index) == _words.back())
			_slug += _words[_word_index];
		else if (_words.at(_word_index) == _words.front())
			_slug += _words[_word_index] + "-";
		else
			_slug += _words[_word_index] + "-";
	}

	// in case the last caught member is a non-alphanumeric character
	if (_slug.back() == '-')
		_slug.erase(_slug.size() - 1);

	return _slug;
}
