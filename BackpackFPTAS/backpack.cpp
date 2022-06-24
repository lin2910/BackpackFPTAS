#include "backpack.h"


bool isInBackpack(int* inBackpack, const int* weight, const size_t size, const int maxWeight, int& countOperation) {
	int sumWeight = 0;
	for (size_t i = 0; i < size; i++)
		if (inBackpack[i] == 1) {
			sumWeight += weight[i];
			countOperation++;
		}
	countOperation += size + 1;
	return sumWeight <= maxWeight;
}

void backpackCheck(int* inBackpack, const int* weight, const int* value, const size_t size,
	int& record, int*& recordWeight, const int maxWeight, int& countOperation) {
	if (!isInBackpack(inBackpack, weight, size, maxWeight, countOperation))
		return;
	int sumValue = 0;
	for (size_t i = 0; i < size; i++)
		if (inBackpack[i] == 1) {
			sumValue += value[i];
		}
	if (sumValue >= record) {
		record = sumValue;
		delete[]recordWeight;
		recordWeight = copy(inBackpack, size);
	}
	countOperation += size + 1;
	return;
}

void generate(int*& inBackpack, const int* weight,
	const int* value,
	const size_t size, int& record, int*& recordWeight, const int maxWeight, size_t num, int& countOperation) {
	countOperation++;
	if (num == 0) {
		inBackpack[num] = 0;
		backpackCheck(inBackpack, weight, value, size, record, recordWeight, maxWeight, countOperation);
		inBackpack[num] = 1;
		backpackCheck(inBackpack, weight, value, size, record, recordWeight, maxWeight, countOperation);
		return;
	}
	inBackpack[num] = 0;
	generate(inBackpack, weight, value, size, record, recordWeight, maxWeight, num - 1, countOperation);
	inBackpack[num] = 1;
	generate(inBackpack, weight, value, size, record, recordWeight, maxWeight, num - 1, countOperation);
}


int* copy(const int* original, const size_t size) {
	int* copy = new int[size];
	for (size_t i = 0; i < size; i++)
		copy[i] = original[i];
	return copy;
}


int min(int a, int b) {
	return a < b ? a : b;
}

void print(int** arr, const size_t row, const size_t column) {
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < column; j++)
		{
			std::cout << arr[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}


size_t columnSize(const int* value, const size_t size, int& countOperation)
{
	size_t columnSize = 0;
	for (size_t i = 0; i < size; i++) {
		countOperation++;
		if (columnSize < value[i]) {
			countOperation++;
			columnSize = value[i];
		}
	}
	countOperation++;
	return size * columnSize + 1;
}


void fill(int** solveTable, const size_t row, const size_t column, const int* weight, const int* value, const size_t size, int** helpTable, const int inf, int& countOperation)
{
	// Начальная инициализация таблицы  минимального суммарного веса
	for (size_t i = 0; i < column; i++) {
		countOperation++;
		solveTable[0][i] = inf; //A[0, r] = +inf
	}
	for (size_t i = 0; i < row; i++) {
		countOperation++;
		solveTable[i][0] = 0; //A[i, 0] = 0 
	}
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			std::cout << solveTable[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	// инициализация вспомогательной таблицы
	countOperation++;
	for (int i = 0; i < row; i++)
	{
		for (int r = 0; r < column; r++) 
		{
			countOperation++;
			helpTable[i][r] = 0;
		}
	}

	// Заполнение таблицы минимального суммарного веса 
	for (int i = 1; i < row; i++) {
		for (int r = 1; r < column; r++)
		{
			if (value[i - 1] <= r)
			{
				countOperation+3;
				int minim = min(solveTable[i - 1][r - value[i - 1]] + weight[i - 1], solveTable[i - 1][r]);
				solveTable[i][r] = minim; 
				if (minim == solveTable[i - 1][r - value[i - 1]] + weight[i - 1]) // если новый предмет меньше - кладем в рюкзак
				{
					countOperation++;
					helpTable[i][r] = 1; // взяли предмет
				}
			}
			else 
			{
				countOperation++;
				solveTable[i][r] = solveTable[i - 1][r];
			}

		}
	}
}

int* getSolve(int** solveTable, const size_t row, const size_t column, int** helpTable, int * scaleValue, int * value, size_t size, int& record, const int maxWeight, int& countOperation)
{
	countOperation += 2;
	int index = 0;
	record = 0;
	int* result = new int[size];

	countOperation += size;
	for (size_t i = 0; i < size; i++)
	{
		result[i] = 0;
	}

	// Стоимость оптимального решения - 
	// значение в самой правой ячейке нижней строки, 
	// не превышающее максимально разрешенное
	countOperation++;
	for (int i = column - 1; i > -1; i--) 
	{
		countOperation++;
		if (solveTable[row - 1][i] <= maxWeight)
		{
			countOperation+=2;
			index = i; 
			break;
		}
	}

	for (int i = row - 1; i > -1; i--) 
	{
		countOperation++;
		if (helpTable[i][index]) 
		{
			countOperation += 3;
			result[i - 1] = 1;
			index -= scaleValue[i - 1]; 
			record += value[i - 1];
		}
	}
	return result;
}

int* scale(int * value, const size_t size, const double eps, int& countOperation)
{
	countOperation++;
	int max = 0; // стоимость самого дорогого предмета
	for (int i = 0; i < size; i++) {
		countOperation++;
		if (value[i] > max) {
			countOperation++;
			max = value[i];
		}
	}

	countOperation++;
	int t = eps / 2 * max / size;

	int* scaleValue = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		countOperation+2;
		if (t != 0)
			scaleValue[i] = value[i] / t;
		else
			scaleValue[i] = value[i];
	}

	return scaleValue;
}

