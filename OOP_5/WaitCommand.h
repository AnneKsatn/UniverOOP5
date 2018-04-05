#pragma once
#include<cstdlib>
#include <fstream>
#include<cmath>
#include<string>
#include <cstdlib>
#include "NumberMultiplier.h"
#include <windows.h>
#include"ThreadSafeQueue.h"
#include<thread>
#include"ThreadPool.h"

using namespace std;

class WaitCommand {
	bool pause_;
	bool exit_;
public:

	WaitCommand() {
		pause_ = true;
		exit_ = false;
	}

	bool pause() {
		return pause_;
	}

	bool exit() {
		return exit_;
	}

	void stop() {
		exit_=true;
	}


	void work() {

		pause_ = false;
		string command;

		while ((true)&&(!exit())) {
			cin >> command;
			if (command == "exit") {
				exit_ = true;
				break;
			}
			if (command == "pause") {
				pause_ = true;
			}
			if (command == "resume") {
				pause_ = false;
			}
		}
	}
};