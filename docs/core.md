# The core of the program

Here's the basic representation of the program from multiple files:

`interface.cpp`
    └─── cli/`cli_actions.hpp`
        ├─── `create()`
        ├─── `update()`
        ├─── `reset()`
        └─── `extract()`

All of the functions from `cli/cli_actions.hpp` are derived further from `file_io/file_io.hpp`.

But the main files to be inspected for the core functions to work is from `/cli/cli_actions.hpp` and `/functions/file_io.hpp`.

## Error list:
### General
- 1 - this only occurs when opening the program with only an action and has no parameter
- 2 - given action is not available
- 3 - file I/O error

### Command-specific
#### `create` (10 - 19) 
- 10 - length of the given `@title` has exceeded permitted length of 64 characters
- 11 - param `@publish_date` has invalid characters for conversion to `long`

#### `update` (20 - 29)
- 20 - needing at least one optional parameter

#### `reset` (30 - 39)
- 30 - needing the param `@file_path`

#### `extract` (40 - 49)
- 40 - needing a param `@output_path`
- 41 - content extracted from the file is empty (if the param `@part` is `content`)

