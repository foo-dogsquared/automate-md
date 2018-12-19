#include <iostream>
#include <string>

#include "cli_action_list.hpp"

void cli_intro_section() {
    std::cout << 
    "Hello and thank you for using automate-md, a tool that helps you manage frontmatter data without touching a text editor.\n" <<
    "If you want to start somewhere, go and execute the program with the -h or --help option.\n\n" <<
    "Created by foo-dogsquared (https://github.com/foo-dogsquared)\n" <<
    "You can also visit the repo right here --> https://github.com/foo-dogsquared/automate-md\n";
}

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
