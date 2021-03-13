#ifndef DLOGIC_TRUTHTABLE_H
#define DLOGIC_TRUTHTABLE_H

#include "SVector.h"
#include "../utils/Printer.h"

#include <cmath>
#include <memory>
#include <vector>
#include <list>

class TruthTable {
	const size_t m_width_input;
	const size_t m_width_output;
	struct Record {
		const size_t index;
		const LVector input;
		const LVector output;
	};
	using List_t = std::list<Record>;
	using ConstIterator_t = List_t::const_iterator;

	List_t m_list;

public:

	TruthTable(size_t width_input, size_t width_output) noexcept
		: m_width_input(width_input)
		, m_width_output(width_output)
		, m_list() {
		assert(width_input);
		assert(width_output);
	}

	inline size_t width_input() const noexcept {
		return m_width_input;
	}

	inline size_t width_output() const noexcept {
		return m_width_output;
	}

	void push_record(const LVector& input, const LVector& output) noexcept {
		assert(input.width() == m_width_input);
		assert(output.width() == m_width_output);
		m_list.push_back({m_list.size(), input, output});
//		if(output.any(LSignal::X)) {
//			fprintf(stderr, "Skip useless record input='");
//			Printer::lvector(stderr, input);
//			fprintf(stderr, "' output='");
//			Printer::lvector(stderr, output);
//			fprintf(stderr, "'\n");
//			return false;
//		}
//		for(const auto pair : m_table) {
//			if(intersect(pair.first, input) && pair.second != output){
//				fprintf(stderr, "Record conflict ");
//				Printer::truth_table_pair(stderr, pair.first, pair.second);
//				fprintf(stderr, " and ");
//				Printer::truth_table_pair(stderr, input, output);
//				fprintf(stderr, "\n");
//				return false;
//			}
//		}
	}

//	bool validate(FILE* out) noexcept {
//
//	}

	LVector read(const LVector& input) const noexcept {
		assert(input.width() == m_width_input);
//		return prev;
	}

	void dump(FILE* out) const noexcept {
		fprintf(out, "==== truth-table(%zu) ====\n", m_list.size());
		for(const auto item : m_list) {

		}
	}

	// std access methods

	inline size_t size() const noexcept {
		return m_list.size();
	}

	inline ConstIterator_t begin() const noexcept {
		return m_list.cbegin();
	}

	inline ConstIterator_t end() const noexcept {
		return m_list.cend();
	}

private:

//	void truth_table_pair(FILE* out, const LVector& input, const LVector& output) noexcept {
//		fprintf(out, "{");
//		lvector(out, input);
//		fprintf(out, "} -> {");
//		lvector(out, output);
//		fprintf(out, "}");
//	}

	bool intersect(const LVector& lvec) const noexcept {
		for(const auto item : m_list) {
			if(intersect(item.input, lvec)) {
				return true;
			}
		}
		return false;
	}

	static bool intersect(const LVector& p0, const LVector& p1) noexcept {
		for(size_t i = 0; i < p0.width(); ++i) {
			if(p0[i] == LSignal::X || p1[i] == LSignal::X) {
				continue;
			}
			if(p0[i] == p1[i]) {
				continue;
			}
			return false;
		}
		return true;
	}

};


#endif //DLOGIC_TRUTHTABLE_H
