#include <vector>
#include <thread>
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

class Data
{
	string name = "unknown";
	int speed = 0, time = 0;

  public:

	void setName(string value)
	{
	  name = value;
	}

	string getName()
	{
		return name;
	}

	void setSpeed(int value)
	{
		speed = value;
	}

	int getSpeed()
	{
		return speed;
	}

	int getTime()
	{
		return time;
	}

	int calculateDistance(int inTime)
	{
		time = inTime;
		int path = 0;
		path = time * speed;
		if (path > 100)
		{
			path = 100;
		}
		return path;
	}
};

class Swim
{
	vector<Data>vec;
	vector<Data>res;

  public:
	
	void setVec(Data& data)
	{
		vec.push_back(data);
	}

	vector<Data> getVec()
	{
		return vec;
	}

	void outVec(Data& data, int count)
	{
		data = vec.at(count);
	}

	void outRes(Data& data, int count)
	{
		data = res.at(count);
	}

	void erase(Data& data, int count)
	{
		res.push_back(data);
		vec.erase(vec.begin() + count);
	}
};

void Match(Data& data, Swim& swim)
{
	int q = 0, time = 1;
	while (q != -1)
	{
		if (swim.getVec().empty())
		{
			q = -1;
			continue;
		}
		this_thread::sleep_for(chrono::seconds(1));
		cout << time << " second" << endl;
		for (int i = 0; i < swim.getVec().size(); ++i)
		{
			swim.outVec(data, i);
			cout << "Traversed path " << data.getName() << ": " << data.calculateDistance(time) << " meters" << endl;
			if (data.calculateDistance(time) == 100)
			{
				swim.erase(data, i);
			}
		}
		time++;
	}
}

int main()
{
	string name;
	int speed = 0;
	Swim* swim = new Swim();
	Data* data = new Data();

	for (int j = 1; j <= 5; ++j)
	{
		cout << "Input name  " << j << " swimmer: ";
		cin >> name;
		cout << "Input speed " << j << " swimmer: ";
		cin >> speed;
		data->setName(name);
		data->setSpeed(speed);
		swim->setVec(*data);
	}	
	assert(speed > 0 && speed <= 10);
	cout << endl;
	Match(*data, *swim);
	cout << endl;
	for (int i = 0; i < 5; ++i)
	{
		swim->outRes(*data, i);
		cout << "Swimmer " << data->getName() << ": " << data->getTime() << " seconds" << endl;
	}
}