#include <vector>
#include<algorithm>
#include<boost/circular_buffer.hpp>
#include <ctime>
#include"Buffer.h"
#include"Device.h"
#include"Order.h"
#include"Source.h"

typedef std::vector<Order>::iterator vOi;

template < class T >
void Clear(std::vector<T> & vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		vec[i].Clear();
	}
}

int ChooseDevice(std::vector<Device> & d, int prev)
{
	if (prev < d.capacity() - 1) return ++prev;
	else return 0;
}
int ChooseSource(std::vector<Order> & o)
{
	vOi it = o.begin();
	vOi min = o.begin();
	int source = 0;
	while (it != o.end())
	{
		if ((*it).GetTimeOfArrive() < (*min).GetTimeOfArrive())
		{
			min = it;
		}
		++it;
	}
	return (*min).GetNumOfSource();
}
bool CanContinue(std::vector<Source> & s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i].GetNumOfOrders() > 1000) return false;
	}
	return true;
}
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	int const numOfSources = 4;
	int const bufferSize = 3;
	int const numOfDevices = 3;
	double lambdaOfDevice = 0.5;

	std::vector<Source> sources;
	Buffer buffer(bufferSize);
	std::vector<Device> devices;
	std::vector<Order> orders;
	

	for (int i = 0; i < numOfSources; ++i)
	{
		sources.push_back(Source(i));
	}
	std::copy(sources.begin(), sources.end(), std::ostream_iterator< Source >(std::cout, " "));
	for (int i = 0; i < numOfDevices; ++i)
	{
		devices.push_back(Device(lambdaOfDevice, i));
	}
	int deviceToUse = 0;
	//big circle
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < numOfSources; ++j)
		{
			orders.push_back(sources[j].Generate());
		}
		globalTime = 0.0;
		while (CanContinue(sources))
		{
			Order order = orders[ChooseSource(orders)];
			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
			{
				Order order2 = buffer.Take();
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service();
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
					orders.push_back(sources[order.GetNumOfSource()].Generate());
				}
				else
				{
					devices[deviceToUse].Service();
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				if (buffer.Put(order) == -1)
				{
					orders.push_back(sources[order.GetNumOfSource()].Generate());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					sources[order.GetNumOfSource()].IncNumOfRefuse();
					orders.push_back(sources[order.GetNumOfSource()].Generate());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		Clear(devices);
		Clear(sources);
		orders.clear();
		buffer.Clear();
	}
	return 0;
}