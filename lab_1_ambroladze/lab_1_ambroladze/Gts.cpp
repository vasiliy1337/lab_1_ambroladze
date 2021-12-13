#include "Gts.h"


void ShowAllPipes(const unordered_map<int, pipe>& pipes) {
    cout << "Трубопроводы" << endl;
    pipe::DrawHeader();
    for (auto& [i, p] : pipes) cout << setw(10) << i << p;
}

void ShowAllKompres(const unordered_map<int, KS>& kompres) {
    cout << "Компрессорные станции" << endl;
    KS::DrawHeader();
    for (auto& [i, k] : kompres) cout << setw(10) << i << k;
}

void EditAllPipes(unordered_map<int, pipe>& pipes) {
    cout << "Введите id трубы, которую хотите изменить: " << endl;
    int id = NumberInput(0);
    if (SearchId(pipes, id) != -1) {
        if (pipes[id].linked() && pipes[id].repair == 0) {
            cout << "Труба " << id << " включена в сеть, вы уверены, что хотите выключить ее ? (1 - да, 0 - нет)" << endl;
            if (NumberInput(0, 1) == 0) return;
        }
        pipes[id].edit();
        pipe::DrawHeader();
        cout << setw(10) << id << pipes[id] << "Успешное редактирование" << endl;
        return;
    }
    else
        cout << "Такого id не существует " << endl;
}

void EditAllKompres(unordered_map<int, KS>& kompres) {
    int NewCountInWork, id = NumberInput(0);
    cout << "Введите id станции, которую хотите изменить: " << endl;
    if (SearchId(kompres, id) != -1) {
        cout << "Введите количество цехов в работе: " << endl;
        NewCountInWork = NumberInput(0, kompres[id].Count);
        kompres[id].edit(NewCountInWork);
        KS::DrawHeader();
        cout << setw(10) << id << kompres[id] << "Успешное редактирование" << endl;
        return;
    }
    else
        cout << "Такого id не существует " << endl;
}

bool CreateFile(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres, const string& FileName) {
    ofstream fout;
    fout.open(FileName);
    if (!fout.is_open())
        return false;
    if (pipes.size() > 0) {
        fout << "pipe" << endl << pipes.size() << endl << pipe::MaxId << endl;
        for (auto& [i, p] : pipes) {
            fout << i << endl;
            fout << p;
        }
    }
    else
        fout << "nopipe" << endl;
    if (kompres.size() > 0) {
        fout << "kc" << endl << kompres.size() << endl << KS::MaxId << endl;
        for (auto& [i, k] : kompres) {
            fout << i << endl;
            fout << k;
        }
    }
    else
        fout << "nokc" << endl;
    fout.close();
    return true;
}

bool ReadFile(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres, const string& FileName) {
    pipes.clear();
    ifstream fin;
    string input;
    fin.open(FileName);
    if (!fin.is_open())
        return false;
    fin >> input;
    if (input != "nopipe") {
        int n;
        pipe NewPipe;
        int id;
        fin >> n;
        fin >> pipe::MaxId;
        for (int i = 0; i < n; ++i) {
            fin >> id;
            fin >> NewPipe;
            pipes.insert({ id, NewPipe });
        }
    }
    kompres.clear();
    fin >> input;
    if (input != "nokc") {
        KS NewKS;
        int id;
        int n;
        fin >> n;
        fin >> KS::MaxId;
        for (int i = 0; i < n; ++i) {
            fin >> id;
            fin >> NewKS;
            kompres.insert({ id, NewKS });
        }
    }
    return true;
}

void ShowConnection(const unordered_map<int, pipe>& pipes) {
    for (auto& [i, p] : pipes)
        if (p.linked())
            p.showlink(i);
}

void CreateBranch(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres) {
    cout << "Введите ID трубы, которую нужно связать: " << endl;
    int pipeId = SearchId(pipes, NumberInput(0));
    cout << "Введите ID КС, откуда выходит труба: " << endl;
    int out = SearchId(kompres, NumberInput(0));
    cout << "Введите ID КС, куда входит труба: " << endl;
    int in = SearchId(kompres, NumberInput(0));
    if (pipeId != -1 && pipes[pipeId].in == 0 && pipes[pipeId].out == 0 && out != -1 && in != -1 && out != in) {
        pipes[pipeId].link(in, out);
        kompres[in].createLink();
        kompres[out].createLink();
    }
    else
        cout << "Ошибка" << endl;
}

