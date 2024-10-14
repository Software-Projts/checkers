#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int piecNumber = 1;
char board[8][8][3];
char pieceAndNum[];
char playerTurn; //will hold 'b' or 'r' for whoevers turn in currently is
//add [] to board

//Functions
char makeBoard(char even, char odd, int outIt, int inIt);
void printBoard();
void turn();
void getUserInput();
int convertLetter(char a);
bool pieceCanMove(int row, int col, char playerT);

//Main function
int main() {
    //Sets black to have the first turn
    playerTurn = 'b';
    //Sets ups the board with pieces in place
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            //0, 2, 4, 6 rows
            if(i % 2 == 0) {
                
                if((i == 6)) {
                    makeBoard('r', '2', i, j);
                }else if ((i==0)||(i==2)) {
                    makeBoard('b', '2', i, j);
                }else {
                    makeBoard('1', '2', i, j);
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
        // r == 72
        // b == 62
        printf("\n");
    }
    printf("\n");
    //printBoard();
    turn();
}

char makeBoard(char even, char odd, int outIt, int inIt) {
    if(inIt % 2 == 0) {
        if(inIt != 7) {
            pieceAndNum[0] = odd;
            pieceAndNum[1] = '0' + inIt;
            pieceAndNum[2] = '\0';
            //printf("Combine char %s", pieceAndNum);
            strcpy(board[outIt][inIt], pieceAndNum);
            //printf("In board array %s", board[outIt][inIt]);
            printf("%s  ", board[outIt][inIt]);
        }else {
             board[outIt][inIt][0] = odd;
            printf("%s", board[outIt][inIt]);
        }
    }else {
        if(inIt != 7) {
            board[outIt][inIt][0] = even;
            printf("%s  ", board[outIt][inIt]);
        }else {
            board[outIt][inIt][0] = even;
            printf("%s", board[outIt][inIt]);
        }
    }
}

void printBoard() //for printing the board after every turn (we can add the graphics corresponding to values of the board later)
{
    printf("   a  b  c  d  e  f  g  h\n");
    printf("\n");
    for(int i=0; i<8; i++)
    {
        printf("%d  ", 8-i);
        for(int j=0; j<8;j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }

}

void turn()
{
    if(playerTurn =='b')
    {
        printf("It's Black's turn!\n");
        printf("Please enter the piece you want to move.\n");
        char input[3]; //used for initial location
        //char input2[3]; //will be used for the end location later
        getUserInput(input);
        int i= 7-(input[1]-'1');
        int j = convertLetter(input[0]);
    //checks and makes user reinput
    while(board[i][j] != 'b' || !(pieceCanMove(i, j, playerTurn)))
    {
        if(board[i][j] != 'b' )
        {
            printf("This is not your piece!\n");
            printf("The value at this spot is: %c\n", board[i][j]);
            printf("Please enter the location of the piece you'd like to move.\n");
            getUserInput(input);
            i= 7-(input[1]-'1');
            j = convertLetter(input[0]);
        }
        if(!(pieceCanMove(i, j, playerTurn)))
        {
            printf("This piece you chose cannot move.\n");
            printf("The value at this spot is: %c\n", board[i][j]);
            printf("Please enter a different location of the piece you'd like to move.\n");
            getUserInput(input);
            i= 7-(input[1]-'1');
            j = convertLetter(input[0]);
        }
    }
    if(board[i][j] == 'b')
    {
        printf("This is your piece!\n");
        printf("The value at this spot is: %c\n", board[i][j]);
        pieceCanMove(i, j, playerTurn);
    }
    

        
    }
    else
    {
        printf("It's Red's turn!\n");
    }
    
}
void getUserInput(char input[])
    {
    printf("Please enter the location in the form LetterNumber (EX: a5): ");
    scanf("%s", &input);
    printf("\nYou inputed: %s\n",input);
    while(!((input[0] >= 'a' && input[0] <= 'h') || (input[0] >= 'A' && input[0] <= 'H')) || !(input[1] >= '1' && input[1] <= '8'))
    {
        printf("Error please correct your input: ");
        scanf("%s", &input);
        printf("\nYou inputed: %s\n",input);
    }
    }
int convertLetter(char a) //converts the letter from location to its corresponding int value
{
   int j;
        if(a == 'a' ||a == 'A')
        {
            j=0;
        }
        else if(a == 'b' || a =='B')
        {
            j=1;
        }
        else if(a == 'c' ||a =='C')
        {
            j=2;
        }
        else if(a == 'd' ||a =='D')
        {
            j=3;
        }
        else if(a == 'e' ||a =='E')
        {
            j=4;
        }
        else if(a == 'f' ||a =='F')
        {
            j=5;
        }
        else if(a == 'g' ||a =='G')
        {
            j=6;
        }
        else if(a == 'h' ||a =='H')
        {
            j=7;
        } 
        return j;
}
bool pieceCanMove(int i, int j, char playerT)
{
    if(playerT == 'b')
    {
    if((board[i+1][j-1] == '1') || (board[i+1][j+1] == '1') || ((board[i+1][j-1] == 'r') && (board[i+2][j-2] == '1')) || (board[i+1][j+1] == 'r') && (board[i+2][j+2] == '1'))
    {
        printf("Has open spot to move!\n");
        return true;
    }
    }
    printf("Does not have open spot.\n");
    return false;
}

