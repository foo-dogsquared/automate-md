#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "cli/cli_actions.hpp"

#define CREATE "create"
#define UPDATE "update"
#define RESET "reset"
#define EXTRACT "extract"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cli_help_section();
        return 0;
    }
    else if (argc == 2) {   
        cli_action_detect(argv[1]);
        exit_error_code(1, "Needs a parameter for the said action");
    }
    else if (argc == 3) {
        std::string action = argv[1];

        if (action == CREATE)
            create(argv[2]);
        else if (action == UPDATE)
            exit(0);
        else if (action == RESET)
            reset(argv[2]);
        else
            exit_error_code(2, "No available command");
    }
    else if (argc == 4) {
        std::string action = argv[1];

        if (action == CREATE)
            create(argv[2], argv[3]);
        else if (action == EXTRACT)
            extract(argv[2], argv[3]);
		else
			exit_error_code(2, "No available command");
    }
    else if (argc == 5) {
        std::string action = argv[1];

        if (action == CREATE)
            create(argv[2], argv[3], argv[4]);
        else if (action == EXTRACT)
            extract(argv[2], argv[3], argv[4]);
		else
			exit_error_code(2, "No available command");
    }
    else if (argc == 6) {
        std::string action = argv[1];
        if (action == CREATE)
            create(argv[2], argv[3], argv[4], argv[5]);
		else
            exit_error_code(2, "No available command");
    }
}