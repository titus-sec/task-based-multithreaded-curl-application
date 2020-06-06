#include "farm.h"

void Farm::add_task(Task *task) // add a task pointer to the task queue
{
	taskQueue.push(task);
}

void Farm::run()
{
	// run() is using fork-join design pattern

	std::vector<std::thread> threads;
	int con_threads = std::thread::hardware_concurrency(); // storing the number of concurrent threads supported

	for (int i = 0; i < con_threads; ++i)
	{
		// thread worker function
		// each time round the loop, remove a task from the task queue
		// run the task
		// delete the task pointer
		threads.push_back(std::thread([&] // starting all supported threads
		{
			while (!taskQueue.empty()) // do the tasks until the task queue is empty
			{
				Task* myTask;
				
				std::mutex queueMutex;

				queueMutex.lock(); // protecting the shared resource

				myTask = taskQueue.front();
				taskQueue.pop();

				queueMutex.unlock();

				myTask->run();
			}
		}));
	}

	// join all ran threads
	for (auto& t : threads)
	{
		t.join();
	}
}