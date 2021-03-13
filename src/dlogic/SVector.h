#ifndef DLOGIC_SVECTOR_H
#define DLOGIC_SVECTOR_H

#include "dlogic.h"

#include <cassert>
#include <memory>
#include <algorithm>

namespace dlogic {

class SVector {
	const size_t m_width;
	std::unique_ptr<Level[]> m_vec;

public:

	SVector(const std::initializer_list<Level>& list) noexcept
		: m_width(list.size())
		, m_vec(new Level[list.size()]) {
		std::copy(list.begin(), list.end(), m_vec.get());
	}

	SVector(const size_t width, Level init) noexcept
		: m_width(width)
		, m_vec(new Level[width]) {
		std::fill(m_vec.get(), m_vec.get() + m_width, init);
	}

	SVector(const SVector& rv) noexcept: m_width(rv.m_width), m_vec(new Level[rv.m_width]) {
		std::copy(rv.m_vec.get(), rv.m_vec.get() + m_width, m_vec.get());
	}

	SVector& operator=(const SVector& rv) noexcept {
		assert(m_width == rv.m_width);
		std::copy(rv.m_vec.get(), rv.m_vec.get() + m_width, m_vec.get());
		return *this;
	}

	bool operator==(const SVector& rv) const noexcept {
		assert(m_width == rv.m_width);
		return std::equal(m_vec.get(), m_vec.get() + m_width, rv.m_vec.get());
	}

	inline bool operator!=(const SVector& rv) const noexcept {
		return not operator==(rv);
	}

	void reverse() noexcept {
		std::reverse(m_vec.get(), m_vec.get() + m_width);
	}

	// std access methods

	inline size_t width() const noexcept {
		return m_width;
	}

	inline Level& operator[](size_t index) noexcept {
		assert(index < m_width);
		return m_vec[index];
	}

	inline const Level& operator[](size_t index) const noexcept {
		assert(index < m_width);
		return m_vec[index];
	}

	inline const Level* begin() const noexcept {
		return m_vec.get();
	}

	inline const Level* end() const noexcept {
		return m_vec.get() + m_width;
	}

	inline Level* begin() noexcept {
		return m_vec.get();
	}

	inline Level* end() noexcept {
		return m_vec.get() + m_width;
	}

	void dump(FILE* out) const noexcept {
		fprintf(out, "{");
		for(size_t i = 0; i < m_width; ++i) {
			fprintf(out, "%c", level_name(m_vec[i]));
		}
		fprintf(out, "}");
	}
};

}; // namespace dlogic

#endif //DLOGIC_SVECTOR_H
