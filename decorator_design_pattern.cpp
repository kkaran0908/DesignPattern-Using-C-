#include <iostream>
using namespace std;

class TradeOperation
{
public:
	virtual void ExecuteTrade(const std::string& tradeInfo) = 0;
	virtual ~TradeOperation() = default;
};

class BasicTradeInfo: public TradeOperation{
public:
	virtual void ExecuteTrade(const std::string& tradeInfo) override
	{
		std::cout << "BasicTradeInfo: tradeInfo" << std::endl;
	}

	~BasicTradeInfo()=default;
};

class AuditTradeHandler : public TradeOperation{
	TradeOperation* tp = nullptr;
public:
	AuditTradeHandler(TradeOperation* t) : tp(t){};
	virtual void ExecuteTrade(const std::string& tradeInfo) override
	{
		if (tp)
		{
			tp->ExecuteTrade(tradeInfo);
		}
		else
		{
			std::cout << "Something went wrong" << std::endl;
		}
	}
	~AuditTradeHandler() = default;
};

int main()
{
	BasicTradeInfo t;
	AuditTradeHandler* ath = new AuditTradeHandler(&t);

	ath->ExecuteTrade("100 lot of ES-FEB25 executed");

	delete ath;
	return 0;
}