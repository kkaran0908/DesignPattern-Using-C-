#include <iostream>

using namespace std;

class PassiveStrategy;
class AggressiveStrategy;

class Strategy {
public:
	virtual void HandleCombinationOfStrategy(Strategy& s) = 0;
	virtual void HandleCombo(const PassiveStrategy& s) = 0;
	virtual void HandleCombo(const AggressiveStrategy& s) = 0;
	virtual ~Strategy() = default;
};

class AggressiveStrategy : public Strategy {
public:
	virtual void HandleCombinationOfStrategy(Strategy& s)
	{
		s.HandleCombo(*this);
	}
	virtual void HandleCombo(const AggressiveStrategy& s)
	{
		std:cout << "Handling combination of Aggressive and Aggresive using AggressiveStrategy" << std::endl;
	}

	virtual void HandleCombo(const PassiveStrategy& s)
	{
		std:cout << "Handling combination of Passive and Aggresive using AggressiveStrategy" << std::endl;
	}
};

class PassiveStrategy : public Strategy {
public:
	virtual void HandleCombinationOfStrategy(Strategy& s)
	{

		s.HandleCombo(*this);
	}

	virtual void HandleCombo(const AggressiveStrategy& s)
	{
		std:cout << "Handling combination of Passive and Aggresive using passive strategy" << std::endl;
	}

	virtual void HandleCombo(const PassiveStrategy& s)
	{
		std:cout << "Handling combination of Passive and Passive using passive strategy" << std::endl;
	}
};

int main()
{
	Strategy* s = new PassiveStrategy();
	AggressiveStrategy a;

	s->HandleCombinationOfStrategy(a);

	delete s;
	return 0;
}
