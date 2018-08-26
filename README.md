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