

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <print>

// Simple

class MyContainer
{
private:
	std::vector<int> m_data;   // Containment

public:
	MyContainer()
	{
		m_data = std::vector<int>{1, 2, 3, 4, 5 };
	}

	std::vector<int>::iterator begin() { return m_data.begin(); }
	std::vector<int>::iterator end() { return m_data.end(); }
};

void test_user_defined_iteration()
{
	MyContainer cont;

	for ( int elem : cont) {

		std::cout << elem << std::endl;
	}
}

class MyOtherContainer
{
public:
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::vector<int>::iterator;
    using pointer = const value_type*;
    using reference = const value_type&;

private:
    std::vector<int> m_data;

public:
    MyOtherContainer(const std::initializer_list<int>& values) : m_data(values) {}

    // nested iterator class
    class Iterator {
    private:
        std::vector<int>::iterator m_iter;

    public:
        // c'tor
        Iterator(std::vector<int>::iterator it) : m_iter{ it } {}

        // dereference operator
        int& operator*() { return *m_iter; }

        // pre-increment operator
        Iterator& operator++() {
            ++m_iter;
            return *this;
        }

        // post-increment operator
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // equality comparison
        bool operator==(const Iterator& other) const {
            return m_iter == other.m_iter;
        }

        // inequality comparison
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    using iterator = Iterator;

public:
    // begin iterator
    Iterator begin() noexcept { return Iterator{ m_data.begin() }; }

    // end iterator
    Iterator end() noexcept { return Iterator{ m_data.end() }; }
};

void test_conceptual_example_01()
{
    MyOtherContainer container{ 1, 2, 3, 4, 5 };

    for (MyOtherContainer::iterator it = container.begin(); it != container.end(); ++it) {
        std::print("{} ", *it);
    }
    std::println();

    for (auto elem : container) {
        std::print("{} ", elem);
    }
    std::println();

    for (const auto& elem : container) {
        std::print("{} ", elem);
    }
}