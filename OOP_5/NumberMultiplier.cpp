#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<string>
#include <cstdlib>
#include<mutex>
#include<fstream>
#include<thread>
#include <stdint.h>
#include "NumberMultiplier.h"

using namespace std;

mutex mutx;


void NumberMultiplier::findAllMultiplier(uint64_t n) {
	s= to_string(n)+ " = ";
	while (true) {
		if (!isPrime(n)) {
			uint64_t k = findNextMultiplier(n);
			multiplier.push_back(k);
			string add = to_string(k);
			s = s + add + "*";
			n = n / k;
		}
		else break;
	}
	multiplier.push_back(n);
	string add = to_string(n);
	s = s + add;
	lock_guard<mutex> lk(mutx);
	result.push_back(s);
	return;
}

void NumberMultiplier::findAndSave(uint64_t n, ThreadSafeQueue<string>& value) {
	findAllMultiplier(n);
	value.push(multiplierInString());
	return;
}

uint64_t NumberMultiplier::checkMultiplier() {
	uint64_t number = 1;
	for (int i = 0; i < multiplier.size(); i++) {
		number = number*multiplier[i];
	}
	return number;
}


string NumberMultiplier::multiplierInString() {
	return s;
}


uint64_t NumberMultiplier::findNextMultiplier(uint64_t n) {
	uint64_t i, multiplier;
	i = 1;
	vector<uint64_t> x(20000);
	x[0] = 2;
	multiplier = 1;
	while (multiplier == 1) {
		i++;
		x[i] = (x[i - 1] * x[i - 1] + 1) % n;
		for (uint64_t j = 1; j < i; j++) {
			multiplier = findGcd(x[i] - x[j], n);
		    if (multiplier != 1) break;
		}
	}
	return multiplier;
}


uint64_t NumberMultiplier::findGcd(uint64_t a, uint64_t b) {
	return b ? findGcd(b, a % b) : a;
}


bool NumberMultiplier::isPrime(uint64_t n) {
	for (uint64_t i = 2; i <= sqrt(n); i++)
		if (n%i == 0)
			return false;
	return true;
}


