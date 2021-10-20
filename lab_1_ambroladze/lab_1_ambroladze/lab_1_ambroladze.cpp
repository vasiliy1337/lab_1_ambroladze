#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>  //файлы
#include <ctime> // для рандомных id
#include <unordered_map>
using namespace std;

struct pipe {
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
         "10. Поиск КС по имени " << endl <<
         "11. Поиск труб по признаку «в ремонте» " << endl <<
         "12. Поиск КС по проценту незадействованных цехов " << endl <<
         "13. Пакетное редактирование труб " << endl <<
         "0. Выход  " << endl <<
         "Выберите пункт меню: ";
}

pipe AddPipeline() {
    pipe NewPipe;
    cout << "Введите характеристики трубы: " << endl;
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
    cout << "Введите характеристики компрессорной станции: " << endl;
    cout << "Имя: " << endl;
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

void ShowAllPipes(const unordered_map<int, pipe> &pipes) {
    cout << "Трубопроводы" << endl << setw(10) << "ID" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20)
         << "В ремонте" << endl;
    for (auto &p: pipes) ShowPipe(p);   //for (int i = 0; i < pipes.size(); ++i) ShowPipe(pipes[i]);
}

void ShowAllKompres(const unordered_map<int, KS> &kompres) {
    cout << "Компрессорные станции" << endl << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов"
         << setw(20) << "Цехов в работе" << setw(20) << "Эффективность" << endl;
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
    int id, i;
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    while (true) {
        id = NumberInput(0);
        if (SearchId(pipes, id) != -1) {
            EditPipe(pipes[id]);
            cout << endl << setw(10) << "ID" << setw(20) << "Длина" << setw(20) << "Диаметр" << setw(20) << "В ремонте"
                 << endl;
            ShowPipe({id, pipes[id]});
            cout << "Успешное редактирование" << endl;
            return;
        } else
            cout << "Такого номера не существует, попробуйте еще раз: " << endl;
    }
}

void EditAllKompres(unordered_map<int, KS> &kompres) {
    int NewCountInWork, id, i;
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
            cout << setw(10) << "ID" << setw(20) << "Название" << setw(20) << "Кол-во цехов" << setw(20)
                 << "Цехов в работе" << setw(20) << "Эффективность" << endl;
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
        fout << "pipe" << endl;
        fout << pipes.size() << endl;
        for (auto &p: pipes) {
            fout << p.first << endl << p.second.length << endl << p.second.diameter << endl << p.second.repair << endl;
        }
    } else {
        cout << "Трубы не были добавлены" << endl;
        fout << "nopipe" << endl;
    }
    if (kompres.size() > 0) {
        fout << "kc" << endl;
        fout << kompres.size() << endl;
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
            fin >> id >> NewPipe.length >> NewPipe.diameter >> NewPipe.repair;
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
            fin >> NewKS.Count;
            fin >> NewKS.CountInWork;
            fin >> NewKS.Efficiency;
            kompres.insert({id, NewKS});
        }
    }
    return true;
}

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
        int id = NumberInput(1);
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
int SearchByName(const unordered_map<int, KS> &kompres, string InputName) {
    for (auto &k: kompres) {
        if (k.second.Name == InputName)
            return k.first;
    }
    return -1;
}

vector<int> SearchByRepair(const unordered_map<int, pipe> &pipes, bool InRepair) {
    vector<int> index;
    for (auto &p: pipes) {
        if (p.second.repair == InRepair)
            index.push_back(p.first);
    }
    return index;
}

vector<int> SearchByCount(const unordered_map<int, KS> &kompres, double percent) {
    vector<int> index;
    for (auto &k: kompres) {
        if (round(((double(k.second.Count) - double(k.second.CountInWork)) / double(k.second.Count)) * 100) == percent)
            index.push_back(k.first);
    }
    return index;
}

