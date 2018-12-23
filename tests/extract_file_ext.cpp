#include <iostream>
#include <string>

#include "../src/file_io/file_io_extract.hpp"

int main() {
    std::string __TEST__file_path = "./test/dogs/lol.md";
    std::string __TEST__file_path_double = "./test/dogs/lol.md.markdown";

    std::cout << "Test 1: File path is in the usual case" << std::endl;
    std::string __TEST_file_path_result = file_io::extract_file_extension(__TEST__file_path);
    std::cout << "file_io::extract_file_extension --> " <<  __TEST_file_path_result << std::endl;
    if (__TEST_file_path_result == "md")
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail" << std::endl;

    std::cout << "Test 2: File path contains two file extension" << std::endl;
    std::string __TEST_file_path_double_result = file_io::extract_file_extension(__TEST__file_path_double);
    std::cout << "file_io::extract_file_extension --> " <<  __TEST_file_path_double_result << std::endl;
    if (__TEST_file_path_double_result == "markdown")
        std::cout << "OK" << std::endl;
    else
        std::cout << "Fail" << std::endl;

    return 0;
}