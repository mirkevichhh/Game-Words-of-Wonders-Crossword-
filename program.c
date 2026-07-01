#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "curses.h"
#include "locale.h"
#include "time.h"

#define MAX_WORD_LENGTH 12
#define MAX_SIZE 17
#define MAX_WORDS 10
#define CELL_WIDTH 4
#define CELL_HEIGHT 2
#define MAX_INPUT_LEN 20


char game_board[MAX_SIZE][MAX_SIZE];
char guessed_words[MAX_WORDS][MAX_WORD_LENGTH];
int current_score = 0;
int current_size = 0;
int current_total_words = 0;
const char *current_available_letters = NULL;


time_t start_time;
long total_time_seconds;

const char *EASY_WORDS[] = {"PART", "ART", "RAT", "PAIR", "TRIP"};
const int EASY_R[] = {1, 0, 4, 1, 1};
const int EASY_C[] = {5, 1, 3, 3, 0};
const char EASY_D[] = {'V', 'V', 'H', 'V', 'H'};
const int EASY_LEN[] = {4, 3, 3, 4, 4};
const char *EASY_LETTERS = "P O T A R I";
const int EASY_COUNT = 5;
const int EASY_SIZE = 6;
const long EASY_TIME = 5 * 60;


const char *MEDIUM_WORDS[] = {"STRANGE", "GRANT", "ANGER", "RANG", "STAR", "REST", "AGE"};
const int MEDIUM_R[] = {1, 6, 5, 9, 1, 3, 8};
const int MEDIUM_C[] = {0, 0, 3, 3, 0, 0, 6};
const char MEDIUM_D[] = {'V', 'H', 'V', 'H', 'H', 'H', 'V'};
const int MEDIUM_LEN[] = {7, 5, 5, 4, 4, 4, 3};
const char *MEDIUM_LETTERS = "T A N E G S R";
const int MEDIUM_COUNT = 7;
const int MEDIUM_SIZE = 12;
const long MEDIUM_TIME = 4 * 60 + 30;

const char *HARD_WORDS[] = {"PROTAGONIST", "STATION", "PART", "POST", "STOP", "TANGO", "START", "GOAT", "TOP"};
const int HARD_R[] = {6, 1, 0, 15, 1, 3, 9, 3, 6};
const int HARD_C[] = {8, 1, 3, 6, 1, 3, 7, 6, 6};
const char HARD_D[] = {'V', 'H', 'V', 'H', 'V', 'H', 'H', 'V', 'H'};
const int HARD_LEN[] = {11, 7, 4, 4, 4, 5, 5, 4, 3};
const char *HARD_LETTERS = "R O T P A G N I S T O";
const int HARD_COUNT = 9;
const int HARD_SIZE = 17;
const long HARD_TIME = 4 * 60;
const char **active_words;
const int *active_rows;
const int *active_cols;
const char *active_dirs;
const int *active_lengths;


void ncurses_settings() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
}

int draw_menu() {
    int choice = 0;

    while (choice < '1' || choice > '3') {
        clear();
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw(6, 10, "   WELCOME TO THE \"Words of Wonders\" GAME  ");
        attroff(A_BOLD | COLOR_PAIR(1));

        mvprintw(10, 15, "Select Difficulty Mode (1-3):");

        mvprintw(12, 18, "1. EASY Mode : %d words - Time: 5:00",EASY_COUNT);
        mvprintw(13, 18, "2. MEDIUM Mode : %d words - Time: 4:30",MEDIUM_COUNT);
        mvprintw(14, 18, "3. HARD Mode : %d words - Time: 4:00",HARD_COUNT);

        mvprintw(16, 15, "Your choice: ");
        refresh();

        choice = getch();
    }
    mvaddch(16, 15 + strlen("Your choice: "), choice);
    refresh();
    timeout(500);
    getch();
    timeout(-1);

    return choice - '0';
}

