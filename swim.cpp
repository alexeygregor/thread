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

void swim(vector<string> name, vector<int> speed, vector<int>distance)
{
	this_thread::sleep_for(chrono::seconds(1));
	for (int i = 0; i < name.size(); ++i)
	{
		if (distance.size() < speed.size())
		{
			distance.push_back(speed[i]);
		}
		else
		{
			distance[i] += speed[i];
		}
		if (distance[i] < 100)
		{
			cout << name[i] << "  " << distance[i] << " m." << endl;
		}
		else if (distance[i] >= 100)
		{
			cout << name[i] << "  100 m." << endl;
			name.erase(name.begin() + i);
			speed.erase(speed.begin() + i);
			distance.erase(distance.begin() + i);
		}
	}
	for (int i = 0; i < name.size(); ++i)
	{
		if (distance[i] < 100)
		{
			swim(name, speed, distance);
			break;
		}
	}
}

int main()
{
	string name;
	int speed = 0;
	vector<string>Name;
	vector<int>Speed;
	vector<int>Distance;

	for (int i = 1; i <= 5; ++i)
	{
		cout << "Input name " << i << " swimmer: ";
		cin >> name;
		cout << "Input speed " << i << " swimmer: ";
		cin >> speed;
		assert(speed > 0 && speed <= 10);
		Name.push_back(name);
		Speed.push_back(speed);
	}

	cout << "\n_____Match:" << endl;
	thread Timer(timer, 0);
	Timer.detach();
	thread Swim(swim, Name, Speed, Distance);
	timer(-1);
	Swim.join();
}