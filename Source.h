#ifndef SOURCE_H
#define SOURCE_H
#include <cstdlib>
#include <iostream>
#include <math.h>
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
	double timeOfService;
	double dTimeOfWaiting;
	double dTimeOfService;
	double prevAvWait;
	double prevAvSev;
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
		timeOfService = 0;
		dTimeOfWaiting = 0;
		dTimeOfService = 0;
		prevAvWait = 0;
		prevAvSev = 0;
	}
	int GetNumOfOrders() const
	{
		return numOfOrders;
	}
	int GetNumOfRefuse() const
	{
		return numOfRefuse;
	}
	int GetNumOfSucceed() const
	{
		return numOfSuceed;
	}
	double GetTimeOfWaiting() const
	{
	return timeOfWaiting;
	}
	double GetTimeOfArrive() const
	{
	return timeOfArrive;
	}
	double GetTimeOfService() const
	{
		return timeOfService;
	}
	double GetdTimeOfService() const
	{
		return dTimeOfService;
	}
	double GetdTimeOfWaiting() const
	{
		return dTimeOfWaiting;
	}
	Order Generate(double & gt)
	{
		double time = t1 + (t2 - t1)* (double) rand() / (double) RAND_MAX;
		timeOfArrive += time;
		gt += time;
		//std::cout << "Source " << num << " Order " << numOfOrders << " TimeOfArrive " << gt << '\n';
		Order order(num, numOfOrders, gt);
		++numOfOrders;
		return order;
	}
	void UpDateTimeOfWaitingAndService(double tR, double tS)
	{
		timeOfService += tS;
		double tW = timeOfArrive + tR - tS;
		timeOfWaiting += tW;
		//timeOfWaiting = timeOfArrive + tR - tS;
		if (numOfOrders > 1)
		{
			dTimeOfWaiting = (double)(numOfOrders - 2) / (double)(numOfOrders - 1)*dTimeOfWaiting 
				+ 1 / (double)numOfOrders*powf(tW - prevAvWait, 2);
			dTimeOfService = (double)(numOfOrders - 2) / (double)(numOfOrders - 1)*dTimeOfService 
				+ 1 / (double)numOfOrders*powf(tW - timeOfService, 2);
		}
		prevAvWait = (prevAvWait*(numOfOrders - 1) + tW) / (double)numOfOrders;
		prevAvSev = (prevAvSev*(numOfOrders - 1) + tW) / (double)numOfOrders;
	}
	int GetNum() const
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
		dTimeOfWaiting = 0;
		dTimeOfService = 0;
		prevAvWait = 0;
		prevAvSev = 0;
	}
	friend std::ostream & operator << (std::ostream & out, const Source & source) 
	{
		return out << source.num << "\n";
	}
};
#endif
