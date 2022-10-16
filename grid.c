#include <stdio.h>
#include <Windows.h>
#include <time.h>
int px, py, score;

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

void move() {#include <stdio.h>
#include <Windows.h>
#include <time.h>
int px, py, score, hscore;

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

void move() {
    char inp = getch();

    if (inp == 'w' || inp == 'a' || inp == 's' || inp == 'd') {
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
    }
}

void spawnbullets() {
    int num1,num2,num3,num4;
    //num = rand() % (upper - lower + 1) + lower;
    num1 = rand() % (39 - 0 + 1);
    
    num2 = rand() % (78 - 40 + 1);

    num3 = rand() % (86 - 79 + 1);
    
    num4 = rand() % (94 - 87 + 1);

    screen[0][num1] = 'i';
    screen[9][num2] = 'k';
    screen[num3][0] = 'j';
    screen[num4][39] = 'l';
}

void display() {
    score++;
    printf("SCORE : %d \t\t\t\t\t\t\t\t HI-SCORE : %d\n\n", score, hscore);
    for (int x= 0; x < 10; x++) {
        printf("      ");
        for (int y= 0; y < 40; y++) {
            if (x == 0 || x == 9 || y == 0 || y == 39) printf(".");
            else if (screen[x][y] == 'i' || screen[x][y] == 'j' || screen[x][y] == 'k' || screen[x][y] == 'l') printf("O");
            else printf("%c", screen[x][y]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n\n\n__________________________________________________________________________________________\n\n\n\t\t   USE 'WASD' KEYS TO MOVE\n\t\t   DODGE THE BULLETS TO SURVIVE\n\n\t\t   REMEMBER TO KEEP TRACK OF THEM OR YOU WON'T KNOW\n\t\t   WHICH DIRECTION THEY ARE GOING IN");
}

void update() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 'i') screen[x][y] = 't';
            if (screen[x][y] == 'j') screen[x][y] = 'f';
            if (screen[x][y] == 'k') screen[x][y] = 'g';
            if (screen[x][y] == 'l') screen[x][y] = 'h';
        }
    }
    
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 't') {
                screen[x][y] = '.';
                screen[x + 1][y] = 'i';
            }
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 39; y++) {
            if (screen[x][y] == 'f') {
                screen[x][y] = '.';
                screen[x][y + 1] = 'j';
            }
        }
    }
    for (int x = 1; x < 10; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 'g') {
                screen[x][y] = '.';
                screen[x - 1][y] = 'k';
            }
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int y = 1; y < 40; y++) {
            if (screen[x][y] == 'h') {
                screen[x][y] = '.';
                screen[x][y - 1] = 'l';
            }
        }
    }
}

char start[50][50] = {
{"..OOOOOO......OOOOOOOO.....OOOO....OOOOOOO..."},
{".OO....OO.....OO.....OO.....OO.....OO....OOO."},
{".OO...........OO.....OO.....OO.....OO.....OO."},
{".OO...OOOX....OOOOOOOO......OO.....OO.....OO."},
{".OO....OO.....OO...OO.......OO.....OO.....OO."},
{".OO....OO.....OO....OO......OO.....OO....OOO."},
{"..OOOOOO......OO.....OO....OOOO....OOOOOOO..."},                                
};

void boot() {
    for (int m = 0; m <= 45; m++) {
        system("cls");
        for (int x = 0; x <= 10; x++) {
            printf("\t\t\t");
            for (int y = 0; y <= m; y++) {
                printf("%c", start[x][y]);
            }
            printf("\n");
        }
        Sleep(0.1);
    }
}

struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};

int main() {
    srand(time(0));
    FILE *hiscore;
    if ((hiscore = fopen("hiscore.txt", "r")) == NULL) hiscore = fopen("hiscore.txt", "w+");
    else hiscore = fopen("hiscore.txt", "r");
    
    HANDLE wHnd;    // Handle to write to the console
    HANDLE rHnd;    // Handle to read from the console.

    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("GRID");
    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {100, 100};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 90, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    boot();
    printf("\n\n\n\t\t\t\t    PRESS ENTER TO BEGIN");

    int i;
    do
    {
        i = getch();
    } while (i != 13);
    
    int reset = 1;

    while (reset = 1) {
        fscanf(hiscore, "%d", &hscore);

        system("cls");
        
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 40; y++) {
                screen[x][y] = '.';
            }
        }
        
        system("cls");

        px = 5;
        py = 20;
        score = 0;
        screen[px][py] = 'X';
        int flag = 1;

        display();

        while (flag == 1) {
            move();
            update();
            system("cls");
            spawnbullets();
            display();

            flag = 0;
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 40; y++) {
                    if (screen[x][y] == 'X') flag = 1;
                }
            }
        }

        system("cls");

        int choose = 1;
        printf("SCORE : %d \n", score);
        if (score > hscore) {
            printf("NEW HI-SCORE!! \n");
            hiscore = fopen("hiscore.txt", "w");
            fprintf(hiscore, "%d", score);
            fclose(hiscore);
        }
        printf("GAME OVER \n");
        printf("  Retry\n  Exit\n\n\n");
        printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");

        while (1) {
            char key = getch();
            system("cls");
            printf("SCORE : %d \n", score);
            if (score > hscore) printf("NEW HI-SCORE!! \n");
            printf("GAME OVER \n");

            
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
                hscore = score;
                if (choose == 1) break;
                else return 0;
            }
            else system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");
        }
    }
}
    char inp = getch();

    if (inp == 'w' || inp == 'a' || inp == 's' || inp == 'd') {
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
    }
}

