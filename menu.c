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

void setup(int difficulty,int nbPlayers, int maxRound,int artStyle){
    
    int *choice = NULL;
    srand(time(NULL)); 
    int size = rand()%(MAX_GRID_SIZE-MIN_GRID_SIZE+1)+MIN_GRID_SIZE; // Generate random number between MAX_GRID_SIZE and MIN_GRID_SIZE
    int clear = system("clear");
    clearScreen(clear);
    printf(" \n\n   \x1B[35m_____   __\x1B[34m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[35m / __\\ \\ / /\x1B[34m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[35m | (__ \\ V /\x1B[34m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[35m \\___| |_| \x1B[34m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n");
    startGame(); // Ask player to press Enter to start

    clear = system("clear");
    clearScreen(clear);
    printf("   \x1B[34m_____   __\x1B[35m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[34m / __\\ \\ / /\x1B[35m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[34m | (__ \\ V /\x1B[35m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[34m \\___| |_| \x1B[35m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n\n");

    // PLAYER BOARD CREATION
    Player *player = createPlayerBoard(nbPlayers);

    // GRID CREATION
    Box **grid = createGrid(size); // Create an empty grid
    addBoxes(grid, size); // Fill the grid
    addTargets(grid, size, 18); // Add 18 targets
    addSpikes(grid, size); // Add two spike in each border
    addRobots(grid, size); // Add robots randomly 
    
    int r=1;
    for (int r = 1; r <= maxRound; r++) { // Loop until the number of rounds = maxRound
        printf("\x1B[35mRound %d/%d\n\n", r,maxRound); // Print the round count
        int *choice = randomChoice(grid, size,artStyle); // Choose randomly a robot and a target
        playRound(grid, player,difficulty, nbPlayers, size, choice, r, maxRound,artStyle); // Play a round
  }
  	displayWinner(player, nbPlayers); // Shows the final scoreboard 
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

void moveUser(int **menu, UserPosition *user, char direction) { // move in the menu
    switch(direction) {
        case 'z': // move up
            if (user->x > 1) {
                user->x--;
            }
            break;
        case 's': // move down
            if (user->x < 5) {
                user->x++;
            }
            break;
        case 'q': // move left
            if (user->y > 1) {
                user->y--;
            }
            break;
        case 'd': // move right
            if (user->y < 5){
                user->y++;
            }
            break;
    }
    menu[user->x][user->y] = 2; // Put the user in the new coordinates
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
                    printf("❌");
                    break;
            }
        }
        printf("\n");
    }
}

int** createMenu(UserPosition user){
        int **menu=malloc(7*sizeof(int*)); // The menu size is 7*7 with 6*6 where the user can move
        for (int i = 0; i < 7; i++) {
            menu[i] = calloc(7,sizeof(int));
        }
        for (int i=0;i<7;i++){
            for (int j=0;j<7;j++){
                if(i==0 || i == 6 || j ==0|| j==6){
                    menu[i][j]=1; // Fill borders with 1
                }
            }
        }
        for (int i=1;i<4;i++){ // Top left area
            for (int j=1;j<3;j++){
                menu[i][j]=3; 
            }
        }
        menu[1][1]=4;

        for (int i=1;i<3;i++){ // Top right area
            for (int j=3;j<6;j++){
                menu[i][j]=5;
            }
        }
        menu[1][5]=6;

        for (int i=4;i<6;i++){ // Bottom left area
            for (int j=1;j<4;j++){
                menu[i][j]=7;
            }
        }
        menu[5][1]=8;

        for (int i=3;i<6;i++){ // Bottom right area
            for (int j=4;j<6;j++){
                menu[i][j]=9;
            }
        }
        menu[5][5]=10;
        menu[user.x][user.y]=2; // Place user
        return menu;
}

