//
// Parse a 'line' and split it by the '=' char
//
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