void DeleteBranches(unordered_map<int, pipe>& pipes, unordered_map<int, KS>& kompres) {
    ShowConnection(pipes);
    cout << "Введите ID трубы, связь которой хотите удалить: " << endl;
    int pipeId = SearchId(pipes, NumberInput(0));
    if (pipeId != -1 && pipes[pipeId].linked()) {
        kompres[pipes[pipeId].in].ClearLink();
        kompres[pipes[pipeId].out].ClearLink();
        pipes[pipeId].ClearLink();
    }
    else
        cout << "Ошибка" << endl;
}

//------------------------------------------------For Graph------------------------------------------------------

unordered_map<int, int> CreateIndexOfVertices(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    set<int> vertices;
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed() && kompres.count(p.in) && kompres.count(p.out)) {
            vertices.insert(p.out);
            vertices.insert(p.in);
        }
    unordered_map<int, int> VerticesIndex;
    int i = 0;
    for (const int& v : vertices)
        VerticesIndex.insert({ v, i++ });
    return VerticesIndex;
}

unordered_map<int, int> CreateIndexOfVerticesReverse(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    set<int> vertices;
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed() && kompres.count(p.in) && kompres.count(p.out)) {
            vertices.insert(p.out);
            vertices.insert(p.in);
        }
    unordered_map<int, int> VerticesIndex;
    int i = 0;
    for (const int& v : vertices)
        VerticesIndex.insert({ i++, v });
    return VerticesIndex;
}

vector<vector<int>> CreateGraph(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    unordered_map<int, int> VerticesIndex = CreateIndexOfVertices(pipes, kompres);
    vector<vector<int>> r;
    r.resize(VerticesIndex.size());
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed())
            r[VerticesIndex[p.out]].push_back(VerticesIndex[p.in]);
    return r;
}

vector<vector<double>> CreateMatrixWeights(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    unordered_map<int, int> VerticesIndex = CreateIndexOfVertices(pipes, kompres);
    vector<vector<double>> w;
    w.assign(VerticesIndex.size(), {});
    for (int i = 0; i < VerticesIndex.size(); ++i) {
        w[i].assign(VerticesIndex.size(), INT_MAX);
        w[i][i] = 0;
    }
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed())
            w[VerticesIndex[p.out]][VerticesIndex[p.in]] = p.length;
    return w;
}

vector<vector<double>> CreateMatrixThroughput(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    unordered_map<int, int> VerticesIndex = CreateIndexOfVertices(pipes, kompres);
    vector<vector<double>> t;
    t.assign(VerticesIndex.size(), {});
    for (int i = 0; i < VerticesIndex.size(); ++i)
        t[i].assign(VerticesIndex.size(), 0);
    for (const auto& [i, p] : pipes)
        if (p.CanBeUsed())
            t[VerticesIndex[p.out]][VerticesIndex[p.in]] = p.GetProductivity();
    return t;
}

void Gts::GraphСalculation(const unordered_map<int, pipe>& pipes, const unordered_map<int, KS>& kompres) {
    ribs = CreateGraph(pipes, kompres);
    weights_matrix = CreateMatrixWeights(pipes, kompres);
    throughput_matrix = CreateMatrixThroughput(pipes, kompres);
    unordered_map<int, int> VerticesIndex = CreateIndexOfVertices(pipes, kompres);
    unordered_map<int, int> VerticesIndexForOutput = CreateIndexOfVerticesReverse(pipes, kompres);
    while (true) {
        cout << endl << "1. Топоплогическая сортировка " << endl << "2. Поиск кратчайшего пути " << endl << "3. Поиск максимального потока" << endl << "0. Выход " << endl;
        int graphcase = NumberInput(0, 3);
        switch (graphcase) {
        case 0:
        {
            return;
        }
        case 1:
        {
            TopologicalSort(VerticesIndexForOutput);
            break;
        }
        case 2:
        {
            int start, end;
            cout << "Введите id КС, откуда начинать поиск пути " << endl;
            start = SearchId(kompres, NumberInput(0));
            cout << "Введите id КС, куда нужно найти путь " << endl;
            end = SearchId(kompres, NumberInput(0));
            if (start == -1 || end == -1 || start == end) return;
            FindWay(VerticesIndex[start], VerticesIndex[end], VerticesIndexForOutput);
            break;
        }
        case 3:
        {
            int start, end;
            cout << "Введите id КС, откуда начинать рассчет максимального потока " << endl;
            start = SearchId(kompres, NumberInput(0));
            cout << "Введите id КС конца " << endl;
            end = SearchId(kompres, NumberInput(0));
            if (start == -1 || end == -1 || start == end) return;
            MaxStream(VerticesIndex[start], VerticesIndex[end], VerticesIndexForOutput);
            break;
        }
        }
    }
}


