#pragma once
#include <iostream>
#include <string>

using namespace std;

class KS
{
public:
    string Name;
    int Count, CountInWork;
    double Efficiency;
    void edit(int NewCountInWork);
    void save(ofstream& out) const;
    void load(ifstream&);
    void show(int id) const;
    KS();
};