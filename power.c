#include "includes.h"

// Use config file 
// to get path to
// POWER SUPPLY information
//
void find_info(char* bat_path) {

	char buf[MAX_LEN] = {0};
	char key[MAX_LEN] = {0};
	char value[MAX_LEN] = {0};
	char config_path[MAX_LEN] = {0};
	char config_file_path[MAX_LEN * 2] = {0};

	char* env_config;
	char* home;

	// First, looks if the
	// environment variable: POWPRINTPATH
	// is set
	env_config = getenv("POWPRINTPATH");

	if (env_config)
		strcpy(config_path, env_config);
	else {
		home = getenv("HOME");
		snprintf(config_path, sizeof config_path, "%s/%s", home, CONFIG_DEF_PATH);
	}

	snprintf(config_file_path, sizeof config_file_path, "%s/%s", config_path, CONFIG_FILE);

	FILE* fp = fopen(config_file_path, "r");

	if (fp == NULL) {
		perror("configuration file ");
		_exit(EXIT_FAILURE);
	}

	fgets(buf, sizeof buf, fp);

	parse_line(buf, key, value);

	if (strcmp(key, "PATH") == 0)
		strcpy(bat_path, value);
}

//
// Reads the file in 'path' for information
// about the battery, and stores it in the 
// 'info' struct
//
void get_info(struct power_info* info, char* path) {

	char buf[LINE_LEN] = {0};
	char key[MAX_LEN] = {0};
	char value[MAX_LEN] = {0};

	FILE* file = fopen(path, "r");

	while (fgets(buf, sizeof buf, file) != NULL) {

		parse_line(buf, key, value);

		store_info(info, key, value);
	}
}

//
// Prints final information
//
void print_info(struct power_info* info) {

	printf("Power Information: STATUS:[%s] CAPACITY:[%s] HEALTH:[%s] TECH:[%s]\n",
			info->status,
			info->capacity,
			info->health,
			info->technology);
}

void power_print() {

	char path[MAX_LEN] = {0};
	struct power_info info = {0};

	find_info(path);

	get_info(&info, path);
	
	print_info(&info);
}

