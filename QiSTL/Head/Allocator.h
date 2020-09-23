#pragma once
#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

// 这个头文件包含一个模板类 allocator，用于管理内存的分配、释放，对象的构造、析构

#include "Alloc.h"
#include "Construct.h"
#include "Uninitialized.h"
#include "Util.h"

namespace QTL {

	template <class T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;


	public:
		static T*	allocate();
		static T*	allocate(size_type n);

		static void deallocate(T* ptr);
		static void deallocate(T* ptr, size_type n);

		static void construct(T* ptr);
		static void construct(T* ptr, const T& value);
		static void construct(T* ptr, T&& value);

		template <class... Args>
		static void construct(T* ptr, Args&& ...args);

		static void destroy(T* ptr);
		static void destroy(T* first, T* last);

	};

}
#endif // !_ALLOCATOR__H_
