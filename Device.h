#ifndef DEVICE_H
#define DEVICE_H
#include "Order.h"
class Device
{
private:
	double timeOfService;
	double timeOfRelease;
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
	}
	void Service(double & gt)
	{
		timeOfService = 1 - exp(-lambda*gt);
		timeOfRelease += timeOfService;
		avService += timeOfService;
		++orders;
		//gt += timeOfService;
	}
	double GetAvService()
	{
		return avService / (orders*1.0);
	}
	int GetOrders()
	{
		return orders;
	}
	double GetTimeOfRelease()
	{
		return timeOfRelease;
	}
	double GetTimeOfService()
	{
		return timeOfService;
	}
	int GetNum()
	{
		return num;
	}
	void Clear()
	{
		timeOfRelease = 0;
		timeOfService = 0;
		avService = 0;
		orders = 0;
	}
	friend std::ostream & operator << (std::ostream & out, const Device & device)
	{
		return out << device.num << "\n";
	}
};
#endif