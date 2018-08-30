#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INVALID_CHARS " ,-?!<>/\\|:\"*"
#define MAX_WORDS_LENGTH 32

char *slugize_str(char *str)
{
    char **str_arr = malloc(sizeof(char*) * MAX_WORDS_LENGTH);
    char *slug = malloc(sizeof(char) * 64);

    char *delimiters = INVALID_CHARS;

    char *token = strtok(str, delimiters);
    int word_num = 0;
    // putting all of those into an array
    for (int index = 0; token != NULL && index < 32; index++) 
    {
        str_arr[index] = token;
        word_num++;
        // printf("token %i: %s\n", index + 1, str_arr[index]);
        token = strtok(NULL, delimiters);
    }

    int word_index = 0; 
    char *word = str_arr[0]; 
    while (word_index < word_num)
    {
        // making the string to be lowercase
        for (int char_index = 0; word[char_index]; char_index++)
        {
            word[char_index] = tolower(word[char_index]);
        }

        if (word_index == 0 && word_index == word_num - 1)
        {
            strcpy(slug, str_arr[word_index]);
        }
        else if (word_index == 0)
        {
            strcpy(slug, str_arr[word_index]);
            strcat(slug, "-");
        }
        else if (word_index == word_num - 1)
        {
            strcat(slug, str_arr[word_index]);
        }
        else
        {
            strcat(slug, str_arr[word_index]);
            strcat(slug, "-");
        }
        word_index++;
        word = str_arr[word_index];
    }
    return slug;
}