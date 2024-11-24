#include <iostream>

template<typename T>
class OrderManager
{
public:
	void PerformTask()
	{
		T* t = static_cast<T*>(this);

		t->SendOrder();
	}
};

class MarketOrderManager : public OrderManager<MarketOrderManager>
{
public:
	void SendOrder()
	{
		std::cout << "Sending Market Order to the Exchange!" << std::endl;
	}

};

class LimitOrderManager : public OrderManager<LimitOrderManager>
{
public:
	void SendOrder()
	{
		std::cout << "Sending Limit Order to the Exchange" << std::endl;
	}
};

int main()
{
	LimitOrderManager*  order_manager = new LimitOrderManager();
	order_manager->PerformTask();

	delete order_manager;

	return 0;
}