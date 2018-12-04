typedef struct _frontmatter_type_obj {
	std::string __open_divider;
	std::string __close_divider;
	std::string __tab;
	std::string __assigner;
	std::string __type;
}
frontmatter_type;

frontmatter_type init(std::string __fm_type) {
	frontmatter_type __f;

	if (__fm_type == "YAML" || __fm_type == "yaml") {
		__f.__open_divider = "---";
		__f.__close_divider = "---";
		__f.__tab = "";
		__f.__assigner = ":";
	}
	else if (__fm_type == "TOML" || __fm_type == "toml") {
		__f.__open_divider = "+++";
		__f.__close_divider = "+++";
		__f.__tab = "";
		__f.__assigner = "=";
	}
	else if (__fm_type == "JSON" || __fm_type == "json") {
		__f.__open_divider = "{";
		__f.__close_divider = "}";
		__f.__tab = "\t";
		__f.__assigner = ":";
	}

	return __f;
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
