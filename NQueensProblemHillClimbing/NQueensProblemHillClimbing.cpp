#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

using namespace std;

int n; //dimensiune

int* p;//vector curent
int a;//atacuri curente
int* u;//vector urmator


int eval(int vec[]) {
	int erori = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (abs(vec[i] - vec[j]) == j - i)
				erori++;
	return erori;
}

void cpy(int from[], int to[]) {
	for (int i = 0;i < n;i++)
		to[i] = from[i];
}


int main() {
	cout << "N: "; cin >> n;

	srand(unsigned(time(NULL)));


	//initializare vector
	p = new int[n];
	u = new int[n];
	for (int i = 0;i < n;i++)
		p[i] = i;
	for (int i = 0; i < n;i++)
		swap(p[i], p[rand() % n]);

	/*
	for (int i = 0;i < n;i++)
		cout << p[i] << ' ';
	cout << endl;
	*/
	int iteratie;
	cpy(p, u);
	for (iteratie = 0; iteratie < n * n * n;iteratie++) {
		
		//cout << iteratie + 1 << ": " << ev << '\n';

		int x, y;
		x = rand() % n;
		do y = rand() % n; while (x == y);


		//cout << x << ' ' << y << endl;
		swap(u[x], u[y]);
		int ev = eval(u);
		if (ev < eval(p)) {
			swap(p[x], p[y]);
			cout << iteratie << ": " << ev << endl;
		}
		else {
			swap(u[x], u[y]);
		}

		//cout << iteratie << ": " << eval(p)<<endl;

		if (eval(p) == 0)
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
		//toate damele
		for (int j = 0;j < n;j++) {
			//toate coloanele;
			if (i == j)
				continue;
			int x = p[i] - (i - j);
			int y = p[i] + (i - j);
			if (x < n && x >= 0)
				mat[x][j]++;
			if (y < n && y >= 0)
				mat[y][j]++;
		}

	}

	system("cls");

	//afis
	for (int i = 0;i < n;i++)
		cout << p[i] + 1 << ' ';
	cout << "\n\n";

	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			if (p[j] == i) {
				if (mat[i][j]) cout << " X";
				else cout << " O";
			}
			else cout << " -";
		}
		cout << endl;
	}
	cout << eval(p) << ' ' << iteratie << "\n\n";

	//debug matrice atacuri
	/*
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			cout << mat[i][j] << ' ';
		cout << endl;
	}
	*/

	_getch();
	return 0;
}