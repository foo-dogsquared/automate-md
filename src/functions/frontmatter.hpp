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
    std::string type;
    std::string __open_divider;
	std::string __close_divider;
	std::string __tab;
	std::string __assigner;
} 
frontmatter;

void init(frontmatter &__fm) {
	if (__fm.type == "YAML" || __fm.type == "yaml") {
		__fm.__open_divider = "---";
		__fm.__close_divider = "---";
		__fm.__tab = "";
		__fm.__assigner = ":";
	}
	else if (__fm.type == "TOML" || __fm.type == "toml") {
		__fm.__open_divider = "+++";
		__fm.__close_divider = "+++";
		__fm.__tab = "";
		__fm.__assigner = "=";
	}
	else if (__fm.type == "JSON" || __fm.type == "json") {
		__fm.__open_divider = "{";
		__fm.__close_divider = "}";
		__fm.__tab = "\t";
		__fm.__assigner = ":";
	}
}

std::string detect_type(std::string __str) {
	if (__str == "---")
		return "YAML";
	else if (__str == "+++")
		return "TOML";
	else if (__str == "{" || __str == "}")
		return "JSON";
	else
		return nullptr;
}
