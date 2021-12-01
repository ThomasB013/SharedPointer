#pragma once

#include <stdexcept>
#include <new>

namespace Ptr {
	class myPointer
	{
		int* base;
		int* cur;
		size_t size;
	public:
		myPointer();
		myPointer(const myPointer& ptr);
		myPointer(myPointer&& ptr) noexcept;
		myPointer& operator=(const myPointer& ptr);
		myPointer& operator=(myPointer&& ptr) noexcept;
		~myPointer();
		
		static myPointer alloc(size_t n) throw(std::bad_alloc);

		int& operator[](size_t i) throw(std::out_of_range);
		const int& operator[](size_t i) const throw(std::out_of_range);

		int& operator*();
		const int& operator*() const;
		
		myPointer& operator++();
		myPointer& operator--();

		myPointer operator++(int);
		myPointer operator--(int);

		myPointer& operator+=(size_t n);
		myPointer& operator-=(size_t n);

		int operator-(const myPointer& ptr) const;

		bool operator==(const myPointer& ptr) const;
		bool operator!=(const myPointer& ptr) const;
		bool operator<(const myPointer& ptr) const;
		bool operator>(const myPointer& ptr) const;
		bool operator<=(const myPointer& ptr) const;
		bool operator>=(const myPointer& ptr) const;

		myPointer begin() const;
		myPointer end() const;
	};
}

