#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "frontmatter.h"
#include "str_c.h"

#define CHAR_NUMBER_DATE 11

#define CHAR_NUMBER_MAX_FILE 89

/* CREDITS: https://stackoverflow.com/a/14099507 */
int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1)
    {
        printf(ANSI_COLOR_RED "There is no argument inputted." ANSI_COLOR_RESET "\n");
        return 0;
    }
    else if (argc >= 2)
    {
        // name of the title

        long days;
        if (argv[2] == NULL)
        {
            days = 0;
        }
        else
        {
            days = strtol(argv[2], NULL, 0);
        }

        if (strlen(argv[1]) > TITLE_MAX_LENGTH)
        {
            printf(ANSI_COLOR_RED "Title is more than 64 characters." ANSI_COLOR_RESET "\n");
            return 1;
        }

        // getting the name by copying it
        char *name = malloc(sizeof(char) * TITLE_MAX_LENGTH);
        strcpy(name, argv[1]);

        // another one set for the title
        char *title = argv[1];

        /* reason why we have two variables set for the name is because strtok() modifies the given string
        which will be used for cutting the sentences into words to be put in an array */

        time_t t;
        struct tm *tmp;
        char date_string[COMPLETE_DATE_LENGTH];
        time(&t);
        tmp = localtime(&t);
        tmp->tm_mday += days;
        mktime(tmp);

        // writing the complete date
        strftime(date_string, sizeof(date_string), "%F %T +0800", tmp);

        // maximum number of characters in our markdown file
        char file_name[CHAR_NUMBER_MAX_FILE];
        char *slugized_name = slugize_str(name);

        printf("Formatted time: %s\n", date_string);
        // writing the file name starting with the date
        strftime(file_name, sizeof(file_name), "%F", tmp);
        strcat(file_name, "-");
        strcat(file_name, slugized_name);
        strcat(file_name, ".md");

        // creating the post with the frontmatter variable 
        frontmatter post;

        // filling out the details
        post.layout = "post";

        strcpy(post.date, date_string);

        strcpy(post.title, title);

        strcpy(post.author, prompt_for_author("Who is the author of the post?"));

        char c;
        do
        {
            printf(ANSI_COLOR_BRIGHT_CYAN "\nEnter an integer to indicate how many categories (only up to 16 categories):\n>>> " ANSI_COLOR_RESET);

        } while (((scanf("%d%c", &post.categories_length, &c)!=2 || c!='\n') && clean_stdin()) || post.categories_length < 1 || post.categories_length > 16);

        // prompting for the categories
        prompt(post.categories_length, "\nCategory", post.categories);

        do
        {
            printf(ANSI_COLOR_BRIGHT_CYAN "\nEnter an integer to indicate how many tags (only up to 16 tags):\n>>> " ANSI_COLOR_RESET);

        } while (((scanf("%d%c", &post.tags_length, &c)!=2 || c!='\n') && clean_stdin()) || post.tags_length < 1 || post.tags_length> 16);

        // prompting for the tags
        prompt(post.tags_length, "\nTag", post.tags);

        // creating the file
        printf(ANSI_COLOR_CYAN "\nCreating the post '%s'...\n" ANSI_COLOR_RESET, file_name);
        FILE* post_md = fopen(file_name, "w");
        if (!post_md) {
            printf(ANSI_COLOR_RED "\nFile creation failed." ANSI_COLOR_RESET);
        }

        fprintf(
        post_md, 
        "---\n"
        "layout: %s\n" /* first string placeholder */
        "title: \"%s\"\n" /* second string placeholder */
        "date: %s\n" /* third string placeholder */
        "author: %s\n" /* fourth string placeholder */, 
        post.layout, post.title, post.date, post.author
        );
        
        if (post.categories_length == 1)
        {
            fprintf(post_md, "categories: %s\n", post.categories[0]);
        } else {
            fprintf(post_md, "categories: [");
            for (int index = 0; index < post.categories_length; index++)
            {
                if (index == post.categories_length - 1)
                {
                    fprintf(post_md, "%s", post.categories[index]);
                } else {
                    fprintf(post_md, "%s, ", post.categories[index]);
                }
            }
            fprintf(post_md, "]\n");
        }

        if (post.tags_length == 1)
        {
            fprintf(post_md, "tags: %s\n", post.tags[0]);
        } else {
            fprintf(post_md, "tags: [");
            for (int index = 0; index < post.tags_length; index++)
            {
                (index == post.tags_length - 1) ? fprintf(post_md, "%s", post.tags[index]) : fprintf(post_md, "%s, ", post.tags[index]);
            }
            fprintf(post_md, "]\n");
        }


        fprintf(post_md, "---");

        printf(ANSI_COLOR_BRIGHT_GREEN "\nPost successfully created!\n" ANSI_COLOR_RESET);

        fclose(post_md);
        return 0;
    }
}