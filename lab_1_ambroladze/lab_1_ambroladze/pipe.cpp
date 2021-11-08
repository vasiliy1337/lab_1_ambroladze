#include "pipe.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> 

using namespace std;
string name;
double length;
int diameter;
bool repair;
int in, out;

void pipe::link(int in, int out) {
	this->out = out;
	this->in = in;
}
void pipe::edit() {
	repair = !repair;
}
bool pipe::islinked() const
{
	return in > 0 && out > 0;   // && repair == false
}
void pipe::showlink(int ID) const
{
	cout << "�� " << out << " -> ����� " << ID << " -> �� " << in << ((repair == false) ? " � ������� " : " �������� ") << endl;
}
void pipe::show(int id) const
{
		cout << setw(10) << id <<
			setw(20) << name <<
			setw(20) << length <<
			setw(20) << diameter <<
			setw(20) << ((repair == true) ? "��" : "���") << endl;
}
void pipe::save(ofstream& fout) const
{
	fout << name << endl
		<< length << endl
		<< diameter << endl
		<< repair << endl
		<< in << endl
		<< out << endl;
}
void pipe::load(ifstream& fin)
{	
	string input;
	getline(fin, input);
	getline(fin, input);
	name = input;
	fin >> length >> diameter >> repair >> in >> out;
}
//ostream& operator<<(std::ostream& out, const pipe& p)
//{
//	out << "�����: " << p.length << endl;
//	out << "�������: " << p.diameter << endl;
//	out << p.repair;
//	return out;
//}
pipe::pipe()
{
	name = "";
	length = 0.;
	diameter = 0;
	repair = false;
	in = 0;
	out = 0;
}

