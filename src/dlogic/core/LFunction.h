#pragma once

#include <cassert>

namespace dlogic {

class LFunction {
public:

	using TypeSingleArg = Level (*)(Level);
	using TypeDoubleArg = Level (*)(Level, Level);


	// -------------------------------
	// Single argument logic functions
	// -------------------------------
	static Level salf_not(Level left) noexcept {
		assert(left < __LEVEL);
		static const Level tt[__LEVEL] =
			//U LOW   X  HIGH Z
			{U, HIGH, X, LOW, X};
		return tt[left];
	}

	static Level salf_buf(Level left) noexcept {
		assert(left < __LEVEL);
		static const Level tt[__LEVEL] =
			//U LOW  X  HIGH  Z
			{U, LOW, X, HIGH, X};
		return tt[left];
	}


	// -------------------------------
	// Double argument logic functions
	// -------------------------------
	static Level dalf_wire(Level left, Level right) noexcept {
		assert(left < __LEVEL);
		assert(right < __LEVEL);
		static const Level tt[__LEVEL][__LEVEL] = {
			//U LOW      X        HIGH     Z
			{U, U,       U,       U,       U},   // U
			{U, __LEVEL, __LEVEL, __LEVEL, LOW}, // LOW
			{U, __LEVEL, __LEVEL, __LEVEL, X},   // X
			{U, __LEVEL, __LEVEL, __LEVEL, HIGH},// HIGH
			{U, LOW,     X,       HIGH,    Z},   // Z
		};
		return tt[left][right];
	}

	static Level dalf_or(Level left, Level right) noexcept {
		assert(left < __LEVEL);
		assert(right < __LEVEL);
		static const Level tt[__LEVEL][__LEVEL] = {
			//U LOW   X     HIGH  Z
			{U, U,    U,    U,    U}, // U
			{U, LOW,  X,    HIGH, X}, // LOW
			{U, X,    X,    HIGH, X}, // X
			{U, HIGH, HIGH, HIGH, X}, // HIGH
			{U, X,    X,    X,    X}, // Z
		};
		return tt[left][right];
	}

	static Level dalf_nor(Level left, Level right) noexcept {
		return salf_not(dalf_or(left, right));
	}

	static Level dalf_and(Level left, Level right) noexcept {
		assert(left < __LEVEL);
		assert(right < __LEVEL);
		static const Level tt[__LEVEL][__LEVEL] = {
			//U LOW  X     HIGH  Z
			{U, U,   U,    U,    U}, // U
			{U, LOW, LOW,  LOW,  X}, // LOW
			{U, LOW, X,    X,    X}, // X
			{U, LOW, X,    HIGH, X}, // HIGH
			{U, X,   X,    X,    X}, // Z
		};
		return tt[left][right];
	}

	static Level dalf_nand(Level left, Level right) noexcept {
		return salf_not(dalf_and(left, right));
	}

	static Level dalf_xor(Level left, Level right) noexcept {
		assert(left < __LEVEL);
		assert(right < __LEVEL);
		static const Level tt[__LEVEL][__LEVEL] = {
			//U LOW   X  HIGH  Z
			{U, U,    U, U,    U}, // U
			{U, LOW,  X, HIGH, X}, // LOW
			{U, X,    X, X,    X}, // X
			{U, HIGH, X, LOW,  X}, // HIGH
			{U, X,    X, X,    X}, // Z
		};
		return tt[left][right];
	}

	static Level dalf_nxor(Level left, Level right) noexcept {
		return salf_not(dalf_xor(left, right));
	}

};

}; // namespace dlogic
