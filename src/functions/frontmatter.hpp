#define MAX_ARR_LENGTH 16
#define MAX_DATE_LENGTH 26
#define MAX_TITLE_LENGTH 64
#define MAX_AUTHOR_LENGTH 32

typedef struct _frontmatter
{
    std::string layout;
    std::string author;
    std::string title;
    std::string date;
    std::string *categories;
    int categories_length;
    std::string *tags;
    int tags_length;
} 
frontmatter;
