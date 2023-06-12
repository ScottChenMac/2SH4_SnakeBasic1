// Game Objects Header File

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define BSIZE_X 24
#define BSIZE_Y 12

#define MAX_FOOD_COUNT 100

#define FOODCOUNT_PER_ROUND 2
#define STRING_ONE "McMaster-ECE-2023"

#include "../include/BasicGameObjects.h"
//#include "../include/Snake.h"

typedef struct
{
	int BoardSizeX; 
	int BoardSizeY;
	char** GameBoardArray;
} GameBoard;

typedef struct
{
	ItemPos foodPos[MAX_FOOD_COUNT];
	char foodChar[MAX_FOOD_COUNT];
	int foodBucketSize;
} foodBucket;

void initBoard(GameBoard* thisBoard);
void clearBoard(GameBoard* thisGB);

void initFoodBucket(foodBucket* thisBucket);
void generateFoods(foodBucket* thisBucket, GameBoard* thisGB, ItemPos blockoffs[], int blockoff_size);
char removeFood(foodBucket* thisBucket, ItemPos thisPos);


#endif