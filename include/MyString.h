// Basic String Library Header

#ifndef MY_STRING_H
#define MY_STRING_H

typedef struct
{
	char* str;
	int size;
} String;

void String_Init(String *s, const char* const input_s, int sz);
int String_getSize(const String const *s);
char* String_getString(const String const *s);
int String_compareString(const String const *s1, const String const *s2);

#endif