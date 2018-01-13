#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

int threads = 0;

string white="255 255 255";
string black="0 0 0";

void Triagle(string **array, int size, int x, int y, int level) {

	if (size >= pow(2,level)) {
		for(int i=0; i<size/2; i++) {
			array[i+x][0+y] = black;
			array[size/2-1+x][i+y] = black;
			array[i+x][i+y] = black;
		}

		for(int i=size/2; i<size; i++) {
			array[i+x][0+y] = black;
			array[size-1+x][size-i+y] = black;
			array[i+x-1][i-size/2+y] = black;
		}

		for(int i=size/2; i<size; i++) {
			array[i+x][size/2+y] = black;
			array[size-1+x][i+y] = black;
			array[i+x][i+y] = black;
		}

		/*Triagle(array, size/2, x, y, level);
		Triagle(array, size/2, x+size/2, y, level);
		Triagle(array, size/2, x+size/2, y+size/2, level);*/

		/*while (( threads > 2048 )) {
		}
			threads++;
			auto thread1 = thread (Triagle,array, size/2, x, y, level);
			while(! thread1.joinable()) {
			}
			thread1.join();
			threads--;

		while (( threads > 2048 )) {
		}
			threads++;
			auto thread2 = thread (Triagle,array, size/2, x+size/2, y, level);
			while(! thread2.joinable()) {
			}
			thread2.join();
			threads--;

		while (( threads > 2048 )) {
		}
			threads++;
			auto thread3 = thread (Triagle,array, size/2, x+size/2, y+size/2, level);
			while(! thread3.joinable()) {
			}
			thread3.join();
			threads--;*/

		thread thread1(Triagle,array, size/2, x, y, level);
		thread thread2(Triagle,array, size/2, x+size/2, y, level);
		thread thread3(Triagle,array, size/2, x+size/2, y+size/2, level);

		thread1.join();
		thread2.join();
		thread3.join();
	}
}


void CreateFile(string **array, int size) {
	ofstream myfile;
	myfile.open("triagle.ppm");
	myfile << "P3" << endl << "1024 1024" << endl << "255" << endl;

	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			myfile << array[i][j] << " ";
		}
		myfile << endl;
	}

	myfile.close();

	system("open /Users/niquit/WIZUT/PW/triagle.ppm");
}

void CreateArray(string **array, int size) {
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			array[i][j] = white;
		}
	}
}
int main(int argc, char **argv)
{
	char cwd[1024];
	chdir("/Users/niquit/WIZUT/PW/");

	int level;

	cout << "Podaj poziom [1-10]: ";
	cin >> level;

	if (level > 10) {
		cout << "Poziom za duży, ustawiony został na 10." << endl;
		level = 0;
	}
	else if (level < 1){
		cout << "Poziom za niski, ustawiony został na 1." << endl;
		level = 10;
	}
	else {
		level=11-level;
	}

	string** array = new string*[1024];
	for (int i=0; i<1024; i++)
		array[i] = new string[1024];

	CreateArray(array, 1024);
	thread thread(Triagle, array, 1024, 0, 0, level);
	thread.join();

	CreateFile(array, 1024);
}


