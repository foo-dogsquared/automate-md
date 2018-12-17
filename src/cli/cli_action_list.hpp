#include <map>
#include <iostream>

typedef struct __action_desc 
{
    std::string action;
    std::string action_desc;
    std::string required_param;
    std::string required_param_desc;
    std::map<std::string, std::string> optional_param_list;
    std::string footnote;
}
action_desc;

void cli_action_template(action_desc __action) {
    std::cout << "\t" << __action.action << " - " << __action.action_desc << "\n" <<
    "\t\t" << __action.required_param << " :: " << __action.required_param_desc << "\n";

    if (__action.optional_param_list.size() > 0) {
        std::cout << "\t\tOptional command parameter(s):\n";

        for (std::map<std::string, std::string>::iterator _trav = __action.optional_param_list.begin(); _trav != __action.optional_param_list.end(); _trav++) {
            std::cout << "\t\t\t--%" << _trav->first << " :: " << _trav->second << "\n";
        }
    }

    if (!__action.footnote.empty())
        std::cout << "\n\t\t" << __action.footnote << "\n";

    std::cout << "\n\n";
}

// action constants for CLI formatting
void cli_specify_section(std::string __part) {
    action_desc CREATE, UPDATE, RESET, EXTRACT;

    CREATE.action = "create";
    CREATE.action_desc = "creates a new markdown file with the user-specified data inserted in the frontmatter";
    CREATE.required_param = "TITLE [String]";
    CREATE.required_param_desc = "The title of the post and the file name.";
    CREATE.optional_param_list.insert(std::make_pair("fm_type", "the frontmatter format of the file; possible values are JSON, YAML, and TOML"));
    CREATE.optional_param_list.insert(std::make_pair("output_path", "location of the new markdown file"));
    CREATE.footnote = "Optional parameters are any key-value objects delimited by an equal sign.\nAny specified data in the correct format will be added in the frontmatter.";

    UPDATE.action = "update";
    UPDATE.action_desc = "changes a certain aspect of the frontmatter in the file";
    UPDATE.required_param = "FILE_PATH [String]";
    UPDATE.required_param_desc = "the location of the markdown file to be updated";
    UPDATE.optional_param_list.insert(std::make_pair("delete_key", "contains a JSON array of comma-separated values representing the key to be deleted inside of the file"));
    UPDATE.optional_param_list.insert(std::make_pair("fm_type", "changes the frontmatter format into the specified value; possible values are JSON, YAML, and TOML"));
    UPDATE.optional_param_list.insert(std::make_pair("update_date", "changes the date relative to current date"));
    UPDATE.optional_param_list.insert(std::make_pair("force", "skips the prompt if the value is true"));
    UPDATE.footnote = "Optional parameters are any key-value objects delimited by an equal sign.\nAny specified data in the correct format will be added or changed its value in the frontmatter.";

    RESET.action = "reset";
    RESET.action_desc = "simply deletes the content of the markdown file while retaining the frontmatter";
    RESET.required_param = "FILE_PATH [String]";
    RESET.required_param_desc = "the location of the markdown file to be reset";

    EXTRACT.action = "extract";
    EXTRACT.action_desc = "extracts the specified part of the markdown file";
    EXTRACT.required_param = "FILE_PATH [String]";
    EXTRACT.required_param_desc = "the location of the file to be inspected";
    EXTRACT.optional_param_list.insert(std::make_pair("part", "specifies the part of the markdown file to be extracted; possible values are \"frontmatter\" or \"content\""));
    EXTRACT.optional_param_list.insert(std::make_pair("output_path", "specifies the location to where the extracted data will be saved"));

    if (__part == "all" || __part.empty()) {
        cli_action_template(CREATE);
        cli_action_template(UPDATE);
        cli_action_template(RESET);
        cli_action_template(EXTRACT);
    }
    else if (__part == "create")
        cli_action_template(CREATE);
    else if (__part == "update")
        cli_action_template(UPDATE);
    else if (__part == "reset")
        cli_action_template(UPDATE);
    else if (__part == "extract")
        cli_action_template(UPDATE);
}
