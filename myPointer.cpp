#include "myPointer.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

namespace {
	map<int*, unsigned> ref_count = {};
}

Ptr::myPointer::~myPointer() {
	/* Destructor deallocates memory if the count is zero.
	   If the count is zero, delete the referenced content.
	   If the to is the nullptr, ignore. 
	*/
	if (base) {
		ref_count[base]--;
		if (ref_count[base] == 0) {
			ref_count.erase(base);
			delete[] base;
		}
	}
}

Ptr::myPointer::myPointer() {
	cur = base = nullptr;
	size = 0;
}

Ptr::myPointer::myPointer(const Ptr::myPointer& ptr) {
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ref_count[base]++;
}

Ptr::myPointer::myPointer(myPointer&& ptr) noexcept {
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ptr.size = 0;
	ptr.cur = ptr.base = nullptr;
}

Ptr::myPointer& Ptr::myPointer::operator=(const Ptr::myPointer& ptr) {
	this->~myPointer(); //Destroy current pointer.
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ref_count[base]++;
	return *this;
}

Ptr::myPointer& Ptr::myPointer::operator=(Ptr::myPointer&& ptr) noexcept {
	this->~myPointer();
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ptr.size = 0;
	ptr.cur = ptr.base = nullptr;
	return *this;
}

Ptr::myPointer Ptr::myPointer::alloc(size_t n) throw(bad_alloc) {
	Ptr::myPointer p;
	p.base = new int[n]; //throws bad_alloc
	p.cur = p.base;
	p.size = n;
	ref_count[p.base]++;
	return p;
}

int& Ptr::myPointer::operator[](size_t i) throw(out_of_range) {
	if (cur >= base && i + (cur - base) < size)
		return cur[i];
	throw out_of_range{ "Ptr::myPointer::operator[](size_t " + to_string(i) + ") out of range for size " + to_string(size) };
}

const int& Ptr::myPointer::operator[](size_t i) const throw(out_of_range) {
	if (cur >= base && i + (cur - base) < size)
		return cur[i];
	throw out_of_range{ "Ptr::myPointer::operator[](size_t " + to_string(i) + ") const out of range for size " + to_string(size) };
}

int& Ptr::myPointer::operator*() throw(out_of_range)  {
	if (cur >= base && cur - base < size)
		return *cur;
	throw out_of_range("Ptr::myPointer::operator*() out of range");
}

const int& Ptr::myPointer::operator*() const throw(out_of_range) {
	if (cur >= base && cur - base < size)
		return *cur;
	throw out_of_range("Ptr::myPointer::operator*() const out of range");
}

Ptr::myPointer& Ptr::myPointer::operator++() {
	cur++;
	return *this;
}

Ptr::myPointer& Ptr::myPointer::operator--() {
	cur--;
	return *this;
}

Ptr::myPointer Ptr::myPointer::operator++(int) {
	const myPointer TEMP = *this;
	cur++;
	return TEMP;
}

Ptr::myPointer Ptr::myPointer::operator--(int) {
	const myPointer TEMP = *this;
	cur--;
	return TEMP;
}

Ptr::myPointer& Ptr::myPointer::operator+=(size_t n) {
	cur += n;
	return *this;
}

Ptr::myPointer& Ptr::myPointer::operator-=(size_t n) {
	cur -= n;
	return *this;
}

int Ptr::myPointer::operator-(const Ptr::myPointer& ptr) const {
	return cur - ptr.cur;
}

bool Ptr::myPointer::operator==(const Ptr::myPointer& ptr) const {
	return (cur == ptr.cur);
}

bool Ptr::myPointer::operator!=(const Ptr::myPointer& ptr) const {
	return (cur != ptr.cur);
}

bool Ptr::myPointer::operator<(const Ptr::myPointer& ptr) const {
	return (cur < ptr.cur);
}

bool Ptr::myPointer::operator>(const Ptr::myPointer& ptr) const {
	return (cur > ptr.cur);
}

bool Ptr::myPointer::operator<=(const Ptr::myPointer& ptr) const {
	return (cur <= ptr.cur);
}

bool Ptr::myPointer::operator>=(const Ptr::myPointer& ptr) const {
	return (cur >= ptr.cur);
}

Ptr::myPointer Ptr::myPointer::begin() const {
	myPointer TEMP = *this;
	TEMP.cur = TEMP.base;
	return TEMP;
}

Ptr::myPointer Ptr::myPointer::end() const {
	myPointer TEMP = *this;
	TEMP.cur = TEMP.base + TEMP.size;
	return TEMP;
}

Ptr::myPointer Ptr::myPointer::deep_copy() const {
	myPointer TEMP = Ptr::myPointer::alloc(size);
	for (auto val : *this)
		*TEMP++ = val;
	TEMP.cur = TEMP.base + (cur - base);
	return TEMP;
}