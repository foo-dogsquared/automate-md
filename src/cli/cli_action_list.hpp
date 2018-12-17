#include <map>
#include <iostream>

typedef struct __action_desc 
{
    std::string action;
    std::string action_desc;
    std::string required_param;
    std::string required_param_desc;
    std::map<std::string, std::string> optional_param_list;
}
action_desc;

void cli_action_template(action_desc __action) {
    std::cout << __action.action << " - " << __action.action_desc << "\n" <<
    "\t" << __action.required_param << " :: " << __action.required_param_desc << "\n";

    if (__action.optional_param_list.size() > 0) {
        std::cout << "\tOptional parameter(s):\n";

        for (std::map<std::string, std::string>::iterator _trav = __action.optional_param_list.begin(); _trav != __action.optional_param_list.end(); _trav++) {
            std::cout << "\t\t- " << _trav->first << " :: " << _trav->second << "\n";
        }
    }
}