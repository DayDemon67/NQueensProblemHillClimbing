#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

int n;

int* now;//current array
int a;//eval of now
int* after;//next array


int eval(int vec[]) {
	int errors = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (abs(vec[i] - vec[j]) == j - i)
				errors++;
	return errors;
}
void cpy(int from[], int to[]) {
	for (int i = 0;i < n;i++)
		to[i] = from[i];
}

int main() {
	cout << "N: "; cin >> n;

	srand(unsigned(time(NULL)));


	//initializare vector
	now = new int[n];
	after = new int[n];
	for (int i = 0;i < n;i++)
		now[i] = i;
	for (int i = 0; i < n;i++)
		swap(now[i], now[rand() % n]);

	/*
	for (int i = 0;i < n;i++)
		cout << p[i] << ' ';
	cout << endl;
	*/
	int iter;
	cpy(now, after);
	for (iter = 0; iter < n * n * n;iter++) {
		
		//cout << iteratie + 1 << ": " << ev << '\n';

		int x, y;
		x = rand() % n;
		do y = rand() % n; while (x == y);


		//cout << x << ' ' << y << endl;
		swap(after[x], after[y]);
		int ev = eval(after);
		if (ev < a) {
			swap(now[x], now[y]);
			a = ev;
			cout << iter << ": " << ev << endl;
		}
		else {
			swap(after[x], after[y]);
		}

		//cout << iter << ": " << eval(p)<<endl;

		if (eval(now) == 0)
			break;
	}


	int** mat;
	mat = new int* [n];
	for (int i = 0;i < n;i++)
		mat[i] = new int[n];

	for (int i = 0;i < n;i++)
		for (int j = 0;j < n;j++)
			mat[i][j] = 0;


	for (int i = 0;i < n;i++) {
		//all queens
		for (int j = 0;j < n;j++) {
			//all collumns;
			if (i == j)
				continue;
			int x = now[i] - (i - j);
			int y = now[i] + (i - j);
			if (x < n && x >= 0)
				mat[x][j]++;
			if (y < n && y >= 0)
				mat[y][j]++;
		}

	}

	system("cls");

	//show
	for (int i = 0;i < n;i++)
		cout << now[i] + 1 << ' ';
	cout << "\n\n";

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (now[j] == i) {
				if (mat[i][j]) cout << " X";
				else cout << " O";
			}
			else cout << " -";
		}
		cout << endl;
	}
	cout << eval(now) << ' ' << iter << "\n\n";

	_getch();
	return 0;
}
