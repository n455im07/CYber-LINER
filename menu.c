#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Headers/utilities.h"
#include "Headers/struct.h"
#include "Headers/choices.h"
#include "Headers/gameplay.h"
#include "Headers/utilities.h"
#include "Headers/display.h"
#include "Headers/create.h"
#include "Headers/add_content.h"

void setup(int difficulty,int nbPlayers, int maxRound){
    
    int *choice = NULL;
    srand(time(NULL)); 
    int size = rand()%(MAX_GRID_SIZE-MIN_GRID_SIZE+1)+MIN_GRID_SIZE;
    int clear = system("clear");

  
    printf(" \n\n   \x1B[35m_____   __\x1B[34m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[35m / __\\ \\ / /\x1B[34m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[35m | (__ \\ V /\x1B[34m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[35m \\___| |_| \x1B[34m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n");
    startGame();
    clear = system("clear");
    clearScreen(clear);

    // menu();

    printf("   \x1B[34m_____   __\x1B[35m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[34m / __\\ \\ / /\x1B[35m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[34m | (__ \\ V /\x1B[35m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[34m \\___| |_| \x1B[35m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n\n");



    // PLAYER BOARD CREATION
    Player *player = createPlayerBoard(nbPlayers, size);

    // GRID CREATION
    Box **grid = createGrid(size);
    addBoxes(grid, size);
    addTargets(grid, size, 18); // Add 18 targets
    addSpikes(grid, size);
    addRobots(grid, size);
    
    int r=1;
    for (int r = 1; r <= maxRound; r++) {
        printf("\x1B[35mRound %d/%d\n\n", r,maxRound);            
        int *choice = randomChoice(grid, size); // Choose choice
        playRound(grid, player,difficulty, nbPlayers, size, choice, r, maxRound);
  }
  	displayWinner(player, nbPlayers);
  	printf("   \x1B[32m_____   __\x1B[36m_                 _    ___ _  _ ___ ___ \n");
  	printf(" \x1B[32m / __\\ \\ / /\x1B[36m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
  	printf("\x1B[32m | (__ \\ V /\x1B[36m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
  	printf(" \x1B[32m \\___| |_| \x1B[36m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n");
    // Free all memory
    for (int k = 0; k < size; k++)
    {
        free(grid[k]);
    }
    free(grid);
    free(player);
    free(choice);
}

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
                    printf("◾");
                    break;
                case 1:
                    printf("  ");
                    break;
                case 2:
                    printf("🤖");
                    break;
                case 3:
                    printf("⬜");
                    break;
                case 4:
                    printf("🤍");
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
                    printf("❌");
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

void displaySelection(int** menu, UserPosition user, int nbPlayers, int difficulty, int maxRound) {
    printf("\n");
    printf(" X = %d et Y = %d\n", user.x, user.y);
    if (user.x == 3 && user.y == 3) {
        printf(" 🤍 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 4 && user.x > 0 && user.y < 3 && user.y > 0) {  
        printf(" 🤍 \033[1;34m: \033[1;4;34mNumber of rounds (Currently %d)\033[0m\033[1;34m ☜\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 3 && user.x > 0 && user.y < 6 && user.y > 2) {
        printf(" 🤍 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: \033[1;4;32mPlayers (Currently %d)\033[0m\033[1;32m ☜\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 6 && user.x > 2 && user.y < 4 && user.y > 0) {
        printf(" 🤍 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: \033[1;4;35mDifficulty (Currently %d)\033[0m\033[1;35m ☜\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 6 && user.x > 2 && user.y < 6 && user.y > 3) {
        printf(" 🤍 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: \033[1;4;31mLeave\033[0m\033[1;31m ☜\n");
    }
}

void useMenu(){
    int difficulty = 1;
    int nbPlayers = 2;
    int maxRound = 5;
    UserPosition user = {3, 3};
    int** menu = createMenu(user);
    char direction, b;
    int scan;
    int clear = system("clear");
    clearScreen(clear);

    while (1) {
        clear = system("clear");
        clearScreen(clear);
        printMenu(menu);
        if (user.x == 5 && user.y == 5) {
            printf(" ❤️  \e[1;31m: \e[1;4;31mYou left the game.\e[0m\e[1;31m\n");
            exit(1);
        }
        if (user.x == 1 && user.y == 5) {
            nbPlayers = chooseNbPlayers();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user);
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }
        if (user.x == 1 && user.y == 1){
            maxRound = chooseRounds();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user);
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }
        if (user.x==5 && user.y == 1){
            difficulty = chooseDifficulty();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user);
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }

        printf("\x1B[37mChoose a direction using z-q-s-d  | e to start\n");
        displaySelection(menu, user, nbPlayers, difficulty, maxRound);
        int scan = scanf("%1c%c", &direction, &b);
        if (direction == 'e'){
            break;
        }
        if ((direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' && direction != 'e') || scan != 2 || b != '\n') {
            printf("Wrong input\n");
            while (getchar() != '\n');
        } else {
            moveUser(menu, &user, direction);
            menu = createMenu(user);
        }
    }
    setup(difficulty,nbPlayers,maxRound);
    for (int k = 0; k < 7; k++){
        free(menu[k]);
    }
    free(menu);
}   
