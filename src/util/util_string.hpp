#include <iostream>
#include <string>
#include <regex>
#include <vector>

#define MAX_DATE_STRING 64

std::string enclose_str(std::string __word, std::string __start = "\"", std::string __end = "\"") {
	return __start + __word + __end;
}

std::string remove_quote(std::string __word) {
	if (__word.front() == '\"' && __word.back() == '\"') {
		__word.erase(0);
		__word.erase(__word.size() - 1);
	}

	return __word;
}

std::string getFormattedDateString(int __num = 0, const char *__format = "%F %T %z") {
	time_t _now = time(0);
	char iso_string[MAX_DATE_STRING];

	tm *_local_time = localtime(&_now);

	_local_time->tm_mday += __num;

	mktime(_local_time);

	strftime(iso_string, sizeof(iso_string), __format, _local_time);

	return iso_string;
}

std::vector<std::string> split(std::string __str, const std::regex __delimiters) {
	const std::vector<std::string> _arr{ 
		std::sregex_token_iterator(__str.begin(), __str.end(), __delimiters, -1), 
		std::sregex_token_iterator() 
	};
	return  _arr;
}

std::vector<std::string> arr_extract(std::string __arr_str) {

	std::vector<std::string> _arr;

	if (__arr_str.front() != '[' && __arr_str.back() != ']') {
		_arr.push_back(__arr_str);
		return _arr;
	}

	std::regex _vector_elem("\"\\w*\"");
	
	for (std::sregex_iterator _match = std::sregex_iterator(__arr_str.begin(), __arr_str.end(), _vector_elem); _match != std::sregex_iterator(); ++_match) {
		std::smatch _word = *_match;
		if (_word.empty())
			continue;

		_arr.push_back(remove_quote(_word.str())); 
	}
	
	return _arr;
}

std::string slugize_str(std::string __str) {
	const std::regex __invalid_chars("[^A-Za-z0-9]");
	std::string _slug;
	std::vector<std::string> _words = split(__str, __invalid_chars);

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
