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
	    �� [first, last) �ϵ����ݸ��Ƶ��� result Ϊ��ʼ���Ŀռ䣬���ظ��ƽ�����λ��
		
		uninitialized_copy()ʹ�����ܹ����ڴ�����úͶ���Ĺ�����Ϊ���뿪����
		�����Ϊ���Ŀ�ĵص�[result,result+(last-first))��Χ�ڵ�ÿһ��������
		��ָ��Ϊ��ʼ��������uninitialized_copy()��ʹ��copy constructor��
		����Ϊ������Դ֮[first,last)��Χ�ڵ�ÿһ���������һ�ݸ���Ʒ��
		�Ž������Χ�С����仰˵��������뷶Χ�ڵ�ÿһ��������i��
		�ú��������construct(&*(result+(i-first)),*i)������*i�ĸ���Ʒ��
		�����������Χ�����λ���ϡ�
	*/
	
	//char��double�ȵĸ��ƣ�����ɿ�type_traits
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
		�� [first, first + n) �ϵ����ݸ��Ƶ��� result Ϊ��ʼ���Ŀռ䣬���ظ��ƽ�����λ��
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
		�� [first, last) ���������Ԫ��ֵ
	*/

	template<class ForwardIter, class T>
	void _uninitialized_fill(ForwardIter first, ForwardIter last, const T& value, true_type) {

	}



}
#endif // !_UNINITIALIZED_H_

