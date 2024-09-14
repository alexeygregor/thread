#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

void timer(int time)
{
	while (time != -1)
	{
		this_thread::sleep_for(chrono::seconds(1));
		time++;
		cout << time << " sec." << endl;
	}
}

void swim(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}

int main()
{
	string name;
	int speed = 0, distance = 0, time = 0;
	vector<string>Name;
	vector<int>Speed;

	for (int i = 1; i <= 6; ++i)
	{
		cout << "Input name " << i << " swimmer: ";
		cin >> name;
		cout << "Input speed " << i << " swimmer: ";
		cin >> speed;
		assert(speed > 0 && speed <= 10);
		Name.push_back(name);
		Speed.push_back(speed);
	}

	cout << "\n_____Match:\n" << endl;
	thread Timer(timer, 0);
	Timer.detach();
	thread Swim1(swim, Name[0], Speed[0], distance);
	thread Swim2(swim, Name[1], Speed[1], distance);
	thread Swim3(swim, Name[2], Speed[2], distance);
	thread Swim4(swim, Name[3], Speed[3], distance);
	thread Swim5(swim, Name[4], Speed[4], distance);
	thread Swim6(swim, Name[5], Speed[5], distance);
	timer(-1);
	Swim1.join();
	Swim2.join();
	Swim3.join();
	Swim4.join();
	Swim5.join();
	Swim6.join();

	for (int i = 1; i < Speed.size(); i++)
	{
		int j = i;
		while (j > 0 && Speed[j - 1] < Speed[j])
		{
			swap(Speed[j - 1], Speed[j]);
			swap(Name[j - 1], Name[j]);
			j--;
		}
	}

	cout << "\n_____Result:\n" << endl;
	for (int i = 0; i < 6; ++i)
	{
		time = 100 / Speed[i];
		if (100 % Speed[i] != 0)
		{
			++time;
		}
		cout << Name[i] << "  " << time << " sec." << endl;
	}
}