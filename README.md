# automate-md
A program that just automates creation of .md files that is suitable for Jekyll (and Hugo) with the correct frontmatter, probably.

## How to use
For now, to use the program, you would have to build it yourself with `gcc` or any compilers you have installed. Just for 
reference, I compiled mine to get the program working with GCC 7.3.0.

The program only needs two parameters: 
- A string that is the title of the post
- An integer that represents how many days **from now** the post will be published on the `date` frontmatter. If no integer is given, the present date will be accepted as the data.

### Example use case
```bash
    # To create a post that will be published 5 days from now with the title
    ./automate-md "SAMPLE TITLE" 5 

    # It can also accept negative integers making the post meant to be published x days ago
    ./automate-md "THE DOGS ARE IN THE RYE" -2

    # To easily create a post that is meant for today, just leave out the second parameter
    ./automate-md "BATMAN"
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