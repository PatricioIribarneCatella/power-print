#ifndef DEFS_H
#define DEFS_H

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

#endif // DEFS_H

