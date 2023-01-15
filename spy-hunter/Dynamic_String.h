#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H
#include <string.h>
#include <cstdlib>

class Dynamic_String
{
private:
	char* string;

public:
	Dynamic_String();
	Dynamic_String(const char* source);
	Dynamic_String(const Dynamic_String& source);
	~Dynamic_String();

	int length() const;
	char value_at(int index) const;

	Dynamic_String& operator = (const char* source);
	Dynamic_String& operator = (const Dynamic_String& source);
	friend Dynamic_String operator + (const Dynamic_String& first_element, const Dynamic_String& second_element);
	friend Dynamic_String operator + (const Dynamic_String& first_element, int number);
	friend Dynamic_String operator + (const Dynamic_String& first_element, float number);
	operator char* () const;
};

#endif