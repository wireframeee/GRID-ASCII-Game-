/*'X' is the player character and 'O' is the bullet character. Each iteration of the game loop is refered to as a frame since the screen also gets refreshed.
"Movement" is simulated by switching the character to be moved with the one "in front" of it. Game ends when player gets overlapped with bullet, this is reffered to as a collision.
The game is run by manipulating a 2-d array to simulate graphics. The formula for random number generation in a given range and the code to set default console size are not 
products of my own thinking.*/

#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
int px, py, score, hscore;

                    //------------------------ 2-d array that acts as the playing field
char screen[10][40] = {
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
    {"........................................"},
};

                    //------------------------ funtion to that moves the player
void move() {
    int f = 1;
    while (f == 1) {
        char inp = getch();
                        //------------------------ only allow 'w/a/s/d' as input, prevents other keys from triggering next frame
        if (inp == 'w' || inp == 'a' || inp == 's' || inp == 'd') {
                        //------------------------ switch case that moves player in the appropriate direction and updates player coords
            switch (inp) {
            case 'w':
                if (px == 1) {
                    break;
                }
                else {
                    screen[px - 1][py] = 'X';
                    screen[px][py] = '.';
                    px = px - 1;
                }
                break;

            case 'a':
                if (py == 1) {
                    break;
                }
                else {
                    screen[px][py - 1] = 'X';
                    screen[px][py] = '.';
                    py = py - 1;
                }
                break;

            case 's':
                if (px == 8) {
                    break;
                }
                else {
                    screen[px + 1][py] = 'X';
                    screen[px][py] = '.';
                    px = px + 1;
                }
                break;

            case 'd':
                if (py == 38) {
                    break;
                }
                else {
                    screen[px][py + 1] = 'X';
                    screen[px][py] = '.';
                    py = py + 1;
                }
                break;
            }
            f = 0;        
        }
    }
}

                    //------------------------ function to randomly generate bullet characters
void spawnbullets() {
    int num1,num2,num3,num4;
                    //------------------------ generates a random number within given lower and upper bounds using below formula
                    //------------------------ num = rand() % (upper - lower + 1) + lower
                    //------------------------ above formula is modified for easier calculations later
    num1 = rand() % (39 - 0 + 1);
    
    num2 = rand() % (78 - 40 + 1);

    num3 = rand() % (86 - 79 + 1);
    
    num4 = rand() % (94 - 87 + 1);
                    //------------------------ creates bullet character using number generated
    screen[0][num1] = 'i';
    screen[9][num2] = 'k';
    screen[num3][0] = 'j';
    screen[num4][39] = 'l';
}

                    //------------------------ function to display the screen along with its contents
void display() {
                    //------------------------ increment the score everytime the screen refreshes and print it along with hi-score
    score++;
    printf("SCORE : %d \t\t\t\t\t\t\t\t HI-SCORE : %d\n\n", score, hscore);
                    //------------------------ standard loop to print the screen
    for (int x= 0; x < 10; x++) {
        printf("      ");
        for (int y= 0; y < 40; y++) {
            if (x == 0 || x == 9 || y == 0 || y == 39) printf("."); //prints '.' on the edges of the screen to create a border
            else if (screen[x][y] == 'i' || screen[x][y] == 'j' || screen[x][y] == 'k' || screen[x][y] == 'l') printf("O"); //prints 'O' to replace the different buller characters
            else printf("%c", screen[x][y]);
            printf(" ");
        }
        printf("\n");
    }
                    //------------------------ prints instructions
    printf("\n\n\n__________________________________________________________________________________________\n\n\n\t\t   USE 'WASD' KEYS TO MOVE\n\t\t   DODGE THE BULLETS TO SURVIVE\n\n\t\t   REMEMBER TO KEEP TRACK OF THEM OR YOU WON'T KNOW\n\t\t   WHICH DIRECTION THEY ARE GOING IN");
}

                    //------------------------ function to move all bullets on screen
void update() {
                    //------------------------ an underlay to store if a given bullet has moved
    int uscreen[10][40] = {
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
        {0000000000000000000000000000000000000000},
    };
                    //------------------------ moves bullet characters
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 40; y++) {
            if (uscreen[x][y] == 0) {    
                if ((screen[x][y] == 'i') && (x != 9)) {
                    screen[x][y] = '.';
                    screen[x + 1][y] = 'i';
                    uscreen[x + 1][y] = 1;
                }
                if ((screen[x][y] == 'j') && (y != 39)) {
                    screen[x][y] = '.';
                    screen[x][y + 1] = 'j';
                    uscreen[x][y + 1] = 1;
                }
                if ((screen[x][y] == 'k') && (x != 0)) {
                    screen[x][y] = '.';
                    screen[x - 1][y] = 'k';
                    uscreen[x - 1][y] = 1;
                }
                if ((screen[x][y] == 'l') && (y != 0)) {
                    screen[x][y] = '.';
                    screen[x][y - 1] = 'l';
                    uscreen[x][y - 1] = 1;
                }
            }    
        }
    }
}

                    //------------------------ 2-d array that stores title screen name
