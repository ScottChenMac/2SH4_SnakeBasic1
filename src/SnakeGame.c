#include <stdio.h>
#include <stdlib.h>

#include "../include/MacUILib.h"
#include "../include/BasicGameObjects.h"
#include "../include/GameObjects.h"
#include "../include/Snake.h"
//#include "../include/MyString.h"

GameBoard myGB;
Snake mySnake;
foodBucket myFB;

char keyPressed;
int gameEnd;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
	//Initialize the game
	Initialize();
	
	//Start the game loop
	while(!gameEnd)
	{
		
		// Collect User Input
		GetInput();

		// Run game logic to update the game state with the most recent game state and user input
		RunLogic();

		// Draw the contents on the screen after updating the game state
		DrawScreen();
		
		// Introduce arbitrary delay so to "dumbify" the game
		LoopDelay();
	}
	
	//Release all resources to prevent memory leak
	CleanUp();
	
	return 0;
}

void Initialize(void)
{
	int i,j;
	
	keyPressed = '\0';

	gameEnd = 0;
	
	initBoard(&myGB);	
	
	// Input System Initialization
	MacUILib_init();	
	
	// Game Objects Initialization
	Snake_Init(&mySnake, myGB.BoardSizeX, myGB.BoardSizeY);
	//__Snake_Init(&mySnake, myGB.BoardSizeX, myGB.BoardSizeY);  // debugging version

	initFoodBucket(&myFB);

	generateFoods(&myFB, &myGB, mySnake.snakeBody, mySnake.snakeLength);
}


void GetInput(void)
{
	if(MacUILib_hasChar())
	{
		keyPressed = MacUILib_getChar();		
	}
	else
	{
		keyPressed = '\0';
	}
}

void RunLogic(void)
{
	int i, moveStatus;
	
	// Process Input
	switch(keyPressed)
	{
		case 'w':
			if(mySnake.dir != DOWN) mySnake.dir = UP;
			break;
		case 'a':
			if(mySnake.dir != RIGHT) mySnake.dir = LEFT;
			break;
		case 's':
			if(mySnake.dir != UP) mySnake.dir = DOWN;
			break;
		case 'd':
			if(mySnake.dir != LEFT) mySnake.dir = RIGHT;
			break;
		case 'x':
			gameEnd = 1;  // end the game
			break;
		default:
			break;		
	}

	// Update Snake Position, wraparound, and check for eating food		
	moveStatus = Snake_Move_EatFood(&mySnake, &myFB, myGB.BoardSizeX, myGB.BoardSizeY);

	if(moveStatus >= 0)
	{
		generateFoods(&myFB, &myGB, mySnake.snakeBody, mySnake.snakeLength);
	}

	// for every eaten food, spawn more
	else if(moveStatus == -999) // Snake ate into its own body!! Game Over
	{
		gameEnd = 1;
	}

	// Update board contents
	clearBoard(&myGB);

	for(i = 0; i < myFB.foodBucketSize; i++)				
	{
		myGB.GameBoardArray[myFB.foodPos[i].y][myFB.foodPos[i].x] = myFB.foodChar[i];
	}	

	for(i = 0; i < mySnake.snakeLength; i++)
    {
		myGB.GameBoardArray[mySnake.snakeBody[i].y][mySnake.snakeBody[i].x] = mySnake.eatenChars[i];        
    }

	for(i = 0; i < myGB.BoardSizeX; i++)
	{
		myGB.GameBoardArray[0][i] = '#'; 
		myGB.GameBoardArray[myGB.BoardSizeY-1][i] = '#'; 
	}
	
	for(i = 0; i < myGB.BoardSizeY; i++)
	{
		myGB.GameBoardArray[i][0] = '#'; 
		myGB.GameBoardArray[i][myGB.BoardSizeX-1] = '#'; 
	}   
	
}

void DrawScreen(void)
{
	// Non-persisting local variable
	int i, j;
		
	// Clear the Screen
	MacUILib_clearScreen();

	//printw("This is a test!\n");
	
	// Unix Version - Use printw
	// Draw Contents Array on Screen
	for(i = 0; i < myGB.BoardSizeY; i++)
	{
		for(j = 0; j < myGB.BoardSizeX; j++)
	 	{
	 		MacUILib_printf("%c", myGB.GameBoardArray[i][j]);
	 	}
	 	MacUILib_printf("%c", '\n');
	}	
	
	// Debug Use
	MacUILib_printf("Food Eaten: %s\n", mySnake.eatenChars);

	// Windows Version - use printf
	/* // Draw Contents Array on Screen
	for(i = 0; i < myGB.BoardSizeY; i++)
	{
		for(j = 0; j < myGB.BoardSizeX; j++)
	 	{
	 		printw("%c", myGB.GameBoardArray[i][j]);
	 	}
	 	printw("%c", '\n');
	}	
	
	// Debug Use
	printw("Food Eaten: %s\n", mySnake.eatenChars); */
}

// Arbitrary Delay
// Design Option 1 - Large Loops (Blocking)
// Design Option 2 - Conditional Variable (Non-Blocking)
// Design Option 3 - Thread Sleep (Blocking)
// Design Option 4 (Advanced) - POSIX Alarm (Blocking)
// Many other options
void LoopDelay(void)
{
	// For now, use thread sleep (not the best method)
	MacUILib_Delay(50000);
}

// Resource Cleanup
void CleanUp(void)
{
	int i;
	
	for(i = 0; i < myGB.BoardSizeY; i++)
		free(myGB.GameBoardArray[i]);		
					
	free(myGB.GameBoardArray);	
	
	MacUILib_clearScreen();

	MacUILib_printf("\n\n       Game Over");
	MacUILib_printf("\n\nPress ENTER to Shut Down");

	getchar();
}