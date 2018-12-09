# automate-md
[![HitCount](http://hits.dwyl.io/foo-dogsquared/automate-md.svg)](http://hits.dwyl.io/foo-dogsquared/automate-md)
![Size](https://github-size-badge.herokuapp.com/foo-dogsquared/automate-md.svg)

A program that just automates creation of .md files that is suitable for Jekyll (and Hugo) with the correct frontmatter, probably.

## How to use
Clone the Git repo with:
```
git clone https://github.com/foo-dogsquared/automate-md.git
cd automate-md
```

For now, to use the program, you would have to build it yourself with `cmake` and `make`.

```bash
cmake CMakeLists.txt
make
```

Just for reference, here are the related tools and their version by the time I successfully built the program:
- CMake 3.6.2
- GCC 7.3.0

### Available commands
Format: `COMMAND "MANDATORY_ARG" [optional_arg1] [optional_arg2] ...`

The program has multiple functions available and can be activated with these commands:
- `create` - creates a new markdown file with a frontmatter
- `update` - updates the markdown file in the specified path
- `extract` - extract a certain part of a markdown file (either the frontmatter part or the content)
- `reset` - deletes the content but the frontmatter retains

### Example use case
Each of the available command has at least one optional parameters that are user-configured. These optional parameters requires a value delimited by an equal sign and must lack a whitespace character (if it's needed you must escape it) due to how I plan the program to parse through these parameters.

Most of them also has a optional command argument that triggers a specific kind of event during the execution of the program. These optional command arguments are also option with the difference of being prefixed by a percentage sign (%) to avoid conflict with your own optional parameter.

Some of example of these optional command arguments:

```bash
automate-md create "My Monthly Dues and Fees" --%fm_type=JSON

automate-md update ./other_posts/notes.md --%delete_keys=[slug,title,auto_url]

automate-md extract ./my_notebook.md --%part=content
```

#### `create()`
##### Format and available parameters:

```bash
create "TITLE" --%fm_type=[JSON || YAML || TOML]  --%output_path=PATH_OF_OUTPUT🤣 --%ssg_template=[jekyll || hugo] --any_options=any_value_you_want
```

##### Command parameters:
- `fm_type` - the frontmatter format to be based on; the default format is in YAML, the frontmatter format of Jekyll posts
- `output_path` - well, self-explanatory --- this is where the markdown file will be written; take note that the output path for the markdown file must already exists, just like how the system command `touch` won't create a file when the specified directories cannot be found
- `ssg_template` - the usual template of key-value objects where certain static site generators always have them; default template to be used is Jekyll

How about the `any-options` one? I'll explain it shortly after the next sentence.

First, running the command in subject will bring up a bunch of prompts that requires your input (obviously, that's what prompts are for) to complete the frontmatter's default values (at least for most static site generators, anyway).

Now, for the `any-options` optional parameter. The deal is kinda simple, you can set any options to be used as the key and set any values you want and it'll be the part of the frontmatter (as long as you input it correctly).

Say that I want to include the key `favorite_animal` with the value of `dog` on the frontmatter. I can just run it like so:

```bash
automate-md create "Let's talk about our favorite animals today!" --favorite_animal=dog
```

A few prompts later and the markdown file will be created with a frontmatter that is included in the file.
```md
---
...
favorite_animal: dog
...
---    
```

There are some things to be noted though:
- Be sure to check your spelling and the usage of lowercase and uppercase letters. The keys/fields from the optional parameters are case-sensitive. `--Author` is different from `--author`, meaning there will be another key/value object with a similar key.
- Markdown files can only be created with less than or equal to 16 categories.
- Also, the same length applies to the tags.
- Titles are only limited up to 64 characters.
- Author name is limited only up to 32 characters. So if your name is "\___xXX---THE-ULTIMATE-WARRIOR-ALPHA-AND-OMEGA---XXx\___", or any name with longer variants and/or similar length of characters, then I'm sorry to say that you're not qualified to create a markdown file with this tool. 🙃

These restrictions are put out to be a lighter burden when your SSG takes those markdown files. Also, there are plentiful of ways on how to break such things so there's also that.

For this command, you can set out multiple options (`--option=value`) and it will be added as one of the key-value objects in the frontmatter.

Also, if certain non-command options like `--author` or `layout` are set, certain prompts will be skipped and will use the value that you provided from the state before the program ran. 

Assuming I ran the program with these arguments (and assuming I ran this on 2018-12-09 (December 9, 2018)):
```bash
    # To create a post that will be published in 5 days with the frontmatter format of JSON
    ./automate-md create "SAMPLE TITLE" --date=5 --%fm_type=JSON --%output_path=./path/to/this 

    # prompts here and prompts there...

    # It can also accept negative integers making the post meant to be published 2 days ago with 
    # an additional key of "sound" with the value of "windy days"
    ./automate-md create "THE DOGS ARE IN THE RYE" --date=-2 --sound="windy days"

    # a set of prompts later...

    # To easily create a post that is meant for today
    ./automate-md create "BATMAN"

    # another set of prompts later...
```

There should be 3 markdown files that is located in the following:
- ./path/to/this/2018-12-14-sample-title.md
- ./2018-12-07-the-dogs-are-in-the-rye.md
- ./2018-12-09-batman.md

With each of the markdown has difference like with the first file having JSON format as the frontmatter, the second file having an additional key-value object, and the third file... nothing, just nothing.

#### `update()`
##### Format and available parameters:

```bash
update FILE_PATH --%delete_key=[key1,key2,key3,...] --%fm_type=[JSON || YAML || TOML] --%force --any_option=any_value
```

##### Command parameters:
- `delete_key` - a list of keys separated by a comma **with no whitespace character** to be deleted on the frontmatter
- `fm_type` - the format of the frontmatter to be updated with

Just like from the `create()` function, you can set any option with any value to be included in the frontmatter. And get this, there's only one prompt which is there for safety reasons, for course. Well, you can skip the prompt by typing `--%force` although it requires more key presses than pressing the enter button, typing `Y`, `y`, `N`, or `n`, and pressing Enter again. Could be useful for automated updating, who knows...

#### `extract()`
##### Format and available parameters:

```bash
extract FILE_PATH --%part=[frontmatter || content] --%output_path=TO_THE_MARKDOWN_HEAVEN
```

##### Command parameters:
- `part` - the part of the markdown file to be extracted
- `output_path` - the location to where the part shall be written; take note that the result will be written in markdown although I'm considering of expanding that

Also, no user-configured options this time. :sad:

## How to contribute?
You can refer [here](./docs/CONTRIBUTING.md) for the guidelines.
