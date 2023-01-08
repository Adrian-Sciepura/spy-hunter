#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <malloc.h>

template <class T>
class Dynamic_Array
{
private:
	T** items;
	int number_of_elements;
	int capacity;

public:
	Dynamic_Array(int initial_size = 1);
	~Dynamic_Array();

	void resize(int new_size);
	int size() const;
	int add(const T& item);
	void remove(int index);
	T& element(int index);
};

#endif

template <class T>
inline Dynamic_Array<T>::Dynamic_Array(int initial_size)
{
	this->items = (T**)malloc(initial_size * sizeof(T*));
	this->capacity = initial_size;
	this->number_of_elements = 0;
}

template <class T>
inline Dynamic_Array<T>::~Dynamic_Array()
{
	for (int i = 0; i < number_of_elements; i++)
		delete items[i];

	free(items);
}

template <class T>
inline void Dynamic_Array<T>::resize(int new_size)
{
	if (new_size < capacity)
		return;

	T** new_array = (T**)malloc(new_size * sizeof(T*));

	for (int i = 0; i < number_of_elements; i++)
	{
		new_array[i] = items[i];
	}

	capacity = new_size;
	free(items);
	items = new_array;
	new_array = nullptr;
}

template <class T>
inline int Dynamic_Array<T>::size() const
{
	return number_of_elements;
}

template <class T>
inline int Dynamic_Array<T>::add(const T& item)
{
	if (number_of_elements == capacity)
		resize(capacity*2);

	items[number_of_elements] = new T(item);
	number_of_elements++;
	return (number_of_elements - 1);
}

template <class T>
inline void Dynamic_Array<T>::remove(int index)
{
	if (index >= number_of_elements)
		return;

	delete items[index];
	items[index] = nullptr;
	number_of_elements--;

	if (index == number_of_elements)
		return;

	for (int i = 0; i < number_of_elements; i++)
	{
		if (i >= index)
		{
			items[i] = items[i + 1];
		}
	}
}

template <class T>
inline T& Dynamic_Array<T>::element(int index)
{
	return *items[index];
}