char start[50][50] = {
{"..OOOOOO......OOOOOOOO.....OOOO....OOOOOOO..."},
{".OO....OO.....OO.....OO.....OO.....OO....OOO."},
{".OO...........OO.....OO.....OO.....OO.....OO."},
{".OO...OOOO....OOXOOOOO......OO.....OO.....OO."},
{".OO....OO.....OO...OO.......OO.....OO.....OO."},
{".OO....OO.....OO....OO......OO.....OO....OOO."},
{"..OOOOOO......OO.....OO....OOOO....OOOOOOO..."},                                
};

                    //------------------------ function to animate title screen name
void boot() {
                    //------------------------ standard loop, but prints increasing numbers of columns to "animate" title screen
    for (int m = 0; m <= 45; m++) {
        system("cls");
        printf("V1.2.0");
        for (int x = 0; x <= 10; x++) {
            printf("\t\t\t");
            for (int y = 0; y <= m; y++) {
                printf("%c", start[x][y]);
            }
            printf("\n");
        }
    }
}
                    //------------------------ Function that beeps (maybe use it to create music in the future)
void openm() {
    while (1)
    {
        Beep(350,300);
        Sleep(300);
    }
    
}

                    //------------------------ structure used for defining console size
struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};

                    //------------------------ main funtion (duh)
int main() {
                    //------------------------ creates file pointer for external file
    FILE *hiscore;
                    //------------------------ creates file if not present else edits available file
    if ((hiscore = fopen("hiscore.txt", "r")) == NULL) hiscore = fopen("hiscore.txt", "w+");
    else hiscore = fopen("hiscore.txt", "r");
    
    HANDLE wHnd;    // Handle to write to the console
    HANDLE rHnd;    // Handle to read from the console

                    //------------------------ Set up the handles for reading/writing
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
                    //------------------------ Change the window title
    SetConsoleTitle("GRID");
    
                    //------------------------ Create a COORD to hold the buffer size
    COORD bufferSize = {100, 100};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

                    //------------------------ Set up window size
    SMALL_RECT windowSize = {0, 0, 90, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    HANDLE Title, OpenM;

                    //------------------------ Make threads
    Title = CreateThread(NULL, 0, boot, NULL, 0, NULL);
    OpenM = CreateThread(NULL, 0, openm, NULL, 0, NULL);

                    //------------------------ Wait for them to finish
    WaitForSingleObject(Title, INFINITE);
    TerminateThread(OpenM, NULL);

    printf("\n\n\n\t\t\t\t    PRESS ENTER TO BEGIN");
                    //------------------------ only allows 'ENTER' button to start game
    int i;
    do
    {
        i = getch();
    } while (i != 13); // 13 is the value for 'ENTER'

    int reset = 1;
                    //------------------------ loop stays till user wants to exit in which case the value of reset will be changed
    while (reset = 1) {
                    //------------------------ sets seed based on current time to use in random number generation
        srand(time(0));
                    //------------------------ loads hi-score from external file
        fscanf(hiscore, "%d", &hscore);
        
        system("cls");
                    //------------------------ sets the defaults
        px = 5;
        py = 20;
        score = 0;
        int flag = 1;
                    //------------------------ for reseting the screen values
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 40; y++) {
                screen[x][y] = '.';
            }
        }
        screen[px][py] = 'X';

        display();
                    //------------------------ game loop begins
        while (flag == 1) {
                    //------------------------ move player, move current bullets, spawn new bullets, refesh screen (every frame)
            move();
            update();
            spawnbullets();
            system("cls");
            display();
            Beep(700,100);
                    //------------------------ checks if collision occurs (game over)
            flag = 0;
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 40; y++) {
                    if (screen[x][y] == 'X') flag = 1;
                }
            }
        }
        Beep(1000,500);
        system("cls");
                    //------------------------ saves externally if a new hi-score is made
        if (score > hscore) {
            printf("NEW HI-SCORE!! \n");
            hiscore = fopen("hiscore.txt", "w");
            hscore = score;
            fprintf(hiscore, "%d", hscore);
            fclose(hiscore);
            Sleep(2000);
        }

        system("cls");
                    //------------------------ sets default action as retry
        int choose = 1;

                    //------------------------ end screen
        printf("SCORE : %d \n", score);
        printf("GAME OVER \n");
        printf("  Retry\n  Exit\n\n\n");
                    //------------------------ print instructions
        printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");
                    //------------------------ choose between retry and exit
        while (1) {
            char key = getch();
            system("cls");
            printf("SCORE : %d \n", score);
            printf("GAME OVER \n");
                    //------------------------ UI for end screen using switch case
            if (key == 'w') {
                printf("> Retry \n");
                printf("  Exit \n\n\n");
                choose = 1;
            }
            else if (key == 's') {
                printf("  Retry \n");
                printf("> Exit \n\n\n");
                choose = 2;
            }
            else if (key == 13) {
                system("cls");
                if (choose == 1) break;
                else return 0;
            }
            else {
                if (choose == 1) {
                    printf("> Retry \n");
                    printf("  Exit \n\n\n");
                }
                else {
                    printf("  Retry \n");
                    printf("> Exit \n\n\n");
                }
            }
                    //------------------------ print instrctions
            printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");
        }
    }
}
