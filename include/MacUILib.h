#ifndef MAC_UI_LIB
#define MAC_UI_LIB

	//#define WINDOWS
	#define POSIX

	#include <stdio.h>
	#include <stdlib.h>	
	#include <unistd.h>

	void MacUILib_init(void);
	void MacUILib_Delay(int usec);
	int MacUILib_hasChar(void);
	char MacUILib_getChar(void);	
	void MacUILib_clearScreen(void);
	void MacUILib_uninit(void);

#endif
