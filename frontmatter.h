#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPLETE_DATE_LENGTH 28

#define TITLE_MAX_LENGTH 64
#define AUTHOR_NAME_MAX_LENGTH 64

#define CT_ARR_LENGTH 16
#define CT_NAME_MAX_LENGTH 16

#define INVALID_CHARACTERS

typedef struct frontmatter
{
    char *layout;
    char title[TITLE_MAX_LENGTH];
    char date[COMPLETE_DATE_LENGTH + 6];
    char author[AUTHOR_NAME_MAX_LENGTH + 7];
    int categories_length;
    char categories[CT_ARR_LENGTH][CT_NAME_MAX_LENGTH];
    int tags_length;
    char tags[CT_ARR_LENGTH][CT_NAME_MAX_LENGTH];
}
frontmatter;

void prompt(int length, char type[], char string_arr[CT_ARR_LENGTH][CT_NAME_MAX_LENGTH]) {
    for (int index = 0; index < length; index++) {
        char *input = malloc(sizeof(char) * CT_ARR_LENGTH);
        do
        {
            fprintf(stdout, "%s #%i: ", type, index + 1);
            scanf("%s", input);
            if (strlen(input) > CT_ARR_LENGTH || strlen(input) < 1) {
                printf("Must be from 1 to 16 characters only.\n\n");
            } else {
                strcpy(string_arr[index], input);
            }
        } while (strlen(input) > 16 || strlen(input) < 1);
        free(input);
    }
}

char *prompt_for_author(char question[])
{
    char *input = malloc(sizeof(char) * AUTHOR_NAME_MAX_LENGTH);
    do
    {
        fprintf(stdout, "%s\n>>> ", question);
        scanf("%s", input);
    } while (strlen(input) <= 0 || strlen(input) >= AUTHOR_NAME_MAX_LENGTH);

    return input;
}