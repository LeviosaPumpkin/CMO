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
		num = num_;
		timeOfRelease = 0;
		timeOfService = 0;
	}
	void Service(double gt)
	{
		timeOfService = 1 - exp(-lambda*gt);
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
	friend std::ostream & operator << (std::ostream & out, const Device & device)
	{
		return out << device.num << "\n";
	}
};
#endif