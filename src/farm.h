#ifndef FARM_H
#define FARM_H

#include <queue> // std::queue
#include <thread> // std::thread
#include <mutex> // std::mutex
#include <memory>
#include "task.h"

// a collection of tasks that are ran in parallel - farming pattern
class Farm {
public:
	// add a task to the Farm and delete once it has been run
	void add_task(Task *task);

	// run all the tasks that have been added (with add_task()) to the Farm
	void run();

private:
	std::queue<Task*> taskQueue; // a queue of Task(s)
};

#endif
