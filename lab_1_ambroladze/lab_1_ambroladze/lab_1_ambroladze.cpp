#include <iostream>
#include <string>
#include <conio.h> //getch
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <ctime> // для рандомных id
using namespace std;

struct pipe{
    unsigned int id;
    double length;
    int diameter;
    bool repair;
};

struct KS{
    unsigned int id;
    string Name;
    unsigned int Count, CountInWork;
    double Efficiency;
};

template <typename T>
int SearchId(const T& vector, int id)
{
    int i = 0;
    for (auto& p : vector) {
        if (p.id == id) return i;
        ++i;
    }
    return -1;
}

template <typename T>
int CreateID(const T& vector)
{
    int NewID;
    do {
        srand((int)time(0));
        NewID = rand();
    } while (SearchId(vector, NewID) != -1);
    return NewID;
}

double DoubleInput() {
    double input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введен неверный символ, попробуйте еще раз: ";
    }
    cin.ignore(10000, '\n');
    return input;
}

int IntInput() {
    int input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введен неверный символ, попробуйте еще раз: ";
    }
    cin.ignore(10000, '\n');
    return input;
}

void DrawMenu() {
    cout << "1. Добавить трубу " << endl <<
        "2. Добавить КС  " << endl <<
        "3. Просмотр всех объектов  " << endl <<
        "4. Редактировать трубу  " << endl <<
        "5. Редактировать КС  " << endl <<
        "6. Сохранить  " << endl <<
        "7. Загрузить  " << endl <<
        "8. Удалить трубу  " << endl <<
        "9. Удалить КС  " << endl <<
        "0. Выход  " << endl;
}

pipe AddPipeline(unsigned int id) {
    pipe NewPipe;
    cout << "Введите характеристики трубы: " << endl;
    NewPipe.id = id;
    cout << "Длина: " << endl;
    while (true) {
        double inputDouble = DoubleInput();
        if (inputDouble > 0) {
            NewPipe.length = inputDouble;
            break;
        }
        else 
            cout << "Длина не может быть нулевой, попробуйте еще раз: " << endl;
    }
    cout << "Диаметр: " << endl;
    while (true) {
        int inputInt = IntInput();
        if (inputInt > 0) {
            NewPipe.diameter = inputInt;
            break;
        }
        else 
            cout << "Диаметр не может быть нулевой, попробуйте еще раз: " << endl;
    }
    cout << "Введите 1, если труба в ремонте, или 0, если труба не в ремонте: " << endl;
    while (true) {
        char inputChar = getchar();
        if (inputChar =='1' || inputChar =='0') {
            NewPipe.repair = (inputChar == '1') ? true : false;
            break;
        }
        else 
            cout << "Введен некорректный символ, попробуйте еще раз: " << endl;
    }
    return NewPipe;
}

KS AddKS(unsigned int id) {
    KS NewKompress;
    double inputDouble;
    cout << "Введите характеристики компрессорной станции: " << endl;
    NewKompress.id = id;
    cout << "Имя: " << endl;
    while (true) {
        string inputStr;
        cin >> inputStr;
        cin.ignore(10000, '\n');
        if (inputStr.length() > 0) {
            NewKompress.Name = inputStr;
            break;
        }
        else 
            cout << "Имя не может быть пустым, попробуйте еще раз: " << endl;
    }
    cout << "Кол-во цехов: " << endl;
    while (true) {
        int inputInt = IntInput();
        if (inputInt > 0) {
            NewKompress.Count = inputInt;
            break;
        }
        else {
            cout << "Кол-во цехов не может быть нулевым, попробуйте еще раз: " << endl;
        }
    }
    cout << "Кол-во цехов в работе: " << endl;
    while (true) {
        int inputInt = IntInput();
        if (inputInt <= NewKompress.Count) {
            NewKompress.CountInWork = inputInt;
            break;
        }
        else {
            cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов: " << endl;
        }
    }
    cout << "Эффективность: " << endl;
    while (true) {
        double inputDouble = DoubleInput();
        if (inputDouble >= 0. && inputDouble <=1.) {
            NewKompress.Efficiency = inputDouble;
            break;
        }
        else {
            cout << "Эффективность должна находиться в пределах от 0 до 1: " << endl;
        }
    }
    return NewKompress;
}

