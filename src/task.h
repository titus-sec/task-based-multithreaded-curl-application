#ifndef TASK_H
#define TASK_H

// Abstract base class: a task to be executed
class Task
{
public:
	virtual ~Task()
	{
		delete this;
	}

	// perform the task
	virtual void run() = 0;
	
};

#endif
