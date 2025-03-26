#include <iostream>
#include <queue>
#include <vector>
#include <mutex>
#include <functional>
#include <thread>
#include <condition_variable>

class Actor {
public:
    void Run() {
        while(1) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this] {return !task_queue.empty() || stop;});
                if (task_queue.empty() && stop)
                {
                    break;
                }
                task = std::move(task_queue.front());
                task_queue.pop();
            }
            task();
        }
    }
    
    void Send(const std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            task_queue.push(std::move(task));
        }
        cv.notify_one();
    }
    
    void Shutdown() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::function<void()>> task_queue;
    bool stop = false;
};
int main()
{
    const int num_of_actors = 5;
    std::vector<Actor> actor(num_of_actors);
    std::vector<std::thread> actor_thread;
    for (int i =0; i<num_of_actors; i++)
        actor_thread.emplace_back(&Actor::Run, &actor[i]);
    
    for(int i =0; i<100;i++)
        actor[i%num_of_actors].Send([i](){std::cout << "This task is executing via actor model, task_id:\t" << i << std::endl;});
    
    for (auto& act: actor)
        act.Shutdown();
    
    for (int i =0; i<num_of_actors; i++) {
        if (actor_thread[i].joinable())
            actor_thread[i].join();
    }
    return 0;
}