//------------------------------------------------Graph------------------------------------------------------

void DepthFirstSearch(int v, vector<char>& cl, vector<int>& p, int& cycle_start, const vector<vector<int>>& ribs, vector<int> &result) {
	cl[v] = 1;
	for (size_t i = 0; i < ribs[v].size(); ++i) {
		int to = ribs[v][i];
		if (cl[to] == 0) {
			p[to] = v;
			DepthFirstSearch(to, cl, p, cycle_start, ribs, result);
		}
		else if (cl[to] == 1) {
			cycle_start = to;
			return;
		}
	}
	result.push_back(v);
	cl[v] = 2;
}

void Gts::TopologicalSort(const unordered_map<int, int>& VerticesIndex) {
	int n = ribs.size();
	vector<int> result;
	vector<char> cl;
	vector<int> p;
	int cycle_start;
	p.assign(n, -1);
	cl.assign(n, 0);
	cycle_start = -1;
	result.clear();
	for (int i = 0; i < n; ++i)
		if (cl[i] != 2)
			DepthFirstSearch(i, cl, p, cycle_start, ribs, result);
	if (cycle_start == -1) {
		cout << "Цикл не обнаружен" << endl;
		reverse(result.begin(), result.end());
		for (int i = 0; i < result.size(); i++) {
			cout << i+1 << " КС: " << VerticesIndex.at(result[i]) << endl;
		}
	}
	else
		cout << "Есть цикл, соритировка невозможна " << endl;
}

void Gts::MaxStream(int start, int end, const unordered_map<int, int>& VerticesIndexForOutput)
{
	int n = throughput_matrix.size();
	vector<vector<double>> c = throughput_matrix;
	double MaxFlow = 0;//Искомый максимальный поток
	while (true) {
		/*< Поиск в ширину */
		vector <int> parent(n, -1);
		vector <bool> used(n, false);
		queue <int> q;

		used[start] = true;
		q.push(start);

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int i = 0; i < n; i++) {
				if (!used[i] && c[v][i] > 0) {
					parent[i] = v;
					used[i] = true;
					q.push(i);
				}
			}
		}
		if (!used[end])//Не дошли до стока - поток уже максимальный
			break;
		double AugFlow = INFINITY;//Дополнительный поток
		/*< Бежим по пути и ищем ребро с минимальной пропускной способностью */
		int ptr = end;
		while (ptr != start) {
			AugFlow = min(AugFlow, c[parent[ptr]][ptr]);
			ptr = parent[ptr];
		}
		/*< Изменяем пропускные способности */
		ptr = end;
		while (ptr != start) {
			c[parent[ptr]][ptr] -= AugFlow;//По пути вычитаем
			c[ptr][parent[ptr]] += AugFlow;//Против пути добавляем
			ptr = parent[ptr];
		}
		MaxFlow += AugFlow;
	}
	cout << "Максимальный поток " << MaxFlow << endl;
}

