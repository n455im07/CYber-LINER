#include <stdio.h>
#include <stdlib.h>

#include "Headers/utilities.h"

typedef struct {
    int x;
    int y;
} UserPosition;

void moveUser(int **menu, UserPosition *user, char direction) {
    switch(direction) {
        case 'z': // move up
            if (user->x > 1) user->x--;
            break;
        case 's': // move down
            if (user->x < 5) user->x++;
            break;
        case 'q': // move left
            if (user->y > 1) user->y--;
            break;
        case 'd': // move right
            if (user->y < 5) user->y++;
            break;
    }
    menu[user->x][user->y] = 2;
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

int** createMenu(UserPosition user){
        int **menu=malloc(7*sizeof(int*));   
        for (int i = 0; i < 7; i++) {
            menu[i] = calloc(7,sizeof(int));
        }
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
        menu[user.x][user.y]=2;
        return menu;
}

void displaySelection(int** menu,UserPosition user){
    printf("\n");
    printf(" X = %d et Y = %d\n",user.x,user.y);
    if (user.x==3 && user.y == 3){
        printf(" 💙 \e[1;34m: Start\n");
        printf(" 💚 \e[1;32m: Players\n");
        printf(" 💜 \e[1;35m: Difficulty\n");
        printf(" ❤️  \e[1;31m: Leave\n");
    } else if (user.x < 4 && user.x > 0 && user.y< 3 && user.y > 0){  
        printf(" 💙 \e[1;34m: \e[1;4;34mStart\e[0m\e[1;34m ☜\n");
        printf(" 💚 \e[1;32m: Players\n");
        printf(" 💜 \e[1;35m: Difficulty\n");
        printf(" ❤️  \e[1;31m: Leave\n");
    }else if (user.x < 3 && user.x > 0 && user.y< 6 && user.y > 2){
        printf(" 💙 \e[1;34m: Start\n");
        printf(" 💚 \e[1;32m: \e[1;4;32mPlayers\e[0m\e[1;32m ☜\n");
        printf(" 💜 \e[1;35m: Difficulty\n");
        printf(" ❤️  \e[1;31m: Leave\n");
    }else if (user.x < 6 && user.x > 2 && user.y< 4 && user.y > 0){
        printf(" 💙 \e[1;34m: Start\n");
        printf(" 💚 \e[1;32m: Players\n");
        printf(" 💜 \e[1;35m: \e[1;4;35mDifficulty\e[0m\e[1;35m ☜\n");
        printf(" ❤️  \e[1;31m: Leave\n");
    }else if (user.x < 6 && user.x > 2 && user.y< 6 && user.y > 3){
        printf(" 💙 \e[1;34m: Start\n");
        printf(" 💚 \e[1;32m: Players\n");
        printf(" 💜 \e[1;35m: Difficulty\n");
        printf(" ❤️  \e[1;31m: \e[1;4;31mLeave\e[0m\e[1;31m ☜\n");
        };
}

int main(){

    
    UserPosition user = {3, 3};
    int** menu = createMenu(user);
    char direction, b;
    int scan;
    int clear = system("clear");

while (1) {
    system("clear");
    printMenu(menu);
    if (user.x==5 && user.y==5){
        printf(" ❤️  \e[1;31m: \e[1;4;31mYou left the game.\e[0m\e[1;31m\n");
        exit(1);
    }

    printf("\x1B[37mChoose a direction using z-q-s-d\n");
    displaySelection(menu,user);
    int scan = scanf("%1c%c", &direction, &b);
    if ((direction != 'd' && direction != 's' && direction != 'q' && direction != 'z') || scan != 2 || b != '\n') {
        printf("Wrong input\n");
        while (getchar() != '\n');
    } else {
        moveUser(menu, &user, direction);
        menu = createMenu(user);
    }
}
    return 0;
}