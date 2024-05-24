#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "add_content.h"
#include "choices.h"
#include "create.h"
#include "display.h"
#include "utilities.h"
#include "search.h"
#include "gameplay.h"

int main()
{
    int *choice = NULL;
    // srand(time(NULL)); 
    int size = GRID_SIZE;
    int clear = system("clear");

  
    printf("   \x1B[35m_____   __\x1B[34m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[35m / __\\ \\ / /\x1B[34m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[35m | (__ \\ V /\x1B[34m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[35m \\___| |_| \x1B[34m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n");
    startGame();
    clear = system("clear");
    clearScreen(clear);
    printf("   \x1B[34m_____   __\x1B[35m_                 _    ___ _  _ ___ ___ \n");
    printf(" \x1B[34m / __\\ \\ / /\x1B[35m |__  ___ _ _ ___| |  |_ _| \\| | __| _ \\\n");
    printf("\x1B[34m | (__ \\ V /\x1B[35m| '_ \\/ -_) '_|___| |__ | || .` | _||   /\n");
    printf(" \x1B[34m \\___| |_| \x1B[35m|_.__/\\___|_|     |____|___|_|\\_|___|_|_\\\n\n");



    // PLAYER BOARD CREATION
    int nbPlayers = ChooseNbPlayers();
    Player *player = createPlayerBoard(nbPlayers, size);

    // GRID CREATION
    Box **grid = createGrid(size);
    addBoxes(grid, size);
    addTargets(grid, size, 18); // Add 18 targets
    addSpikes(grid, size);
    addRobots(grid, size);
    
    // SET CHOICES
    int maxRound = chooseRounds();
    int difficulty = chooseDifficulty();
    
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
    return 0;
}