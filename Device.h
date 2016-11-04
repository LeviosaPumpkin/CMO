#ifndef DEVICE_H
#define DEVICE_H
#include "Order.h"
class Device
{
private:
	double timeOfService;
	double timeOfRelease;
	double lambda;
	int num;
public:
	Device()
	{

	};
	Device (const double lambda_, const int num_)
	{
		lambda = lambda_;
		num = num;
		timeOfRelease = 0;
		timeOfService = 0;
	}
	void Service()
	{
		timeOfService = 1 - exp(-lambda*timeOfService);
		timeOfRelease += timeOfService;
	}
	double GetTimeOfRelease()
	{
		return timeOfRelease;
	}
	int GetNum()
	{
		return num;
	}
	void Clear()
	{
		timeOfRelease = 0;
		timeOfService = 0;
	}
};
#endif