#pragma once

#include <iostream>
#include <fstream> 
#include <vector>
#include <iomanip> //setw
#include <string>
#include <unordered_map>
#include <queue>
#include "pipe.h"
#include "KS.h"
#include "input.h"
#include "Filter.h"

using namespace std;

class Gts
{
	vector<vector<int>> ribs;

	vector<vector<double>> weights_matrix;

	vector<vector<double>> throughput_matrix;

	void TopologicalSort(const unordered_map<int, int>&);

	void MaxStream(int, int, const unordered_map<int, int>&);	

	void FindWay(int, int, const unordered_map<int, int>&);

    void GraphСalculation(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres);

    unordered_map<int, pipe> pipes;
    unordered_map<int, KS> kompres;

public:
    void NEWPipe();

    void NEWKs();

    void PrintObj();

    void EditPipes();

    void EditKSs();

    void SaveData();

    void LoadData();

    void DeletePipes();

    void DeleteKSs();

    void FiltersMenu();

    void ConnectObj();

    void DisconnectObj();

    void PrintConnections();

    void NetCalculation();

};




template<typename T>
int SearchId(const T& map, int id) {
	if (map.find(id) != map.end()) return id;
	return -1;
}



template<typename T>
void Delete(unordered_map<int, T>& map) {
    cout << endl << "Введите id элемента, который хотите удалить (или 0 чтобы вернуться в меню): ";
    while (true) {
        int id = NumberInput(0);
        if (id == 0) return;
        if (SearchId(map, id) != -1) {
            if (map.at(id).linked()) {
                cout << "Элемент находится в ГТС, сначала выключите его" << endl;
                return;
            }
            else {
                DeleteElement(map, id);
                cout << "Элемент с id " << id << " удален";
                return;
            }
        }
        else
            cout << "ID не найден, попробуйте еще раз: ";
    }
}
