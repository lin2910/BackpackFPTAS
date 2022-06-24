#include "work_with_file.h"

int get_number(const char* filename) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";
	int n;
	fin >> n;
	fin.close();

	return n;
}

double get_double(const char* filename)
{
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";
	double d;
	fin >> d;
	fin.close();

	return d;
}

int* get_array(const char* filename) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";

	int* arr = new int[100];
	int k;
	int n = 0;
	fin >> k;
	arr[n] = k;

	while (fin >> k) {
		n++;
		arr[n] = k;
	}
	fin.close();
	return arr;
}

int* get_array(const char* filename, size_t& size) {
	assert(filename);
	ifstream fin(filename);
	if (!fin.is_open()) throw "Не найден указанный файл";

	int* arr = new int[100];
	int k;
	int n = 0;

	while (fin >> k) {
		arr[n] = k;
		n++;
	}

	fin.close();
	cout << endl;
	size = n;
	return arr;
}

void put_number(const char* filename, const int number) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << number << endl;
	fout.close();
}

void put_number(const char* filename, const double time, const int number) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	fout << time << endl;
	fout << number << endl;
	fout.close();
}

void put_array(const char* filename, const int* array, const int size) {
	assert(filename);
	ofstream fout(filename);
	if (!fout.is_open())
		throw "Couldn't open file!";
	for (size_t i = 0; i < size; i++)
		fout << array[i] << ' ';
	fout << endl;
	fout.close();
}
