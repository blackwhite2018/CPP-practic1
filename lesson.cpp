#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <vector>

template <typename T> void swap(T& num1, T& num2) {
	T interim{ num1 };
	num1 = std::move(num2);
	num2 = std::move(interim);
}

int getRandomNum(int, int);
int** createArray(int, int);
void printArray(int*, int);
void printArray(int**, int, int);
void removeArray(int**, int);
int getSumElemsArray(int*, int);
int getSumElemsArray(int**, int, int);
double getAvg(int*, int);
double getAvg(int**, int, int);
int getMinElemInArray(int**, int, int);
int getMaxElemInArray(int**, int, int);
int* getSumCols(int**, int, int);
int getQuantityPositiveNum(int*, int);
int getQuantityNegativeNum(int*, int);
int getQuantityZeroNum(int*, int);
bool isBissextileYear(int);

void fillArrayRandomNum(int* arr, int counts, int min = 1, int max = 9) {
	for (int iter = 0; iter < counts; iter++) {
		arr[iter] = getRandomNum(min, max);
	}
}

void fillArrayRandomNum(int** arr, int rows, int cols, int min = 1, int max = 9) {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			arr[row][col] = getRandomNum(min, max);
		}
	}
}

void task1() {
	int
		rows { 3 },
		cols { 4 };
	int** collection = createArray(rows, cols);
	int firstNumber { 0 };

	std::cout << "Введите первое число массива: ";
	std::cin >> firstNumber;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			collection[row][col] = firstNumber;
			firstNumber = firstNumber * 2;
		}
	}

	printArray(collection, rows, cols);
	removeArray(collection, rows);
}

void task2() {
	int
		rows { 3 },
		cols { 4 };
	int** collection = createArray(rows, cols);
	int firstNumber { 0 };

	std::cout << "Введите первое число массива: ";
	std::cin >> firstNumber;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			collection[row][col] = firstNumber;
			firstNumber++;
		}
	}

	printArray(collection, rows, cols);
	removeArray(collection, rows);
}

enum Position : int {
	left = 1,
	right,
	top,
	bottom
};

void task3() {
	int
		rows { 5 },
		cols { 5 },
		offset { 0 },
		code_offset;
	int** collection = createArray(rows, cols);

	fillArrayRandomNum(collection, rows, cols);
	printArray(collection, rows, cols);

	std::cout << "Введите число сдвигов: ";
	std::cin >> offset;

	if (offset < 0) {
		std::cout << "Неверное число сдвигов.";
		return;
	}

	std::cout << "Сдвиг:\n\t1. Влево\t2. Вправо\n\t3. Вверх\t4. Вниз\n";
	std::cout << "Введите код направления сдвига: ";
	std::cin >> code_offset;

	if (code_offset < 0 || code_offset > 4) {
		std::cout << "Неверный код направления сдвига.";
		return;
	}

	switch (code_offset) {
		case Position::left:
			for (int row { 0 }; row < rows; row++) {
				for (int shift { 0 }; shift < offset; shift++) {
					for (int col { 0 }; col < cols; col++) {
						swap(collection[row][cols - 1], collection[row][cols - 1 - col]);
					}
				}
			}
			break;
		case Position::right:
			for (int row { 0 }; row < rows; row++) {
				for (int shift { 0 }; shift < offset; shift++) {
					for (int col { 0 }; col < cols - 1; col++) {
						swap(collection[row][col], collection[row][col + 1]);
					}
				}
			}
			break;
		case Position::top:
			for (int shift { 0 }; shift < offset; shift++) {
				for (int row { 0 }; row <= rows - 1; row++) {
					for (int col { 0 }; col < cols; col++) {
						swap(collection[rows - 1][col], collection[rows - 1 - row][col]);
					}
				}
			}
			break;
		case Position::bottom:
			for (int shift { 0 }; shift < offset; shift++) {
				for (int row { 0 }; row < rows - 1; row++) {
					for (int col { 0 }; col < cols; col++) {
						swap(collection[row][col], collection[row + 1][col]);
					}
				}
			}
			break;
	}

	printArray(collection, rows, cols);
	removeArray(collection, rows);
}

void task4() {
	int
		rows { 3 },
		cols { 4 };
	int** collection = createArray(rows, cols);

	fillArrayRandomNum(collection, rows, cols);
	printArray(collection, rows, cols);

	int sumElems = getSumElemsArray(collection, rows, cols);
	double avg = getAvg(collection, rows, cols);
	int min = getMinElemInArray(collection, rows, cols);
	int max = getMaxElemInArray(collection, rows, cols);

	std::cout << "Сумма элементов массива: " << sumElems << '\n';
	std::cout << "Среднее арифметическое элементов массива: " << avg << '\n';
	std::cout << "Минимальный элемент в массиве: " << min << '\n';
	std::cout << "Максимальный элемент в массиве: " << max;

	removeArray(collection, rows);
}

void task5() {
	int
		rows { 3 },
		cols { 3 };
	int** collection = createArray(rows, cols);

	fillArrayRandomNum(collection, rows, cols);


	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			std::cout << collection[row][col] << ' ';
		}
		std::cout << " | " << getSumElemsArray(collection[row], cols) << '\n';
	}

	int* sumCols = getSumCols(collection, rows, cols);
	int resultSum = getSumElemsArray(sumCols, cols);
	printArray(sumCols, cols);
	std::cout << " | " << resultSum;

	removeArray(collection, rows);
}

void task6() {
	int
		rows = 5,
		cols1 = 10,
		cols2 = 5;
	int** collection1 = createArray(rows, cols1);
	int** collection2 = createArray(rows, cols2);

	fillArrayRandomNum(collection1, rows, cols1, 0, 50);
	printArray(collection1, rows, cols1);

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols1; col = col + 2) {
			collection2[row][col / 2] = collection1[row][col] + collection1[row][col + 1];
		}
	}

	printArray(collection2, rows, cols2);
	removeArray(collection1, rows);
	removeArray(collection2, rows);
}

