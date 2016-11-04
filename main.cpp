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
	int min = 0;
	for (int i = 0; i < o.size(); ++i)
	{
		if (o[min].GetTimeOfArrive() > o[i].GetTimeOfArrive())
		{
			min = i;
		}
	}
	return min;
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
	int const numOfSources = 7;
	int const bufferSize = 3;
	int const numOfDevices = 3;
	double lambdaOfDevice = 0.01;
	double globalTime=0;

	std::vector<Source> sources;
	Buffer buffer(bufferSize);
	std::vector<Device> devices;
	std::vector<Order> orders;
	
	for (int i = 0; i < numOfSources; ++i)
	{
		sources.push_back(Source(i));
	}
	//std::copy(sources.begin(), sources.end(), std::ostream_iterator< Source >(std::cout, " "));
	for (int i = 0; i < numOfDevices; ++i)
	{
		devices.push_back(Device(lambdaOfDevice, i));
	}
	//std::copy(devices.begin(), devices.end(), std::ostream_iterator< Device >(std::cout, " "));
	int deviceToUse = 0;
	//big circle
	for (int i = 0; i < 1; ++i)
	{
		for (int j = 0; j < numOfSources; ++j)
		{
			orders.push_back(sources[j].Generate(globalTime));
		}
		while (CanContinue(sources))
		{
			Order order = orders[ChooseSource(orders)];
			double x = devices[deviceToUse].GetTimeOfRelease();
			double y = order.GetTimeOfArrive();
			if (x < y)
			{
				std::cout << "Before ";
				std::copy(buffer.buffer.begin(), buffer.buffer.end(), std::ostream_iterator< Order >(std::cout, " "));
				Order order2 = buffer.Take();
				std::cout << "After ";
				std::copy(buffer.buffer.begin(), buffer.buffer.end(), std::ostream_iterator< Order >(std::cout, " "));
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service(globalTime);
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
				}
				else
				{
					devices[deviceToUse].Service(globalTime);
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				std::cout << "Before ";
				std::copy(buffer.buffer.begin(), buffer.buffer.end(), std::ostream_iterator< Order >(std::cout, " "));
				if (buffer.Put(order) == -1)
				{
					std::cout << "After ";
					std::copy(buffer.buffer.begin(), buffer.buffer.end(), std::ostream_iterator< Order >(std::cout, " "));
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					std::cout << "After ";
					std::copy(buffer.buffer.begin(), buffer.buffer.end(), std::ostream_iterator< Order >(std::cout, " "));
					sources[order.GetNumOfSource()].IncNumOfRefuse();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		for (int k = 0; k < numOfSources; ++k)
		{
			std::cout << "all " << sources[k].GetNumOfOrders() <<
				" refuse " << sources[k].GetNumOfRefuse() <<
				" serviced " << sources[k].GetNumOfSucceed() << '\n';
		}
		std::cout << '\n';
		Clear(devices);
		Clear(sources);
		orders.clear();
		buffer.Clear();
	}
	return 0;
}