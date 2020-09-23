#pragma once
#ifndef _UTIL_H_
#define _UTIL_H_

#include <cstddef>
#include "Type_traits.h"

namespace QTL {
	
	// -----------------------------------------------------------------------------------
	// move
	// 将变量转化为右值
	/*
		std::string str = "Hello";
		std::vector<std::string> v;
 
		// uses the push_back(const T&) overload, which means 
		// we'll incur the cost of copying str
		v.push_back(str);
		std::cout << "After copy, str is \"" << str << "\"\n";
 
		// uses the rvalue reference push_back(T&&) overload, 
		// which means no strings will be copied; instead, the contents
		// of str will be moved into the vector.  This is less
		// expensive, but also means str might now be empty.

		v.push_back(std::move(str));
		std::cout << "After move, str is \"" << str << "\"\n";
		std::cout << "The contents of the vector are \"" << v[0]
											 << "\", \"" << v[1] << "\"\n";
		After copy, str is "Hello"
		After move, str is ""
		The contents of the vector are "Hello", "Hello"

		令一个对象无法move
		struct B { B& operator= (B&&) = delete; };

	*/
	template <class T>
	typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
		return static_cast<typename std::remove_reference<T>::type&&>(arg);
	}

	//forward
	template <class T>
	T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
		return static_cast<T&&>(arg);
	}

	template <class T>
	T&& forward(typename std::remove_reference<T>::type&& arg) noexcept
	{
		static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
		return static_cast<T&&>(arg);
	}

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
