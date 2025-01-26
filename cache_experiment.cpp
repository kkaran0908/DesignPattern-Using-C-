#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
using namespace std;


struct PaddedAtomic
{
	PaddedAtomic():counter(0){};
	std::atomic<int> counter;
	char padding[64-sizeof(std::atomic<int>)];
};
//Data structure to avoid false sharing
struct OptData
{
	PaddedAtomic counter1;
	PaddedAtomic counter2;
};
//Data structure where false sharing can happen
struct Data
{
	Data(): counter1(0), counter2(0){};
	std::atomic<int> counter1;
	std::atomic<int> counter2;
};

void IncreaseValue(std::atomic<int>& val)
{
	for(int i =0; i<99999999; i++) {
		val++;
	}
}

int main()
{	
	Data d;
	auto time1 = std::chrono::high_resolution_clock::now();

	std::thread t1(IncreaseValue, std::ref(d.counter1));
	std::thread t2(IncreaseValue, std::ref(d.counter2));

	auto time2 = std::chrono::high_resolution_clock::now();

	t1.join();
	t2.join();

	std::cout << "Calculation time using non-cache friendly data structure:\t" << std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count() << std::endl;


	OptData d1;
	time1 = std::chrono::high_resolution_clock::now();

	std::thread t3(IncreaseValue, std::ref(d1.counter1.counter));
	std::thread t4(IncreaseValue, std::ref(d1.counter2.counter));

	time2 = std::chrono::high_resolution_clock::now();

	t3.join();
	t4.join();

	std::cout << "Calculation time using cache friendly data structure:\t" << std::chrono::duration_cast<std::chrono::microseconds>(time2-time1).count() << std::endl;
	return 0;
}