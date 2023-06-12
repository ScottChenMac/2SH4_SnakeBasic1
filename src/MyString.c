// Basic String Library 

#include "../include/MyString.h"

void String_Init(String *s, const char* const input_s, int sz)
{
	int i;
	
	s->size = sz;
	
	for(i = 0; i < sz; i++)
		s->str[i] = input_s[i];
}

int String_getSize(const String const *s)
{
	return s->size;
}

char* String_getString(const String const *s)
{
	return s->str;
}

int String_compareString(const String const *s1, const String const *s2)
{
	int i;
	
	if(s1->size != s2->size) return 0; // false
	
	for(i = 0; i < s1->size; i++)
	{
		if(s1->str[i] != s2->str[i])
			return 0; // false
	}
	
	return 1; // true
}
