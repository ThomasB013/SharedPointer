#include "myPointer.h"
#include <iostream>
#include <map>
#include <string>

using namespace Ptr;

namespace {
	std::map<int*, unsigned> ref_count = {};
}

myPointer::~myPointer() {
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

myPointer::myPointer() {
	cur = base = nullptr;
	size = 0;
}

myPointer::myPointer(const myPointer& ptr) {
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ref_count[base]++;
}

myPointer::myPointer(myPointer&& ptr) noexcept {
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ptr.size = 0;
	ptr.cur = ptr.base = nullptr;
}

myPointer& myPointer::operator=(const myPointer& ptr) {
	this->~myPointer(); //Destroy current pointer.
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ref_count[base]++;
	return *this;
}

myPointer& myPointer::operator=(myPointer&& ptr) noexcept {
	this->~myPointer();
	base = ptr.base;
	cur = ptr.cur;
	size = ptr.size;
	ptr.size = 0;
	ptr.cur = ptr.base = nullptr;
	return *this;
}

myPointer myPointer::alloc(size_t n) throw(std::bad_alloc) {
	myPointer p;
	p.base = new int[n]; //throws bad_alloc
	p.cur = p.base;
	p.size = n;
	ref_count[p.base]++;
	return p;
}

myPointer::value_type& myPointer::operator[](size_t i) throw(std::out_of_range) {
	if (cur >= base && i + (cur - base) < size)
		return cur[i];
	throw std::out_of_range{ "Ptr::myPointer::operator[](size_t " + std::to_string(i) + ") out of range for size " + std::to_string(size) };
}

const myPointer::value_type& myPointer::operator[](size_t i) const throw(std::out_of_range) {
	if (cur >= base && i + (cur - base) < size)
		return cur[i];
	throw std::out_of_range{ "Ptr::myPointer::operator[](size_t " + std::to_string(i) + ") const out of range for size " + std::to_string(size) };
}

myPointer::value_type & myPointer::operator*() throw(std::out_of_range) {
	if (cur >= base && cur - base < size)
		return *cur;
	throw std::out_of_range("Ptr::myPointer::operator*() out of range");
}

const myPointer::value_type& myPointer::operator*() const throw(std::out_of_range) {
	if (cur >= base && cur - base < size)
		return *cur;
	throw std::out_of_range("Ptr::myPointer::operator*() const out of range");
}

myPointer& myPointer::operator++() {
	cur++;
	return *this;
}

myPointer& myPointer::operator--() {
	cur--;
	return *this;
}

myPointer myPointer::operator++(int) {
	const myPointer TEMP = *this;
	cur++;
	return TEMP;
}

myPointer myPointer::operator--(int) {
	const myPointer TEMP = *this;
	cur--;
	return TEMP;
}

myPointer& myPointer::operator+=(size_t n) {
	cur += n;
	return *this;
}

myPointer&  myPointer::operator-=(size_t n) {
	cur -= n;
	return *this;
}

myPointer::difference_type myPointer::operator-(const myPointer& ptr) const {
	return cur - ptr.cur;
}

bool myPointer::operator==(const myPointer& ptr) const {
	return (cur == ptr.cur);
}

bool myPointer::operator!=(const myPointer& ptr) const {
	return (cur != ptr.cur);
}

bool myPointer::operator<(const myPointer& ptr) const {
	return (cur < ptr.cur);
}

bool myPointer::operator>(const myPointer& ptr) const {
	return (cur > ptr.cur);
}

bool myPointer::operator<=(const myPointer& ptr) const {
	return (cur <= ptr.cur);
}

bool myPointer::operator>=(const myPointer& ptr) const {
	return (cur >= ptr.cur);
}

myPointer myPointer::begin() const {
	myPointer TEMP = *this;
	TEMP.cur = TEMP.base;
	return TEMP;
}

myPointer myPointer::end() const {
	myPointer TEMP = *this;
	TEMP.cur = TEMP.base + TEMP.size;
	return TEMP;
}

myPointer::size_type myPointer::get_size() const {
	return size;
}

myPointer::size_type myPointer::get_dif_end() const {
	return size - (base - cur);
}

myPointer myPointer::deep_copy() const {
	myPointer TEMP = myPointer::alloc(size);
	for (auto val : *this)
		*TEMP++ = val;
	TEMP.cur = TEMP.base + (cur - base);
	return TEMP;
}