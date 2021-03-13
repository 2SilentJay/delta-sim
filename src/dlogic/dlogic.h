#pragma once

#include "core/level.h"
#include "core/LFunction.h"
#include "core/component.h"

#include <cassert>
#include <string>
#include <algorithm>

namespace dlogic {

Level level_first() noexcept {
	return Level::LOW;
}

bool level_next(Level& sig) noexcept {
	assert(sig < __LEVEL);
	static const Level next[__LEVEL] =
		//LOW  X  HIGH  Z  RISE  FALL
		{X, HIGH, Z, LOW};
	static const bool carry[__LEVEL] =
		//LOW  X  HIGH  RISE  FALL
		{true, false, false, false};
	sig = next[sig];
	return carry[sig];
}

// Level function.
ComponentType lfunction_first() noexcept {
	return ComponentType::WIRE;
}

bool lfunction_next(ComponentType& lf) noexcept {
	assert(lf < __COMPOMENT);
	lf = ComponentType(lf + 1);
	return (lf < ComponentType::__COMPOMENT);
}

}; // namespace dlogic
