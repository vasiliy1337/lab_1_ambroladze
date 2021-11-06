#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <ctime> // для рандомных id
#include <unordered_map>

using namespace std;

struct pipe {
    string Name;
    double length;
    int diameter;
    bool repair;
};

struct KS {
    string Name;
    int Count, CountInWork;
    double Efficiency;
};

template<typename T>
int SearchId(const T &map, int id) {
    if (map.find(id) != map.end()) return id;
    return -1;
}

template<typename T>
int CreateID(const T &map) {
    int NewID;
    do {
        srand((int) time(0));
        NewID = rand();
    } while (SearchId(map, NewID) != -1);
    return NewID;
}

template<typename T>
T NumberInput(T min) {
    T input;
    while (!(cin >> input) || input < min) {
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
         "10. Фильтры/пакетное редактирование " << endl <<
         "0. Выход  " << endl <<
         "Выберите пункт меню: ";
}

pipe AddPipeline() {
    pipe NewPipe;
    cout << "Введите характеристики трубы: " << endl << "Имя: " << endl;
    while (true) {
        string inputStr;
        getline(cin, inputStr);
        inputStr.erase(0, inputStr.find_first_not_of(" \n\r\t"));
        inputStr.erase(inputStr.find_last_not_of(" \n\r\t") + 1); //https://stackoverflow.com/a/33099753
        if (inputStr.length() > 0) {
            NewPipe.Name = inputStr;
            break;
        } else
            cout << "Имя не может быть пустым, попробуйте еще раз: " << endl;
    }
    cout << "Длина: " << endl;
    while (true) {
        double inputDouble = NumberInput(0.);
        if (inputDouble > 0) {
            NewPipe.length = inputDouble;
            break;
        } else cout << "Длина не может быть нулевой" << endl;
    }
    cout << "Диаметр: " << endl;
    int inputInt = NumberInput(1);
    NewPipe.diameter = inputInt;
    cout << "Введите 1, если труба в ремонте, или 0, если труба не в ремонте: " << endl;
    while (true) {
        char inputChar = getchar();
        cin.ignore(10000, '\n');
        if (inputChar == '1' || inputChar == '0') {
            NewPipe.repair = (inputChar == '1') ? true : false;
            break;
        } else
            cout << "Введен некорректный символ, попробуйте еще раз: " << endl;
    }
    return NewPipe;
}

KS AddKS() {
    KS NewKompress;
    cout << "Введите характеристики компрессорной станции: " << endl << "Имя: " << endl;
    while (true) {
        string inputStr;
        getline(cin, inputStr);
        inputStr.erase(0, inputStr.find_first_not_of(" \n\r\t"));
        inputStr.erase(inputStr.find_last_not_of(" \n\r\t") + 1); //https://stackoverflow.com/a/33099753
        if (inputStr.length() > 0) {
            NewKompress.Name = inputStr;
            break;
        } else
            cout << "Имя не может быть пустым, попробуйте еще раз: " << endl;
    }
    cout << "Кол-во цехов: " << endl;
    while (true) {
        int inputInt = NumberInput(0);
        if (inputInt > 0) {
            NewKompress.Count = inputInt;
            break;
        } else
            cout << "Кол-во цехов не может быть нулевым, попробуйте еще раз: " << endl;
    }
    cout << "Кол-во цехов в работе: " << endl;
    while (true) {
        int inputInt = NumberInput(0);
        if (inputInt <= NewKompress.Count) {
            NewKompress.CountInWork = inputInt;
            break;
        } else
            cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов: " << endl;
    }
    cout << "Эффективность: " << endl;
    while (true) {
        double inputDouble = NumberInput(0.);
        if (inputDouble >= 0. && inputDouble <= 1.) {
            NewKompress.Efficiency = inputDouble;
            break;
        } else
            cout << "Эффективность должна находиться в пределах от 0 до 1: " << endl;
    }
    return NewKompress;
}

void ShowPipe(const pair<int, pipe> &pipes) {
    cout << setw(10) << pipes.first <<
         setw(20) << pipes.second.Name <<
         setw(20) << pipes.second.length <<
         setw(20) << pipes.second.diameter <<
         setw(20) << ((pipes.second.repair == true) ? "Да" : "Нет") << endl;
}

void ShowKompres(const pair<int, KS> &kompres) {
    cout << setw(10) << kompres.first <<
         setw(20) << kompres.second.Name <<
         setw(20) << kompres.second.Count <<
         setw(20) << kompres.second.CountInWork <<
         setw(20) << kompres.second.Efficiency << endl;
}

void DrawHeader(bool type) {
    if (type)
        cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20)
             << "В ремонте" << endl;
    else
        cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе"
             << setw(20) << "Эффективность" << endl;

}

