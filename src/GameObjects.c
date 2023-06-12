// Game-Related Objects

#include "../include/GameObjects.h"
#include <stdlib.h>
#include <time.h>

void initBoard(GameBoard* thisBoard)
{   
    int i, j;

    // User configurable parameters - Board Size
	thisBoard->BoardSizeX = BSIZE_X;
	thisBoard->BoardSizeY = BSIZE_Y;
	
	// Initialize Game Board
		// Design Option 1 - Global Array (Pre-Midterm)
		// Design Option 2 - Heap Array (Post-Midterm)
		// Design Option 3 - Stack Array (Avoid!)
	thisBoard->GameBoardArray = (char**)malloc(thisBoard->BoardSizeY * sizeof(char*));
	for(i = 0; i < thisBoard->BoardSizeY; i++)
		thisBoard->GameBoardArray[i] = (char*)malloc(thisBoard->BoardSizeX * sizeof(char));
		
	// Populate Board Contents with Spaces
	clearBoard(thisBoard);
}

void clearBoard(GameBoard* thisGB)
{
    int i, j;

    // Populate Board Contents with Spaces
	for(i = 0; i < thisGB->BoardSizeY; i++)
		for(j = 0; j < thisGB->BoardSizeX; j++)
			thisGB->GameBoardArray[i][j] = ' ';
}

void initFoodBucket(foodBucket* thisBucket)
{
    int i;

    thisBucket->foodBucketSize = 0;

    for(i = 0; i < MAX_FOOD_COUNT; i++)    
        thisBucket->foodChar[i] = '\0';
}


void generateFoods(foodBucket* thisBucket, GameBoard* thisGB, ItemPos blockoffs[], int blockoff_size)
{    
    int randNumX, randNumY;
    int i, conflict_confirmed;
    int count = FOODCOUNT_PER_ROUND;

    time_t t;
    srand((unsigned) time(&t));

    static int charPos = 0;

    while(count > 0)    
    {
        randNumX = rand() % (BSIZE_X - 2) + 1;
        randNumY = rand() % (BSIZE_Y - 2) + 1;

        conflict_confirmed = 0;

        for(i = 0; i < blockoff_size; i++)
        {
            if(blockoffs[i].x == randNumX && blockoffs[i].y == randNumY)
            {
                conflict_confirmed++;
                break;
            }
        }
        if(conflict_confirmed > 0) continue;

        for(i = 0; i < thisBucket->foodBucketSize; i++)
        {
            if(thisBucket->foodPos[i].x == randNumX && thisBucket->foodPos[i].y == randNumY)
            {
                conflict_confirmed++;
                break;
            }
        }
        if(conflict_confirmed > 0) continue;
        
        count--;
        thisBucket->foodPos[thisBucket->foodBucketSize].x = randNumX;
        thisBucket->foodPos[thisBucket->foodBucketSize].y = randNumY;
        thisBucket->foodChar[thisBucket->foodBucketSize] = STRING_ONE[charPos];
        thisBucket->foodBucketSize++;
    }

    charPos = (charPos + 1) % 26;
}

char removeFood(foodBucket* thisBucket, ItemPos thisPos)
{
    int i, target;
    char targetChar;

    if(thisBucket->foodBucketSize <= 0) return 0;

    for(i = 0; i < thisBucket->foodBucketSize; i++)
    {
        if(thisPos.x == thisBucket->foodPos[i].x && thisPos.y == thisBucket->foodPos[i].y)
        {
            target = i;
            targetChar = thisBucket->foodChar[i];
            break;  // found match
        }
    }

    for(i = target; i < thisBucket->foodBucketSize - 1; i++)
    {
        thisBucket->foodPos[i].x = thisBucket->foodPos[i + 1].x;
        thisBucket->foodPos[i].y = thisBucket->foodPos[i + 1].y;
        thisBucket->foodChar[i] = thisBucket->foodChar[i + 1]; 
    }

    thisBucket->foodBucketSize--;

    return targetChar;
}