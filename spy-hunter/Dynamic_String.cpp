#include "Dynamic_String.h"

Dynamic_String::Dynamic_String()
{
	string = new char[1];
	string[0] = '\0';
}

Dynamic_String::Dynamic_String(const char* source)
{
	this->string = new char[strlen(source) + 1];
	strcpy(this->string, source);
}

Dynamic_String::Dynamic_String(const Dynamic_String& source)
{
	this->string = new char[source.length() + 1];
	strcpy(this->string, source.string);
}

Dynamic_String::~Dynamic_String()
{
	delete[] string;
}

int Dynamic_String::length() const
{
	return strlen(this->string);
}

char Dynamic_String::value_at(int index) const
{
	if (index > strlen(this->string))
		return NULL;
	else
		return this->string[index];
}


//OPERATOR OVERLOADING


Dynamic_String& Dynamic_String::operator = (const char* source)
{
	delete[] this->string;
	this->string = new char[strlen(source) + 1];
	strcpy(this->string, source);
	return *this;
}

Dynamic_String& Dynamic_String::operator = (const Dynamic_String& source)
{
	delete[] this->string;
	this->string = new char[source.length() + 1];
	strcpy(this->string, source.string);
	return *this;
}

Dynamic_String operator + (const Dynamic_String& first_element, const Dynamic_String& second_element)
{
	char* tmp = new char[first_element.length() + second_element.length() + 1];
	strcpy(tmp, first_element.string);
	strcat(tmp, second_element.string);
	Dynamic_String ds = tmp;
	delete[] tmp;
	return ds;
}

Dynamic_String operator+(const Dynamic_String& element, int number)
{
	char number_as_text[32];
	_itoa(number, number_as_text, 10);
	char* tmp = new char[element.length() + strlen(number_as_text) + 1];
	strcpy(tmp, element.string);
	strcat(tmp, number_as_text);
	Dynamic_String ds = tmp;
	delete[] tmp;
	return ds;
}

Dynamic_String operator+(const Dynamic_String& element, float number)
{
	char number_as_text[32];
	_itoa(number, number_as_text, 10);
	char* tmp = new char[element.length() + strlen(number_as_text) + 1];
	strcpy(tmp, element.string);
	strcat(tmp, number_as_text);
	Dynamic_String ds = tmp;
	delete[] tmp;
	return ds;
}

Dynamic_String::operator char* () const
{
	return this->string;
}