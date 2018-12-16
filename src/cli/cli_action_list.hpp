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
    "";
}
