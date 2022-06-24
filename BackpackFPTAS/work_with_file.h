#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

int get_number(const char* filename);

double get_double(const char* filename);

int* get_array(const char* filename);

int* get_array(const char* filename, size_t& size);

void put_number(const char* filename, const int number);

void put_number(const char* filename, const double time, const int number);

void put_array(const char* filename, const int* array, const int size);


