// Snake Library

#include "../include/Snake.h"
#include "../include/GameObjects.h"

void Snake_Init(Snake* thisSnake, int xPos, int yPos)
{
	int i;
    	
    thisSnake->dir = STOP;
	thisSnake->snakeBody[0].x = xPos / 2;
	thisSnake->snakeBody[0].y = yPos / 2;

    for(i = 0; i < SNAKE_SIZE_MAX; i++)
        thisSnake->eatenChars[i] = '\0';

	thisSnake->eatenChars[0] = '@';  // as Snake Head
	thisSnake->snakeLength = 1;	
}

void __Snake_Init(Snake* thisSnake, int xPos, int yPos)
{
	int i;
    	
    thisSnake->dir = DOWN;
	thisSnake->snakeBody[0].x = xPos / 2;
	thisSnake->snakeBody[0].y = yPos / 2;

	thisSnake->snakeBody[1].x = xPos / 2 - 1;
	thisSnake->snakeBody[1].y = yPos / 2;

	thisSnake->snakeBody[2].x = xPos / 2 - 2;
	thisSnake->snakeBody[2].y = yPos / 2;

	thisSnake->snakeBody[3].x = xPos / 2 - 3;
	thisSnake->snakeBody[3].y = yPos / 2;

    for(i = 0; i < SNAKE_SIZE_MAX; i++)
        thisSnake->eatenChars[i] = '\0';

	thisSnake->eatenChars[0] = '@';  // as Snake Head
	thisSnake->eatenChars[1] = 'M';  // as Snake Head
	thisSnake->eatenChars[2] = 'A';  // as Snake Head
	thisSnake->eatenChars[3] = 'C';  // as Snake Head
	thisSnake->snakeLength = 4;	
}

void Snake_Move(Snake* thisSnake, int boundX, int boundY)
{
    int i;

    for(i = thisSnake->snakeLength - 1; i > 0; i--)
    {
        thisSnake->snakeBody[i].x = thisSnake->snakeBody[i - 1].x;
        thisSnake->snakeBody[i].y = thisSnake->snakeBody[i - 1].y;
    }

    switch(thisSnake->dir)
    {
        case UP:
			thisSnake->snakeBody[0].y--;			
			if(thisSnake->snakeBody[0].y == 0) thisSnake->snakeBody[0].y = boundY - 2;
			break;

		case DOWN:
			thisSnake->snakeBody[0].y++;
			if(thisSnake->snakeBody[0].y == boundY - 1) thisSnake->snakeBody[0].y = 1;
			break;

		case LEFT:
			thisSnake->snakeBody[0].x--;			
			if(thisSnake->snakeBody[0].x == 0) thisSnake->snakeBody[0].x = boundX - 2;
			break;

		case RIGHT:
			thisSnake->snakeBody[0].x++;
			if(thisSnake->snakeBody[0].x == boundX - 1) thisSnake->snakeBody[0].x = 1;
			break;
        
        default:
            break;
    }
}

int Snake_Move_EatFood(Snake* thisSnake, foodBucket* thisBucket, int boundX, int boundY)
{
    int i;
	int target = -1;

	// Check if snake eats into itself
	for(i = 1; i < thisSnake->snakeLength; i++)
	{
		if(thisSnake->snakeBody[0].x == thisSnake->snakeBody[i].x && thisSnake->snakeBody[0].y == thisSnake->snakeBody[i].y)
			return -999;  // indicating suicide!
	}

	// Check Head Collision with Food Positions
	for(i = 0; i < thisBucket->foodBucketSize; i++)
	{
		if(thisSnake->snakeBody[0].x == thisBucket->foodPos[i].x && thisSnake->snakeBody[0].y == thisBucket->foodPos[i].y)
		{
			target = i;
			break;
		}
	}

	// If collided, increase snake length
	if(target >= 0)
	{
		thisSnake->eatenChars[thisSnake->snakeLength] = thisBucket->foodChar[target];
    	thisSnake->snakeLength++;

		// Remove the food from the bucket
		removeFood(thisBucket, thisBucket->foodPos[target]);
	}

	// Then continue moving
    Snake_Move(thisSnake, boundX, boundY);

	return target;
}