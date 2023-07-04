#include "../include/MacUILib.h"

#ifdef WINDOWS

	#include <conio.h>
	
	void MacUILib_init(void)
	{
		// No implementation required
		MacUILib_printf = &printf;
	}

	void MacUILib_Delay(int usec)
	{
		usleep(usec);
	}
	
	int MacUILib_hasChar(void)
	{
		return _kbhit();
	}
	
	char MacUILib_getChar(void)
	{
		return _getch();
	}
	
	void MacUILib_clearScreen(void)
	{
		system("cls");
	}
	
	void MacUILib_uninit(void)
	{
		// No implementation required
		MacUILib_printf("\nPress Any Key to Shut Down\n");
		getchar();
	}
	
#endif

	
#ifdef POSIX

	#include <ncurses.h>
	#include <unistd.h>
	
	int MacUILib_hasChar()
	{
		char ch = getch();
		if(ch == ERR)
			return 0;
		else
		{
			ungetch(ch);
			return 1;
		}		
	}

	void MacUILib_init(void)
	{
		MacUILib_printf = &printw;
		
		initscr();
		noecho();
		cbreak();
		nodelay(stdscr, TRUE);
		curs_set(0);
	}

	void MacUILib_Delay(int usec)
	{
		refresh();
		usleep(usec);
	}

	char MacUILib_getChar(void)
	{
		return getch();
	}

	void MacUILib_clearScreen(void)
	{
		clear();
	}

	void MacUILib_uninit(void)
	{
		MacUILib_printf("\nPress Any Key to Shut Down\n");
		refresh();
		getchar();
		endwin();
	}

#endif