// Пакетное редактирование
void BatchEditingByRepair(unordered_map<int, pipe> &pipes) {
    cout << "Какие трубы нужно редактировать (1 - в ремонте, 0 - не в ремонте): " << endl;
    char inputChar = getchar();
    cin.ignore(10000, '\n');
    if (inputChar == '1' || inputChar == '0') {
        vector<int> index = SearchByRepair(pipes, (inputChar == '1') ? true : false);
        if (index.size() != 0) {
            cout << "Отредактировано " << index.size() << " труб" << endl;
            for (auto &id: index) {
                EditPipe(pipes[id]);
                ShowPipe({id, pipes[id]});
            }
        } else
            cout << "Ничего не найдено " << endl;
    } else
        cout << "Ошибка ввода " << endl;
}

void BatchEditingByInput(unordered_map<int, pipe> &pipes) {
    cout << "Введите ID труб, которые нужно отредактировать: " << endl;
    int input;
    vector<int> edit_id;
    do {
        input = NumberInput(0);
        if (SearchId(pipes, input) != -1)
            edit_id.push_back(input);
        //else cout << "ID " << input << " не найден " << endl;
    } while (input != 0);
    if (edit_id.size() != 0) {
        cout << "Успешное редактирование " << endl;
        for (auto &i: edit_id) {
            EditPipe(pipes[i]);
            ShowPipe({i, pipes[i]});
        }
    }
}

void BatchEditing(unordered_map<int, pipe> &pipes) {
    cout << "1. Поиск по признаку в ремонте \n2. Ввести ID вручную \n0. Выход \n";
    while (true) {
        int edit_case = NumberInput(0);
        switch (edit_case) {
            case 1: {
                BatchEditingByRepair(pipes);
                return;
            }
            case 2: {
                BatchEditingByInput(pipes);
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
                if (kompres.size() == 0) {
                    cout << "КС не добавлены";
                    break;
                }
                string inputName;
                cout << "Введите имя, которое нужно найти: " << endl;
                getline(cin, inputName);
                inputName.erase(0, inputName.find_first_not_of(" \n\r\t"));
                inputName.erase(inputName.find_last_not_of(" \n\r\t") + 1);
                int id = SearchByName(kompres, inputName);
                if (id != -1) {
                    cout << "Найдена КС" << endl << setw(10) << "ID" << setw(20) << "Название" << setw(20)
                         << "Кол-во цехов" << setw(20) << "Цехов в работе" << setw(20) << "Эффективность" << endl;
                    ShowKompres({id, kompres[id]});
                } else
                    cout << "Ничего не найдено ";
                break;
            }
            case 11: {
                if (pipes.size() == 0) {
                    cout << "Трубы не добавлены";
                    break;
                }
                cout << "Какие трубы нужно искать (1 - в ремонте, 0 - не в ремонте): " << endl;
                char inputChar = getchar();
                cin.ignore(10000, '\n');
                if (inputChar == '1' || inputChar == '0') {
                    vector<int> index = SearchByRepair(pipes, (inputChar == '1') ? true : false);
                    if (index.size() != 0) {
                        cout << "Найдено " << index.size() << " труб" << endl << setw(10) << "ID" << setw(20) << "Длина"
                             << setw(20) << "Диаметр" << setw(20) << "В ремонте" << endl;
                        for (auto &id: index) {
                            ShowPipe({id, pipes[id]});
                        }
                    } else
                        cout << "Ничего не найдено ";
                } else
                    cout << "Ошибка ввода ";
                break;
            }
            case 12: {
                if (kompres.size() == 0) {
                    cout << "КС не добавлены";
                    break;
                }
                cout << "Введите процент незадействованных цехов: ";
                double percent = NumberInput(0.);
                if (percent <= 100 && percent >= 0) {
                    vector<int> index = SearchByCount(kompres, percent);
                    if (index.size() != 0) {
                        cout << "Найдено " << index.size() << " КС" << endl << setw(10) << "ID" << setw(20)
                             << "Название" << setw(20) << "Кол-во цехов" << setw(20) << "Цехов в работе" << setw(20)
                             << "Эффективность" << endl;
                        for (auto &id: index) {
                            ShowKompres({id, kompres[id]});
                        }
                    } else
                        cout << "Ничего не найдено ";
                } else
                    cout << "Ошибка ввода ";
                break;
            }
            case 13: {
                if (pipes.size() == 0) {
                    cout << "Трубы не добавлены";
                    break;
                }
                BatchEditing(pipes);
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