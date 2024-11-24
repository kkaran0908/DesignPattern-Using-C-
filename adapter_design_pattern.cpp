#include <iostream>

using namespace std;

//interface to send the order
class IOrderSenderManager
{
public:
	virtual void SendOrder() = 0;
	virtual ~IOrderSenderManager() = default;
};

//fix protocol api provided by exchange
class FixExchangeApi{
public:
	void PlaceOrderUsingFixProtocol()
	{
		cout << "Using fix to send the order to the market" << endl;
	}
};

//binary protocol api provided by exchange
class BinaryExchangeApi{
public:
	void PlaceOrderUsingBinaryProtocol()
	{
		cout << "using binary protocol to send the order to the market" << endl;
	}
};

//adapter to send the order using binary protocol
class BinaryOrderSenderManager : public IOrderSenderManager{
	BinaryExchangeApi bin_exch_api;
public:
	void SendOrder() override
	{
		bin_exch_api.PlaceOrderUsingBinaryProtocol();
	}
};

//adapter to send the order using fix protocol
class FixOrderSenderManager : public IOrderSenderManager{
	FixExchangeApi fix_exch_api;
public:
	void SendOrder() override
	{
		fix_exch_api.PlaceOrderUsingFixProtocol();
	}
};

//client code to place the order using different exchange protocol
void PlaceOrder(IOrderSenderManager* order_sender)
{
	order_sender->SendOrder();
}

int main()
{
	IOrderSenderManager* order_sender = new BinaryOrderSenderManager();

	PlaceOrder(order_sender);

	delete order_sender;

	return 0;
}






