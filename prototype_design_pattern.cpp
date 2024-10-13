/*
Nice article written by Amresh on Medium: https://medium.com/@kamresh485/prototype-pattern-in-c-068824ce0306
*/
#include <iostream>

//Type of order user can create
enum OrderType
{
	LimitOrder		= 	0,
	MarketOrder 	= 	1
};

std::string OrderTypeToString(OrderType order_type)
{
	switch(order_type)
	{
	case OrderType::LimitOrder:
		return "LimitOrder";
	case OrderType::MarketOrder:
		return "MarketOrder";
	default:
		return "Error: InvalidOrderType"; 
	}
}

class Order
{
public:
	Order () = delete; // there must be no order in the system with default params 
	Order (int order_qty, int order_price, OrderType order_type) : 
	order_qty(order_qty),
	order_price(order_price),
	order_type(order_type)
	{};

	//clone method will clone the existing object
	//we need to carefully design this function and if class is containing dynamically allocated
	//resources, we are suppsoed to create the deep copy instead of shallow copy
	Order* clone()
	{
		Order* obj = new Order(this->order_qty, this->order_price, this->order_type);
		return obj;
	}

	/*if user want to update any of the member
	variables such as qty, price, orderType, he/she can update 
	using below function calls*/
	void UpdateQty(const int order_qty)
	{
		this->order_qty = order_qty;
	}

	void UpdatePrice(const int order_price)
	{
		this->order_price = order_price;
	}

	void UpdateOrderType(const OrderType order_type)
	{
		this->order_type = order_type;
	}

	void DisplayOrderFields() const
	{
		std::cout << "OrderQty:\t" << this->order_qty
				<< "\nOrderPrice:\t" << this->order_price
				<< "\nOrderType:\t" << OrderTypeToString(this->order_type) << std::endl;
	}

	~Order()
	{
		std::cout << "Cleaning up the order data" << std::endl;
	}

private:
	int order_qty;
	double order_price;
	OrderType order_type;
};

int main()
{
	Order* order = new Order(10,100,OrderType::LimitOrder);
	order->DisplayOrderFields();

	Order* cloned_order = order->clone();

	cloned_order->UpdateOrderType(OrderType::MarketOrder);

	cloned_order->DisplayOrderFields();
	delete order;
	delete cloned_order;
	return 0;
}