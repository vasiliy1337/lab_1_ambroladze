#include <iostream>
#include "input.h"
#include "Gts.h"

using namespace std;

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
        "11. Соединить трубу " << endl <<
        "12. Удалить связи " << endl <<
        "13. Показать связи " << endl <<
        "14. Операции с графами " << endl <<
        "0. Выход  " << endl <<
        "Выберите пункт меню: ";
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    char inputmenu;
    Gts ESG;
    while (true) {
        DrawMenu();
        inputmenu = NumberInput(0);
        switch (inputmenu) {
            case 1: {
                ESG.NEWPipe();
                break;
            }
            case 2: {
                ESG.NEWKs();
                break;
            }
            case 3: {
                ESG.PrintObj();
                break;
            }
            case 4: {
                ESG.EditPipes();
                break;
            }
            case 5: {
                ESG.EditKSs();
                break;
            }
            case 6: {
                ESG.SaveData();
                break;
            }
            case 7: {
                ESG.LoadData();
                break;
            }
            case 8: {
                ESG.DeletePipes();
                break;
            }
            case 9: {
                ESG.DeleteKSs();
                break;
            }
            case 10: {
                ESG.FiltersMenu();
                break;
            }
            case 11: {
                ESG.ConnectObj();
                break;
            }
            case 12:
            {
                ESG.DisconnectObj();
                break;
            }
            case 13: {
                ESG.PrintConnections();
                break;
            }
            case 14:
            {
                ESG.NetCalculation();
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