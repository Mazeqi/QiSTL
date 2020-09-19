
#include"AlgobaseTest.h"
#include<algorithm>
#include<iostream>
#include<vector>
namespace QTL {
	namespace AlgobaseTest {
		void testMinMax() {
			assert(QTL::min(1, 2) == 1);
			assert(QTL::min(2, 1) == 1);
			assert(QTL::min('a', 'z') == 'a');
			assert(QTL::min(3.14, 2.72) == 2.72);

			assert(QTL::max(1, 2) == 2);
			assert(QTL::max(2, 1) == 2);
			assert(QTL::max('a', 'z') == 'z');
			assert(QTL::max(3.14, 2.73) == 3.14);
		}


		void test_copy() {
			int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
			int exp[5], act[5];

			std::cout << "test_copy_1\n";
			std::copy(arr1, arr1 + 5, exp);
			QTL::copy(arr1, arr1 + 5, act);
			for (int i = 0; i < 5; i++) {
				std::cout << exp[i] << ' ';
			}
			std::cout << std::endl;
			for (int i = 0; i < 5; i++) {
				std::cout << act[i] << ' ';
			}

			std::cout << "\n";

			std::cout << "test_copy_2\n";
			std::copy(arr1+5, arr1 + 10, exp);
			QTL::copy(arr1+5, arr1 + 10, act);
			for (int i = 0; i < 5; i++) {
				std::cout << exp[i] << ' ';
			}
			std::cout << std::endl;
			for (int i = 0; i < 5; i++) {
				std::cout << act[i] << ' ';
			}
			std::cout << std::endl;

		}

		void test_copy_backward() {
			int arr1[] = { 1,2,3,4,5 };
			std::vector<int> exp{ 0,0,0,0,0,6,7,8,9,10 };
			int act[] = { 0,0,0,0,0,6,7,8,9,10 };

			QTL::copy_backward(arr1, arr1 + 5, exp.begin() + 6);
			//QTL::copy_backward(arr1, arr1 + 5, exp.begin() + 6);
			//QTL::copy_backward(arr1, arr1 + 5, act + 6);

			std::vector<int>::iterator iter;
			for (iter = exp.begin(); iter != exp.end(); iter++) {
				std::cout << *iter << " ";
			}

			std::cout << std::endl;

			for (int i = 0; i < 10; i++) {
				std::cout << act[i] << " ";

			}
			std::cout << std::endl;
		}
	}
}