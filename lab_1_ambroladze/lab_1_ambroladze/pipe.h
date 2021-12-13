#pragma once

#include <iostream>
#include <string>
#include "input.h"
#include <fstream>
#include <iomanip>

using namespace std;

class pipe {
    int id;
public :
    static int MaxId;
    string Name;
    double length;
    int diameter;
    bool repair;
    int in, out;

    static void DrawHeader();

    void link(int newIn, int newOut);

    int GetID();

    void ClearLink();

    void edit();

    bool linked() const;

    bool CanBeUsed() const;

    void showlink(int ID) const;

    int GetProductivity() const;

    friend ostream &operator<<(ostream &out, const pipe &p);

    friend ofstream &operator<<(ofstream &fout, const pipe &p);

    friend istream &operator>>(istream &in, pipe &NewPipe);

    friend ifstream &operator>>(ifstream &fin, pipe &NewPipe);

    pipe();
};

