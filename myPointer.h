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
		//using allocator_type = ;
		using difference_type = ptrdiff_t;
		using size_type = size_t;
		using value_type = int;

		myPointer();
		myPointer(const myPointer& ptr);
		myPointer(myPointer&& ptr) noexcept;
		myPointer& operator=(const myPointer& ptr);
		myPointer& operator=(myPointer&& ptr) noexcept;
		~myPointer();
		
		static myPointer alloc(size_t n) throw(std::bad_alloc);

		value_type& operator[](size_t i) throw(std::out_of_range);
		const value_type& operator[](size_t i) const throw(std::out_of_range);

		value_type& operator*();
		const value_type& operator*() const;
		
		myPointer& operator++();
		myPointer& operator--();

		myPointer operator++(int);
		myPointer operator--(int);

		myPointer& operator+=(size_t n);
		myPointer& operator-=(size_t n);

		difference_type operator-(const myPointer& ptr) const;

		bool operator==(const myPointer& ptr) const;
		bool operator!=(const myPointer& ptr) const;
		bool operator<(const myPointer& ptr) const;
		bool operator>(const myPointer& ptr) const;
		bool operator<=(const myPointer& ptr) const;
		bool operator>=(const myPointer& ptr) const;

		myPointer begin() const;
		myPointer end() const;
		
		size_type get_size() const; //Difference between base (= begin) and end.
		size_type get_dif_end() const; //Difference between cur and end.

		myPointer deep_copy() const;
	};
}

