#pragma once

#include <ctime>
#include <iostream>
#include <regex>
#include <string>

#define MAX_DATE_STRING 64
#define MAX_STRING_LENGTH 65535
#define INVALID_CHARS " !@#$%^&*()_+={}[]:;\"'<,>.?/|\\~`"

bool isSame(std::string __word, std::string __compare_str) {
	if (__word.compare(__compare_str) == 0)
		return true;
	else
		return false;
}

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

std::string* prompt_arr(std::string __question, int __count) {
	if (__count <= 0) {
		std::cerr << "Given param \"count\" is less than 0" << std::endl;
		return nullptr;
	}

	std::string *_arr = new std::string[__count];
	
	for (int index = 0; index < __count; index++)
		_arr[index] = prompt(__question + " #" + std::to_string((index + 1)));

	return _arr;
}

std::string encloseQuote(std::string __word) {
	return "\"" + __word + "\"";
}

std::string isJSON(std::string __word, std::string __type) {
	if (isSame(__type, "JSON") || isSame(__type, "json"))
		return encloseQuote(__word);
	else
		return __word;
}

std::string encloseQuote_arr(std::string* __arr, int __arr_length) {
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

std::string slugize_str(std::string __str) {
	std::string _slug;
	std::vector<std::string> _words;

	for (char* _token = std::strtok(&__str[0], INVALID_CHARS); _token != NULL; _token = std::strtok(NULL, INVALID_CHARS))
		_words.push_back(_token);
	
	for (int _word_index = 0; _word_index < _words.size(); _word_index++) {
		for (int _char_index = 0; _words[_word_index][_char_index]; _char_index++)
			_words[_word_index][_char_index] = tolower(_words[_word_index][_char_index]);

		if (_word_index == 0 && _word_index == _words.size() - 1)
			_slug = _words[_word_index];
		else if (_word_index == 0)
			_slug = _words[_word_index] + "-";
		else if (_word_index == _words.size() - 1)
			_slug += _words[_word_index];
		else
			_slug += _words[_word_index] + "-";
	}

	return _slug;
}
