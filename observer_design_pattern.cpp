/*
ObserverDesignPattern:
** It is mainly used in event driven systems ie when we want to notify all the interested components
about some event, we generally use observer design pattern
Example-1: YouTube wants to notify all the channel subscribers about new content upload on the subscribed channel
Example-2: You want your strategy to take certain actions whenever there is some price-update in the exchange
*/

#include <iostream>
#include <vector>
#include <string>

class Component
{
public:
	virtual void OnTrades(double last_traded_price) = 0;
};

/*Similar to Strategy component there can be many other components which are interested in 
price-udapte from the price-client library, so any component 
interested in price-update can register themselves*/
class Strategy : public Component
{
private:
	std::string component_name;
public:
	Strategy(std::string name): component_name(name){};
	void OnTrades(double last_traded_price) override
	{
		std::cout << "Price Update Received!\n last_trade_price: " << last_traded_price << std::endl;
		//whenever there is price-update, strategy can take certain action such as exiting the position etc etc
	}
};

class Price
{
public:
	virtual void SubscribePrices(Component* component) = 0;
	virtual void UnsubscribePrices(Component* component) = 0;
	virtual void NotifyAll() = 0;
};

class PriceClient : public Price
{
	std::vector<Component*> price_observers;
	double last_trade_price;
public:
	void SubscribePrices(Component* component) override
	{
		price_observers.push_back(component);
	}

	void UnsubscribePrices(Component* component) override
	{
		price_observers.erase(std::remove(price_observers.begin(), price_observers.end(), component), price_observers.end());
	}

	void NotifyAll() override
	{
		for(auto observer: price_observers)
		{
			observer->OnTrades(last_trade_price);
		}
	}

	void PriceUpdate(double ltp) 
	{
		last_trade_price = ltp;
		NotifyAll();
	}
};

int main()
{	
	Strategy st("Strategy");
	PriceClient* pc = new PriceClient();

	pc->SubscribePrices(&st);

	pc->PriceUpdate(100);

	pc->UnsubscribePrices(&st);

	pc->PriceUpdate(200);

	return 0;
}