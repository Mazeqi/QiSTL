
#include"AlgobaseTest.h"

namespace QTL {
	namespace AlgobaseTest {
		void testMinMax() {
			assert(QTL::min(1, 2) == 1);
			assert(QTL::min(2, 1) == 1);
			assert(QTL::min('a', 'z') == 'a');
			assert(QTL::min(3.14, 2.72) == 2.72);

			assert(QTL::max(1, 2) == 2);
			assert(QTL::max(2, 1) == 2);
			assert(QTL::max('a', 'z') == 'z');
			assert(QTL::max(3.14, 2.73) == 3.14);
		}
	}
}