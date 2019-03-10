#include "includes.h"

void parse_line(char* line, char* key, char* value) {

	int i = 0, j = 0;

	while (line[i] != '=') {
		key[i] = line[i];
		i++;
	}

	key[i] = '\0';

	i++;

	while (line[i] != '\n') {
		value[j] = line[i];
		i++; j++;
	}

	value[j] = '\0';
}

// Use config file 
// to get path to
// POWER SUPPLY information
//
void find_info(char* path) {

	char config[MAX_LEN] = {0};
	char buf[MAX_LEN] = {0};
	char key[MAX_LEN] = {0};
	char value[MAX_LEN] = {0};

	char* home =  getenv("HOME");
	
	snprintf(config, sizeof config, "%s/%s", home, CONFIG_FILE);

	FILE* fp = fopen(config, "r");

	if (fp == NULL) {
		perror("configuration file ");
		_exit(EXIT_FAILURE);
	}

	fgets(buf, sizeof buf, fp);

	parse_line(buf, key, value);

	if (strcmp(key, "PATH") == 0)
		strcpy(path, value);
}

int get_code(char* key) {

	if (strcmp(key, POWER_STATUS) == 0)
		return INFO_STATUS;
	if (strcmp(key, POWER_HEALTH) == 0)
		return INFO_HEALTH;
	if (strcmp(key, POWER_CAPACITY) == 0)
		return INFO_CAPACITY;
	if (strcmp(key, POWER_TECHNOLOGY) == 0)
		return INFO_TECH;
	return -1;
}

void store_info(struct power_info* info, char* key, char* value) {

	int code = get_code(key);

	switch (code) {
		case INFO_STATUS:
			strcpy(info->status, value);
			break;
		case INFO_HEALTH:
			strcpy(info->health, value);
			break;
		case INFO_CAPACITY:
			strcpy(info->capacity, value);
			break;
		case INFO_TECH:
			strcpy(info->technology, value);
			break;
	}
}

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

void print_info(struct power_info* info) {

	printf("Power Information: STATUS:[%s] CAPACITY:[%s] HEALTH:[%s] TECH:[%s]\n",
			info->status,
			info->capacity,
			info->health,
			info->technology);
}

void power_print() {

	char path[MAX_LEN] = {0};
	struct power_info info;

	find_info(path);

	get_info(&info, path);
	
	print_info(&info);
}

