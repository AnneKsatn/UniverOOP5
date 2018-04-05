#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<atomic>
#include<mutex>
#include<queue>
#include <memory> 
#include <iomanip>
#include "NumberMultiplier.h"

// Ёнтони ”иль€мс - ћногопоточное програмимрование

template <typename T>
class ThreadSafeQueue
{
private:
	mutable std::mutex mut;
	std::queue<std::shared_ptr<T>> dataQueue;
	std::condition_variable data_cond;
public:
	ThreadSafeQueue() {};


	void waitAndPop(T& value) {
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !dataQueue.empty(); });
		value = std::move(*dataQueue.front());
		dataQueue.pop();
	}

	void push(T& new_data) {
		std::shared_ptr<T> data(std::make_shared<T>(std::move(new_data)));
		std::lock_guard<std::mutex> lk(mut);
		dataQueue.push(std::move(data));
		data_cond.notify_one();
	}

	bool tryPop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (dataQueue.empty())
			return false;
		value = std::move(*dataQueue.front());
		dataQueue.pop();
		return true;
	}

	bool empty() const {
		std::lock_guard<std::mutex> lk(mut);
		return dataQueue.empty();
	}

	std::shared_ptr<T> tryPopS()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (dataQueue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res = dataQueue.front();
		dataQueue.pop();
		return res;
	}

	std::shared_ptr<T> waitAndPopS()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !dataQueue.empty(); });
		std::shared_ptr<T> res = dataQueue.front();
		dataQueue.pop();
		return res;
	}
};



