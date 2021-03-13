#pragma once

#include "Primitive.h"
#include "../dlogic.h"
#include "../utils/Log.h"

#include <string>
#include <vector>
#include <set>

namespace dlogic {

class Circuit {

	template<typename T>
	struct NamedRecordComparator {
		using is_transparent = void;

		bool operator()(const T* x, const T* y) const noexcept {
			return x->name() < y->name();
		}

		bool operator()(const std::string& x, const T* y) const noexcept {
			return x < y->name();
		}

		bool operator()(const T* x, const std::string& y) const noexcept {
			return x->name() < y;
		}
	};

	using WireSet_t = std::set<Wire*, NamedRecordComparator<Wire> >;
	using PrimitiveSet_t = std::set<Primitive*, NamedRecordComparator<Primitive> >;

	WireSet_t m_wires;
	PrimitiveSet_t m_components;
	unsigned long m_next_index;

public:
	Circuit(const Circuit&) = delete;
	Circuit(Circuit&&) = delete;

	Circuit& operator=(const Circuit&) = delete;
	Circuit& operator=(Circuit&&) = delete;

	Circuit() noexcept
		: m_next_index(0) {}

	virtual ~Circuit() noexcept {
		clear_set(m_wires);
		clear_set(m_components);
	}

	// wires
	void wire(const std::string& name) noexcept {
		declare_wire(name, true);
	}

	// constant primitives
	inline void declare_supply1(const std::string& output) noexcept {
		declare_const_primitive("supply1", Level::HIGH, output);
	}

	inline void declare_supply0(const std::string& output) noexcept {
		declare_const_primitive("supply0", Level::LOW, output);
	}

	// single argument primitives
	inline void
	declare_buf(const std::string& output, const std::string& input) noexcept {
		declare_sap("buf", LFunction::salf_buf, output, input);
	}

	inline void
	declare_not(const std::string& output, const std::string& input) noexcept {
		declare_sap("not", LFunction::salf_not, output, input);
	}

	// double argument primitives
	inline void
	declare_or(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("or", LFunction::dalf_or, output, input_a, input_b);
	}

	inline void
	declare_nor(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("nor", LFunction::dalf_nor, output, input_a, input_b);
	}

	inline void
	declare_and(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("and", LFunction::dalf_and, output, input_a, input_b);
	}

	inline void
	declare_nand(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("nand", LFunction::dalf_nand, output, input_a, input_b);
	}

	inline void
	declare_xor(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("xor", LFunction::dalf_xor, output, input_a, input_b);
	}

	inline void
	declare_nxor(const std::string& output, const std::string& input_a, const std::string& input_b) noexcept {
		declare_dap("nxor", LFunction::dalf_nxor, output, input_a, input_b);
	}


	bool update() noexcept {
		bool wires = update_set(m_wires);
		bool components = update_set(m_components);
		return wires || components;
	}

	void dump(FILE* out) const noexcept {
		fprintf(out, "---- wires");
		dump_set(out, m_wires);
		fprintf(out, "---- components");
		dump_set(out, m_components);
	}

private:

	template<typename T>
	inline static bool update_set(T& set) noexcept {
		bool result = false;
		for(auto item : set) {
			result |= item->update();
		}
		return result;
	}

	template<typename T>
	inline static void dump_set(FILE* out, T& set) noexcept {
		printf(" (%zu items) ----\n", set.size());
		for(auto item : set) {
			fprintf(out, "%s", item->name().c_str());
			fprintf(out, " : %c\n", level_name(item->level()));
		}
	}

	template<typename T>
	inline static void clear_set(T& set) noexcept {
		for(auto item : set) {
			delete item;
		}
		set.clear();
	}

	inline std::string get_next_name(const std::string& prefix) noexcept {
		return prefix + "#" + std::to_string(m_next_index++);
	}

	Wire* declare_wire(const std::string& name, bool is_explicit) noexcept {
		auto it = m_wires.find(name);
		Wire* wire = nullptr;
		if(it == m_wires.end()) {
			wire = new Wire(name);
			m_wires.insert(wire);
			if(not is_explicit) {
				Log::warning("Implicit wire '%s' declaration.", name.c_str());
			}
		} else {
			wire = *it;
			if(is_explicit) {
				Log::warning("Wire '%s' has already been declared.", name.c_str());
			}
		}
		return wire;
	}

	void declare_const_primitive(
		const std::string& type
		, const Level level
		, const std::string& output
	                ) noexcept {
		auto wire_output = declare_wire(output, false);
		auto cap = new ConstPrimitive(get_next_name(type), level);
		m_components.insert(cap);
		wire_output->connect_input(cap);
	}

	void declare_sap(
		const std::string& type
		, const LFunction::TypeSingleArg lfunc
		, const std::string& output
		, const std::string& input
	                ) noexcept {
		auto wire_output = declare_wire(output, false);
		auto wire_input = declare_wire(input, false);
		auto sap = new SingleArgumentPrimitive(get_next_name(type), lfunc, wire_input);
		m_components.insert(sap);
		wire_output->connect_input(sap);
	}

	void declare_dap(
		const std::string& type
		, const LFunction::TypeDoubleArg lfunc
		, const std::string& output
		, const std::string& input_a
		, const std::string& input_b
	                ) noexcept {
		auto wire_output = declare_wire(output, false);
		auto wire_input_a = declare_wire(input_a, false);
		auto wire_input_b = declare_wire(input_b, false);
		auto dap = new DoubleArgumentPrimitive(get_next_name(type), lfunc, wire_input_a, wire_input_b);
		m_components.insert(dap);
		wire_output->connect_input(dap);
	}

};

}; // namespace dlogic
