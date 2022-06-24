#include <string>
#include <iostream>

#include "work_with_file.h"
#include "backpack.h"
#include "crtdynmem.h"

using namespace std;

int main(int argc, const char* argv[]) {
	if (argc == 8) {
		try {
			const char* InputFile_c = argv[1];
			const char* InputFile_w = argv[2];
			const char* InputFile_p = argv[3];
			const char* InputFile_e = argv[4];
			const char* OutputFile_r = argv[5];
			const char* OutputFile_s = argv[6];
			const char* OutputFile_t = argv[7];
			int maxWeight = get_number(InputFile_c);

			size_t size;
			int* weight = get_array(InputFile_w);
			int* value = get_array(InputFile_p, size);

			double eps = get_double(InputFile_e);

			int countOperation = 0;
			size_t row = size + 1;

			//начало отсчета времени
			clock_t start = clock();

			int* scaleValue = scale(value, size, eps, countOperation);

			size_t column = columnSize(scaleValue, size, countOperation);
			int inf = 0;
			for (int i = 0; i < size; i++)
				inf += weight[i];
			inf++;

			int** solveTable = new int* [row];
			for (size_t i = 0; i < size + 1; i++) {
				solveTable[i] = new int[column];
			}
			int** helpTable = new int* [row];
			for (size_t i = 0; i < size + 1; i++) {
				helpTable[i] = new int[column];
			}

			fill(solveTable, row, column, weight, scaleValue, size, helpTable, inf, countOperation);
			
			int record = 0;
			int* recordWeight = getSolve(solveTable, row, column, helpTable, scaleValue, value, size, record, maxWeight, countOperation);
			
			// конец отсчета времени
			clock_t stop = clock();

			// количество секунд
			double seconds = double(stop - start) / CLOCKS_PER_SEC;

			put_number(OutputFile_s, record);
			put_array(OutputFile_r, recordWeight, size);
			put_number(OutputFile_t, seconds, countOperation);

			delete[]recordWeight;
			delete[]weight;
			delete[]value;
			delete[]scaleValue;
			for (size_t i = 0; i < row; i++)
				delete[]solveTable[i];
			delete[]solveTable;
			for (size_t i = 0; i < row; i++)
				delete[]helpTable[i];
			delete[]helpTable;
		}
		catch (const std::exception& e) {
			cout << "Exeption: " << e.what() << endl;
		}
		//system("pause");
		return 0;
	}
	cout << "Invalid count of arguments" << endl;
	

	const char* InputFile_c = "p01_c.txt";
	const char* InputFile_w = "p01_w.txt";
	const char* InputFile_p = "p01_p.txt";
	const char* InputFile_e = "p01_eps.txt";
	const char* OutputFile_s = "r01_s.txt";
	const char* OutputFile_r = "r01_r.txt";
	const char* OutputFile_t = "r01_t.txt";

	try	{
		int maxWeight = get_number(InputFile_c);

		size_t size;
		int* weight = get_array(InputFile_w);
		int* value = get_array(InputFile_p, size);

		double eps = get_double(InputFile_e);

		cout << "weight : " << endl;
		for (size_t i = 0; i < size; i++)
			cout << weight[i] << ' ';

		cout << endl << "value : "  << endl;
		for (size_t i = 0; i < size; i++)
			cout << value[i] << ' ';
		cout << endl;
		int countOperation = 0;

		size_t row = size + 1;


		//начало отсчета времени
		clock_t start = clock(); 
		
		int* scaleValue = scale(value, size, eps, countOperation);

		cout << endl << "scaleValue : " << endl;
		for (size_t i = 0; i < size; i++)
			cout << scaleValue[i] << ' ';
		cout << endl;
		size_t column = columnSize(scaleValue, size, countOperation);
		int inf = 0;
		for (int i = 0; i < size; i++)
			inf += weight[i];
		inf++;

		
		int** solveTable = new int* [row];
		for (size_t i = 0; i < size + 1; i++) {
			solveTable[i] = new int[column];
		}
		int** helpTable = new int* [row];
		for (size_t i = 0; i < size + 1; i++) {
			helpTable[i] = new int[column];
		}

		



		fill(solveTable, row, column, weight, scaleValue, size, helpTable, inf, countOperation);
		//cout << "solveTable" << endl;
		//print(solveTable, row, column);
		
		int record = 0;
		int* recordWeight = getSolve(solveTable, row, column, helpTable, scaleValue, value, size, record, maxWeight, countOperation);

		
		for (size_t i = 0; i < size; i++)
			cout << recordWeight[i] << ' ';
		cout << endl;	

		

		//generate(inBackpack, weight, value, size, record, recordWeight, maxWeight, size-1, countOperation);
		// конец отсчета времени
		clock_t stop = clock();

		// количество секунд
		double seconds = double(stop - start) / CLOCKS_PER_SEC;

		cout << "time : " << seconds << endl;
		cout << "countOperation : " << countOperation << endl;
		cout << "record : " << record << endl;

		put_number(OutputFile_s, record);
		put_array(OutputFile_r, recordWeight, size);
		put_number(OutputFile_t, seconds, countOperation);

		delete[]recordWeight;
		delete[]weight;
		delete[]value;
		delete[]scaleValue;
		for (size_t i = 0; i < row; i++)
			delete[]solveTable[i];
		delete[]solveTable; 
		for (size_t i = 0; i < row; i++)
			delete[]helpTable[i];
		delete[]helpTable;
	}
	catch (const std::exception& e) {
		cout << "Exeption: " << e.what() << endl;
	}
	cout << "end" << endl;

	_CrtDumpMemoryLeaks();
	//*/

	system("pause");
	return 0;
}
