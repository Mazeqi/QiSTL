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

public:
	/*
	*	noexcept
		该关键字告诉编译器，函数中不会发生异常,这有利于编译器对程序做更多的优化。
		如果在运行时，noexecpt函数向外抛出了异常（如果函数内部捕捉了异常并完成处理，
		这种情况不算抛出异常），程序会直接终止，调用std::terminate()函数，
		该函数内部会调用std::abort()终止程序。
	*/
	//构造、复制、移动、析构函数
	vector() noexcept :
		begin_(nullptr),
		end_(nullptr),
		cap_(nullptr){
		try {
			begin_ = data_allocator::allocate(16);
			end_ = begin_;
			cap_ = begin_ + 16;

		}
		catch (...) {
			begin_ = nullptr;
			end_   = nullptr;
			cap_   = nullptr;
		}

	}

	explicit vector(size_type n) :
		begin_(nullptr),
		end_(nullptr),
		cap_(nullptr) {

		const size_type init_size = QTL::max(static_cast<size_type>(16), n);



	}



};


#endif // !_VECTOR_H_
