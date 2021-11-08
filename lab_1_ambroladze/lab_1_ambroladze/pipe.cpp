#include "pipe.h"
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
	cout << "КС " << out << " - труба " << ID << " - КС " << in << ((repair == false) ? " В ремонте " : " Работает ") << endl;
}
pipe::pipe()
{
	name = "";
	length = 0.;
	diameter = 0;
	repair = false;
	in = 0;
	out = 0;
}

