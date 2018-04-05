#include<iostream>
#include<vector>
#include<cstdlib>
#include <fstream>
#include<cmath>
#include<string>
#include"WaitCommand.h"
#include <cstdlib>
#include "NumberMultiplier.h"
#include <windows.h>
#include"ThreadSafeQueue.h"
#include<thread>
#include"ThreadPool.h"


using namespace std;


int main() {

	setlocale(LC_ALL, "Russian");

	WaitCommand waiting;
	uint64_t number;
	ThreadSafeQueue<string> value;
	string fileInName;
	string fileOutName;
	int count;


	cout << " Введите колличество вычислительных потоков   ";
	cin >> count;
    cout << "Название файла ввода    ";
	cin >> fileInName;
	cout << "Название файла вывода   ";
	cin >> fileOutName;


	ThreadPool pool(count);
	ifstream fin(fileInName);
	ofstream fout(fileOutName);

	std::thread thr(&WaitCommand::work, &waiting);
	while (waiting.pause()) {};
	cout << "Начало считывания";


	while (!fin.eof()) {
			if (waiting.pause()) {
				fout.close();
				while ((waiting.pause()) && (!waiting.exit())) {}
				fout.open(fileOutName, ios::app);
				}


		if (waiting.exit()) break;
		if (pool.empty()) {
			fin >> number;
			NumberMultiplier multiplier;
			auto f = bind(&NumberMultiplier::findAndSave, multiplier, number, ref(value));
			pool.submit(f);
		}

		if (!value.empty()) {
			fout << *value.waitAndPopS() << "\n";
		}

	}

	if (!waiting.exit())
	while (!pool.empty()) {}

	pool.~ThreadPool();

	while (true) {
		if (!value.empty()) {
			fout << *value.waitAndPopS()<< "\n";
		}
		else break;
	}

	waiting.stop();
	thr.join();
	system("pause");
}
