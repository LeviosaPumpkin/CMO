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
	double GetTimeOfArrive() const
	{
		return timeOfArrive;
	}
	int GetNumOfSource() const
	{
		return numOfSource;
	}
	friend std::ostream & operator << (std::ostream & out, const Order & order) 
	{
		return out << order.numOfSource << " " << order.numInSource << " " << order.timeOfArrive << "\n";
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