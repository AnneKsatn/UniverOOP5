#pragma once
#include<string>
#include<vector>
#include<queue>
#include <stdint.h>
#include<fstream>
#include"ThreadSafeQueue.h"



class NumberMultiplier {
public:


	void findAllMultiplier(uint64_t n);
	uint64_t checkMultiplier();
	std::string multiplierInString();
	void findAndSave(uint64_t n, ThreadSafeQueue<std::string>& value);

private:

	std::string s;
	std::vector<uint64_t>  multiplier;
	std::vector<std::string>  result;
	uint64_t findNextMultiplier(uint64_t n);
	uint64_t findGcd(uint64_t a, uint64_t b);
	bool isPrime(uint64_t n);

};