void ShowPipe(const pipe& pipes) {
cout << setw(10) << pipes.id << 
    setw(20) << pipes.length << 
    setw(20) << pipes.diameter << 
    setw(20) << ((pipes.repair == true) ? "Да" : "Нет") << endl;
}

void ShowKompres(const KS& kompres) {
cout << setw(10) << kompres.id << 
    setw(20) << kompres.Name << 
    setw(20) << kompres.Count << 
    setw(20) << kompres.CountInWork << 
    setw(20) << kompres.Efficiency << endl;
}

void ShowAllPipes(const vector<pipe>& pipes)
{
    cout << "Трубопроводы" << endl << setw(10) << "ID" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20) << "В ремонте" << endl;
    //for (int i = 0; i < pipes.size(); ++i) ShowPipe(pipes[i]);
    for (auto& p : pipes) ShowPipe(p);
}

void ShowAllKompres(const vector <KS>& kompres)
{
    cout << "Компрессорные станции" << endl << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе" << setw(20) << "Эффективность" << endl;
    //for (int i = 0; i < kompres.size(); ++i) ShowKompres(kompres[i]);
    for (auto& p : kompres) ShowKompres(p);
}

void EditPipe(pipe &pipe)
{
    pipe.repair = !pipe.repair;
}

void EditKompres(KS &kompres, int NewCountInWork)
{
    if (NewCountInWork < kompres.Count)
        kompres.CountInWork = NewCountInWork;
}

void EditAllPipes(vector<pipe> &pipes) {
    int id, i;
        cout << "Введите id трубы, которую хотите изменить: " << endl;
        while (true) {
            id = IntInput();
            i = SearchId(pipes, id);
            if (i < pipes.size() && i!=-1) {
                EditPipe(pipes[i]);
                cout << endl << setw(10) << "ID" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20) << "В ремонте" << endl;
                ShowPipe(pipes[i]);
                cout << "Успешное редактирование" << endl;
                return;
            }
            else {
                cout << "Такого номера не существует, попробуйте еще раз: " << endl;
            }
        }
}

void EditAllKompres(vector<KS> &kompres) {
    int NewCountInWork, id, i;
        cout << "Введите id станции, которую хотите изменить: " << endl;
        while (true) {
            id = IntInput();
            i = SearchId(kompres, id);
            if (i < kompres.size() && i != -1) {
                while (true) {
                    cout << "Введите количество цехов в работе: " << endl;
                    NewCountInWork = IntInput();
                    if (NewCountInWork <= kompres[i].Count) {
                        EditKompres(kompres[i], NewCountInWork);
                        break;
                    }
                    else {
                        cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов" << endl;
                    }
                }

                ShowKompres(kompres[i]);
                cout << "Успешное редактирование" << endl;
                return;
            }
            else {
                cout << "Такого номера не существует, попробуйте еще раз: " << endl;
            }
        }
}

bool CreateFile(const vector<pipe>& pipes, const vector<KS>& kompres, const string &FileName) {
    ofstream fout;
    fout.open(FileName);
    if (!fout.is_open()) {
        return false;
    }
    if (pipes.size() > 0) {
        fout << "pipe" << endl;
        fout << pipes.size() << endl;
        for (auto& p : pipes) {
            fout << p.id << endl << p.length << endl << p.diameter << endl << p.repair << endl;
        }
    }
    else {
        cout << "Трубы не были добавлены" << endl;
        fout << "nopipe" << endl;
    }
    if (kompres.size() > 0) {
        fout << "kc" << endl;
        fout << kompres.size() << endl;
        for (auto& k : kompres) {
            fout << k.id << endl << k.Name << endl << k.Count << endl << k.CountInWork << endl << k.Efficiency << endl;
        }
    }
    else {
        cout << "КС не были добавлены" << endl;
        fout << "nokc" << endl;
    }
    fout.close();
    return true;
}

