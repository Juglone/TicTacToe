#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_board(char* state) {
    char* board = "\
┏━━━┳━━━┳━━━┓\n\
┃ x ┃ x ┃ x ┃\n\
┣━━━╋━━━╋━━━┫\n\
┃ x ┃ x ┃ x ┃\n\
┣━━━╋━━━╋━━━┫\n\
┃ x ┃ x ┃ x ┃\n\
┗━━━┻━━━┻━━━┛\n";
    do {
        if (*board == 'x') {
            putchar(*state++);
        } else {
            putchar(*board);
        }
    } while (*(++board));
}

int get_input_pos(const char current_state[9], char sign, char target, const char* question) {
    int pos;
    printf("Spelare %c, vilken ruta vill du flytta ditt %c %s ", sign, sign, question);
    fflush(stdout);
    while(!scanf("%i", &pos) || !(0 <= --pos && pos < 9) || current_state[pos] != target) {
        while ((getchar()) != '\n');
        fputs("Platsen du angav var inte giltig, var vänlig försök igen. ", stdout);
        fflush(stdout);
    }
    return pos;
}

const uint16_t winning_lines[8] = {0b111000000, 0b000111000, 0b000000111,
                                   0b100100100, 0b010010010, 0b001001001,
                                   0b100010001, 0b001010100};

uint16_t owned(const char* state, char sign) {
    uint16_t bitset = 0;
    for (int i = 0; i < 9; i++) {
        if (state[i] == sign) {
            bitset++;
        } bitset *= 2;
    }
    return bitset;
}

int main() {
    char current_state[9];
    for (int i = 0; i < 9; i++) current_state[i] = ' ';

    puts("Såhär ser din spelplan ut: ");
    print_board("123456789");
    puts("Nu börjar det, håll i er! :)");


    for (int i = 0;; i++) {
        const char sign = (i % 2 == 0) ? 'O' : 'X';

        if (i < 6) {
            int move_to = get_input_pos(current_state, sign, ' ', "till? Skriv ett tal mellan 1-9:");
            current_state[move_to] = sign;
        } else {
            int move_from = get_input_pos(current_state, sign, sign, "ifrån?");
            int move_to = get_input_pos(current_state, sign, ' ', "till?");
            current_state[move_from] = ' ';
            current_state[move_to] = sign;
        }

        print_board(current_state);

        for(int j = 0; j < 8; j++) {
            if (owned(current_state, sign) == winning_lines[i]) {
                return 0;
            }
        }
    }
}
