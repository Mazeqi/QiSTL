#pragma once
#ifndef _EXCEPTDEF_H_
#define _EXCEPTDEF_H_

#include<cassert>
#include<stdexcept>

namespace QTL {

	#define QTLDEBUG(expt)	assert(expt)

	#define THROW_LENGTH_ERROR_IF(expr, what) if ((expr)) throw std::length_error(what)

	#define THROW_OUT_OF_RANGE_IF(expr, what) if ((expr)) throw std::out_of_range(what)

	#define THROW_RUNTIME_ERROR_IF(expr, what) if ((expr)) throw std::runtime_error(what)

}

#endif // !_EXCEPTDEF_H_
