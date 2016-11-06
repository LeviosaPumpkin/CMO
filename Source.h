#ifndef SOURCE_H
#define SOURCE_H
#include <cstdlib>
#include<iostream>
#include "Order.h"

class Source
{
private:
	double t1 = 0.5;
	double t2 = 0.8;
	int numOfOrders;
	int numOfRefuse;
	int numOfSuceed;
	int num;
	//double time;
	double timeOfWaiting;
	double timeOfArrive;
public:
	Source()
	{}
	Source(int num_)
	{
		num = num_;
		numOfOrders = 0;
		numOfRefuse = 0;
		numOfSuceed = 0;
		timeOfWaiting = 0;
		timeOfArrive = 0;
	}
	int GetNumOfOrders()
	{
		return numOfOrders;
	}
	int GetNumOfRefuse()
	{
		return numOfRefuse;
	}
	int GetNumOfSucceed()
	{
		return numOfSuceed;
	}
	/*double GetTime()
	{
	return time;
	}
	double GetTimeOfWaiting()
	{
	return timeOfWaiting;
	}
	double GetTimeOfArrive()
	{
	return timeOfArrive;
	}*/
	Order Generate(double & gt)
	{
		double time = t1 + (t2 - t1)*rand() / RAND_MAX / 10000;
		//timeOfArrive += time;
		gt += time;
		//std::cout << "Source " << num << " Order " << numOfOrders << " TimeOfArrive " << gt << '\n';
		Order order(num, numOfOrders, gt);
		++numOfOrders;
		return order;
	}
	void UpDateTimeOfWaiting(double timeOfRelease, double timeOfService)
	{
		timeOfWaiting = timeOfWaiting + timeOfRelease - timeOfService;
	}
	int GetNum()
	{
		return num;
	}
	void IncNumOfSuceed()
	{
		++numOfSuceed;
	}
	void IncNumOfRefuse()
	{
		++numOfRefuse;
	}
	void IncNumOfOrders()
	{
		++numOfOrders;
	}
	void Clear()
	{
		numOfOrders = 0;
		numOfRefuse = 0;
		numOfSuceed = 0;
		timeOfWaiting = 0;
		timeOfArrive = 0;
	}
	friend std::ostream & operator << (std::ostream & out, const Source & source)
	{
		return out << source.num << "\n";
	}
};
#endif
