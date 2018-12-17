#include <iostream>
#include <string>

#include "cli_action_list.hpp"

std::string cli_actions_format(std::string action, std::string params, std::string optional_params = "") {
    std::string optional_params_string = (optional_params.length() >= 0) ? " | " + optional_params : "";
    std::string text_desc = action + " | " + params + optional_params_string + "\n";
    return text_desc;
}

void cli_help_section() {
    std::cout << "Usage: automate-md [action] [required_param] [optional_param]...\n" <<
            "Actions:\n" << std::endl;

    action_desc CREATE, UPDATE, RESET, EXTRACT;

    CREATE.action = "create";
    CREATE.action_desc = "creates a new markdown file with the user-specified data inserted in the frontmatter";
    CREATE.required_param = "TITLE [String]";
    CREATE.required_param_desc = "The title of the post and the file name.";
    CREATE.optional_param_list.insert(std::make_pair("fm_type", "the frontmatter format of the file; possible values are JSON, YAML, and TOML"));
    CREATE.optional_param_list.insert(std::make_pair("output_path", "location of the new markdown file"));
    cli_action_template(CREATE);
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
