# automate-md
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
- `create` "TITLE" [RELATIVE_DAYS] [PATH] [FRONTMATTER_TYPE]
- `update` "FILE_NAME" (**WIP**)
- `reset` "FILE_NAME" (**WIP**)
- `extract` "FILE_NAME" [CONTENT_TYPE] (**WIP**)

### Example use case
```bash
    # To create a post that will be published 5 days from now with the title
    ./automate-md create "SAMPLE TITLE" 5 

    # It can also accept negative integers making the post meant to be published x days ago
    ./automate-md create "THE DOGS ARE IN THE RYE" -2

    # To easily create a post that is meant for today, just leave out the second parameter
    ./automate-md create "BATMAN"
```

If the post creation is successful, you should get an `.md` file with the following format:
> [PUBLISH DATE]-[SLUGIZED TITLE]

In the examples above, you should get some markdown files with the following file names (assuming I've 
run the program on 30 Aug, 2018):
- `2018-09-04-sample-title.md`
- `2018-08-28-the-dogs-are-in-the-rye.md`
- `2018-08-30-batman`

The markdown files will be populated with a YAML frontmatter that is mostly made for Jekyll (IDK for 
other SSGs, though), so the usability is pretty limited.

## How to contribute?
You can refer [here](./docs/CONTRIBUTING.md) for the guidelines.
