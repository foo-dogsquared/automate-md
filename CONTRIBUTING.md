# Contributing to automate-md
I very much welcome contributions from anyone with open arms. It helps in improving the quality of the project and my experience developing a project. 

You can contribute from reporting issues, requesting new features, refactoring code, and adding new functions requested from the issues into the codebase.

Here are the guidelines for several formats:
## Issues
### Bugs
For issuing bugs, just prepend the title with a `[BUG]` prefix:
`[BUG] I have lost my faith on humanity`

In the description, make sure to include as much details as possible. Be sure to make the title brief and concise, enlist the exact steps on how to reproduce the bug, and describe the behavior or result that you expected.

### Feature requests / enhancements
For issuing feature requests or enhancements, prepend with a `[FEATURE]` prefix:
`[FEATURE] Make post configuration configurable`

The feature or enhancement request does not have to be about the program itself. It can be also be about the documentation, style guides, anything beneficial for the quality of the project.

Similar to issuing bugs, make sure to include as much discussable details as possible: how this particular enhancement or feature enhance the project overall, how will this make the program easier to use, etc.

## Code
If you want to contribute through code, just do the following:

1. Fork this repository
2. Clone the forked repo
3. Edit whatever files you have (refactoring, adding, etc.)
4. Push your changes
5. Make a pull request into the original repo (this one, of course 😁)

### About pull requests
- Fix only one issue per pull request
- Describe what you've generally made
- Write meaningful commit messages (as stated from [the official book](https://git-scm.com/book))
- You can start with something small like fixing grammatical errors or editing the source code in accordance to the coding style guide (which is just after this one), I even make those mistakes myself 🙃

### Coding style
Well, for consistency. 🙂

I picked this coding style coming from a JavaScript background. In any case, the coding style is pretty much similar to [AirBNB's JavaScript Coding Style Guide](https://github.com/airbnb/javascript) but still, read on.

Variables, functions, and template names are in snakecase:

```c++
int integer_one;
float float_two;
std::string string_three;
is_similar();
```

Parameter names in functions are prefixed with two underscores (_):

```c++
int add_two_numbers(int __number_one, int __number_two);
```

Variables declared inside functions are prepended with one underscore (_):

```c++
int add_two_numbers(int __number_one, int __number_two) {
    int _sum = __number_one + __number_two;
    return _sum;
}
```

Placement of the opening code block brace is the same line of the function declaration:

```c++
int add_two_numbers(int __number_one, int __number_two) {
    return __number_one + __number_two;
}
```

For writing in header files, avoid using the `using` keyword with a `namespace`. Use the scope operator (::) with the often used member instead:

```c++
using namespace std; /* NOPE! */

using std::string /* OK! That's better, I guess */
```

On `if-else` statements, if the executed code consists of one statement or a one-liner, omit the braces and indent accordingly:

```c++
if (__number_one <= 0)
    __number_one = 1;
else
    __number_one = __number_one + 2;
```

## Code of conduct
You know the one, [this one](https://www.contributor-covenant.org/version/1/4/code-of-conduct). 

### tl;dr:
#### do:
- use welcoming language
- be respectful
- carefully give and openly receive constructive criticisms

#### don't:
- don't harass other contributors
- troll, insult, or resort to *ad hominem*
- leak private information of other people