long getPower() {
	int
		num = 0,
		power = 0;

	std::cout << "Введите основание степени: ";
	std::cin >> num;
	std::cout << "Введите показатель степени: ";
	std::cin >> power;

	return pow(num, power);
}

int getSumRange(int min, int max) {
	int sum = 0;

	for (int iter = min + 1; iter < max; iter++) {
		sum = sum + iter;
	}

	return sum;
}

bool isPerfectNum(int number) {
	int sumDividers = 0;

	for (int iter = 1; iter < number; iter++) {
		if (number % iter == 0) {
			sumDividers = sumDividers + iter;
		}
	}

	return sumDividers == number;
}

bool isHappyNum(int num) {
	const int SIZE = 6;
	int nums[SIZE];

	for (int iter = 0; iter < SIZE; iter++) {
		nums[iter] = num % 10;
		num = num / 10;
	}

	return nums[0] + nums[1] + nums[2] == nums[3] + nums[4] + nums[5];
}

void taskAvg() {
	const int SIZE = 5;
	int arr[SIZE];

	fillArrayRandomNum(arr, SIZE);
	printArray(arr, SIZE);
	std::cout << "\nСреднее арифметическое: " << getAvg(arr, SIZE);
}

void taskFunc8() {
	const int SIZE = 10;
	int collection[SIZE];

	fillArrayRandomNum(collection, SIZE, -9);
	printArray(collection, SIZE);

	std::cout << "\nКоличество положительных чисел: " << getQuantityPositiveNum(collection, SIZE);
	std::cout << "\nКоличество отрицательных чисел: " << getQuantityNegativeNum(collection, SIZE);
	std::cout << "\nКоличество нулевых чисел: " << getQuantityZeroNum(collection, SIZE);
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	/*
		P.S. не особо понял в каком видел вообще должна быть выведена игральная карта,
	*/

	/*
		МНОГОМЕРНЫЕ МАССИВЫ - НАЧАЛО
	*/
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	/*
		МНОГОМЕРНЫЕ МАССИВЫ - КОНЕЦ
	*/

	/*
		ФУНКЦИИ - НАЧАЛО
	*/
	//std::cout << "Возведение в степень: " << getPower();            // 1
	//std::cout << "Сумма чисел из диапазона: " << getSumRange(3, 7); // 2
	//std::cout << "Совершенное число: " << isPerfectNum(12);         // 3
	//std::cout << "Счастливое число: " << isHappyNum(333233);        // 5
	//taskAvg();                                                      // 7
	//taskFunc8();                                                    // 8
	/*
		ФУНКЦИИ - КОНЕЦ
	*/

	return 0;
}

int getRandomNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}

int** createArray(int rows, int cols) {
	int** arr = new int* [rows];

	for (int row = 0; row < rows; row++) {
		arr[row] = new int[cols] { 0 };
	}

	return std::move(arr);
}

void printArray(int* arr, int counts) {
	for (int iter = 0; iter < counts; iter++) {
		std::cout << arr[iter] << ' ';
	}
}

void printArray(int** arr, int rows, int cols) {
	for (int row = 0; row < rows; row++) {
		printArray(arr[row], cols);
		std::cout << '\n';
	}
}

void removeArray(int** arr, int rows) {
	for (int row = 0; row < rows; row++) {
		delete[] arr[row];
	}
	delete[] arr;
}

int getSumElemsArray(int* arr, int counts) {
	int sum = 0;

	for (int iter = 0; iter < counts; iter++) {
		sum = sum + arr[iter];
	}

	return sum;
}

int getSumElemsArray(int** arr, int rows, int cols) {
	int sum{ 0 };

	for (int row = 0; row < rows; row++) {
		sum = sum + getSumElemsArray(arr[row], cols);
	}

	return sum;
}

double getAvg(int* arr, int counts) {
	return getSumElemsArray(arr, counts) / (double)((counts * 100) / 100);
}

double getAvg(int** arr, int rows, int cols) {
	return getSumElemsArray(arr, rows, cols) / (double)((rows * cols * 100) / 100);
}

int getMinElemInArray(int** arr, int rows, int cols) {
	int min = arr[0][0];

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (arr[row][col] < min) {
				min = arr[row][col];
			}
		}
	}

	return min;
}

int getMaxElemInArray(int** arr, int rows, int cols) {
	int max = arr[0][0];

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			if (arr[row][col] > max) {
				max = arr[row][col];
			}
		}
	}

	return max;
}

int* getSumCols(int** arr, int rows, int cols) {
	int* result = new int [cols] { 0 };

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			result[col] = result[col] + arr[row][col];
		}
	}

	return result;
}

int getQuantityPositiveNum(int* arr, int SIZE) {
	int quantity = 0;

	for (int iter = 0; iter < SIZE; iter++) {
		if (arr[iter] > 0) {
			quantity++;
		}
	}

	return quantity;
}

int getQuantityNegativeNum(int* arr, int SIZE) {
	int quantity = 0;

	for (int iter = 0; iter < SIZE; iter++) {
		if (arr[iter] < 0) {
			quantity++;
		}
	}

	return quantity;
}

int getQuantityZeroNum(int* arr, int SIZE) {
	int quantity = 0;

	for (int iter = 0; iter < SIZE; iter++) {
		if (arr[iter] == 0) {
			quantity++;
		}
	}

	return quantity;
}

bool isBissextileYear(int year) {
	return year % 4 == 0 && year % 400 == 0;
}

