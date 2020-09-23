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


//模板类：vector
//模板参数T 代表类型
template <class T>
class vector {
	static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned");
	
public:
	//vector 的嵌套型别定义
	typename QTL::allocator<T>			allocator_type;
	typename QTL::allocator<T>			data_allocator;
	

	typedef typename allocator_type::value_type			value_type;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;


	//iterator都是指针
	typedef value_type*								iterator;
	typedef const value_type*						const_iterator;
	typedef QTL::reverse_iterator<iterator>			reverse_iterator;
	typedef QTL::reverse_iterator<const_iterator>	const_reverse_iterator;
	

private:
	// 表示目前使用空间的头部
	iterator begin_;  

	// 表示目前使用空间的尾部
	iterator end_;   

	// 表示目前储存空间的尾部
	iterator cap_;    


};


#endif // !_VECTOR_H_
