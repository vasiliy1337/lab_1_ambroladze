#pragma once
#include <iostream>
#include <string>


class KS
{
public:
    std::string Name;
    int Count, CountInWork;
    double Efficiency;
    void edit(int NewCountInWork);
};