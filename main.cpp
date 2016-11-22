//TO DO: ��������� ��������� � ��������� ������; 

#include <vector>
#include<algorithm>
#include <ctime>
#include"Buffer.h"
#include"Device.h"
#include"Order.h"
#include"Source.h"

typedef std::vector<Order>::iterator vOi;
 
void GetResults(std::vector< Source > & so, std::vector < Device> & d, double gT, double st, double et)
{
	std::cout << " #	orders	Pref	Tdev	Tbuf	Tsys	Dbuf	Dsev\n";
	for (int i = 0; i < so.size(); ++i)
	{
		std::cout << " " << i << "	" << so[i].GetNumOfOrders() << "	" << so[i].GetNumOfRefuse() / (so[i].GetNumOfOrders()*1.0) << 
			"	" << so[i].GetTimeOfService() / (so[i].GetNumOfOrders()*1.0) <<
			"	" << so[i].GetTimeOfWaiting() / (so[i].GetNumOfOrders()*1.0) <<
			"	" << so[i].GetTimeOfService() / (so[i].GetNumOfOrders()*1.0) + so[i].GetTimeOfWaiting() / (so[i].GetNumOfOrders()*1.0) <<
			"	" << sqrt(so[i].GetdTimeOfWaiting()) << "	" << sqrt(so[i].GetdTimeOfService()) << '\n';
	}
	for (int i = 0; i < d.size(); ++i)
	{
		std::cout << '\n' << i << " " << (d[i].GetTimeOfRelease() - d[i].GetStartTime())/(et-st);
	}
	std::cout<< std::endl;
}
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
	if (prev < d.size() - 1) return ++prev;
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
double CountN(double P)
{
	return 1.643*1.643*(1-P) / (0.01 * P);
}
bool NeedContinue(double p0, double p1)
{
	if (abs(p0 - p1) < 0.1) return false;
}
double CountP(std::vector<Source> & sou)
{
	double sum = 0;
	for (int i = 0; i < sou.size(); ++i) 
		sum = sum + (sou[i].GetNumOfRefuse() / (double)sou[i].GetNumOfOrders());
	return sum / sou.size();
}
int main()
{
	//srand(static_cast<unsigned int>(time(NULL)));
	/*int numOfSources;
	int bufferSize;
	int numOfDevices;
	double lambdaOfDevice;
	double globalTime = 0;
	int mode;*/
	/*std::cout << "Number of sources: ";
	std::cin >> numOfSources;
	std::cout << "Size of buffer: ";
	std::cin >> bufferSize;
	std::cout << "Number of devices: ";
	std::cin >> numOfDevices;
	std::cout << "Lambda of device: ";
	std::cin >> lambdaOfDevice;
	std::cout << "Choose mode: 0 - automatic 1 - step ";
	std::cin >> mode;
	std::cout << std::endl;*/

	int numOfSources =4;
	int bufferSize=3;
	int numOfDevices=3;
	double lambdaOfDevice=0.01;
	double globalTime = 0;
	int mode=0;
	int allOrders = 100;
	int k = 0;
	std::vector<Source> sources;
	Buffer buffer(bufferSize);
	std::vector<Device> devices;
	std::vector<Order> orders;
	double p0 = 100;
	double p1 = 200;

	for (int i = 0; i < numOfSources; ++i)
	{
		sources.push_back(Source(i));
	}
	for (int i = 0; i < numOfDevices; ++i)
	{
		devices.push_back(Device(lambdaOfDevice, i));
	}
	int deviceToUse = 0;
	int evenodd = 0;
	//big circle
	while (NeedContinue(p0, p1))
	{
		for (int j = 0; j < numOfSources; ++j)
		{
			orders.push_back(sources[j].Generate(globalTime));
			++k;
		}
		double starttime = sources[0].GetTimeOfArrive();
		while (k < allOrders)
		{
			Order order = orders[ChooseSource(orders)];
			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
			{
				Order order2 = buffer.Take();
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
				}
				else
				{
					devices[deviceToUse].Service(globalTime);
					sources[order2.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				int orderToRefuse = buffer.Put(order);
				if (orderToRefuse == -1)
				{
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					sources[orderToRefuse].IncNumOfRefuse();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		while (!orders.empty())
		{
			Order order = orders[ChooseSource(orders)];
			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
			{
				Order order2 = buffer.Take();
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
				}
				else
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				int orderToRefuse = buffer.Put(order);
				if (orderToRefuse == -1)
				{
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					sources[orderToRefuse].IncNumOfRefuse();
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		double endtime = endtime = (*std::max_element(devices.begin(), devices.end(), [](Device l, Device r) 
			{ return l.GetTimeOfRelease() < r.GetTimeOfRelease(); })).GetTimeOfRelease();
		p0 = CountP(sources);
		std::cout << " p0 = " << p0;
		std::cout << " N = " << allOrders << '\n';
		allOrders = CountN(p0);
		GetResults(sources, devices, globalTime, starttime, endtime);
		Clear(devices);
		Clear(sources);
		orders.clear();
		buffer.Clear();
		k = 0;

		////////////////////////////////////////////////////////////////
		deviceToUse = 0;
		for (int j = 0; j < numOfSources; ++j)
		{
			orders.push_back(sources[j].Generate(globalTime));
			++k;
		}
		starttime = sources[0].GetTimeOfArrive();
		while (k < allOrders)
		{
			Order order = orders[ChooseSource(orders)];
			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
			{
				Order order2 = buffer.Take();
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
				}
				else
				{
					devices[deviceToUse].Service(globalTime);
					sources[order2.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				int orderToRefuse = buffer.Put(order);
				if (orderToRefuse == -1)
				{
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					sources[orderToRefuse].IncNumOfRefuse();
					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
					++k;
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		while (!orders.empty())
		{
			Order order = orders[ChooseSource(orders)];
			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
			{
				Order order2 = buffer.Take();
				if (order2.GetTimeOfArrive() == -1)
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
					sources[order.GetNumOfSource()].IncNumOfSuceed();
				}
				else
				{
					devices[deviceToUse].Service(globalTime);
					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
					sources[order2.GetNumOfSource()].IncNumOfSuceed();
				}
			}
			else
			{
				int orderToRefuse = buffer.Put(order);
				if (orderToRefuse == -1)
				{
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
				else
				{
					sources[orderToRefuse].IncNumOfRefuse();
					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
				}
			}
			deviceToUse = ChooseDevice(devices, deviceToUse);
		}
		endtime = (*std::max_element(devices.begin(), devices.end(), [](Device l, Device r)
			{ return l.GetTimeOfRelease() < r.GetTimeOfRelease(); })).GetTimeOfRelease();
		p1 = CountP(sources);
		std::cout << " p1 = " << p1;
		std::cout << "N = " << allOrders << '\n';
		allOrders = CountN(p1);
		GetResults(sources, devices, globalTime, starttime, endtime);
		Clear(devices);
		Clear(sources);
		orders.clear();
		buffer.Clear();
		k = 0;
	}
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   