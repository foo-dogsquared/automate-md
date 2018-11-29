#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cli/cli_actions.h"

#define CREATE "create"
#define UPDATE "update"
#define RESET "reset"
#define EXTRACT "extract"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cli_help_section();
        return 0;
    }
    else if (argc == 2) {   
        int error_num = return_error_code(1, "Needs a parameter for the said action");
        cli_action_detect(argv[1]);
        return error_num;
    }
    else if (argc == 3) {
        string action = argv[1];

        if (isSame(action, CREATE))
            return create(argv[2]);
        else if (isSame(action, UPDATE))
            return 0;
        else if (isSame(action, RESET))
            return 0;
        else if (isSame(action, EXTRACT))
            return 0;
        else
            return return_error_code(2, "No available command");
    }
    else if (argc == 4) {
        string action = argv[1];

        if (isSame(action, CREATE))
            return create(argv[2], argv[3]);
		else
			return return_error_code(2, "No available command");
    }
    else if (argc == 5) {
        string action = argv[1];

        if (isSame(action, CREATE))
            return create(argv[2], argv[3], argv[4]);
		else
			return return_error_code(2, "No available command");
    }
}