#ifndef DEVICE_H
#define DEVICE_H
#include <cmath>
#include "Order.h"
class Device
{
private:
	double timeOfService;
	double timeOfRelease;
	double startTime;
	double avService;
	int orders;
	double lambda;
	int num;
public:
	Device()
	{

	};
	Device(const double lambda_, const int num_)
	{
		lambda = lambda_;
		num = num_;
		timeOfRelease = 0;
		timeOfService = 0;
		avService = 0;
		orders = 0;
		startTime = 0;
	}
	void Service(double & gt)
	{
		if (orders == 0) startTime = gt;
		timeOfService = - log((double)rand()/(double) RAND_MAX)/lambda;
		timeOfRelease += timeOfService;
		avService += timeOfService;
		++orders;
		gt = timeOfRelease;
	}
	double GetStartTime() const
	{
		return startTime;
	}
	double GetAvService() const
	{
		return avService / (orders*1.0);
	}
	int GetOrders() const
	{
		return orders;
	}
	double GetTimeOfRelease() const
	{
		return timeOfRelease;
	}
	double GetTimeOfService() const
	{
		return timeOfService;
	}
	int GetNum() const
	{
		return num;
	}
	void Clear()
	{
		timeOfRelease = 0;
		timeOfService = 0;
		avService = 0;
		orders = 0;
		startTime = 0;
	}
	friend std::ostream & operator << (std::ostream & out, const Device & device)
	{
		return out << device.num << "\n";
	}
};
#endif