void ShowAllPipes(const unordered_map<int, pipe> &pipes) {
    cout << "Трубопроводы" << endl;
    DrawHeader(1);
    for (auto &p: pipes) ShowPipe(p);   //for (int i = 0; i < pipes.size(); ++i) ShowPipe(pipes[i]);
}

void ShowAllKompres(const unordered_map<int, KS> &kompres) {
    cout << "Компрессорные станции" << endl;
    DrawHeader(0);
    for (auto &p: kompres) ShowKompres(p);  //for (int i = 0; i < kompres.size(); ++i) ShowKompres(kompres[i]);
}

void EditPipe(pipe &pipe) {
    pipe.repair = !pipe.repair;
}

void EditKompres(KS &kompres, int NewCountInWork) {
    if (NewCountInWork <= kompres.Count)
        kompres.CountInWork = NewCountInWork;
}

void EditAllPipes(unordered_map<int, pipe> &pipes) {
    int id;
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    while (true) {
        id = NumberInput(0);
        if (SearchId(pipes, id) != -1) {
            EditPipe(pipes[id]);
            DrawHeader(1);
            ShowPipe({id, pipes[id]});
            cout << "Успешное редактирование" << endl;
            return;
        } else
            cout << "Такого номера не существует, попробуйте еще раз: " << endl;
    }
}

void EditAllKompres(unordered_map<int, KS> &kompres) {
    int NewCountInWork, id;
    cout << "Введите id станции, которую хотите изменить: " << endl;
    while (true) {
        id = NumberInput(0);
        if (SearchId(kompres, id) != -1) {
            while (true) {
                cout << "Введите количество цехов в работе: " << endl;
                NewCountInWork = NumberInput(0);
                if (NewCountInWork <= kompres[id].Count) {
                    EditKompres(kompres[id], NewCountInWork);
                    break;
                } else
                    cout << "Кол-во цехов в работе не может быть больше общего кол-ва цехов" << endl;
            }
            DrawHeader(0);
            ShowKompres({id, kompres[id]});
            cout << "Успешное редактирование" << endl;
            return;
        } else
            cout << "Такого номера не существует, попробуйте еще раз: " << endl;
    }
}

bool CreateFile(const unordered_map<int, pipe> &pipes, const unordered_map<int, KS> &kompres, const string &FileName) {
    ofstream fout;
    fout.open(FileName);
    if (!fout.is_open())
        return false;
    if (pipes.size() > 0) {
        fout << "pipe" << endl << pipes.size() << endl;
        for (auto &p: pipes) {
            fout << p.first << endl << p.second.Name << endl << p.second.length << endl << p.second.diameter << endl
                 << p.second.repair << endl;
        }
    } else {
        cout << "Трубы не были добавлены" << endl;
        fout << "nopipe" << endl;
    }
    if (kompres.size() > 0) {
        fout << "kc" << endl << kompres.size() << endl;
        for (auto &k: kompres) {
            fout << k.first << endl << k.second.Name << endl << k.second.Count << endl << k.second.CountInWork << endl
                 << k.second.Efficiency << endl;
        }
    } else {
        cout << "КС не были добавлены" << endl;
        fout << "nokc" << endl;
    }
    fout.close();
    return true;
}

bool ReadFile(unordered_map<int, pipe> &pipes, unordered_map<int, KS> &kompres, const string &FileName) {
    pipes.clear();
    ifstream fin;
    string input;
    fin.open(FileName);
    if (!fin.is_open())
        return false;
    fin >> input;
    if (input != "nopipe") {
        int n;
        fin >> n;
        for (int i = 0; i < n; ++i) {
            pipe NewPipe;
            int id;
            fin >> id;
            getline(fin, input);
            getline(fin, input);
            NewPipe.Name = input;
            fin >> NewPipe.length >> NewPipe.diameter >> NewPipe.repair;
            pipes.insert({id, NewPipe});
        }
    }
    kompres.clear();
    fin >> input;
    if (input != "nokc") {
        int n;
        fin >> n;
        for (int i = 0; i < n; ++i) {
            KS NewKS;
            int id;
            fin >> id;
            getline(fin, input);
            getline(fin, input);
            NewKS.Name = input;
            fin >> NewKS.Count >> NewKS.CountInWork >> NewKS.Efficiency;
            kompres.insert({id, NewKS});
        }
    }
    return true;
}

// Удаление
template<typename T>
void DeleteElement(T &map, int id) {
    if (map.find(id) != map.end()) {
        map.erase(id);
    }
}

