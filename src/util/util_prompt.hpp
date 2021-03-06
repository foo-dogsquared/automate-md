#include <iostream>
#include <string>

#define MAX_STRING_LENGTH 65535

namespace util {
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
		int _num = 0;
		do {
			_out = prompt(__question);

			if (has_non_digits(_out))
				continue;

			_num = stoi(_out);

			if (_num < __minimum || _num > __maximum)
				std::cout << "Value can only range from " << std::to_string(__minimum) << " to " << std::to_string(__maximum) << std::endl;
		} while (_num < __minimum || _num > __maximum);

		return _num;
	}

	std::string prompt_arr(std::string __question, int __count) {
		std::string _arr;

		if (__count <= 0) {
			std::cerr << "Given param \"count\" is less than or equal to 0." << std::endl;
			return "";
		}

		for (int index = 0; index < __count; index++) {
			std::string _word = enclose_str(prompt( __question + " #" + std::to_string(index + 1)));
			_arr += _word + ((index == __count - 1) ? "" : ", ");
		}
		
		if (__count > 1)
			_arr = enclose_str(_arr, "[", "]");

		return _arr;
	}

	void confirm_prompt(std::string __question = "Are you sure you want to confirm the action? (enter anything other than 'N' or 'n' to confirm)") {
		std::cout.flush();

		std::string _answer;
		std::cout << __question << std::endl << ">>> ";
		std::cin >> _answer;

		if (_answer == "N" || _answer == "n")
			exit(0);
	}
}
