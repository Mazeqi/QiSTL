#pragma once
#ifndef _EXCEPTDEF_H_
#define _EXCEPTDEF_H_

#include<cassert>
#include<stdexcept>

namespace QTL {

	#define QTLDEBUG(expt)	assert(expt)
	
}

#endif // !_EXCEPTDEF_H_
