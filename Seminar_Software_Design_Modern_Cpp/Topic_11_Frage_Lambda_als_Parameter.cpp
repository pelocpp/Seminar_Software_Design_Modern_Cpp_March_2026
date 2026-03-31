
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <print>
#include <functional>

auto lambda = [](int arg) -> void {
	std::println("Argument: {}", arg);
	};

void wozu_std_function()
{
	std::vector<std::function< void(int) >> functions;
}


void indirekter_aufruf_01(std::function< void (int) > func, int argument)
{
	func(argument);
}

void indirekter_aufruf_02(auto func, int argument)
{
	func(argument);
}

void indirekter_aufruf_03(auto&& func, int argument)
{
	func(argument);
}

template <typename T>
void indirekter_aufruf_04(T&& func, int argument)
{
	func(argument);
}

//template <typename T>
//void indirekter_aufruf_05(T&& func, int argument)
//{
//	 std::forward<T> (func) (argument);
//}

template <typename T>
void indirekter_aufruf_06(const T& func, int argument)
{
	func (argument);
}

template <typename T>
void indirekter_aufruf_07(T func, int argument)
{
	func(argument);
}

void test_frage_lambda_als_parameter()
{
	indirekter_aufruf_01(lambda, 123);

	indirekter_aufruf_02(lambda, 123);

	indirekter_aufruf_03(lambda, 123);

	indirekter_aufruf_04(lambda, 123);

//	indirekter_aufruf_05(lambda, 123);

	indirekter_aufruf_06(lambda, 123);

	indirekter_aufruf_07(lambda, 123);
}