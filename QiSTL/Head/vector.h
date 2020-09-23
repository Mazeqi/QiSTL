#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cassert>
#include "Type_traits.h"
#include "Util.h"
#include "Iterator.h"
#include "Allocator.h"

/*
	author : MZQ
	version: 1.0
*/


//ģ���ࣺvector
//ģ�����T ��������
template <class T>
class vector {
	static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned");
	
public:
	//vector ��Ƕ���ͱ���
	typename QTL::allocator<T>			allocator_type;
	typename QTL::allocator<T>			data_allocator;
	

	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;


	//iterator����ָ��
	typedef value_type*								iterator;
	typedef const value_type*						const_iterator;
	typedef QTL::reverse_iterator<iterator>			reverse_iterator;
	typedef QTL::reverse_iterator<const_iterator>	const_reverse_iterator;
	

private:
	// ��ʾĿǰʹ�ÿռ��ͷ��
	iterator begin_;  

	// ��ʾĿǰʹ�ÿռ��β��
	iterator end_;   

	// ��ʾĿǰ����ռ��β��
	iterator cap_;    


};


#endif // !_VECTOR_H_