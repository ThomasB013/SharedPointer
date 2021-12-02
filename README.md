# SharedPointer
Implementation of a more sophisticated pointer that eliminates naked news.

To do:
1. Support generic types.
2. Support allocators. 
3. Add testing.
4. Document member functions.

Problems:
1. Difference between constant content and constant size. For example. If I have a 2D array, I want to be able to give the rows as a result of dereferencing. And I wan't people to be able to change the row. I don't want people to be able to assign a new row, as I want the 2D array to be squared. So arr[4][3] = 3 must be possible, but arr[4] = ::alloc(10) not. Solution: maybe remove operator=. But that leads to new problems. Solution 2: Do a class hierarchy where the base clase cannot change never change after being constructed.
