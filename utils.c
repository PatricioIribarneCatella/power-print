#include <string.h>
#include "defs.h"

//
// Translate string 'key' to a number code
//
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

//
// Stores 'value' in the struct 'info'
// by 'key'
//
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

