#pragma once
#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "Algobase.h"
#include "Type_traits.h"
#include "Construct.h"
#include "Iterator.h"

namespace QTL {
	//------------------------------------------------------------------------------------
	/*
		uninitialized_copy
	    把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
		
		uninitialized_copy()使我们能够将内存的配置和对象的构造行为分离开来，
		如果作为输出目的地的[result,result+(last-first))范围内的每一个迭代器
		都指向为初始化区域，则uninitialized_copy()会使用copy constructor，
		给身为输入来源之[first,last)范围内的每一个对象产生一份复制品，
		放进输出范围中。换句话说，针对输入范围内的每一个迭代器i，
		该函数会调用construct(&*(result+(i-first)),*i)，产生*i的复制品，
		放置于输出范围的相对位置上。
	*/
	
	//char、double等的复制，具体可看type_traits
	template <class InputIter, class ForwardIter>
	inline ForwardIter _uninitialized_copy_aux(
		InputIter first, InputIter last, ForwardIter result, true_type) {
		QTL::copy(first, last, result);
	}

	template <class InputIter, class ForwardIter>
	inline ForwardIter _uninitialized_copy_aux(
		InputIter first, InputIter last, ForwardIter result, false_type) {
		auto cur = result;
		try {
			for (; first != last; ++first, ++cur) {
				QTL::construct(&*cur, *first);
			}
		}
		catch (...) {
			for (; result != cur; ++result) {
				QTL::destroy(&*result);
			}
		}

		return cur;
	}


	template <class InputIter, class ForwardIter, class Tp>
	inline ForwardIter _uninitialized_copy(
		InputIter first, InputIter last, ForwardIter result, Tp*) {

		typedef typename type_traits<Tp>::is_POD_type is_pod;
		return _uninitialized_copy_aux(first, last, result, is_pod());

	}

	template <class InputIter, class ForwardIter>
	inline ForwardIter uninitialized_copy(
		InputIter first, InputIter last, ForwardIter result) {
		return _uninitialized_copy(first, last, result, value_type(first));
	}

	
	//------------------------------------------------------------------------------------
	/*
		uninitialized_copy_n
		把 [first, first + n) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
	*/

	template <class InputIter, class Size, class ForwardIter>
	inline pair<InputIter, ForwardIter> _uninitialized_copy_n(InputIter first, Size count, ForwardIter result, false_type) {

		ForwardIter cur = result;

		try {
			for (; count > 0; --count, ++first, ++cur) {
				QTL::construct(&*cur, *first);
			}
		}
		catch (...) {
			for (; result != cur; ++result) {
				QTL::destroy(&*result);
			}
		}
		return pair<InputIter, ForwardIter>(first, cur);
	}

	template <class InputIter, class Size, class ForwardIter>
	inline pair<InputIter, ForwardIter> _uninitialized_copy_n(InputIter first, Size count, ForwardIter result, true_type) {
		return copy_n(first, count, result);
	}

	template<class InputIter, class Size, class ForwardIter>
	inline pair<InputIter, ForwardIter>
		uninitialized_copy_n(InputIter first, Size count, ForwardIter result) {
		typedef typename type_traits<typename iterator_traits<InputIter>::value_type>::is_POD_type is_pod;
		return _uninitialized_copy_n(first, count, result, is_pod());
	}

	//------------------------------------------------------------------------------------
	/*
		uninitialized_fill
		在 [first, last) 区间内填充元素值
	*/

	template<class ForwardIter, class T>
	void _uninitialized_fill(ForwardIter first, ForwardIter last, const T& value, true_type) {

	}



}
#endif // !_UNINITIALIZED_H_

