#pragma once
#ifndef _ALGOBASE_H_
#define _ALGOBASE_H_

#include"Iterator.h"
#include"Type_traits.h"

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
		格式都是if true? b:a;
		因此min时，是if b<a? b:a;
		而max时，  是if a<b? b:a;
	*/

	// min
	template <class Tp>
	inline const Tp& min(const Tp& a, const Tp& b) {
		return b < a ? b : a;
	}

	//传入特定的比较函数
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

	//传入特定的比较函数
	//if true return b, else return a
	template<class Tp, class Compare>
	inline const Tp& max(const Tp& a, const Tp& b, Compare comp) {
		return comp(a, b) ? b : a;
	}


	//-----------------------------------------------------------------------------
	//copy
	// 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内

	/*
		 All of these auxiliary functions serve two purposes.  (1) Replace
		 calls to copy with memmove whenever possible.  (Memmove, not memcpy,
		 because the input and output ranges are permitted to overlap.)
		 (2) If we're using random access iterators, then write the loop as
		 a for loop with an explicit count.

		 C 库函数 void *memmove(void *str1, const void *str2, size_t n) 从 
		 str2 复制 n 个字符到 str1，但是在重叠内存块这方面，memmove() 是比 memcpy()
		 更安全的方法。如果目标区域和源区域有重叠的话，memmove() 能够保证源串在被
		 覆盖之前将重叠区域的字节拷贝到目标区域中，复制后源区域的内容会被更改。
		 如果目标区域与源区域没有重叠，则和 memcpy() 函数功能相同。
	*/

	// input_iterator_tag 版本
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

	template <class InputIter, class OutputIter>
	inline OutputIter _copy_aux2(InputIter first, InputIter last,
		OutputIter result, false_type) {
		return _copy(first, last, result, iterator_category(first));
	}

	template <class InputIter, class OutputIter>
	inline OutputIter _copy_aux2(InputIter first, InputIter last,
		OutputIter result, true_type) {
		return _copy(first, last, result, iterator_category(first));
	}

	template <class Tp>
	inline Tp* _copy_aux2(Tp *first, Tp *last,
		Tp* result, true_type) {
		return _copy_trivial(first, last, result);
	}

	template <class Tp>
	inline Tp* _copy_aux2(const Tp* first, const Tp* last,
		Tp* result, true_type) {
		return _copy_trivial(first, last, result);
	}

	template<class InputIter, class OutputIter, class Tp>
	inline OutputIter _copy_aux(InputIter first, InputIter last,
		OutputIter result, Tp*) {
		typedef typename type_traits<Tp>::has_trivial_assignment_operator Trivial;
		return _copy_aux2(first, last, result, Trivial());
	}


	template<class InputIter, class OutputIter>
	inline OutputIter copy(InputIter first, InputIter last,
		OutputIter result) {
		return _copy_aux(first, last, result, value_type(first));
	}

	template <class InputIter, class OutputIter, class BoolType>
	struct _copy_dispatch {
		static OutputIter copy(InputIter first, InputIter last,
			OutputIter result) {
			//typedef typename iterator_traits<InputIter>::iterator_category Category;
			return _copy(first, last, result, iterator_category(first));
		}
	};

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


	template <class InputIter, class OutputIter>
	inline OutputIter copy(InputIter first, InputIter last,
		OutputIter result) {

		typedef typename iterator_traits<InputIter>::value_type Tp;
		typedef typename type_traits<Tp>::has_trivial_assignment_operator Trivial;

		return _copy_dispatch<InputIter, OutputIter, Trivial>
			::copy(first, last, result);
	}


	template <class InputIter, class OutputIter>
	inline OutputIter copy(InputIter first, InputIter last,
		OutputIter result) {
		return _copy(first, last, result, value_type(first));
	}

}

#endif // !_ALGOBASE_H_
