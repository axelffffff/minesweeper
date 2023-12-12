// mineswep.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;

int field[100][100];
int field_p[100][100];
const int N = 11, M = 11, K = 10;
// -1 mine
// 0-8 cells



// -2 hide
// -1 P
// 0-8 opened


void print_field() {
	system("cls");
	cout << "  ";
	for (int i = 0; i < M; ++i) {
		
		cout << " " << i + 1;
		if (i + 1 < 10) cout << " ";
	}
	cout << endl;
		
	for (int i = 0; i < N; i++) {
		cout << i + 1 << " ";
		if (i + 1 < 10) cout << " ";
			for (int j = 0; j < M; j++) {
				if (field_p[i][j] == -2) cout << "#  ";
				else if (field_p[i][j] == -1) cout << "P  ";
				else if (field_p[i][j] == -3) cout << "*  ";
				else cout << field_p[i][j] << "  ";

			}
			cout << endl;
		}
	

};

void dfs(int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] > -2) return;
	field_p[x][y] = field[x][y];
	if (field[x][y] > 0) {
		return;
	}
	else for (int i2 = x - 1; i2 <= x + 1; ++i2) {
		for (int j2 = y - 1; j2 <= y + 1; ++j2) {
			if (i2 != x || j2 != y) dfs(i2, j2);
		}
	}
}

void end_game(bool is_win = false) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] == -1) field_p[i][j] = -2;
			if (field[i][j] == -1) field_p[i][j] = -3;
		}
	}
	print_field();
	cout << "YOU " << (is_win ? "WIN" : "LOSE") << "\n to start a new game enter any string\n";
	string s;
	cin >> s;


}
// true - ne vzor
bool open_cell(int x, int y) {

	if (field[x][y] == -1) return false;
	else if (field[x][y] > 0) {
		field_p[x][y] = field[x][y];
		return true;
	}
	else if (field[x][y] == 0) {
		dfs(x, y);
	}

};

bool is_win() {
	int opened = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field_p[i][j] >= 0) opened++;
		}
	}
	return ( N * M - K == opened);

}

int main()
{
	while (true) {
		srand(time(0));
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				field[i][j] = 0;
				field_p[i][j] = -2;
			}
		}

		for (int i = 0; i < K; ++i) {
			while (true) {
				int x = rand() % N;
				int y = rand() % M;
				if (field[x][y] != -1) {
					field[x][y] = -1;
					break;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (field[i][j] != -1) {
					field[i][j] = 0;
					for (int i2 = i - 1; i2 <= i + 1; ++i2) {
						for (int j2 = j - 1; j2 <= j + 1; ++j2) {
							if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M && field[i2][j2] == -1) ++field[i][j];
						}
					}
				}
			}
		}

		while (true) {
			print_field();
			cout << "input command...: ";
			string com;
			cin >> com;
			if (com == "\\o") {
				int x, y;
				cout << "Input coords: ";
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) {
					continue;
				}
				if (!open_cell(x, y)) {
					
					end_game();
					break;
				}
				if (is_win()) {
					end_game(true);
					break;
				}
				//open_cell(x,y);
			}
			else if (com == "\\f") {
				int x, y;
				cout << "Input coords: ";
				
				cin >> x >> y;
				--x; --y;
				if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) {
					continue;
				}
				if (field_p[x][y] == -1) field_p[x][y] = -2;
				else field_p[x][y] = -1;
			}
			else if (com == "\\n") {
				break;
			}
			else if (com == "\\q") {
				return 0;
			}

			/*
			\o = open cell
			\f = set flag
			\n = new game
			\q = quit
			*/
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