template<typename T>
void Delete(T &map) {
    cout << endl << "Введите id элемента, который хотите удалить (или 0 чтобы вернуться в меню): ";
    while (true) {
        int id = NumberInput(0);
        if (id == 0) return;
        if (SearchId(map, id) != -1) {
            DeleteElement(map, id);
            cout << "Элемент с id " << id << " удален";
            return;
        } else
            cout << "ID не найден, попробуйте еще раз: ";
    }
}

// Фильтры
template<typename T>
bool CheckByName(const T &map, string param) {
    return map.Name == param;
}

bool CheckByRepair(const pipe &pipe, bool param) {
    return pipe.repair == param;
}

bool CheckByPercent(const KS &kompres, double param) {
    return round(100 * (1. * (kompres.Count - kompres.CountInWork) / kompres.Count)) == param;
}

template<typename T, typename T_param>
using Filter = bool (*)(const T &map, T_param param);

template<typename T, typename T_param>
vector<int> FindByFilter(const unordered_map<int, T> &map, Filter<T, T_param> f, T_param param) {
    vector<int> res;
    for (auto &m: map)
        if (f(m.second, param))
            res.push_back(m.first);
    return res;
}

void PipeFilterMenu(unordered_map<int, pipe> &pipes) {
    if (pipes.size() == 0) {
        cout << "Трубы не добавлены " << endl;
        return;
    }
    while (true) {
        cout << endl << "Фильтр/редактирование труб" << endl << "1. Поиск труб по названию" << endl
             << "2. Поиск труб по признаку в ремонте " << endl << "3. Ввести id вручную " << endl << "0. Выход "
             << endl;
        int FilterCase = NumberInput(0);
        switch (FilterCase) {
            case 1: {
                cout << "Введите имя, которое нужно найти: " << endl;
                string inputName;
                getline(cin, inputName);
                inputName.erase(0, inputName.find_first_not_of(" \n\r\t"));
                inputName.erase(inputName.find_last_not_of(" \n\r\t") + 1);
                vector<int> index = FindByFilter(pipes, CheckByName, inputName);
                if (index.size() != 0) {
                    cout << "Найдено " << index.size() << " труб" << endl;
                    DrawHeader(1);
                    for (auto &id: index) {
                        ShowPipe({id, pipes[id]});
                    }
                    cout << "1. Редактировать найденые" << endl;
                    if (NumberInput(0) == 1) {
                        for (auto &id: index)
                            EditPipe(pipes[id]);
                    }
                } else
                    cout << "Ничего не найдено " << endl;
                break;
            }
            case 2: {
                cout << "Какие трубы нужно искать (1 - в ремонте, 0 - не в ремонте): " << endl;
                char inputChar = getchar();
                cin.ignore(10000, '\n');
                if (inputChar == '1' || inputChar == '0') {
                    vector<int> index = FindByFilter(pipes, CheckByRepair, (inputChar == '1') ? true : false);
                    if (index.size() != 0) {
                        cout << "Найдено " << index.size() << " труб" << endl;
                        DrawHeader(1);
                        for (auto &id: index) {
                            ShowPipe({id, pipes[id]});
                        }
                        cout << "1. Редактировать найденые" << endl;
                        if (NumberInput(0) == 1)
                            for (auto &id: index)
                                EditPipe(pipes[id]);
                    } else
                        cout << "Ничего не найдено " << endl;
                } else
                    cout << "Ошибка ввода " << endl;
                break;
            }
            case 3: {
                cout << "Введите ID труб, которые нужно отредактировать: " << endl;
                int input;
                vector<int> edit_id;
                do {
                    input = NumberInput(0);
                    if (SearchId(pipes, input) != -1)
                        edit_id.push_back(input);
                } while (input != 0);
                if (edit_id.size() != 0) {
                    cout << "Успешное редактирование " << endl;
                    DrawHeader(1);
                    for (auto &i: edit_id) {
                        EditPipe(pipes[i]);
                        ShowPipe({i, pipes[i]});
                    }
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Такого пункта не существует" << endl;
                break;
        }
    }
}

void KSFilterMenu(unordered_map<int, KS> &kompres) {
    if (kompres.size() == 0) {
        cout << "Трубы не добавлены " << endl;
        return;
    }
    while (true) {
        cout << endl << "Фильтр по КС" << endl << "1. Поиск КС по названию" << endl
             << "2. Поиск КС по проценту незадействованных цехов" << endl << "0. Выход" << endl;
        int FilterCase = NumberInput(0);
        switch (FilterCase) {
            case 1: {
                cout << "Введите название, которое нужно найти: " << endl;
                string inputName;
                getline(cin, inputName);
                inputName.erase(0, inputName.find_first_not_of(" \n\r\t"));
                inputName.erase(inputName.find_last_not_of(" \n\r\t") + 1);
                vector<int> index = FindByFilter(kompres, CheckByName, inputName);
                if (index.size() != 0) {
                    cout << "Найдено " << index.size() << " КС" << endl;
                    DrawHeader(0);
                    for (auto &id: index) {
                        ShowKompres({id, kompres[id]});
                    }
                } else
                    cout << "Ничего не найдено " << endl;
                break;
            }
            case 2: {
                cout << "Введите процент нерабочих цехов: " << endl;
                double percent = NumberInput(0.);
                if (percent <= 100 && percent >= 0) {
                    vector<int> index = FindByFilter(kompres, CheckByPercent, percent);
                    if (index.size() != 0) {
                        cout << "Найдено " << index.size() << " труб" << endl;
                        DrawHeader(0);
                        for (auto &id: index) {
                            ShowKompres({id, kompres[id]});
                        }
                    } else
                        cout << "Ничего не найдено " << endl;
                } else
                    cout << "Ошибка ввода " << endl;
                break;
            }
            case 0:
                return;
            default:
                cout << "Такого пункта не существует" << endl;
                break;
        }
    }
}

void BatchEditing(unordered_map<int, pipe> &pipes, unordered_map<int, KS> &kompres) {
    while (true) {
        cout << endl << "Меню фильтров" << endl << "1. Поиск/редактирование труб " << endl << "2. Поиск КС " << endl
             << "0. Выход " << endl;
        int edit_case = NumberInput(0);
        switch (edit_case) {
            case 1: {

                PipeFilterMenu(pipes);
                return;
            }
            case 2: {
                KSFilterMenu(kompres);
                return;
            }
            case 0:
                return;
            default: {
                cout << "Такого пункта не существует" << endl;
                break;
            }
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    unordered_map<int, pipe> pipes;
    unordered_map<int, KS> kompres;
    char inputmenu;
    while (true) {
        DrawMenu();
        inputmenu = NumberInput(0);
        switch (inputmenu) {
            case 1: {
                int NewID = CreateID(pipes);
                pipes.insert({NewID, AddPipeline()});
                break;
            }
            case 2: {
                int NewID = CreateID(kompres);
                kompres.insert({NewID, AddKS()});
                break;
            }
            case 3: {
                if (pipes.size() == 0)
                    cout << "Трубы не были добавлены, выводить нечего" << endl;
                else
                    ShowAllPipes(pipes);
                cout << endl;
                if (kompres.size() == 0)
                    cout << "Компрессорные станции не были добавлены, выводить нечего" << endl;
                else
                    ShowAllKompres(kompres);
                break;
            }
            case 4: {
                if (pipes.size() > 0) {
                    ShowAllPipes(pipes);
                    EditAllPipes(pipes);
                } else
                    cout << "Трубопроводы не были добавлены, редактировать нечего" << endl;
                break;
            }
            case 5: {
                if (kompres.size() > 0) {
                    ShowAllKompres(kompres);
                    EditAllKompres(kompres);
                } else
                    cout << "Станции не были добавлены, редактировать нечего" << endl;
                break;
            }
            case 6: {
                cout << "Введите название файла: ";
                string FileName;
                getline(cin, FileName);
                FileName = "./saves/" + FileName;
                if (CreateFile(pipes, kompres, FileName)) {
                    cout << "Данные сохранены в файл" << endl;
                } else
                    cout << "Не удалось создать файл" << endl;
                break;
            }
            case 7: {
                cout << "Введите название файла: ";
                string FileName;
                getline(cin, FileName);
                FileName = "./saves/" + FileName;
                if (ReadFile(pipes, kompres, FileName)) {
                    cout << "Данные успешно загружены" << endl;
                    ShowAllPipes(pipes);
                    ShowAllKompres(kompres);
                } else
                    cout << "Файл " << FileName.erase(0, FileName.find_last_of("/") + 1) << " не найден" << endl;
                break;
            }
            case 8: {
                if (pipes.size() > 0) {
                    ShowAllPipes(pipes);
                    Delete(pipes);
                    break;
                } else
                    cout << "Трубы не были добавлены, удалять нечего" << endl;
                break;
            }
            case 9: {
                if (kompres.size() > 0) {
                    ShowAllKompres(kompres);
                    Delete(kompres);
                    break;
                } else
                    cout << "Станции не были добавлены, удалять нечего" << endl;
                break;
            }
            case 10: {
                BatchEditing(pipes, kompres);
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                cout << "Такого пункта не существует" << endl;
                break;
            }
        }
        cout << "\n\n\n\n\n\n";
    }
    return 0;
}