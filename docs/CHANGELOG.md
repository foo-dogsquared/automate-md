# Changelog
Some of the planned changes are also listed in here.

## Work-in-progress
- Add `update` command
- Add `reset` command
- Add `extract` command
- Add flags and options such as `--type VALUE` or `--type=VALUE`

## [Unreleased]
## Added
- Added `extract` command
- Assigned an error number range to each command

### Changed
- Refactored `std::vector<std::string> split` function
- Changed the frontmatter struct contents entirely into one list
- `util.hpp` has been modularized

## [0.9.2] - 2018-12-04
### Added
- Add the `extract` command (barely working...)

### Changed
- Change the structure of the frontmatter
- Revise the regex for most frontmatter formats

## [0.9.1] - 2018-12-01
### Added
- Add `create` command

### Changed
- Update the docs

## [0.9.0] - 2018-11-29
### Changed
- Change from C to C++
- Reorganize the project files

## [0.5.0] - 2018-08-30
### Added
- Complete the prototype
- Add `char* slugify` function

### Changed
- Refactor some code

### [0.4.9] - 2018-08-26
### Added
- Add the correct date indication
- Add .gitignore file