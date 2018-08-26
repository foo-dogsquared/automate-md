#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "frontmatter.h"

#define CHAR_NUMBER_DATE 11

#define CHAR_NUMBER_MAX_FILE 89

int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 1)
    {
        printf("There is no argument inputted.\n");
        return 0;
    }
    else if (argc >= 2)
    {
        // name of the title
        char *name = argv[1];
        long days;
        if (argv[2] == NULL)
        {
            days = 0;
        }
        else
        {
            days = strtol(argv[2], NULL, 0);
        }

        if (strlen(name) > TITLE_MAX_LENGTH)
        {
            printf("Title is more than 64 characters.\n");
            return 1;
        }

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

        printf("Formatted time: %s\n", date_string);
        // writing the file name starting with the date
        strftime(file_name, sizeof(file_name), "%F", tmp);
        strcat(file_name, name);
        strcat(file_name, ".md");

        frontmatter post;

        post.layout = "layout: post";

        strcpy(post.date, "date: ");
        strcat(post.date, date_string);

        strcpy(post.title, "title: ");
        strcat(post.title, name);

        strcpy(post.author, "author: ");
        strcat(post.author, prompt_for_author("Who is the author of the post?"));

        char c;
        do
        {
            printf("\nEnter an integer to indicate how many categories (only up to 16 categories):\n>>> ");

        } while (((scanf("%d%c", &post.categories_length, &c)!=2 || c!='\n') && clean_stdin()) || post.categories_length < 1 || post.categories_length > 16);

        do
        {
            printf("\nEnter an integer to indicate how many tags (only up to 16 tags):\n>>> ");

        } while (((scanf("%d%c", &post.tags_length, &c)!=2 || c!='\n') && clean_stdin()) || post.tags_length < 1 || post.tags_length> 16);

        // prompting for the categories
        prompt(post.categories_length, "\nCategory", post.categories);

        // prompting for the tags
        prompt(post.tags_length, "\nTag", post.tags);

        // creating a file
        printf("Creating the post...\n");
        FILE* post_md = fopen(file_name, "w");
        if (!post_md) {
            printf("File creation failed.");
        }

        fprintf(post_md, "---\n");
        fprintf(post_md, "%s\n", post.layout);
        fprintf(post_md, "%s\n", post.date);
        fprintf(post_md, "%s\n", post.author);
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
                if (index == post.tags_length - 1)
                {
                    fprintf(post_md, "%s", post.tags[index]);
                } else {
                    fprintf(post_md, "%s, ", post.tags[index]);
                }
            }

            fprintf(post_md, "]\n");
        }


        fprintf(post_md, "---");

        printf("File successfully created!\n");

        fclose(post_md);
        return 0;
    }
}