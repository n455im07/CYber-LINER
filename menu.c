#include <stdio.h>
#include <stdlib.h>

#include "Headers/utilities.h"

typedef struct {
    int x;
    int y;
} UserPosition;

void moveUser(int **menu, UserPosition *user, char direction) {
    if (user->x < 4 && user->x > 1 && user->y > 1 && user->y < 3 ){
        menu[user->x][user->y] = 3;
    }
    if(user->x == 1 && user->y == 1){
        menu[user->x][user->y] = 4;
    }
    if (user->x < 3 && user->x > 1 && user->y > 3 && user->y < 6 ){
        menu[user->x][user->y] = 5;
    }
    if(user->x == 1 && user->y == 5){
        menu[user->x][user->y] = 6;
    }
    if (user->x < 6 && user->x > 4 && user->y > 1 && user->y < 4 ){
        menu[user->x][user->y] = 7;
    }
    if(user->x == 5 && user->y == 1){
        menu[user->x][user->y] = 8;
    }
    if (user->x < 6 && user->x > 3 && user->y > 4 && user->y < 6 ){
        menu[user->x][user->y] = 3;
    }
    if(user->x == 5 && user->y == 5){
        menu[user->x][user->y] = 10;
    }
    switch(direction) {
        case 'z': // move up
            if (user->y > 1) user->y--;
            break;
        case 's': // move down
            if (user->y < 5) user->y++;
            break;
        case 'q': // move left
            if (user->x > 1) user->x--;
            break;
        case 'd': // move right
            if (user->x < 5) user->x++;
            break;
    }
    menu[user->y][user->x] = 2;
}

void printMenu(int **menu) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            switch(menu[i][j]) {
                case 0:
                    printf("⬜");
                    break;
                case 1:
                    printf("  ");
                    break;
                case 2:
                    printf("🤖");
                    break;
                case 3:
                    printf("🟦");
                    break;
                case 4:
                    printf("💙");
                    break;
                case 5:
                    printf("🟩");
                    break;
                case 6:
                    printf("💚");
                    break;
                case 7:
                    printf("🟪");
                    break;
                case 8:
                    printf("💜");
                    break;
                case 9:
                    printf("🟥");
                    break;
                case 10:
                    printf("❤️");
                    break;
            }
        }
        printf("\n");
    }
}

int** createMenu(){
        int **menu=malloc(7*sizeof(int*));   
        for (int i = 0; i < 7; i++) {
            menu[i] = calloc(7,sizeof(int));
        }
        menu[3][3]=2;

        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if(i==0 || i == 6 || j ==0|| j==6){
                    menu[i][j]=1;
                }
            }
        }
        for (int i=1;i<4;i++){
            for (int j=1;j<3;j++){
                menu[i][j]=3;
            }
        }
        menu[1][1]=4;

        for (int i=1;i<3;i++){
            for (int j=3;j<6;j++){
                menu[i][j]=5;
            }
        }
        menu[1][5]=6;

        for (int i=4;i<6;i++){
            for (int j=1;j<4;j++){
                menu[i][j]=7;
            }
        }
        menu[5][1]=8;

        for (int i=3;i<6;i++){
            for (int j=4;j<6;j++){
                menu[i][j]=9;
            }
        }
        menu[5][5]=10;
        return menu;
}


int main(){

    int** menu = createMenu();
    UserPosition user = {3, 3};
    char direction, b;
    int scan;
    int clear = system("clear");

while (1) {
    system("clear");
    printMenu(menu);
    printf("\x1B[37mChoose a direction using z-q-s-d\n");
    int scan = scanf("%1c%c", &direction, &b);
    if ((direction != 'd' && direction != 's' && direction != 'q' && direction != 'z') || scan != 2 || b != '\n') {
        printf("Wrong input\n");
        while (getchar() != '\n');
    } else {
        moveUser(menu, &user, direction);
    }
}

    printf(" 💙 \e[1;34m: Start\n");
    printf(" 💚 \e[1;32m: Players\n");
    printf(" 💜 \e[1;35m: Difficulty\n");
    printf(" ❤️  \e[1;31m: Leave\n");
    printf("\n");
    printf(" 💙 \e[1;34m: \e[1;4;34mStart\e[0m\n");
    printf(" 💚 \e[1;32m: \e[1;4;32mPlayers\e[0m\n");
    printf(" 💜 \e[1;35m: \e[1;4;35mDifficulty\e[0m\n");
    printf(" ❤️  \e[1;31m: \e[1;4;31mLeave\e[0m\n");



    return 0;
}