#include <vector>
#include <thread>
#include <string>
#include <cassert>
#include <iostream>
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

void swim1(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim1(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}

void swim2(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim2(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}

void swim3(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim3(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}
void swim4(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim4(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}

void swim5(string name, int speed, int distance)
{
	distance += speed;
	this_thread::sleep_for(chrono::seconds(1));
	if (distance < 100)
	{
		cout << name << "  " << distance << " m." << endl;
		swim5(name, speed, distance);
	}
	else if (distance >= 100)
	{
		cout << name << "  100 m." << endl;
	}
}

int main()
{
	string name;
	int speed = 0, distance = 0;
	vector<string>Name;
	vector<int>Speed;

	for (int i = 0; i < 5; ++i)
	{
		cout << "Input name: ";
		cin >> name;
		cout << "Input speed: ";
		cin >> speed;
		assert(speed > 0 && speed <= 10);
		Name.push_back(name);
		Speed.push_back(speed);
	}

	cout << "\n_____Match:" << endl;
	thread Timer(timer, 0);
	Timer.detach();
	thread Swim1(swim1, Name[0], Speed[0], distance);
	thread Swim2(swim2, Name[1], Speed[1], distance);
	thread Swim3(swim3, Name[2], Speed[2], distance);
	thread Swim4(swim4, Name[3], Speed[3], distance);
	thread Swim5(swim5, Name[4], Speed[4], distance);
	timer(-1);
	Swim1.join();
	Swim2.join();
	Swim3.join();
	Swim4.join();
	Swim5.join();

	cout << "\n_____Result:" << endl;
	for (int i = 0; i < 5; ++i)
	{
		int result = 0;
		result = 100 / Speed[i];
		if (100 % Speed[i] != 0)
		{
			++result;
		}
		cout << Name[i] << "  " << result << " sec." << endl;;
	}
}