void definition(int mode) {
    if (mode == 1) {
        current_size = EASY_SIZE;
        current_total_words = EASY_COUNT;
        current_available_letters = EASY_LETTERS;
        active_words = EASY_WORDS;
        active_rows = EASY_R;
        active_cols = EASY_C;
        active_dirs = EASY_D;
        active_lengths = EASY_LEN;
        total_time_seconds = EASY_TIME;
    } else if (mode == 2) {
        current_size = MEDIUM_SIZE;
        current_total_words = MEDIUM_COUNT;
        current_available_letters = MEDIUM_LETTERS;
        active_words = MEDIUM_WORDS;
        active_rows = MEDIUM_R;
        active_cols = MEDIUM_C;
        active_dirs = MEDIUM_D;
        active_lengths = MEDIUM_LEN;
        total_time_seconds = MEDIUM_TIME;
    } else if (mode == 3) {
        current_size = HARD_SIZE;
        current_total_words = HARD_COUNT;
        current_available_letters = HARD_LETTERS;
        active_words = HARD_WORDS;
        active_rows = HARD_R;
        active_cols = HARD_C;
        active_dirs = HARD_D;
        active_lengths = HARD_LEN;
        total_time_seconds = HARD_TIME;
    }
}

void initialize_board() {

    for (int i = 0; i < current_size; i++) {
        for (int j = 0; j < current_size; j++) {
            game_board[i][j] = '\0';
        }
    }

    for (int k = 0; k < current_score; k++) {
        const char *current_guessed = guessed_words[k];

        for (int i = 0; i < current_total_words; i++) {
            if (strcmp(current_guessed, active_words[i]) == 0) {
                for (int l = 0; l < active_lengths[i]; l++) {
                    int r = active_rows[i];
                    int c = active_cols[i];

                    if (active_dirs[i] == 'H') {
                        game_board[r][c + l] = current_guessed[l];
                    } else if (active_dirs[i] == 'V') {
                        game_board[r + l][c] = current_guessed[l];
                    }
                }
                break;
            }
        }
    }
}

