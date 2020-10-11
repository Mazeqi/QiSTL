#pragma once
#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_
#include<new.h>
#include "Type_traits.h"
#include"Iterator.h"
#include "Util.h"

/*
	Author : MZQ
	version: 1.0
*/
namespace QTL {

	//new 的用法:https://www.cnblogs.com/luxiaoxun/archive/2012/08/10/2631812.html
	/*
		这里传入的p是指向某块内存的指针，已经分配好的，
		这样写的目的是在已经分配好的内存，即p指向的内存上
		分配一个新的对象，这里为T1类的对象,并且把value的值赋给T1
	*/
	template <class T1, class T2>
	inline void _Construct(T1* p, const T2& value) {
		new ((void*)p) T1(value);
	}


	template <class T1>
	inline void _Construct(T1* p) {
		new ((void*)p) T1();
	}


	template <class Tp>
	inline void _Destroy(Tp* pointer) {
		pointer->~Tp();
	}

	//释放某个区间内的内存
	template <class ForwardIter>
	void _destroy_aux(ForwardIter first, ForwardIter last, false_type) {
		for (; first != last; ++first) {
			destroy(&*first);
		}
	}

	//一般char、double这些是不用destroy的，所以函数空执行
	template <class ForwardIter>
	inline void _destroy_aux(ForwardIter, ForwardIter, true_type) {
	
	}

	//有默认解构器
	template <class ForwardIter, class Tp>
	inline void _destroy(ForwardIter first, ForwardIter last, Tp*) {
		typedef typename type_traits<Tp>::has_trivial_destructor Trivial_destructor;
		_destroy_aux(first, last, Trivial_destructor());
	}

	template <class ForwardIter>
	inline void _Destroy(ForwardIter first, ForwardIter last) {
		_destroy(first, last, value_type(first));
	}

	//对外接口
	template <class T1, class T2>
	inline void construct(T1* p, const T2& value) {
		_Construct(p, value);
	}

	template <class T1>
	inline void construct(T1* p) {
		_Construct(p);
	}

	template<class Ty, class ... Args>
	inline void construct(Ty* ptr, Args&&...args) {
		new ((void*)ptr) Ty(QTL::forward<Args>(args)...);
	}

	template <class Tp>
	inline void destroy(Tp* pointer) {
		_Destroy(pointer);
	}

	template <class ForwardIter>
	inline void destroy(ForwardIter first, ForwardIter last) {
		_Destroy(first, last);
	}
}



#endif // !_CONSTRUCT_H_