#ifndef CIRCLEQUEUE_H
#define CIRCLEQUEUE_H
#include <Queue>
#include <iostream>
template <class T>
class CircleQueue : public Queue < T >
{
private:
	int size;
public:
	CircleQueue(int size_) : Queue<T>(), size(size_)
	{
	}

};
#endif