void displaySelection(int** menu, UserPosition user, int nbPlayers, int difficulty, int maxRound) {
    if (user.x == 3 && user.y == 3) { // Underline selected option 
        printf(" 💙 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 4 && user.x > 0 && user.y < 3 && user.y > 0) {  
        printf(" 💙 \033[1;34m: \033[1;4;34mNumber of rounds (Currently %d)\033[0m\033[1;34m ☜\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 3 && user.x > 0 && user.y < 6 && user.y > 2) {
        printf(" 💙 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: \033[1;4;32mPlayers (Currently %d)\033[0m\033[1;32m ☜\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 6 && user.x > 2 && user.y < 4 && user.y > 0) {
        printf(" 💙 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: \033[1;4;35mDifficulty (Currently %d)\033[0m\033[1;35m ☜\n", difficulty);
        printf(" ❌  \033[1;31m: Leave\n");
    } else if (user.x < 6 && user.x > 2 && user.y < 6 && user.y > 3) {
        printf(" 💙 \033[1;34m: Number of rounds (Currently %d)\n", maxRound);
        printf(" 💚 \033[1;32m: Players (Currently %d)\n", nbPlayers);
        printf(" 💜 \033[1;35m: Difficulty (Currently %d)\n", difficulty);
        printf(" ❌  \033[1;31m: \033[1;4;31mLeave\033[0m\033[1;31m ☜\n");
    }
}

void useMenu(){
    // Default settings
    int difficulty = 1;
    int nbPlayers = 2;
    int maxRound = 5;
    int artStyle = 0;
    UserPosition user = {3, 3}; // Put user in the middle
    int** menu = createMenu(user);
    char direction, b;
    int scan;
    int clear = system("clear");
    clearScreen(clear);

    while (1) {
        clear = system("clear");
        clearScreen(clear);
        printMenu(menu);
        if (user.x == 5 && user.y == 5) { // Bottom right button to leave the game
            printf(" ❤️  \e[1;31m: \e[1;4;31mYou left the game.\e[0m\e[1;31m\n");
            exit(1);
        }
        if (user.x == 1 && user.y == 5) { // Top right button to choose the number of players
            nbPlayers = chooseNbPlayers();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user); // Put back robot in the middle
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }
        if (user.x == 1 && user.y == 1){ // Top left button to choose the maximum number of rounds
            maxRound = chooseRounds();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user); // Put back robot in the middle
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }
        if (user.x==5 && user.y == 1){ // Bottom left button to choose difficulty
            difficulty = chooseDifficulty();
            user.x = 3;
            user.y = 3;
            menu = createMenu(user); // Put back robot in the middle
            clear = system("clear");
            clearScreen(clear);
            printMenu(menu);
        }

        printf("\x1B[0;37mChoose a direction using z-q-s-d  | e to start\n");
        printf("\n");
        if (artStyle==0){
            printf("\x1B[0;37mIn game art style : ☻   ⒮  ⓟ  ⓔ  ⒞  Ⓘ  Ⓐ  ⓛ    Ⓒ  Ⓗ  Ⓐ  ⓡ  Ⓐ  Ⓒ  ⓣ  Ⓔ  ⓡ  ⓢ    | a to change\n");
        }else if (artStyle==1){
            printf("\x1B[0;37mIn game art style :\x1B[34m 😊   🅴 🅼 🅾  🅹 🅸  \x1B[37m| a to change\n");
        }
        
        displaySelection(menu, user, nbPlayers, difficulty, maxRound);
        direction = getchar();
        empty_buffer();
        if (direction == 'e'){ // Exit the loop and starts the game
            break;
        } 
        if (direction == 'a'){
            artStyle=(artStyle+1)%2; // Swap the in game art style between 0 and 1
        }
        if (direction != 'd' && direction != 's' && direction != 'q' && direction != 'z' && direction != 'e' && direction != 'a') {
            printf("Wrong input\n");
            empty_buffer();
        } else {
            moveUser(menu, &user, direction);
            menu = createMenu(user);
        }
    }
    setup(difficulty,nbPlayers,maxRound,artStyle); // Create all the needs for the grid, players and starts the game
    // Free all memory
    for (int k = 0; k < 7; k++){ 
        free(menu[k]);
    }
    free(menu);
}   