bool ReadFile(vector<pipe>& pipes, vector<KS>& kompres, const string& FileName) {
    ifstream fin;
    string input;
    fin.open(FileName);
    if (!fin.is_open())
    {
        return false;
    }
    getline(fin, input);
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
        for (int i = 0; i < kompres.size(); ++i) {
            getline(fin, input);
            kompres[i].id = stoi(input);
            getline(fin, input);
            kompres[i].Name = input;
            getline(fin, input);
            kompres[i].Count = stoi(input);
            getline(fin, input);
            kompres[i].CountInWork = stoi(input);
            getline(fin, input);
            kompres[i].Efficiency = stod(input);
        }
    }
    return true;
}

template <typename T>
void DeleteElement(T& vector, int i)
{
    if (i < vector.size()) {
        vector.erase(vector.begin() + i);
    }
}

template <typename T>
void Delete(T& vector)
{
    cout << endl << "Введите id элемента, который хотите удалить: ";
    while (true) {
        int id = IntInput();
        int i = SearchId(vector, id);
        if (i < vector.size() && i != -1) {
            DeleteElement(vector, i);
            cout << "Элемент с id " << id << " удален";
            return;
        }
        else cout << "ID не найден";
    }
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    vector<pipe> pipes = {};
    vector<KS> kompres = {};
    char inputmenu;
    while (true) {
        DrawMenu();
        inputmenu = _getch();
        switch (inputmenu) {
        case '1':
        {
            int NewID = CreateID(pipes);
            pipes.push_back(AddPipeline(NewID));
            break;
        }
        case '2':
        {
            int NewID = CreateID(kompres);
            kompres.push_back(AddKS(NewID));
            break;
        }
        case '3':
        {
            if (pipes.size() == 0) {
                cout << "Трубы не были добавлены, выводить нечего" << endl;
            }
            else {
                ShowAllPipes(pipes);
            }
            cout << endl;
            if (kompres.size() == 0) {
                cout << "Компрессорные станции не были добавлены, выводить нечего" << endl;
            }
            else {
                ShowAllKompres(kompres);
            }
            break;
        }
        case '4':
        {
            if (pipes.size() > 0) {
                ShowAllPipes(pipes);
                EditAllPipes(pipes);
            }
            else {
                cout << "Трубопроводы не были добавлены, редактировать нечего" << endl;
            }
            break;
        }
        case '5':
        {
            if (kompres.size() > 0) {
                ShowAllKompres(kompres);
                EditAllKompres(kompres);
            }
            else {
                cout << "Станции не были добавлены, редактировать нечего" << endl;
            }
            break;
        }
        case '6':
        {
            cout << "Введите название файла: ";
            string FileName = "";
            getline(cin, FileName);
            FileName = FileName + ".txt";
            if (CreateFile(pipes, kompres, FileName)) {
                cout << "Данные сохранены в файл" << endl;
            }
            else
                cout << "Не удалось создать файл" << endl;
            break;
        }
        case '7':
        {
            cout << "Введите название файла: ";
            string FileName = "";
            getline(cin, FileName);
            FileName = FileName + ".txt";
            if (ReadFile(pipes, kompres, FileName)) {
                cout << "Данные успешно загружены" << endl;
                ShowAllPipes(pipes);
                ShowAllKompres(kompres);
            }
            else {
                cout << "Файл не найден" << endl;
            }
            break;
        }
        case '8':
        {
            if (pipes.size() > 0) {
                ShowAllPipes(pipes);
                Delete(pipes);
                break;
            }
            else {
                cout << "Трубы не были добавлены, удалять нечего" << endl;
                break;
            }
        }
        case '9':
        {
            if (kompres.size() > 0) {
                ShowAllKompres(kompres);
                Delete(kompres);
                break;
            }
            else {
                cout << "Станции не были добавлены, удалять нечего" << endl;
                break;
            }
        }
        case '0':
        {
            return 0;
        }
        }
        cout << "\n\n\n\n\n\n\n\n\n\n";
    }
    return 0;
}