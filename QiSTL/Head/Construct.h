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

	//new ���÷�:https://www.cnblogs.com/luxiaoxun/archive/2012/08/10/2631812.html
	/*
		���ﴫ���p��ָ��ĳ���ڴ��ָ�룬�Ѿ�����õģ�
		����д��Ŀ�������Ѿ�����õ��ڴ棬��pָ����ڴ���
		����һ���µĶ�������ΪT1��Ķ���
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

	//�ͷ�ĳ�������ڵ��ڴ�
	template <class ForwardIter>
	void _destroy_aux(ForwardIter first, ForwardIter last, false_type) {
		for (; first != last; ++first) {
			destroy(&*first);
		}
	}

	//һ��char��double��Щ�ǲ���destroy�ģ����Ժ�����ִ��
	template <class ForwardIter>
	inline void _destroy_aux(ForwardIter, ForwardIter, true_type) {
	
	}

	//��Ĭ�Ͻ⹹��
	template <class ForwardIter, class Tp>
	inline void _destroy(ForwardIter first, ForwardIter last, Tp*) {
		typedef typename type_traits<Tp>::has_trivial_destructor Trivial_destructor;
		_destroy_aux(first, last, Trivial_destructor());
	}

	template <class ForwardIter>
	inline void _Destroy(ForwardIter first, ForwardIter last) {
		_destroy(first, last, value_type(first));
	}

	//����ӿ�
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