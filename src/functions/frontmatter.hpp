#include <map>
#include <regex>

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
	std::string __space;
} 
frontmatter;

void init_fm_format_data(frontmatter &__fm) {
	if (__fm.type == "YAML" || __fm.type == "yaml") {
		__fm.__open_divider = "---";
		__fm.__close_divider = "---";
		__fm.__tab = "";
		__fm.__assigner = ":";
		__fm.__space = "";
	}
	else if (__fm.type == "TOML" || __fm.type == "toml") {
		__fm.__open_divider = "+++";
		__fm.__close_divider = "+++";
		__fm.__tab = "";
		__fm.__assigner = "=";
		__fm.__space = " ";
	}
	else if (__fm.type == "JSON" || __fm.type == "json") {
		__fm.__open_divider = "{";
		__fm.__close_divider = "}";
		__fm.__tab = "\t";
		__fm.__assigner = ":";
		__fm.__space = "";
	}
}

std::string detect_type(std::string __str) {
	std::regex __YAML("---\\s*"), __TOML("\\+\\+\\+\\s*"), __JSON("\\{\\s*|\\}\\s*");
	if (std::regex_match(__str, __YAML))
		return "YAML";
	else if (std::regex_match(__str, __TOML))
		return "TOML";
	else if (std::regex_match(__str, __JSON))
		return "JSON";
	else
		return nullptr;
}
