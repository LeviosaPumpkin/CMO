#ifndef ORDER_H
#define ORDER_H

class Order
{
	int numOfSource;
	int numInSource;
	//double timeOfWaiting;
	double timeOfArrive;
public:
	Order(int numOfSource_, int numInSource_, double timeOfArrive_)
	{
		numOfSource = numOfSource_;
		numInSource = numInSource_;
		timeOfArrive = timeOfArrive_;

	}
	//double GetTimeOfWaiting()
	//{
	//	return timeOfWaiting;
	//}
	double GetTimeOfArrive()
	{
		return timeOfArrive;
	}
	int GetNumOfSource()
	{
		return numOfSource;
	}
	friend bool operator == (const Order& left, const Order& right);
};
bool operator == (const Order& left, const Order& right)
{
	return (left.numOfSource == right.numOfSource &&
		left.numInSource == right.numInSource &&
		left.timeOfArrive == right.timeOfArrive);
};
#endif