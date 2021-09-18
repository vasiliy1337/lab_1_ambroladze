#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <fstream>
//#include <windows.h>
using namespace std;

struct pipe{
    unsigned int id;
    double length;
    int diameter;
    bool repair;
};

struct KS {
    unsigned int id;
    string Name;
    unsigned int Count, CountInWork;
    double Efficiency;
};

double DoubleInput() {
    int length, point_count=0;
    bool valid = true;
    string input;
    while (true) {
        valid = true;
        getline(cin, input);
        length = input.length() - 1;
        if (input.length() == 0) {
            valid = false;
        }
        for ( int i = 0; i <= length; ++i) {
            if ((input[i] == '.')) {
                point_count++;
            }
            else {
                if (!isdigit(input[i])) {
                    valid = false;
                    break;
                }
            }
        }
        if (point_count <= 1 && valid) {
            return stod(input);
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: " << endl;
        }
    }
}

int IntInput() {
    int length;
    bool valid;
    string input;
    while (true) {
        valid = true;
        getline(cin, input);
        length = input.length() - 1;
        if (input.length() == 0) {
            valid = false;
            break;
        }
        for (int i = 0; i <= length; ++i) {
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return stoi(input);
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: " << endl;
        }
    }
}

void AddPipeline(vector<pipe> &pipes) {
    system("cls");
    double input;
    string inputStr;
    cout << "Введите характеристики трубы: " << endl;
    pipes.resize(pipes.size() + 1);
    pipes[pipes.size() - 1].id = pipes.size();
    cout << "Длина: " << endl;
    while (true) {
        input = DoubleInput();
        if (input > 0) {
            pipes[pipes.size() - 1].length = input;
            break;
        }
        else {
            cout << "Длина не может быть нулевой, попробуйте еще раз: " << endl;
        }
    }
    cout << "Диаметр: " << endl;
    while (true) {
        input = IntInput();
        if (input > 0) {
            pipes[pipes.size() - 1].diameter = input;
            break;
        }
        else {
            cout << "Диаметр не может быть нулевой, попробуйте еще раз: " << endl;
        }
    }
    cout << "Введите 1, если труба в ремонте, или 0, если труба не в ремонте: " << endl;
    while (true) {
        getline(cin, inputStr);
        if (inputStr =="1" || inputStr =="0") {
            pipes[pipes.size() - 1].repair = (inputStr == "1") ? true : false;
            break;
        }
        else {
            cout << "Введен некорректный символ, попробуйте еще раз: " << endl;
        }
    }
    cout << "0.Выход";
}

void AddKS(vector<KS> &kompres) {
    system("cls");
    int input;
    string inputStr;
    double inputDouble;
    cout << "Введите характеристики компрессорной станции: " << endl;
    kompres.resize(kompres.size() + 1);
    kompres[kompres.size() - 1].id = kompres.size();
    cout << "Имя: " << endl;
    while (true) {
        getline (cin, inputStr);
        if (inputStr.length() > 0) {
            kompres[kompres.size() - 1].Name = inputStr;
            break;
        }
        else {
            cout << "Имя не может быть пустым, попробуйте еще раз: " << endl;
        }
    }
    cout << "Кол-во цехов: " << endl;
    while (true) {
        input = IntInput();
        if (input > 0) {
            kompres[kompres.size() - 1].Count = input;
            break;
        }
        else {
            cout << "Кол-во цехов не может быть нулевым, попробуйте еще раз: " << endl;
        }
    }
    cout << "Кол-во цехов в работе: " << endl;
    while (true) {
        input = IntInput();
        if (input <= kompres[kompres.size() - 1].Count) {
            kompres[kompres.size() - 1].CountInWork = input;
            break;
        }
        else {
            cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов: " << endl;
        }
    }
    cout << "Эффективность: " << endl;
    while (true) {
        inputDouble = DoubleInput();
        if (inputDouble >= 0. && inputDouble <=1.) {
            kompres[kompres.size() - 1].Efficiency = inputDouble;
            break;
        }
        else {
            cout << "Эффективность должна находиться в пределах от 0 до 1: " << endl;
        }
    }
    cout << "0.Выход";
}

void ShowPipes(const vector<pipe> &pipes) {
    cout <<"Трубопроводы"<< endl << setw(10) << "ID" << setw(20) << "Длина" <<  setw(20) << "Диаметр" <<  setw(20) << "В ремонте" << endl;
    if (pipes.size() > 0) {
        for (int i = 0; i < pipes.size(); ++i) {
            cout << setw(10) << pipes[i].id << 
                setw(20) << pipes[i].length << 
                setw(20) << pipes[i].diameter << 
                setw(20) << ((pipes[i].repair == true) ? "Да" : "Нет") << endl;
        }
    }
    else {
        cout << setw(40) << "Массив пуст" << endl;
    }
}

void ShowKompres(const vector<KS> &kompres) {
    cout << "Компрессорные станции" << endl << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе" << setw(20) << "Эффективность" << endl;
    if (kompres.size() > 0) {
        for (int i = 0; i < kompres.size(); ++i) {
            cout << setw(10) << kompres[i].id << 
                setw(20) << kompres[i].Name << 
                setw(20) << kompres[i].Count << 
                setw(20) << kompres[i].CountInWork << 
                setw(20) << kompres[i].Efficiency << endl;
        }
    }
    else {
        cout << setw(40) << "Массив пуст" << endl;
    }
}

