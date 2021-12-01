using namespace std;

#include <map>
#include <iostream>

#include "myPointer.h"

using namespace Ptr;

int main() {	
	while (1) {
		myPointer p = myPointer::alloc(10);
		for (size_t i = 0; i < 10; ++i) {
			*p = i;
			p++;
		}
		myPointer p2 = p;
		myPointer p3 = move(p2);
		p3 -= 3;
		myPointer p4 = p3.deep_copy();
		cout << *p4 << ": ";
		for (auto x : p4)
			cout << x;
		cout << '\n';
	}
}