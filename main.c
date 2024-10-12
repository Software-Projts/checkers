#include <stdio.h>

char board[8][8];
//Functions
char makeBoard(char even, char odd, int outIt, int inIt);
char assignPieceNum(char piece, int num);
int main() {
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                
                if((i == 6)) {
                    makeBoard('r', '2', i, j);
                }else if ((i==0)||(i==2)) {
                    makeBoard('b', ' ', i, j);
                }else {
                    makeBoard('1', ' ', i, j);
                }
            // 1, 3, 5, 7 rows
             }else {
                if((i == 7)||(i == 5)) {
                    makeBoard('2', 'r', i, j);
                }else if(i==1) {
                    makeBoard('2', 'b', i, j);
                }else {
                    makeBoard('2', '1', i, j);
                }
             }        
        }
        char out = assignPieceNum('w', 1);
        printf("%s", out);
        printf("\n");
    }
}

char makeBoard(char even, char odd, int outIt, int inIt) {
    if(inIt % 2 == 0) {
        board[outIt][inIt] = even;
        printf("%c  ", board[outIt][inIt]);
    }else {
        if(inIt != 7) {
            board[outIt][inIt] = odd;
            printf("%c  ", board[outIt][inIt]);
        }else {
            board[outIt][inIt] = odd;
            printf("%c", board[outIt][inIt]);
        }
    }
}

char assignPieceNum(char piece, int num) {
    char pieceNum[2];
    pieceNum[0] = piece;
    pieceNum[1] = num;
    return pieceNum; 
}

