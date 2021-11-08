#include "KS.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 

using namespace std;

string Name;
int Count, CountInWork;
double Efficiency;

void KS::edit(int NewCountInWork) {
    if (NewCountInWork <= Count)
        CountInWork = NewCountInWork;
}
void KS::save(ofstream& fout) const
{
	fout << Name << endl
		<< Count << endl
		<< CountInWork << endl
		<< Efficiency << endl;
}
void KS::load(ifstream& fin)
{
	string input;
	getline(fin, input);
	getline(fin, input);
	Name = input;
	fin >> Count >> CountInWork >> Efficiency;
}

void KS::show(int id) const
{
		cout << setw(10) << id <<
			setw(20) << Name <<
			setw(20) << Count <<
			setw(20) << CountInWork <<
			setw(20) << Efficiency << endl;
}

KS::KS()
{
	Name = "";
	Count = 0;
	CountInWork = 0;
	Efficiency = 0.;
}

