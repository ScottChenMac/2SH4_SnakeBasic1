// Snake Library Header

#ifndef SNAKE_H
#define SNAKE_H

#include "../include/BasicGameObjects.h"
#include "../include/GameObjects.h"

#define SNAKE_SIZE_MAX 256

typedef enum 
{
	STOP = 0, 
	LEFT, 
	RIGHT, 
	UP, 
	DOWN
} direction;

// Array Implementation
typedef struct 
{
	direction dir;
	ItemPos snakeBody[SNAKE_SIZE_MAX];	
	char eatenChars[SNAKE_SIZE_MAX];
	int snakeLength;
} Snake;

void Snake_Init(Snake* thisSnake, int xPos, int yPos);
void Snake_Move(Snake* thisSnake, int boundX, int boundY);
int Snake_Move_EatFood(Snake* thisSnake, foodBucket* thisBucket, int boundX, int boundY);

void __Snake_Init(Snake* thisSnake, int xPos, int yPos);  /// debugging onlyu


#endif