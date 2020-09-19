#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

namespace QTL {


	// --------------------------------------------------------------------------------------
	// pair
	// 结构体模板 : pair
	// 两个模板参数分别表示两个数据的类型
	// 用 first 和 second 来分别取出第一个数据和第二个数据
	template <class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(T1()), second(T2()) {}
		pair(const T1& a, const T2& b) : first(a), second(b) {}

	};


}

#endif // !_UTIL_H_
