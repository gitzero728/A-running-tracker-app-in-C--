#ifndef RUNNER_HPP
#define RUNNER_HPP

#include <list>
#include <string>
#include "run.hpp"

using namespace std;

class Runner {
private:
    string username;
    int age;
    int weight;
    int height;
    list<Run> runList;

public:
    string getUsername();
    void setUsername(string new_username);
    int getAge();
    void setAge(int new_age);
    int getWeight();
    void setWeight(int new_weight);
    int getHeight();
    void setHeight(int new_height);
    list<Run> getRunList();
    void setRunList(list<Run> new_runList);
    void newRun(double start_time);
};

#endif // RUNNER_HPP