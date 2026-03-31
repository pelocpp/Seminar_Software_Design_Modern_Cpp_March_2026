
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <deque>
#include <map>
#include <unordered_map>

static void test_stl_01()
{
    std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	for (int i = 0; i != numbers.size(); ++i) {
		std::cout << numbers[i] << std::endl;
	}
}

static void test_stl_02()
{
	std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// C++ / STL konform
	std::vector<int>::iterator pos = numbers.begin();
	// auto pos2 = numbers.begin();

	// 
	pos = std::next(pos);

	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	int elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;
}

//WEITER: a) MIt Algorithmus  // Range 
//
//WEITER: b) Range-based Loop
//
//WEITER: c) Ein Range für MEINE Klassen
//
//WEITER: d) STL: Range ==> Überarbeitung: Neues, verbessertes Ranges-Konzept: "Ranges"



static void printElem(int& elem)
{
	int n = elem;

	std::cout << elem << std::endl;
}

static void test_stl_03()
{
	std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// Nomenklatur:  numbers.begin() bis hin zu numbers.end() bezeichnet man als Bereich // Range

	std::for_each(
		numbers.begin(),
		numbers.end(),
		printElem
	);
}

static void test_stl_04()
{
	std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// Nomenklatur:  numbers.begin() bis hin zu numbers.end() bezeichnet man als Bereich // Range
	// Range-based For-Loop
	for ( const int& elem :  numbers) {

		//++elem;
		std::cout << elem << std::endl;
	}
}

static void multiplyByTwo(int& elem) {

	elem = 2 * elem;
}

static void test_stl_05()
{
	std::vector<int> numbers(10);

	// Stilistik der STL:  Building Blocks // keine Indices (int i)

	// Alle Elemente sollen den Wert 123 haben
	std::fill(
		numbers.begin(),
		numbers.end(),
		123
	);

	std::for_each(
		numbers.begin(),
		numbers.end(),
		printElem
	);

	// Alle Elemente in dem Container mit 2 multiplizieren 
	std::for_each(
		numbers.begin(),
		numbers.end(),
		multiplyByTwo
	);
}

static void test_stl_06()
{
	//std::vector<int> numbers;
	//std::list<int> numbers;
	std::deque<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// C++ / STL konform
	//std::vector<int>::iterator pos = numbers.begin();
	auto pos = numbers.begin();

	// 
	pos = std::next(pos);

	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	int elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;

	++pos;
	if (pos == numbers.end()) {
		std::cout << "Done." << std::endl;
		return;
	}

	elem = *pos;
	std::cout << elem << std::endl;
}

void test_stl()
{
	test_stl_05();
}