#include <iostream>
#include <memory>

using namespace std;

//exchange interface
class IExchange
{
public:
	virtual void SendOrder(const std::string orderType) = 0;
	virtual ~IExchange() = default;
};

//concrete implementation of eurex
class Eurex : public IExchange
{
public:
	void SendOrder(const std::string orderType) override
	{
		cout << "Sending " << orderType << " to eurex market" << endl;
	}

	~Eurex()
	{
		cout << "Cleaning done for eurex" << endl; 
	}
};

//concrete implementation of ice
class ICE : public IExchange
{
public:
	void SendOrder(const std::string orderType) override
	{
		cout << "Sending " << orderType << " to ICE market" << endl;
	}

	~ICE()
	{
		cout << "Cleaning done for ice" << endl; 
	}

};

class Order
{
protected:
	shared_ptr<IExchange> exchange_;
public:
	Order(shared_ptr<IExchange> exchange) : exchange_(std::move(exchange)){};
	virtual void SubmitOrder() = 0;
	virtual ~Order() = default;
};

class LimitOrder: public Order
{
public:
	LimitOrder(shared_ptr<IExchange> exchange) : Order(std::move(exchange)){};
	void SubmitOrder() override
	{
		exchange_->SendOrder("LimitOrder");
	}

	~LimitOrder()
	{
		cout << "LimitOrder resources deleted" << endl;
	}
};

class MarketOrder: public Order
{
public:
	MarketOrder(shared_ptr<IExchange> exchange) : Order(std::move(exchange)){};
	void SubmitOrder() override
	{
		exchange_->SendOrder("MarketOrder");
	}

	~MarketOrder()
	{
		cout << "MarketOrder resources deleted" << endl;
	}
};

int main()
{
	auto eurex = make_shared<Eurex>();
	auto ice = make_shared<ICE>();

	LimitOrder limit_order(ice);
	limit_order.SubmitOrder();

	return 0;

}