void EditPipes(vector<pipe> &pipes) {
    int input;
    system("cls");
    if (pipes.size() > 0) {
        ShowPipes(pipes);
        cout << "Введите номер трубы, которую хотите изменить: " << endl;
        while (true) {
            input = IntInput() - 1;
            if (input < pipes.size()) {
                pipes[input].repair = !pipes[input].repair;
                system("cls");
                ShowPipes(pipes);
                cout << "Успешное редактирование" << endl;
                break;
            }
            else {
                cout << "Такого номера не существует, попробуйте еще раз: " << endl;
            }
        }
    }
    else {
        cout << "Трубопроводы не были добавлены, редактировать нечего" << endl;
    }
}

void EditKompres(vector<KS> &kompres) {
    int input;
    system("cls");
    if (kompres.size() > 0) {
        ShowKompres(kompres);
        cout << "Введите номер станции, которую хотите изменить: " << endl;
        while (true) {
            input = IntInput() - 1;
            if (input < kompres.size()) {
                while (true) {
                    cout << "Введите количество цехов в работе: " << endl;
                    input = IntInput();
                    if (input <= kompres[kompres.size() - 1].Count) {
                        kompres[kompres.size() - 1].CountInWork = input;
                        break;
                    }
                    else {
                        cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов" << endl;
                    }
                }
                system("cls");
                ShowKompres(kompres);
                cout << "Успешное редактирование" << endl;
                break;
            }
            else {
                cout << "Такого номера не существует, попробуйте еще раз: " << endl;
            }
        }
    }
    else {
        cout << "Станции не были добавлены, редактировать нечего" << endl;
    }
}

void CreateFile(const vector<pipe>& pipes, const vector<KS>& kompres) {
    ofstream fout;
    fout.open("data.txt");
    if (pipes.size() > 0) {
        fout << "pipe" << endl;
        fout << pipes.size() << endl;
        for (int i = 0; i < pipes.size(); ++i) {
            fout << pipes[i].id << endl << pipes[i].length << endl << pipes[i].diameter << endl << ((pipes[i].repair == true) ? 1 : 0) << endl;
        }
    }
    else {
        cout << "Трубы не были добавлены" << endl;
        fout << "nopipe" << endl;
    }
    if (kompres.size() > 0) {
        fout << "kc" << endl;
        fout << kompres.size() << endl;
        for (int i = 0; i < kompres.size(); ++i) {
            fout << kompres[i].id << endl << kompres[i].Name << endl << kompres[i].Count << endl << kompres[i].CountInWork << endl << kompres[i].Efficiency << endl;
        }
    }
    else {
        cout << "КС не были добавлены" << endl;
        fout << "nokc" << endl;
    }
    fout.close();
    cout << "Данные сохранены в файл" << endl;
}

void ReadFile(vector<pipe>& pipes, vector<KS>& kompres) {
    ifstream fin;
    string input;
    fin.open("data.txt");
    getline (fin,input);
    if (input != "nopipe") {
        getline(fin, input);
        pipes.resize(stoi(input));
        for (int i = 0; i < pipes.size(); ++i) {
            getline(fin, input);
            pipes[i].id = stoi(input);
            getline(fin, input);
            pipes[i].length = stod(input);
            getline(fin, input);
            pipes[i].diameter = stoi(input);
            getline(fin, input);
            pipes[i].repair = stoi(input);
        }
    }
    getline(fin, input);
    if (input != "nokc") {
        getline(fin, input);
        kompres.resize(stoi(input));
        for (int i = 0; i < pipes.size(); ++i) {
            getline(fin, input);
            kompres[i].id = stoi(input);
            getline(fin, input);
            kompres[i].Name = input;
            getline(fin, input);
            kompres[i].Count = stoi(input);
            getline(fin, input);
            kompres [i].CountInWork = stoi(input);
            getline(fin, input);
            kompres[i].Efficiency = stod(input);
        }
    }
    cout << "Данные загружены" << endl;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    vector<pipe> pipes;
    vector<KS> kompres;
    char inputmenu;
    pipes.resize(0);
    kompres.resize(0);
    while (true) {
        system("cls");
        cout << "1. Добавить трубу " << endl << 
            "2. Добавить КС  " << endl << 
            "3. Просмотр всех объектов  " << endl << 
            "4. Редактировать трубу  " << endl << 
            "5. Редактировать КС  " << endl << 
            "6. Сохранить  " << endl << 
            "7. Загрузить  " << endl << 
            "0. Выход  " << endl;
        inputmenu = _getch();
        switch (inputmenu) {
        case '1':
            system("cls");
            AddPipeline(pipes);
            while (true) {
                if (_getch() == '0') {
                    break; 
                }
            }
            break;
        case '2':
            system("cls");
            AddKS(kompres);
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '3':
            system("cls");
            ShowPipes(pipes);
            cout << endl;
            ShowKompres(kompres);
            cout << "0.Выход";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '4':
            system("cls");
            EditPipes(pipes);
            cout << "0.Выход";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '5':
            system("cls");
            EditKompres(kompres);
            cout << "0.Выход";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '6':
            system("cls");
            CreateFile(pipes, kompres);
            cout << "0.Выход";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '7':
            system("cls");
            ReadFile(pipes, kompres);
            cout << "0.Выход";
            while (true) {
                if (_getch() == '0') {
                    break;
                }
            }
            break;
        case '0':
            return 0;
        }
    }
    return 0;
}