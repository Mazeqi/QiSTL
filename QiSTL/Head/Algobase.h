#pragma once
#ifndef _ALGOBASE_H_
#define _ALGOBASE_H_

#include"Iterator.h"
#include"Type_traits.h"
#include<string.h>
#include<iostream>
/*
	@author: MZQ
	@version:1.0
*/

namespace QTL {


#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

	//-------------------------------------------------------------------
	//swap
	template<class ForwardIter1, class ForwardIter2, class Tp>
	inline void _iter_swap(ForwardIter1 a, ForwardIter2 b, Tp*) {
		Tp tmp = *a;
		*a = *b;
		*b = tmp;
	}

	template<class ForwardIter1, class ForwardIter2>
	inline void iter_swap(ForwardIter1 a, ForwardIter2 b) {
		_iter_swap(a, b, value_type(a));
	}

	template <class Tp>
	inline void swap(Tp& a, Tp& b) {
		Tp tmp = a;
		a = b;
		b = tmp;
	}
	

	//------------------------------------------------------------------------
	//min max
	/*
		��ʽ����if true? b:a;
		���minʱ����if b<a? b:a;
		��maxʱ��  ��if a<b? b:a;
	*/

	// min
	template <class Tp>
	inline const Tp& min(const Tp& a, const Tp& b) {
		return b < a ? b : a;
	}

	//�����ض��ıȽϺ���
	//if true return b, else return a
	template<class Tp, class Compare>
	inline const Tp& min(const Tp& a, const Tp& b, Compare comp) {
		return comp(b, a) ? b : a;
	}


	//max
	template <class Tp>
	inline const Tp& max(const Tp& a, const Tp& b) {
		return a < b ? b : a;
	}

	//�����ض��ıȽϺ���
	//if true return b, else return a
	template<class Tp, class Compare>
	inline const Tp& max(const Tp& a, const Tp& b, Compare comp) {
		return comp(a, b) ? b : a;
	}


	//-----------------------------------------------------------------------------
	//copy
	// �� [first, last)�����ڵ�Ԫ�ؿ����� [result, result + (last - first))��

	/*
		 All of these auxiliary functions serve two purposes.  (1) Replace
		 calls to copy with memmove whenever possible.  (Memmove, not memcpy,
		 because the input and output ranges are permitted to overlap.)
		 (2) If we're using random access iterators, then write the loop as
		 a for loop with an explicit count.

		 C �⺯�� void *memmove(void *str1, const void *str2, size_t n) �� 
		 str2 ���� n ���ַ��� str1���������ص��ڴ���ⷽ�棬memmove() �Ǳ� memcpy()
		 ����ȫ�ķ��������Ŀ�������Դ�������ص��Ļ���memmove() �ܹ���֤Դ���ڱ�
		 ����֮ǰ���ص�������ֽڿ�����Ŀ�������У����ƺ�Դ��������ݻᱻ���ġ�
		 ���Ŀ��������Դ����û���ص������ memcpy() ����������ͬ��
	*/

	// input_iterator_tag �汾
	template<class InputIter, class OutputIter>
	inline OutputIter _copy(InputIter first, InputIter last,
		OutputIter result, input_iterator_tag) {

		for (; first != last; ++result, ++first) {
			*result = *first;
		}
		return result;

	}

	//random_access_iterator_tag
	template<class RandomIter, class OutputIter>
	inline OutputIter _copy(RandomIter first, RandomIter last,
		OutputIter result, random_access_iterator_tag) {

		for (auto n = last - first; n > 0; --n, ++first, ++result)
		{
			*result = *first;
		}
		return result;
	}


	template <class Tp>
	inline Tp*
		_copy_trivial(const Tp* first, const Tp* last, Tp* result) {
		memmove(result, first, sizeof(Tp) * (last - first));
		return result + (last - first);
	}

	
	
	template <class InputIter, class OutputIter, class BoolType>
	struct _copy_dispatch {
		static OutputIter copy(InputIter first, InputIter last,
			OutputIter result) {
			//typedef typename iterator_traits<InputIter>::iterator_category Category;
			return _copy(first, last, result, iterator_category(first));
		}
	};

	/*
		��ָ��������ȫ����ֱ�ӵ���copy_trivial
	*/
	template<class Tp>
	struct _copy_dispatch<Tp*, Tp*, true_type> {
		static Tp* copy(const Tp* first, const Tp* last, Tp* result) {
			return _copy_trivial(first, last, result);
		}
	};

	template<class Tp>
	struct _copy_dispatch<const Tp*, Tp*, true_type> {
		static Tp* copy(const Tp* first, const Tp* last, Tp* result) {
			return _copy_trivial(first, last, result);
		}
	};


	//Ψһ����ӿ�
	template <class InputIter, class OutputIter>
	inline OutputIter copy(InputIter first, InputIter last,
		OutputIter result) {

		typedef typename iterator_traits<InputIter>::value_type Tp;
		typedef typename type_traits<Tp>::has_trivial_assignment_operator Trivial;

		return _copy_dispatch<InputIter, OutputIter, Trivial>
			::copy(first, last, result);
	}


	//-----------------------------------------------------------------------------
	//copy_backward
	// �� [first, last)�����ڵ�Ԫ�ؿ����� [result - (last - first), result)��

	//bidirectional_iterator_tag�汾
	template<class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2 _copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
		BidirectionalIter2 result, bidirectional_iterator_tag) {
		while (first != last) {
			*--result = *--last;
		}
		return result;
	}

	//random_access_iterator_tag
	template<class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2 _copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
		BidirectionalIter2 result, random_access_iterator_tag) {
		//std::cout << "random\n";
		for (auto n = last - first; n > 0; --n) {
			*--result = *--last;
		}
		return result;
	}
	

	template<class BidirectionalIter1, class BidirectionalIter2, class BoolType>
	struct _copy_backward_dispatch {
		static BidirectionalIter2 copy(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result) {
			//typedef typename iterator_traits<InputIter>::iterator_category Category;
			return _copy_backward(first, last, result, iterator_category(first));
		}
	};


	template <class Tp>
	struct _copy_backward_dispatch<Tp*, Tp*, true_type>
	{
		static Tp* copy(const Tp* first, const Tp* last, Tp* result) {
			//std::cout << "memmove\n";
			const ptrdiff_t Num = last - first;
			memmove(result - Num, first, sizeof(Tp) * Num);
			return result - Num;
		}
	};
	
	
	template <class Tp>
	struct _copy_backward_dispatch<const Tp*, Tp*, true_type>
	{
		static Tp* copy(const Tp* first, const  Tp* last, Tp* result) {
			return  _copy_backward_dispatch<Tp*, Tp*, true_type>
				::copy(first, last, result);
		}
	};

	//Ψһ����ӿ�
	template <class BidirectionalIter1, class BidirectionalIter2>
	inline BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
		BidirectionalIter2 result) {

		typedef typename iterator_traits<BidirectionalIter1>::value_type Tp;
		typedef typename type_traits<Tp>::has_trivial_assignment_operator Trivial;

		return _copy_backward_dispatch<BidirectionalIter1, BidirectionalIter2, Trivial>
			::copy(first, last, result);
	}


	//-------------------------------------------------------------------------------------
	//move



}

#endif // !_ALGOBASE_H_
