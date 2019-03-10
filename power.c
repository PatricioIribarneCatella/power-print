#include <stdio.h>
#include <string.h>

#define MAX_LEN 256
#define LINE_LEN 512
#define PATH "/sys/class/power_supply/axp288_fuel_gauge/uevent"

#define POWER_STATUS "POWER_SUPPLY_STATUS"
#define POWER_HEALTH "POWER_SUPPLY_HEALTH"
#define POWER_CAPACITY "POWER_SUPPLY_CAPACITY"
#define POWER_TECHNOLOGY "POWER_SUPPLY_TECHNOLOGY"

enum {
	INFO_STATUS = 0,
	INFO_HEALTH,
	INFO_CAPACITY,
	INFO_TECH
};

struct power_info {
	char status[MAX_LEN];
	char health[MAX_LEN];
	char capacity[MAX_LEN];
	char technology[MAX_LEN];
};

void find_info(char* path) {

}

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

	get_info(&info, PATH);
	
	print_info(&info);
}

int main(void) {

	power_print();

	return 0;
}

