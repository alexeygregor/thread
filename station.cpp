#include <cassert>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

mutex station;
mutex depo_access;
vector<int>depo = {0, 0, 0};

bool TrainA(int train1)
{
	this_thread::sleep_for(chrono::seconds(train1));
	depo_access.lock();
	for (int i = 0; i < 3; ++i)
	{
		if (depo[i] > 0 && i != 0)
		{
			cout << "\nTrain A in depo" << endl;
			break;
		}
	}
	depo[0] = 1;
	depo_access.unlock();
	return true;
}

bool TrainB(int train2)
{
	this_thread::sleep_for(chrono::seconds(train2));
	depo_access.lock();
	for (int i = 0; i < 3; ++i)
	{
		if (depo[i] > 0 && i != 1)
		{
			cout << "\nTrain B in depo" << endl;
			break;
		}
	}
	depo[1] = 2;
	depo_access.unlock();
	return true;
}

bool TrainC(int train3)
{
	this_thread::sleep_for(chrono::seconds(train3));
	depo_access.lock();
	for (int i = 0; i < 3; ++i)
	{
		if (depo[i] > 0 && i != 2)
		{
			cout << "\nTrain C in depo" << endl;
			break;
		}
	}
	depo[2] = 3;
	depo_access.unlock();
	return true;
}

void Admin(int value)
{
	string command;
	int q = 0;
	while (q != -1)
	{
		cin >> command;
		if (command == "depart")
		{
			depo[value] = 0;
			q--;
		}
	}
}

int Station(int count)
{
	station.lock();
	for (int i = 0; i < 3; ++i)
	{
		if (depo[i] == 1)
		{
			cout << "\nTrain A in station" << endl;
			Admin(i);
			count++;
			break;
		}
		if (depo[i] == 2)
		{
			cout << "\nTrain B in station" << endl;
			Admin(i);
			count++;
			break;
		}
		if (depo[i] == 3)
		{
			cout << "\nTrain C in station" << endl;
			Admin(i);
			count++;
			break;
		}
	}
	station.unlock();
	return count;
}

int main()
{
	int A = 0, B = 0, C = 0;
	cout << "Input travel time A, B, C: ";
	cin >> A >> B >> C;
	assert(A > 0 && B > 0 && C > 0);
	thread train1(TrainA, A);
	thread train2(TrainB, B);
	thread train3(TrainC, C);

	int count = 0;
	while (count != 3)
	{
		if (TrainA)
		{
			count = Station(count);
		}
		if (TrainB)
		{
			count = Station(count);
		}
		if (TrainC)
		{
			count = Station(count);
		}
	}

	train1.join();
	train2.join();
	train3.join();
}