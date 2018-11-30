#include "util.hpp"

typedef struct _frontmatter_type_obj {
	std::string __open_divider;
	std::string __close_divider;
	std::string __tab;
	std::string __assigner;
}
frontmatter_type;

frontmatter_type init(std::string __fm_type) {
	frontmatter_type __f;

	if (isSame(__fm_type, "YAML") || isSame(__fm_type, "yaml")) {
		__f.__open_divider = "---";
		__f.__close_divider = "---";
		__f.__tab = "";
		__f.__assigner = ":";
	}
	else if (isSame(__fm_type, "TOML") || isSame(__fm_type, "toml")) {
		__f.__open_divider = "+++";
		__f.__close_divider = "+++";
		__f.__tab = "";
		__f.__assigner = "=";
	}
	else if (isSame(__fm_type, "JSON") || isSame(__fm_type, "json")) {
		__f.__open_divider = "{";
		__f.__close_divider = "}";
		__f.__tab = "\t";
		__f.__assigner = ":";
	}

	return __f;
}