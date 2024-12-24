#include <iostream>

using namespace std;

class Strategy {
public:
	int z;
	Strategy(int z):z(z){};
	Strategy& operator=(const Strategy& rhs)
	{
		if (this != &rhs)
		{
			this->z = rhs.z;
		}
		return *this;
	}
};

class Strategy1: public Strategy {
public:
	int x;
	Strategy1(int val): Strategy(val){
		this->x = val;
	};
	Strategy1& operator=(const Strategy1& rhs)
	{
		if (this!=&rhs)
		{
			this->x = rhs.x;
		}
		return *this;
	}
};

class Strategy2: public Strategy {
public:
	int y;
	Strategy2(int val): Strategy(val) {
		this->y = val;
	};
	Strategy& operator=(const Strategy2& rhs)
	{
		if (this != &rhs)
		{
			this->y = rhs.y;
		}
		return *this;
	}
};

int main() {
	Strategy1 s1(20);
	Strategy1 s2(40);

	Strategy* ptr1 = &s1;
	Strategy* ptr2 = &s2;

	*ptr1 = *ptr2;

	return 0;
}