# Changelog
Some of the planned changes are also listed in here.

## Work-in-progress
- Add `reset` command.

## [Unreleased]
- Unit tests (still a beginner when it comes to properly testing out codes)

## [1.0.3] - 2019-01-18
### Changed
- Changed the documentation

### What's fixed?
- Fixed the infinite optional command error message bug when running the command with `create`

## [1.0.2] - 2018-12-23
### Changed
- Updated the regex
- Revised the way how variables are placed

### What's fixed?
- Fixed the wrong and buggy outputting process of `extract`

## [1.0.1] - 2018-12-17
### Changed
- Revised the help section of the program

## [1.0.0] - 2018-12-11
### Added
- Added the `%force` optional command parameter on the `update` function.

### Changed
- Added minor improvements
- Fixed the way how the program puts an array of values

## [0.9.6] - 2018-12-10
### Added
- Added the `reset` command.
- Added the `%update_date` optional command parameter on the `update` function.

### What's fixed?
- Fixed how quotes are interpreted and added in the markdown file.

## [0.9.5] - 2018-12-09
### Added
- Added command parameters
- Added the ability to correctly interpret flags and options such as `--type VALUE` or `--type=VALUE`.
- Added `update` command (in prototype).

## [0.9.4] - 2018-12-08
### Changed
- Updated the regex to interpret files more correctly.

### What's fixed?
- Fixed the bug of hanging out when interpreting files that are not created with `automate-md` due to how inserting characters were actually applied when it is being copied or inserted by non-`automate-md` programs.

## [0.9.3] - 2018-12-06
### Added
- Added `extract` command.
- Assigned an error number range to each command.

### Changed
- Refactored `std::vector<std::string> split` function.
- Changed the frontmatter struct contents entirely into one list.
- `util.hpp` has been modularized.

### What are the bugs?
- Markdown files that are not created with `automate-md` cannot be parsed properly.

## [0.9.2] - 2018-12-04
### Added
- Add the `extract` command (barely working...).

### Changed
- Change the structure of the frontmatter.
- Revise the regex for most frontmatter formats.

## [0.9.1] - 2018-12-01
### Added
- Add `create` command.

### Changed
- Update the docs.

## [0.9.0] - 2018-11-29
### Changed
- Change from C to C++.
- Reorganize the project files.

## [0.5.0] - 2018-08-30
### Added
- Complete the prototype.
- Add `char* slugify` function.

### Changed
- Refactor some code.

### [0.4.9] - 2018-08-26
### Added
- Add the correct date indication.
- Add .gitignore file.
