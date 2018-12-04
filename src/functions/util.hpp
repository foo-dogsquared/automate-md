#pragma once

#include <ctime>
#include <iostream>
#include <regex>
#include <string>

#define MAX_DATE_STRING 64
#define MAX_STRING_LENGTH 65535
#define INVALID_CHARS " !@#$%^&*()_+={}[]:;\"'<,>.?/|\\~`"

bool _begin_isDir(std::string __path)
{
	std::regex _begin__dir_regex("^\\.\\.?/.*");

	if (regex_match(__path, _begin__dir_regex))
		return true;
	else
		return false;
}

bool _end_isDir(std::string __path) {
	std::regex _end__dir_regex(".*/$");

	if (std::regex_match(__path, _end__dir_regex))
		return true;
	else
		return false;
}

bool hasNondigits(std::string __str) {
	std::regex __digit_regex("\\d+");

	if (!std::regex_match(__str, __digit_regex))
		return true;
	else
		return false;
}

int return_error_code(int error_num, std::string description) {
    std::cerr << "Error " << error_num << ": " << description << std::endl;
    return error_num;
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

std::string prompt(std::string __question, int __max_size = MAX_STRING_LENGTH)
{
	if (__max_size <= 0)
		return "";

	std::string _out;
	int _out_length;
	do {
		std::cout.flush();
		std::cout << __question << "\n>>> ";
		std::getline(std::cin, _out);
		_out_length = _out.length();
	} while (_out_length <= 0 || _out_length > __max_size);

	return _out;
}

int prompt_int(std::string __question, int __minimum = 0, int __maximum = INT8_MAX)
{
	std::string _out;
	int _num;
	do {
		_out = prompt(__question);

		if (hasNondigits(_out))
			continue;

		_num = stoi(_out);

		if (_num < __minimum || _num > __maximum)
			std::cout << "Value can only range from " << std::to_string(__minimum) << " to " << std::to_string(__maximum) << std::endl;
	} while (_num < __minimum || _num > __maximum);

	return _num;
}

std::vector<std::string> prompt_arr(std::string __question, int __count) {
	std::vector<std::string> _arr;

	if (__count <= 0) {
		std::cerr << "Given param \"count\" is less than 0" << std::endl;
		return _arr;
	}

	for (int index = 0; index < __count; index++)
		_arr.push_back(prompt( __question + " #" + std::to_string((index + 1))) );

	return _arr;
}

std::string encloseQuote(std::string __word) {
	return "\"" + __word + "\"";
}

std::string removeQuote(std::string __word) {
	if (__word.front() == '\"' && __word.back() == '\"') {
		__word.erase(0);
		__word.erase(__word.size() - 1);
	}

	return __word;
}

std::string is_json(std::string __word, std::string __type) {
	if (__type == "JSON" || __type == "json")
		return encloseQuote(__word);
	else
		return __word;
}

std::string encloseQuote_arr(std::vector<std::string> __arr, int __arr_length) {
	std::string __val;

	if (__arr_length <= 0)
		return "";
	else if (__arr_length == 1)
		return __arr[0];
	
	__val = "[";

	for (int index = 0; index < __arr_length; index++) {
		if (index == __arr_length - 1)
			__val += encloseQuote(__arr[index]);
		else
			__val += encloseQuote(__arr[index]) + ",";
	}

	__val += "]";

	return __val;
}

std::vector<std::string> split(std::string __str, const std::regex __delimiters) {
	const std::vector<std::string> _arr{ 
		std::sregex_token_iterator(__str.begin(), __str.end(), __delimiters, -1), 
		std::sregex_token_iterator() 
	};
	return  _arr;
}

std::string slugize_str(std::string __str) {
	const std::regex __invalid_chars("[^A-Za-z0-9]");
	std::string _slug;
	std::vector<std::string> _words = split(__str, __invalid_chars);

	if (_words.empty())
		return __str;
	
	for (int _word_index = 0; _word_index < _words.size(); _word_index++) {
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

	if (_slug.back() == '-')
		_slug.erase(_slug.size() - 1);

	return _slug;
}

std::vector<std::string> arr_extract(std::string __arr_str) {

	std::vector<std::string> _arr;

	if (__arr_str.front() != '[' && __arr_str.back() != ']')
		return _arr;

	std::regex _vector_elem("\".*\"");
	
	for (std::sregex_iterator _match = std::sregex_iterator(__arr_str.begin(), __arr_str.end(), _vector_elem); _match != std::sregex_iterator(); ++_match) {
		std::smatch _word = *_match;

		if (_word.empty())
			continue;

		_arr.push_back(_word.str()); 
	}
	
	return _arr;
}
