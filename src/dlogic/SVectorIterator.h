#ifndef DLOGIC_SVECTORITERATOR_H
#define DLOGIC_SVECTORITERATOR_H

#include "SVector.h"

namespace dlogic {

class SVectorIterator {
	SVector m_svec;

public:

	SVectorIterator(size_t width) noexcept : m_svec(width, level_first()) {}

	inline bool next() noexcept {
		size_t bit = 0;
		while(bit < m_svec.width() && level_next(m_svec[bit])){
			bit++;
		}
		return bit < m_svec.width();
	}

	inline SVector lvector() const noexcept {
		SVector result(m_svec);
		result.reverse();
		return result;
	}

};

}; // namespace dlogic

#endif //DLOGIC_SVECTORITERATOR_H
