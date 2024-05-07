#include "runner.hpp"
#include <iostream>
#include <list>
#include <string>

using namespace std;

string Runner::getUsername() {
    return username;
}

void Runner::setUsername(string new_username) {
    username = new_username;
}

int Runner::getAge() {
    return age;
}

void Runner::setAge(int new_age) {
    age = new_age;
}

int Runner::getWeight() {
    return weight;
}

void Runner::setWeight(int new_weight) {
    weight = new_weight;
}

int Runner::getHeight() {
    return height;
}

void Runner::setHeight(int new_height) {
    height = new_height;
}

list<Run> Runner::getRunList() {
    return runList;
}

void Runner::setRunList(list<Run> new_runList) {
    runList = new_runList;
}

void Runner::newRun(double start_time) {
    Run new_run(start_time);
    runList.push_front(new_run);
}
