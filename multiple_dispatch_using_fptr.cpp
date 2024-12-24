#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <map>

class PassiveStrategy;
class AggressiveStrategy;

class Strategy {
public:
	virtual ~Strategy() = default;
	virtual std::type_index getType() const = 0;
};

class AggressiveStrategy : public Strategy {
public:

	virtual std::type_index getType() const {
		return typeid(AggressiveStrategy);
	}
};

class PassiveStrategy : public Strategy {
public:
	virtual std::type_index getType() const {
		return typeid(PassiveStrategy);
	}
};

using DispatchKey = std::pair<std::type_index, std::type_index>;
using DispatchFunction = std::function<void(Strategy&, Strategy&)>;

class Dispatcher{
	std::map<DispatchKey, DispatchFunction> dispatchTable;
public:
	template<typename t1, typename t2>
	void RegisterDispatchFunction(void(*fun)(t1&, t2&)) {
		dispatchTable[{typeid(t1), typeid(t2)}] = [fun](Strategy& s1, Strategy& s2) {
			fun(dynamic_cast<t1&>(s1), dynamic_cast<t2&>(s2));
		};
	}

	void dispatch(Strategy& s1, Strategy& s2) const {
		const auto dispatchKey = std::make_pair(s1.getType(), s2.getType());

		auto it = dispatchTable.find(dispatchKey);

		if (it != dispatchTable.end())
		{
			it->second(s1, s2);
		}
		else
		{
			std::cout << "No Handler to handle this case" << std::endl;
		}
	}
};

void handleAggressiveWithAggressive(AggressiveStrategy& s1, AggressiveStrategy& s2) {
    std::cout << "Handling Aggressive vs Aggressive" << std::endl;
}
void handleAggressiveWithPassive(AggressiveStrategy& s1, PassiveStrategy& s2) {
    std::cout << "Handling Aggressive vs Passive" << std::endl;
}
void handlePassiveWithPassive(PassiveStrategy& s1, PassiveStrategy& s2) {
    std::cout << "Handling Passive vs Passive" << std::endl;
}
void handlePassiveWithAggressive(PassiveStrategy& s1, AggressiveStrategy& s2) {
    std::cout << "Handling Passive vs Aggressive" << std::endl;
}

int main() {
	AggressiveStrategy a1, a2;
	PassiveStrategy p1, p2;
	Dispatcher d;

	d.RegisterDispatchFunction<AggressiveStrategy, AggressiveStrategy>(handleAggressiveWithAggressive);
	d.RegisterDispatchFunction<AggressiveStrategy, PassiveStrategy>(handleAggressiveWithPassive);

	d.dispatch(a1, p1);
	return 0;
}
