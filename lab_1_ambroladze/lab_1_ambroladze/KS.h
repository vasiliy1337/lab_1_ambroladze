#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

class KS {
    int id;
public:
    static int MaxId;
    string Name;
    int Count, CountInWork;
    double Efficiency;
    bool connected;

    static void DrawHeader();

    int GetID();

    void createLink();

    void ClearLink();

    bool linked();

    void edit(int NewCountInWork);

    friend ostream &operator<<(ostream &out, const KS &k);

    friend ofstream &operator<<(ofstream &fout, const KS &k);

    friend istream &operator>>(istream &in, KS &NewKS);

    friend ifstream &operator>>(ifstream &fin, KS &NewKS);

    KS();
};