#include <iostream>
using namespace std;

//abstract interface for PriceManager
class IPriceManager {
public:
	virtual void ProcessPriceUpdate() = 0;
	virtual ~IPriceManager() = default;
};


//concrete class to handle priceUpdate from Crypto Market Segment
class CryptoPriceManager : public IPriceManager {
public:
	void ProcessPriceUpdate() override
	{
		cout << "Processing price update for crypto market segment!" << endl;
	}
};

//concrete class to handle priceUpdate from Equity Market Segment
class EquityPriceManager: public IPriceManager {
public:
	void ProcessPriceUpdate() override
	{	
		cout << "Processing price update for equity market segment!" << endl;

	}
};

//Abstract factory for creating priceUpdate handler for different market segments
class IPriceManagerFactory {
public:
	virtual IPriceManager* CreatePriceManagerFactory() = 0;

	virtual ~IPriceManagerFactory() = default;
};


//Concrete factory for crypto market segment
class CryptoPriceManagerFactory: public IPriceManagerFactory {
public:
	IPriceManager* CreatePriceManagerFactory() override
	{
		return new CryptoPriceManager();
	}
};

//concrete factory for equity market segment
class EquityPriceManagerFactory: public IPriceManagerFactory {
public:
	IPriceManager* CreatePriceManagerFactory() override
	{
		return new EquityPriceManager();
	}
};


void PriceManager (IPriceManagerFactory* pmf)
{
	IPriceManager* f = pmf->CreatePriceManagerFactory();
	f->ProcessPriceUpdate();
	delete f;
}

int main()
{
	 IPriceManagerFactory* f = new CryptoPriceManagerFactory();
	 PriceManager(f);
	 delete f;
	 return 0;
}