bool is_word_guessed(const char *word) {
    for (int i = 0; i < current_score; i++) {
        if (strcmp(word, guessed_words[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_part_of_any_word(int r, int c) {
    for (int i = 0; i < current_total_words; i++) {
        int start_r = active_rows[i];
        int start_c = active_cols[i];
        int length = active_lengths[i];
        char dir = active_dirs[i];

        if (dir == 'H') {
            if (r == start_r && c >= start_c && c < start_c + length) {
                return true;
            }
        } else if (dir == 'V') {
            if (c == start_c && r >= start_r && r < start_r + length) {
                return true;
            }
        }
    }
    return false;
}

void draw_cell(int r, int c, char letter) {
    int start_y = r * (CELL_HEIGHT - 1) + 2;
    int start_x = c * CELL_WIDTH + 2;

    if (is_part_of_any_word(r, c)) {
        attron(COLOR_PAIR(1));
        mvaddch(start_y, start_x, '|');
        mvaddch(start_y, start_x + 2, '|');
        attroff(COLOR_PAIR(1));
        if (letter != '\0') {
            attron(A_BOLD | COLOR_PAIR(2));
            mvaddch(start_y, start_x + 1, letter);
            attroff(A_BOLD | COLOR_PAIR(2));
        } else {
             mvaddch(start_y, start_x + 1, ' ');
        }
    }
}


void draw_board() {
    clear();
    time_t current_time = time(NULL);
    long elapsed_time = (long)difftime(current_time, start_time);
    long time_left = total_time_seconds - elapsed_time;

    int minutes = time_left / 60;
    int seconds = time_left % 60;


    attron(A_BOLD);
    mvprintw(0, 0, "| WORDS GUESSED: %d/%d |",current_score, current_total_words);
    attroff(A_BOLD);
    attron(A_BOLD | COLOR_PAIR(4));
    mvprintw(0, COLS - 20, "TIME LEFT: %02d:%02d", minutes, seconds);
    attroff(A_BOLD | COLOR_PAIR(4));
    for (int i = 0; i < current_size; i++) {
        for (int j = 0; j < current_size; j++) {
            draw_cell(i, j, game_board[i][j]);
        }
    }
}

void draw_message(const char* message) {
    int input_row = current_size * (CELL_HEIGHT - 1) + 4;
    int input_col = 3;

    move(input_row, 0);
    clrtoeol();
    move(input_row + 1, 0);
    clrtoeol();
    move(input_row + 2, 0);
    clrtoeol();
    move(input_row + 3, 0);
    clrtoeol();
    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(input_row, input_col, "AVAILABLE LETTERS: %s", current_available_letters);
    attroff(A_BOLD | COLOR_PAIR(3));
    mvprintw(input_row + 1, input_col, "Message from admin: %s", message);
    mvprintw(input_row + 2, input_col, "Enter word (EXIT to quit): ");

    refresh();
}

void let_the_game_begin() {
    char input_word[MAX_INPUT_LEN] = {0};
    WINDOW *input_win;
    int input_row = current_size * (CELL_HEIGHT - 1) + 6;
    int input_col = 3 + 27;
    input_win = newwin(1, MAX_INPUT_LEN, input_row, input_col);
    keypad(input_win, TRUE);

    start_time = time(NULL);

    while (current_score < current_total_words) {
        time_t current_time = time(NULL);
        long elapsed_time = (long)difftime(current_time, start_time);
        long time_left = total_time_seconds - elapsed_time;

        if (time_left <= 0) {
            draw_board();
            draw_message(" TIME'S UP! Game Over.");
            timeout(2000);
            getch();
            break;
        }
        draw_board();
        draw_message("...");
        wtimeout(input_win, 1000);
        wmove(input_win, 0, 0);
        wclrtobot(input_win);
        echo();
        int result = wgetnstr(input_win, input_word, MAX_INPUT_LEN - 1);
        noecho();
        if (result == ERR || strlen(input_word) == 0) {

            continue;
        }

        move(current_size * (CELL_HEIGHT - 1) + 6, 3);
        clrtoeol();
        for (int i = 0; input_word[i]; i++) {
            input_word[i] = toupper(input_word[i]);
        }

        if (strcmp(input_word, "EXIT") == 0) {
            break;
        }

        bool found = false;

        for (int i = 0; i < current_total_words; i++) {
            if (strcmp(input_word, active_words[i]) == 0) {
                found = true;

                if (!is_word_guessed(input_word)) {
                    strcpy(guessed_words[current_score], input_word);
                    current_score++;

                    initialize_board();
                    draw_board();
                    draw_message(" Correct! Word recorded.");
                    break;
                } else {
                    draw_message(" Word already guessed!");
                    break;
                }
            }
        }
        if (!found) {
            draw_message(" Incorrect word or not in the solution list.");
        }
        timeout(1000);
        getch();
        timeout(-1);
        memset(input_word, 0, MAX_INPUT_LEN);
    }

    if (input_win != NULL) {
        delwin(input_win);
    }
    clear();
    long final_time_left = total_time_seconds - (long)difftime(time(NULL), start_time);
    if (current_score == current_total_words) {
        mvprintw(5, 5, " CONGRATULATIONS! You guessed all %d words! ", current_total_words);
    } else if (final_time_left <= 0) {
        mvprintw(5, 5, " TIME IS UP! Final Score: %d/%d.", current_score, current_total_words);
    } else {
        mvprintw(5, 5, "Thank you for playing! Final Score: %d/%d.", current_score, current_total_words);
    }
    refresh();
    getch();
}

int main() {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    ncurses_settings();
    int mode = draw_menu();
    definition(mode);
    current_score = 0;
    initialize_board();
    let_the_game_begin();
    endwin();
    return 0;
}