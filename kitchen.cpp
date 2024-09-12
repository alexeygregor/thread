#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
using namespace std;

vector<int>vec1;
vector<int>vec2;
vector<int>vec3;
mutex restaurant;

void menu(int value)
{
    if (value == 1)
    {
        cout << "Pizza" << endl;
    }
    if (value == 2)
    {
        cout << "Soup" << endl;
    }
    if (value == 3)
    {
        cout << "Steak" << endl;
    }
    if (value == 4)
    {
        cout << "Salad" << endl;
    }
    if (value == 5)
    {
        cout << "Sushi" << endl;
    }
}

int order()
{
    int rnd = 0, timer = 0;
    while (true)
    {
        srand(time(nullptr));
        timer = rand() % 5 + 5;
        this_thread::sleep_for(chrono::seconds(timer));
        restaurant.lock();
        rnd = rand() % 5 + 1;
        vec1.push_back(rnd);
        cout << "Order:      "; 
        menu(vec1[vec1.size() - 1]);
        restaurant.unlock();
    }
}

void kitchen()
{
    int timer = 0;
    bool begin = true;
    while (true)
    {
        srand(time(nullptr));
        timer = rand() % 6 + 10;
        if (begin)
        {
            timer += 10;
            begin = false;
        }
        this_thread::sleep_for(chrono::seconds(timer));
        restaurant.lock();
        if (vec1.size() > 0)
        {
            vec2.push_back(vec1[vec2.size()]);
            cout << "Kitchen:    ";
            menu(vec1[vec2.size() - 1]);
        }
        restaurant.unlock();
    }
}

int courier()
{
    int cnt = 0;
    while (true)
    {
        ++cnt;
        this_thread::sleep_for(chrono::seconds(30));
        restaurant.lock();
        if (vec2.size() > 0)
        {
            vec3.push_back(vec2[vec3.size()]);
            cout << "Courier(" << cnt << "): ";
            menu(vec2[vec3.size() - 1]);
        }
        if (cnt == 10)
        {
            return 0;
        }
        restaurant.unlock();
    }
}

int main()
{
    thread Order(order);
    Order.detach();
    thread Kitchen(kitchen);
    Kitchen.detach();   
    thread Courier(courier);
    Courier.join();
}   