#include <iostream>
#include <string>

#define MAX_STRING_LENGTH 65535

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

std::string prompt_arr(std::string __question, int __count) {
	std::string _arr;

	if (__count <= 0) {
		std::cerr << "Given param \"count\" is less than 0" << std::endl;
		return "";
	}

	if (__count > 1)
		_arr = "[";

	for (int index = 0; index < __count; index++) {
		std::string _word = "\"" + prompt( __question + " #" + std::to_string(index + 1)) + "\"";
		_arr += _word + ((index == __count - 1) ? "" : ", ");
	}
	
	if (__count > 1)
		_arr += "]";

	return _arr;
}
