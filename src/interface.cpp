#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cli/cli_actions.hpp"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cli_help_section();
        return 0;
    }
    else if (argc == 2) {
        std::string action = argv[1];
        if (action == "--help" || action == "-h")
            cli_help_section();    
        else
            cli_action_detect(argv[1]);
    }
    else if (argc >= 3) {
        std::string action = argv[1];
        std::string required_param = argv[2];

        std::regex option_regex("--(%?[A-Za-z0-9_-]+)=\"?(.+?)\"?");
        std::map<std::string, std::string> optional_params;
        std::smatch matches;
        std::string op_param, value;
        if (argc >= 4) {
            for (int option_param_index = 3; option_param_index < argc; option_param_index++) {
                std::string option = argv[option_param_index];
                if (std::regex_match(option, matches, option_regex)) {
                    op_param = matches[1].str();
                    value = matches[2].str();
                    optional_params.insert(std::make_pair(op_param, value));
                }
                else
                    std::cout << option << " at index " + std::to_string(option_param_index) +  " is not detected as an option" << std::endl;
            }
        }

        if (action == "CREATE" || action == "create")
            create(required_param, optional_params);
        else if (action == "UPDATE" || action == "update")
            update(required_param, optional_params);
        else if (action == "RESET" || action == "reset")
            reset(required_param);
        else if (action == "EXTRACT" || action == "extract")
            extract(required_param, optional_params);
        
        return 0;
    }
}