void spawnbullets() {
    int num1,num2,num3,num4;
    //num = rand() % (upper - lower + 1) + lower;
    num1 = rand() % (39 - 0 + 1);
    
    num2 = rand() % (78 - 40 + 1);

    num3 = rand() % (86 - 79 + 1);
    
    num4 = rand() % (94 - 87 + 1);

    screen[0][num1] = 'i';
    screen[9][num2] = 'k';
    screen[num3][0] = 'j';
    screen[num4][39] = 'l';
}

void display() {
    score++;
    printf("SCORE : %d \n\n", score);
    for (int x= 0; x < 10; x++) {
        printf("      ");
        for (int y= 0; y < 40; y++) {
            if (x == 0 || x == 9 || y == 0 || y == 39) printf(".");
            else if (screen[x][y] == 'i' || screen[x][y] == 'j' || screen[x][y] == 'k' || screen[x][y] == 'l') printf("O");
            else printf("%c", screen[x][y]);
            printf(" ");
        }
        printf("\n");
    }
    printf("\n\n\n__________________________________________________________________________________________\n\n\n\t\t   USE 'WASD' KEYS TO MOVE\n\t\t   DODGE THE BULLETS TO SURVIVE\n\n\t\t   REMEMBER TO KEEP TRACK OF THEM OR YOU WON'T KNOW\n\t\t   WHICH DIRECTION THEY ARE GOING IN");
}

void update() {
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 'i') screen[x][y] = 't';
            if (screen[x][y] == 'j') screen[x][y] = 'f';
            if (screen[x][y] == 'k') screen[x][y] = 'g';
            if (screen[x][y] == 'l') screen[x][y] = 'h';
        }
    }
    
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 't') {
                screen[x][y] = '.';
                screen[x + 1][y] = 'i';
            }
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 39; y++) {
            if (screen[x][y] == 'f') {
                screen[x][y] = '.';
                screen[x][y + 1] = 'j';
            }
        }
    }
    for (int x = 1; x < 10; x++) {
        for (int y = 0; y < 40; y++) {
            if (screen[x][y] == 'g') {
                screen[x][y] = '.';
                screen[x - 1][y] = 'k';
            }
        }
    }
    for (int x = 0; x < 10; x++) {
        for (int y = 1; y < 40; y++) {
            if (screen[x][y] == 'h') {
                screen[x][y] = '.';
                screen[x][y - 1] = 'l';
            }
        }
    }
}

char start[50][50] = {
{"..OOOOOO......OOOOOOOO.....OOOO....OOOOOOO..."},
{".OO....OO.....OO.....OO.....OO.....OO....OOO."},
{".OO...........OO.....OO.....OO.....OO.....OO."},
{".OO...OOOX....OOOOOOOO......OO.....OO.....OO."},
{".OO....OO.....OO...OO.......OO.....OO.....OO."},
{".OO....OO.....OO....OO......OO.....OO....OOO."},
{"..OOOOOO......OO.....OO....OOOO....OOOOOOO..."},                                
};

void boot() {
    for (int m = 0; m <= 45; m++) {
        system("cls");
        for (int x = 0; x <= 10; x++) {
            printf("\t\t\t");
            for (int y = 0; y <= m; y++) {
                printf("%c", start[x][y]);
            }
            printf("\n");
        }
        Sleep(1);
    }
}

struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};

int main() {
    srand(time(0));

    HANDLE wHnd;    // Handle to write to the console
    HANDLE rHnd;    // Handle to read from the console.

    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    // Change the window title:
    SetConsoleTitle("GRID");
    
    // Create a COORD to hold the buffer size:
    COORD bufferSize = {90, 100};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set up the required window size:
    SMALL_RECT windowSize = {0, 0, 90, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

    boot();
    printf("\n\n\n\t\t\t    PRESS ENTER TO BEGIN");

    int i;
    do
    {
        i = getch();
    } while (i != 13);
    
    int reset = 1;

    while (reset = 1) {
        system("cls");
        
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 40; y++) {
                screen[x][y] = '.';
            }
        }
        
        system("cls");

        px = 5;
        py = 20;
        score = 0;
        screen[px][py] = 'X';
        int flag = 1;

        display();

        while (flag == 1) {
            move();
            update();
            system("cls");
            spawnbullets();
            display();

            flag = 0;
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 40; y++) {
                    if (screen[x][y] == 'X') flag = 1;
                }
            }
        }

        system("cls");

        int choose = 1;
        printf("SCORE : %d \n", score);
        printf("GAME OVER \n");
        printf("  Retry\n  Exit\n\n\n");
        printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");

        while (1) {
            char key = getch();
            system("cls");
            printf("SCORE : %d \n", score);
            printf("GAME OVER \n");

            
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
            else system("cls");
            printf("\n\n\n\n\n\n\n\n\n\n\n__________________________________________________________________________________________\n\n\n\n\n  USE 'W'/'S' TO SCROLL AND 'ENTER' TO SELECT OPTION");
        }
    }
}
