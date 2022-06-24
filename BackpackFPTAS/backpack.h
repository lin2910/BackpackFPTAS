#pragma once
#include <iostream>

bool isInBackpack(int* inBackpack, const int* weight, const size_t size, const int maxWeight, int& countOperation);

void backpackCheck(int* inBackpack, const int* weight, const int* value,
	const size_t size, int& record, int*& recordWeight, const int maxWeight, int& countOperation);

void generate(int*& inBackpack, const int* weight, const int* value,
	const size_t size, int& record, int*& recordWeight, const int maxWeight, size_t num, int& countOperation);

int* copy(const int* original, const size_t size);

int min(int a, int b);

void print(int** arr, const size_t row, const size_t column);

size_t columnSize(const int* value, const size_t size, int& countOperation);

void fill(int** solveTable, const size_t row, const size_t column,
	const int* weight, const int* value, const size_t size,
	int** helpTable, const int inf, int& countOperation);

int* getSolve(int** solveTable, const size_t row, const size_t column, int** helpTable, 
	int * scaleValue, int * value, size_t size,
	int& record, const int maxWeight, int& countOperation);

int* scale(int * value, const size_t size, const double eps, int& countOperation);