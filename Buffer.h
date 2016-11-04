#ifndef BUFFER_H
#define BUFFER_H
#include <vector>
#include <iostream>
#include <algorithm>
#include "Order.h"
class Buffer
{
private:
	int size;
	std::vector<Order> buffer;
	int FindOrderToRefuse(Order order)
	{
		int orderToRefuse = 0;
		for (int i = 0; i < buffer.size(); ++i)
		{
			if (buffer[orderToRefuse].GetNumOfSource() < buffer[i].GetNumOfSource())
			{
				orderToRefuse = i;
			}
			if (buffer[orderToRefuse].GetNumOfSource() == buffer[i].GetNumOfSource())
			{
				if (buffer[orderToRefuse].GetTimeOfArrive() < buffer[i].GetTimeOfArrive())
				{
					orderToRefuse = i;
				}
			}
		}
		if (buffer[orderToRefuse].GetNumOfSource() < order.GetNumOfSource())
		{
			orderToRefuse = -1;
		}
		if (buffer[orderToRefuse].GetNumOfSource() == order.GetNumOfSource())
		{
			if (buffer[orderToRefuse].GetTimeOfArrive() < order.GetTimeOfArrive())
			{
				orderToRefuse = -1;
			}
		}
		return orderToRefuse;
	}
public:
	Buffer(const int size_)
	{
		size = size_;
		buffer.reserve(size);
	}
	int Put(Order order)
	{
		if (buffer.size() < size)
		{
			buffer.push_back(order);
			return -1;
		}
		else
		{
			int orderToRefuse = FindOrderToRefuse(order);
			if (orderToRefuse != -1)
			{
				std::swap(buffer[orderToRefuse], order);
				return order.GetNumOfSource();
			}
			else
			{
				return order.GetNumOfSource();
			}
		}
	}
	Order Take()
	{
		//Order order = *(std::min(buffer.begin(), buffer.end(), &Buffer::Comparator));
		if (buffer.empty())
		{
			Order order(-1,-1,-1);
			return order;

		}
		else
		{
			Order order = buffer[0];
			for (int i = 0; i < buffer.size(); ++i)
			{
				if (order.GetTimeOfArrive() < buffer[i].GetTimeOfArrive())
				{
					order = buffer[i];
				}
			}
			buffer.erase(std::remove(buffer.begin(), buffer.end(), order), buffer.end());
			return order;
		}
	}
	void Clear()
	{
		buffer.clear();
	}
	/*bool Comparator(Order lhs, Order rhs)
	{
		return lhs.GetTimeOfArrive() < rhs.GetTimeOfArrive();
	}*/
};
#endif