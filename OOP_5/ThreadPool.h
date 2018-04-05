#pragma once

#include<iostream>
#include<vector>
#include<thread>
#include<atomic>
#include"ThreadSafeQueue.h"
#include "NumberMultiplier.h"
#include"JoinThreads.h"


class ThreadPool {
	std::atomic_bool done;
	std::vector<std::thread> threads;
	ThreadSafeQueue<std::function<void()> > work_queue;
	JoinThreads joiner;
	int size;

	void worker_thread()
	{
		while (!done)
		{
			std::function<void()> task;
			if (work_queue.tryPop(task))
			{
				task();
				size--;
			}
			else {
				std::this_thread::yield();
			}
		}
	}


public:

	bool empty() {
		return  work_queue.empty();
	}

	ThreadPool(int n) : done(false), joiner(threads)
	{
		unsigned const thread_count = n;
		try {
			for (unsigned i = 0; i < thread_count; ++i)
			{
				threads.push_back(std::thread(&ThreadPool::worker_thread, this));
			}
		}

		catch (...) {
			done = true;
			throw;
		}
	}

	~ThreadPool() {
		done = true;
	}


	template<typename FunctionType>

	void submit(FunctionType f)
	{
		work_queue.push(std::function<void()>(f));
		size++;
	}

};