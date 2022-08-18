#include "../h/console.h"

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void print_char(char character){
    buffer[col + NUM_COLS * row] = (struct Char){
        character,
        color
    };
    col++;
    if(col > NUM_COLS) print_newline();
}

void print_backspace(){
    col--;
    buffer[col + NUM_COLS * row] = (struct Char){
        ' ',
        color
    };
}

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        ' ',
        color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS - 1) {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_str(char* str) {
    char *ptr = str;
    while(*ptr != '\0'){
        print_char(*(ptr++));
    }
}

void print(char* format, char* args[], int n){
    int arg_cnt = 0;
    char *ptr = format;
    while(*ptr){
        if(*ptr == '$' && arg_cnt < n) print_str(args[arg_cnt++]);
        else print_char(*ptr);
        ptr++;
    }
}

void print_str_len(char* str, size_t length) {
    for (size_t i = 0; i < length; i++) {
        char character = (uint8_t) str[i];
        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}
