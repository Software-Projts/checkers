#include <stdio.h>

int board[8][8];

int main() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = 1;
        }
    }
    printf("%d", board);

}
