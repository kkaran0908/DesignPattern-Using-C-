#include <iostream>
#include <vector>
using namespace std;

class MemoryManager{
	std::vector<void*> freeList;
	char* memoryBlock;
	std::size_t objectSize;
	std::size_t totalCapacity;

public:
	MemoryManager(const std::size_t objectSize, const std::size_t numOfObj)
	{
		memoryBlock = new char[objectSize*numOfObj];

		for(int i =0; i<numOfObj;i++)
		{
			freeList.push_back(memoryBlock + i*objectSize);
		}
	}

	~MemoryManager()
	{
		delete[] memoryBlock;
	}

	void* allocateMemory()
	{
		if (freeList.empty())
		{
			throw std::bad_alloc();
		}
		else
		{
			void* memoryChunk = freeList.back();
			freeList.pop_back();
			return memoryChunk;
		}
	}

	void deallocateMemory(void* memoryChunk)
	{
		freeList.push_back(memoryChunk);
	}
};

class Order
{
	double qty;
	double price;
public:
	Order(double qty, double price): qty(qty), price(price){};

	void DispOrderParams()
	{
		std::cout << "OrderQty:\t" << this->qty << ", Price:\t" << this->price << std::endl;
	}

	static MemoryManager memoryManager;

	void* operator new(std::size_t size)
	{
		return memoryManager.allocateMemory();
	}

	void operator delete(void* ptr)
	{
		memoryManager.deallocateMemory(ptr);
	}
};

MemoryManager Order::memoryManager(sizeof(Order), 10);

int main()
{
	Order* obj;
	for (int i =0; i<100; i++)
	{
		obj = new Order(10,20);
		obj->DispOrderParams();
	}	

	delete obj;

	return 0;


}