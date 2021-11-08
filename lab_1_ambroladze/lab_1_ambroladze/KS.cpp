#include "KS.h"

using namespace std;

string Name;
int Count, CountInWork;
double Efficiency;

void KS::edit(int NewCountInWork) {
    if (NewCountInWork <= Count)
        CountInWork = NewCountInWork;
}