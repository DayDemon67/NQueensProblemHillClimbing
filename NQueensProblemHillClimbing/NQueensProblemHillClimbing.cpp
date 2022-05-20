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

int* possibilitiesX;  //vector of the X possibilities
int** possibilitiesY; //matrix of the Y possibilities for each X

int lenX; //actual length of possibilitiesX
int* lenY;//actual length of each row in possibilitiesY


void initPossibilities() {
	lenX = n;
	lenY = new int[n];

	possibilitiesX = new int[n];
	possibilitiesY = new int* [n];

	for (int i = 0;i < n;i++) {
		lenY[i] = n;
		possibilitiesX[i] = i;

		possibilitiesY[i] = new int[n];
		for (int j = 0;j < n;j++)
			possibilitiesY[i][j] = j;

	}
}
void resetPossibilities() {
	lenX = n;

	for (int i = 0;i < n;i++)
		lenY[i] = n;
}

bool removeX(int x) {
	lenX--;
	for (int i = x;i < lenX;i++) {
		swap(possibilitiesX[i], possibilitiesX[i + 1]);
		swap(lenY[i], lenY[i + 1]);
	}
	return lenX<1;
}
bool removeXY(int x, int y) {
	lenY[x]--;
	//lenY[y]--;

	for (int i = y;i < lenY[x];i++)
		swap(possibilitiesY[x][i], possibilitiesY[x][i + 1]);

	//for (int i = x;i < lenY[y];i++)
	//	swap(possibilitiesY[y][i], possibilitiesY[y][i + 1]);

	bool X = lenY[x] > 0 ? false : removeX(x);
	//bool Y = lenY[y] > 0 ? false : removeX(y);
	
	return X; //|| Y;
}

void initArray(){
	now = new int[n];
	after = new int[n];
	for (int i = 0;i < n;i++)
		now[i] = i;
	for (int i = 0; i < n;i++)
		swap(now[i], now[rand() % n]);
}

int main() {
	cout << "N: "; cin >> n;

	srand(unsigned(time(NULL)));

	initArray();

	/* //print the initial array
	for (int i = 0;i < n;i++)
		cout << p[i] << ' ';
	cout << endl;
	*/

	initPossibilities();

	/*//test initPossibilities
	cout <<"lenX: "<< lenX<<"\nLenY: ";

	for (int i = 0;i < n;i++)
		cout << lenY[i] << ' ';
	cout << "\nPossibilitiesX";

	for (int i = 0;i < n;i++)
		cout << possibilitiesX[i] << ' ';
	cout << "\nPossibiliyiesY:\n";
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			cout << possibilitiesY[i][j] << ' ';
		cout << '\n';
	}
	_getch();
	system("cls");
	*/


	int iter = 0;
	a = eval(now);
	cpy(now, after);
	while(a>0) {

		iter++;
		int randX, randY, actualX, actualY;
		
		//x = rand() % n;
		//do y = rand() % n; while (x == y);

		randX = rand() % lenX;
		actualX = possibilitiesX[randX];

		randY = rand() % lenY[randX];
		actualY = possibilitiesY[randX][randY];


		//cout << actualX << ' ' << actualY << endl;

		swap(after[actualX], after[actualY]);
		
		int ev = eval(after);
		if (ev < a) {
			swap(now[actualX], now[actualY]);
			a = ev;
			resetPossibilities();
			cout << iter << ": " << ev << endl;
		}
		else {
			swap(after[actualX], after[actualY]);
			if (removeXY(randX, randY))
				break;
		}
		//cout << iter << ": " << eval(p)<<endl;
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
				if (mat[i][j]) cout << "X";
				else cout << "O";
			}
			else cout << "-";
		}
		cout << endl;
	}
	cout << eval(now) << ' ' << iter << "\n\n";

	_getch();
	return 0;
}