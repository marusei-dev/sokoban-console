/*
	SOKOBAN Console by Marsel Yuldashev
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// structure that contains info about the currently loaded profile 
typedef struct Profile_Info {
	char name[20];
	int max_level;
	int min_steps[3];
} profile_info_t;

// structure that contains coordinates of the player, or any coordinates
typedef struct Position {
	int row;
	int column;
} position_t;

// function that prints the title
void print_title() {
	printf("SOKOBAN\n\n");
}

// function that prints the main menu of the game
void main_menu() {
	printf("1. NEW GAME\n");
	printf("2. CHOOSE LEVEL\n");
	printf("3. SAVE PROFILE\n");
	printf("4. LOAD PROFILE\n");
	printf("5. PROFILE INFO\n");
	printf("0. QUIT GAME\n");
	printf("--->: ");
}

// function that saves progress to the file indicated by the user
void save_progress_to_file(profile_info_t profile_info) {
	int profile_name_length = strlen(profile_info.name);
	char* file_name = (char*)malloc((profile_name_length + 5) * sizeof(char));
	int i = 0;
	while (profile_info.name[i] != '\0') {
		file_name[i++] = profile_info.name[i];
	}
	file_name[i] = '.';
	file_name[i+1] = 't';
	file_name[i+2] = 'x';
	file_name[i+3] = 't';
	file_name[i + 4] = '\0';
	FILE* fp;
	fp = fopen(file_name, "w");
	fprintf(fp, "max_level=%d name=%s min_steps=%d,%d,%d", profile_info.max_level, profile_info.name, profile_info.min_steps[0], profile_info.min_steps[1], profile_info.min_steps[2]);
	fclose(fp);
	free(file_name);
}

// function that loads progress from the file indicated by the user
int load_progress_from_file(profile_info_t* profile_info, char* profile_name) {
	char* file_name = (char*)malloc((strlen(profile_name) + 5) * sizeof(char));
	int i = 0;
	while (profile_name[i] != '\0') {
		file_name[i++] = profile_name[i];
	}
	file_name[i] = '.';
	file_name[i + 1] = 't';
	file_name[i + 2] = 'x';
	file_name[i + 3] = 't';
	file_name[i + 4] = '\0';
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp == NULL)
		return 0;
	else {
		fscanf(fp, "max_level=%d name=%s min_steps=%d,%d,%d", &profile_info->max_level, &profile_info->name, &profile_info->min_steps[0], &profile_info->min_steps[1], &profile_info->min_steps[2]);
		fclose(fp);
		return 1;
	}
	free(file_name);
}

// function that displays a message about incorrect input
void incorrect_input_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("INCORRECT INPUT\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("INCORRECT INPUT\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays a message about successful load from file
void successful_load_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("LOAD SUCCESSFUL\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("LOAD SUCCESSFUL\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays a message about succesful save to file
void successful_save_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("SAVE SUCCESSFUL\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("SAVE SUCCCESSFUL\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays a message about failed load from file
void unsuccessful_load_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("LOAD FAILED\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("LOAD FAILED\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays a message about a cleared level
void level_clear_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("LEVEL CLEAR\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("LEVEL CLEAR\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays a new record message
void new_record_message() {
	system("cls");
	int msec = 0, msec_trigger = 500;
	clock_t before_1 = clock();
	printf("NEW RECORD\n");
	do {
		clock_t difference = clock() - before_1;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	system("cls");
	clock_t before_2 = clock();
	do {
		clock_t difference = clock() - before_2;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
	printf("NEW RECORD\n");
	clock_t before_3 = clock();
	do {
		clock_t difference = clock() - before_3;
		msec = difference * 1000 / CLOCKS_PER_SEC;
	} while (msec < msec_trigger);
}

// function that displays information about the currently loaded profile
void profile_info_display(profile_info_t profile_info) {
	fseek(stdin, 0, SEEK_END);
	system("cls");
	printf("PROFILE INFO\n\n");
	printf("NAME: %s\n", profile_info.name);
	printf("MAX LEVEL: %d\n\n", profile_info.max_level);
	printf("MINIMAL STEPS:\n");
	int min_steps;
	for (int i = 0; i < 3; i++) {
		if (profile_info.min_steps[i] == 1000)
			min_steps = 0;
		else
			min_steps = profile_info.min_steps[i];
		printf("LEVEL %d: %d\n", i + 1, min_steps);
	}
	printf("\n");
	printf("Press Enter to return back\n");
	printf("--->: ");
	char c;
	while (scanf("%c", &c) == 1 && c != '\n');
}

// function that displays choose level menu
void choose_level_menu_display(profile_info_t profile_info) {
	fseek(stdin, 0, SEEK_END);
	system("cls");
	printf("CHOOSE LEVEL\n\n");
	int i = 1;
	for (; i <= profile_info.max_level; i++) {
		printf("%d. LEVEL %d\n", i, i);
	}
	printf("--->: ");
}

// function that draws map from 2D matrix
void draw_map(int level[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (level[i][j]) {
			case 0:
				printf(" ");
				break;
			case 1:
				printf("#");
				break;
			case 9:
				printf("0");
				break;
			case 5:
				printf("m");
				break;
			case 8:
				printf("v");
				break;
			}
		}
		printf("\n");
	}
}

// function that finds player's position
position_t find_player_position(int level[10][10]) {
	position_t player_position;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (level[i][j] == 9) {
				player_position.row = i;
				player_position.column = j;
			}
		}
	}
	return player_position;
}

// function that checks whether there are any boxes left on the map
bool boxes_left(int level[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (level[i][j] == 5)
				return true;
		}
	}
	return false;
}

// the main function of the game. reads input from the user about the directions and updates the currently loaded profile's information.
int game_engine(profile_info_t* profile_info, int level[10][10], int level_num) {
	bool level_closed = false;
	int game_result;
	int steps_num = 0;
	bool target_stepped_on = false;
	int level_copy[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			level_copy[i][j] = level[i][j];
		}
	}
	position_t player_position = find_player_position(level);
	while (!level_closed) {
		fseek(stdin, 0, SEEK_END);
		system("cls");
		char c;
		printf("LEVEL %d\n\n", level_num);
		draw_map(level_copy);
		printf("\n");
		printf("# OF STEPS: %d\n", steps_num);
		if (profile_info->min_steps[level_num-1] == 1000)
			printf("NO RECORD YET\n");
		else
			printf("BEST RECORD: %d\n", profile_info->min_steps[level_num - 1]);
		printf("--->: ");
		scanf("%c", &c);
		while (c != 'w' && c != 'a' && c != 's' && c != 'd' && c != '0') {
			incorrect_input_message();
			system("cls");
			printf("LEVEL %d\n\n", level_num);
			draw_map(level_copy);
			printf("\n");
			printf("--->: ");
			scanf("%c", &c);
		}
		if (c == '0') {
			level_closed = true;
		}
		else if (c == 'a') {
			if (level_copy[player_position.row][player_position.column - 1] == 5 && level_copy[player_position.row][player_position.column - 2] != 1) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row][player_position.column - 1] == 8)
					target_stepped_on = true;
				level_copy[player_position.row][player_position.column - 1] = 9;
				if (level_copy[player_position.row][player_position.column - 2] != 8)
					level_copy[player_position.row][player_position.column - 2] = 5;
				player_position.column -= 1;
			}
			else if (player_position.column > 1 && level_copy[player_position.row][player_position.column - 1] != 1 && level_copy[player_position.row][player_position.column - 1] != 5) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row][player_position.column - 1] == 8)
					target_stepped_on = true;
				level_copy[player_position.row][player_position.column - 1] = 9;
				player_position.column -= 1;
			}
			steps_num++;
		}
		else if (c == 'd') {
			if (level_copy[player_position.row][player_position.column + 1] == 5 && level_copy[player_position.row][player_position.column + 2] != 1) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row][player_position.column + 1] == 8)
					target_stepped_on = true;
				level_copy[player_position.row][player_position.column + 1] = 9;
				if (level_copy[player_position.row][player_position.column + 2] != 8)
					level_copy[player_position.row][player_position.column + 2] = 5;
				player_position.column += 1;
			}
			else if (player_position.column < 9 && level_copy[player_position.row][player_position.column + 1] != 1 && level_copy[player_position.row][player_position.column + 1] != 5) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row][player_position.column + 1] == 8)
					target_stepped_on = true;
				level_copy[player_position.row][player_position.column + 1] = 9;
				player_position.column += 1;
			}
			steps_num++;
		}
		else if (c == 'w') {
			if (level_copy[player_position.row - 1][player_position.column] == 5 && level_copy[player_position.row - 2][player_position.column] != 1) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row - 1][player_position.column] == 8)
					target_stepped_on = true;
				level_copy[player_position.row - 1][player_position.column] = 9;
				if (level_copy[player_position.row - 2][player_position.column] != 8)
					level_copy[player_position.row - 2][player_position.column] = 5;
				player_position.row -= 1;
			}
			else if (player_position.row > 1 && level_copy[player_position.row - 1][player_position.column] != 1 && level_copy[player_position.row - 1][player_position.column] != 5) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row - 1][player_position.column] == 8)
					target_stepped_on = true;
				level_copy[player_position.row - 1][player_position.column] = 9;
				player_position.row -= 1;
			}
			steps_num++;
		}
		else if (c == 's') {
			if (level_copy[player_position.row + 1][player_position.column] == 5 && level_copy[player_position.row + 2][player_position.column] != 1) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row + 1][player_position.column] == 8)
					target_stepped_on = true;
				level_copy[player_position.row + 1][player_position.column] = 9;
				if (level_copy[player_position.row + 2][player_position.column] != 8)
					level_copy[player_position.row + 2][player_position.column] = 5;
				player_position.row += 1;
			}
			else if (player_position.row < 9 && level_copy[player_position.row + 1][player_position.column] != 1 && level_copy[player_position.row + 1][player_position.column] != 5) {
				if (target_stepped_on) {
					level_copy[player_position.row][player_position.column] = 8;
					target_stepped_on = false;
				}
				else
					level_copy[player_position.row][player_position.column] = 0;
				if (level_copy[player_position.row + 1][player_position.column] == 8)
					target_stepped_on = true;
				level_copy[player_position.row + 1][player_position.column] = 9;
				player_position.row += 1;
			}
			steps_num++;
		}
		if (!boxes_left(level_copy)) {
			level_clear_message();
			level_closed = true;
			if (profile_info->max_level == level_num)
				profile_info->max_level++;
			if (profile_info->min_steps[level_num - 1] > steps_num) {
				profile_info->min_steps[level_num - 1] = steps_num;
				new_record_message();
			}
		}
	}
}

int main(void)
{
	bool app_closed = false;
	char c;
	int n, d;
	char profile_name[20];
	profile_info_t profile_info;
	profile_info.max_level = 1;
	strcpy(profile_info.name, "GUEST");
	profile_info.name[5] = '\0';
	profile_info.min_steps[0] = 1000;
	profile_info.min_steps[1] = 1000;
	profile_info.min_steps[2] = 1000;

	int level_database[3][10][10] = {
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 5, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 8, 0, 5, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 9, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 5, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		},
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 8, 0, 5, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 9, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 5, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		},
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 8, 0, 5, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 9, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 5, 0, 1},
			{1, 1, 5, 0, 0, 0, 0, 5, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 5, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		}
	};

	// Main menu
	while (!app_closed) {
		fseek(stdin, 0, SEEK_END);
		system("cls");
		print_title();
		main_menu();
		scanf("%c", &c);
		while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '0') {
			incorrect_input_message();
			system("cls");
			main_menu();
			scanf("%c", &c);
		}
		n = c - '0';
		switch (n) {
		case 1:
			profile_info.max_level = 1;
			profile_info.min_steps[0] = 1000;
			profile_info.min_steps[1] = 1000;
			profile_info.min_steps[2] = 1000;
			game_engine(&profile_info, level_database[0], 1);
			break;
		case 2:
			fseek(stdin, 0, SEEK_END);
			choose_level_menu_display(profile_info);
			if (scanf("%c", &c) == 1) {
				d = c - '0';
				if (d > profile_info.max_level || d <= 0)
					incorrect_input_message();
				else
					game_engine(&profile_info, level_database[d - 1], d);
			}
			else
				incorrect_input_message();
			break;
		case 3:
			system("cls");
			printf("SAVE PROFILE\n");
			printf("Enter profile name (max 20 characters)\n");
			printf("--->: ");
			scanf("%s", profile_name);
			strcpy(profile_info.name, profile_name);
			save_progress_to_file(profile_info);
			successful_save_message();
			break;
		case 4:
			system("cls");
			printf("LOAD PROFILE\n");
			printf("Enter profile name (max 20 characters)\n");
			printf("--->: ");
			scanf("%s", profile_name);
			if (load_progress_from_file(&profile_info, profile_name))
				successful_load_message();
			else
				unsuccessful_load_message();
			break;
		case 5:
			profile_info_display(profile_info);
			break;
		case 0:
			app_closed = true;
			break;
		}
	}
	return 0;
}