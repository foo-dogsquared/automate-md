#pragma once

#include <iostream>
#include <string>

std::string cli_actions_format(std::string action, std::string params, std::string optional_params = "") {
    std::string optional_params_string = (optional_params.length() >= 0) ? " | " + optional_params : "";
    std::string text_desc = action + " | " + params + optional_params_string + "\n";
    return text_desc;
}

void cli_help_section() {
    std::cout << "Usage: automate-md [action] [required_param] [optional_param]...\n" <<
            "Actions:\n" << std::endl;
}

void cli_action_detect(std::string action) {
    if (action == "create" || action == "CREATE") 
        std::cout << "\tUsage: " << cli_actions_format("create", "TITLE") << std::endl;
    else if (action == "update" || action == "UPDATE")
        std::cout << "\tUsage: " << cli_actions_format("update", "FILE_NAME") << std::endl;
    else if (action == "reset" || action == "RESET")
        std::cout << "\tUsage: " << cli_actions_format("reset", "FILE_NAME") << std::endl;
    else if (action == "extract" || action == "EXTRACT")
        std::cout << "\tUsage: " << cli_actions_format("extract", "FILE_NAME") << std::endl;
    else {
        std::cout << "Found no available command." << std::endl;
        return;
    }
    exit_error_code(1, "Needs a parameter for the said action");
}