void Gts::FindWay(int start, int end, const unordered_map<int, int>& VerticesIndexForOutput)
{
	vector<vector<double>> res = weights_matrix;
	vector<vector<int>> next; // матрица для восстановления пути
	int n = res.size();
	next.resize(n);
	for (int i = 0; i < n; i++)
		for (int t = 0; t < n; t++)
			next[i].push_back(t);
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (res[i][j] > res[i][k] + res[k][j]) {
					res[i][j] = res[i][k] + res[k][j];
					next[i][j] = next[i][k];
				}
	if (res[start][end] == INT_MAX) {
		cout << "Пути не существует" << endl;
		return;
	}
	cout << "Путь из КС " << VerticesIndexForOutput.at(start) << " в КС " << VerticesIndexForOutput.at(end) << " равен " << res[start][end] << endl << "Путь: " << endl;
	int temp = start;
	while (temp != end) {
		cout << VerticesIndexForOutput.at(temp) << " -> ";
		temp = next[temp][end];
	}
	cout << VerticesIndexForOutput.at(end) << endl;
}


//------------------------------------------------Public------------------------------------------------------

void Gts::NEWPipe() {
    pipe NewPipe;
    int NewID = ++NewPipe.MaxId;
    cin >> NewPipe;
    pipes.insert({ NewID, NewPipe });
}

void Gts::NEWKs() {
    KS NewKS;
    int NewID = ++NewKS.MaxId;
    cin >> NewKS;
    kompres.insert({ NewID, NewKS });
}

void Gts::PrintObj() {
    if (pipes.size() == 0)
        cout << "Трубы не были добавлены, выводить нечего" << endl;
    else
        ShowAllPipes(pipes);
    cout << endl;
    if (kompres.size() == 0)
        cout << "Компрессорные станции не были добавлены, выводить нечего" << endl;
    else
        ShowAllKompres(kompres);
}

void Gts::EditPipes() {
    if (pipes.size() > 0) {
        ShowAllPipes(pipes);
        EditAllPipes(pipes);
    }
    else
        cout << "Трубопроводы не были добавлены, редактировать нечего" << endl;
}

void Gts::EditKSs() {
    if (kompres.size() > 0) {
        ShowAllKompres(kompres);
        EditAllKompres(kompres);
    }
    else
        cout << "Станции не были добавлены, редактировать нечего" << endl;
}

void Gts::SaveData() {
    cout << "Введите название файла: ";
    string FileName;
    getline(cin, FileName);
    if (CreateFile(pipes, kompres, "./saves/" + FileName)) {
        cout << "Данные сохранены в файл" << endl;
    }
    else
        cout << "Не удалось создать файл" << endl;
}

void Gts::LoadData() {
    cout << "Введите название файла: ";
    string FileName;
    getline(cin, FileName);
    if (ReadFile(pipes, kompres, "./saves/" + FileName)) {
        cout << "Данные успешно загружены" << endl;
        ShowAllPipes(pipes);
        ShowAllKompres(kompres);
    }
    else
        cout << "Файл " << FileName.erase(0, FileName.find_last_of("/") + 1) << " не найден" << endl;
}

void Gts::DeletePipes() {
    if (pipes.size() > 0) {
        ShowAllPipes(pipes);
        Delete(pipes);
    }
    else
        cout << "Трубы не были добавлены, удалять нечего" << endl;
}

void Gts::DeleteKSs() {
    if (kompres.size() > 0) {
        ShowAllKompres(kompres);
        Delete(kompres);
    }
    else
        cout << "Станции не были добавлены, удалять нечего" << endl;
}

void Gts::FiltersMenu() {
    cout << endl << "Меню фильтров" << endl << "1. Поиск/редактирование труб " << endl << "2. Поиск КС "
        << endl;
    int editCase = NumberInput(0);
    if (editCase == 1) {
        PipeFilterMenu(pipes);
    }
    else if (editCase == 2) {
        KSFilterMenu(kompres);
    }
}

void Gts::ConnectObj() {
    if (pipes.size() > 0 && kompres.size() > 1)
        CreateBranch(pipes, kompres);
    else
        cout << "Необходимые элементы не были добавлены " << endl;
}

void Gts::DisconnectObj() {
    if (pipes.size() > 0 && kompres.size() > 1)
        DeleteBranches(pipes, kompres);
    else
        cout << "Ошибка " << endl;
}

void Gts::PrintConnections() {
    if (pipes.size() > 0 && kompres.size() > 1)
        ShowConnection(pipes);
    else
        cout << "Ошибка " << endl;
}

void Gts::NetCalculation() {
    if (pipes.size() > 0 && kompres.size() > 1)
        GraphСalculation(pipes, kompres);
    else
        cout << "Ошибка " << endl;
}
