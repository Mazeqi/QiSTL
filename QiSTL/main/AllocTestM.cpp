#include<iostream>
#include"../Head/Alloc.h"
using namespace std;
using namespace QTL;

//---------------------------------------------------------------------------------
void test_allocate();
void test_deallocate();


//---------------------------------------------------------------------------------

/*
int main() {
	test_deallocate();
	return 0;
}
*/


void test_allocate() {
	for (int i = 0; i < 10000; i++) {
		int* a = (int*)QTL::alloc::allocate(32);
		*a = i;
		cout << *a << "  ";
	}
}


void test_deallocate() {
	for (int i = 0; i < 10000; i++) {
		int* a = (int*)QTL::alloc::allocate(sizeof(int));
		*a = i;
		cout << *a << "  ";
		//cout << sizeof(*a) << "  ";
		QTL::alloc::deallocate(a, sizeof(int));
		//*a = i;
		//cout << sizeof(a) << "  ";
	}
}
