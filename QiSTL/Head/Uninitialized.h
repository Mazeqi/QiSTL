#pragma once
#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "Algobase.h"
#include "Type_traits.h"
#include "Construct.h"
#include "Iterator.h"

namespace QTL {
	

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



}
#endif // !_UNINITIALIZED_H_

