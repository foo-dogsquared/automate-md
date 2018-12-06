#include <map>

#define MAX_ARR_LENGTH 16
#define MAX_DATE_LENGTH 26
#define MAX_TITLE_LENGTH 64
#define MAX_AUTHOR_LENGTH 32

typedef struct _frontmatter
{
    std::map<std::string, std::string> list;
    int categories_length;
    int tags_length;
} 
frontmatter;
