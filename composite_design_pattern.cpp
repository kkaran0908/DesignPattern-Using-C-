#include <iostream>
#include <vector>

using namespace std;

struct PrcUpdate
{
	double bid;
	double ask;
	uint32_t sequence_no;
};

class IMarketFeed{
public:
	virtual void ProcessUpdate() = 0;
	virtual ~IMarketFeed() = default;
};

class SinglePriceUpdateManager: IMarketFeed{
	PrcUpdate price_update;
public:
	SinglePriceUpdateManager(double bid, double ask, uint32_t sequence_no) : price_update{bid, ask, sequence_no}{};
	void ProcessUpdate() override
	{
		std::cout << "SequenceNo=" << price_update.sequence_no << ", bid=" << price_update.bid <<", ask=" << price_update.ask << std::endl;
	}
};

class BundledPriceUpdateManager: IMarketFeed{
	vector<SinglePriceUpdateManager*> single_price_update_manager_;
public:
	BundledPriceUpdateManager(vector<SinglePriceUpdateManager*> single_price_update_manager) : single_price_update_manager_(single_price_update_manager){};
	void ProcessUpdate()
	{
		for (const auto& single_price_update_manager : single_price_update_manager_)
		{
			single_price_update_manager->ProcessUpdate();
		}
	}
};

int main()
{
	SinglePriceUpdateManager spm1(10,20,1);
	SinglePriceUpdateManager spm2(11,21,2);
	SinglePriceUpdateManager spm3(12,22,3);
	SinglePriceUpdateManager spm4(13,20,4);
	SinglePriceUpdateManager spm5(14,21,5);
	vector<SinglePriceUpdateManager*> price_bundle{&spm2, &spm3, &spm4};
	BundledPriceUpdateManager bpm(price_bundle);

	bpm.ProcessUpdate();

	return 0;

}