# Changelog
Some of the planned changes are also listed in here.

## Work-in-progress
- Add `reset` command.

## [Unreleased]
- Nothing yet.

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