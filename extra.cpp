//*/else
//{
//	for (int i = 0; i < 1; ++i)
//	{
//		for (int j = 0; j < numOfSources; ++j)
//		{
//			orders.push_back(sources[j].Generate(globalTime));
//			std::cout << "GENERATE" << " source " << j << " # " << sources[j].GetNumOfOrders() << " time " << sources[j].GetTimeOfArrive() << '\n';
//		}
//		int k = 0;
//		while (CanContinue(sources))
//		{
//			Order order = orders[ChooseSource(orders)];
//			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
//			{
//				Order order2 = buffer.Take();
//				if (order2.GetTimeOfArrive() == -1)
//				{
//					devices[deviceToUse].Service(globalTime);
//					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
//						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
//					std::cout << "SERVICE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " release " << devices[deviceToUse].GetTimeOfRelease() << " service " << devices[deviceToUse].GetTimeOfService() << '\n';
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//					sources[order.GetNumOfSource()].IncNumOfSuceed();
//					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
//					std::cout << "GENERATE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " time " << sources[order.GetNumOfSource()].GetTimeOfArrive() << '\n';
//				}
//				else
//				{
//					devices[deviceToUse].Service(globalTime);
//					sources[order2.GetNumOfSource()].UpDateTimeOfWaitingAndService(
//						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
//					std::cout << "SERVICE" << " source " << order2.GetNumOfSource() << " # " << sources[order2.GetNumOfSource()].GetNumOfOrders()
//						<< " release " << devices[deviceToUse].GetTimeOfRelease() << " service " << devices[deviceToUse].GetTimeOfService() << '\n';
//					sources[order2.GetNumOfSource()].IncNumOfSuceed();
//				}
//			}
//			else
//			{
//				int orderToRefuse = buffer.Put(order);
//				if (orderToRefuse == -1)
//				{
//					std::cout << "TO BUFFER" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders() << '\n';
//					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
//					std::cout << "GENERATE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " time " << sources[order.GetNumOfSource()].GetTimeOfArrive() << '\n';
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//				}
//				else
//				{
//					std::cout << "OUT BUFFER" << " source " << orderToRefuse << " # " << sources[orderToRefuse].GetNumOfOrders() << '\n';
//					sources[orderToRefuse].IncNumOfRefuse();
//					orders.push_back(sources[order.GetNumOfSource()].Generate(globalTime));
//					std::cout << "GENERATE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " time " << sources[order.GetNumOfSource()].GetTimeOfArrive() << '\n';
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//				}
//			}
//			deviceToUse = ChooseDevice(devices, deviceToUse);
//		}
//		while (!orders.empty())
//		{
//			Order order = orders[ChooseSource(orders)];
//			if (devices[deviceToUse].GetTimeOfRelease() < order.GetTimeOfArrive())
//			{
//				Order order2 = buffer.Take();
//				if (order2.GetTimeOfArrive() == -1)
//				{
//					devices[deviceToUse].Service(globalTime);
//					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
//						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
//					std::cout << "SERVICE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " release " << devices[deviceToUse].GetTimeOfRelease() << " service " << devices[deviceToUse].GetTimeOfService() << '\n';
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//					sources[order.GetNumOfSource()].IncNumOfSuceed();
//				}
//				else
//				{
//					devices[deviceToUse].Service(globalTime);
//					sources[order.GetNumOfSource()].UpDateTimeOfWaitingAndService(
//						devices[deviceToUse].GetTimeOfRelease(), devices[deviceToUse].GetTimeOfService());
//					std::cout << "SERVICE" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders()
//						<< " release " << devices[deviceToUse].GetTimeOfRelease() << " service " << devices[deviceToUse].GetTimeOfService() << '\n';
//					sources[order2.GetNumOfSource()].IncNumOfSuceed();
//				}
//			}
//			else
//			{
//				int orderToRefuse = buffer.Put(order);
//				if (orderToRefuse == -1)
//				{
//					std::cout << "TO BUFFER" << " source " << order.GetNumOfSource() << " # " << sources[order.GetNumOfSource()].GetNumOfOrders() << '\n';
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//				}
//				else
//				{
//					std::cout << "OUT BUFFER" << " source " << orderToRefuse << " # " << sources[orderToRefuse].GetNumOfOrders() << '\n';
//					sources[orderToRefuse].IncNumOfRefuse();
//					orders.erase(std::remove(orders.begin(), orders.end(), order), orders.end());
//				}
//			}
//			deviceToUse = ChooseDevice(devices, deviceToUse);
//			++k;
//		}
//		GetResults(sources, devices, globalTime);
//		Clear(devices);
//		Clear(sources);
//		orders.clear();
//		buffer.Clear();
//	}
//}*/