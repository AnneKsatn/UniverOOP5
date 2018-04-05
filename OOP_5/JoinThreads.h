#pragma once
#include<thread>
#include<vector>
#include<iostream>

class JoinThreads
{
	std::vector<std::thread>& threads;
public:
	explicit JoinThreads(std::vector<std::thread>& threads_) : threads(threads_) {};

	~JoinThreads()
	{
		for (unsigned long i = 0; i < threads.size(); i++)
		{
			if (threads[i].joinable())
				threads[i].join();
		}

		std::cout << "ALL DELETE    ";
	}
};