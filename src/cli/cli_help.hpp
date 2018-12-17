#include <iostream>
#include <string>

#include "cli_action_list.hpp"

void cli_help_section() {
    std::cout << "Usage: automate-md [action] [required_param] [optional_param]... [optional_command_param]...\n" << "Actions:\n";
    cli_specify_section("all");
}

void cli_action_detect(std::string action) {
    if (action == "create" || action == "CREATE") 
        cli_specify_section(action);
    else if (action == "update" || action == "UPDATE")
        cli_specify_section(action);
    else if (action == "reset" || action == "RESET")
        cli_specify_section(action);
    else if (action == "extract" || action == "EXTRACT")
        cli_specify_section(action);
    else {
        std::cout << "Found no available command." << std::endl;
        return;
    }
    exit_error_code(1, "Needs a parameter for the said action");
}
