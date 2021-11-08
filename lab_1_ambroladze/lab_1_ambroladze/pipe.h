#pragma once
#include <iostream>
#include <string>

using namespace std;

class pipe
{
public :
    string name;
    double length;
    int diameter;
    bool repair;
    int in, out;
    void link(int IdStart, int IdEnd);
    void edit();
    bool islinked() const;
    void showlink(int ID) const;
    void save(ofstream& out) const;
    void load(ifstream&);
    void show(int id) const;
   /* friend std::ostream& operator << (ostream& out, const pipe& p);*/
    pipe();
};

