#pragma once

#include "../core/level.h"
#include "../core/LFunction.h"

#include <string>
#include <vector>

namespace dlogic {

class Primitive {
protected:
	const std::string m_name;
	Level m_level;

	virtual Level update_level() noexcept = 0;

public:

	Primitive(const Primitive&) = delete;
	Primitive(Primitive&&) = delete;

	Primitive& operator=(const Primitive&) = delete;
	Primitive& operator=(Primitive&&) = delete;

	Primitive(const std::string& name) noexcept
		: m_name(name)
		, m_level(Level::U) {}

	virtual ~Primitive() noexcept = default;

	inline const std::string& name() const noexcept {
		return m_name;
	}

	inline Level level() const noexcept {
		return m_level;
	}

	bool update() noexcept {
		const auto new_level = update_level();
		const bool is_updated = new_level != m_level;
		m_level = new_level;
		return is_updated;
	}

};

class ConstPrimitive : public Primitive {
protected:
	Level update_level() noexcept override {
		return m_level;
	}

public:

	ConstPrimitive(const std::string& name, const Level level) noexcept
		: Primitive(name) {
		m_level = level;
	}

};

class SingleArgumentPrimitive : public Primitive {
protected:
	const LFunction::TypeSingleArg m_lfunc;
	const Primitive* const m_input;

	Level update_level() noexcept override {
		return m_lfunc(m_input->level());
	}

public:

	SingleArgumentPrimitive(
		const std::string& name, const LFunction::TypeSingleArg lfunc, const Primitive* input
	                       ) noexcept
		: Primitive(name)
		, m_lfunc(lfunc)
		, m_input(input) {}

};

class DoubleArgumentPrimitive : public Primitive {
protected:
	const LFunction::TypeDoubleArg m_lfunc;
	const Primitive* const m_input_a;
	const Primitive* const m_input_b;

	Level update_level() noexcept override {
		return m_lfunc(m_input_a->level(), m_input_b->level());
	}

public:
	DoubleArgumentPrimitive(
		const std::string& name
		, const LFunction::TypeDoubleArg lfunc
		, const Primitive* input_a
		, const Primitive* input_b
	                       ) noexcept
		: Primitive(name)
		, m_lfunc(lfunc)
		, m_input_a(input_a)
		, m_input_b(input_b) {}

};

class Wire : public Primitive {
protected:
	std::vector<const Primitive*> m_input;

	Level update_level() noexcept override {
		Level l = Level::Z;
		for(auto in : m_input) {
			l = LFunction::dalf_wire(l, in->level());
		}
		return l;
	}

public:
	Wire(const std::string& name) noexcept
		: Primitive(name) {}

	inline void connect_input(const Primitive* comp) noexcept {
		m_input.push_back(comp);
	}
};

}; // namespace dlogic
