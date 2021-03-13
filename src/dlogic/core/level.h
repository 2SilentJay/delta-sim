#pragma once

namespace dlogic {

using LevelBase_t = unsigned char;

enum Level : LevelBase_t {
	U,      // Not initialized.
	LOW,    // Strong drive, low level.
	X,      // Strong drive, unknown level.
	HIGH,   // Strong drive, high level.
	Z,      // Tri-state.
	__LEVEL // Enum length.
};

char level_name(Level level) noexcept {
	static const char* map = "U0X1Z#";
	return map[level > __LEVEL ? __LEVEL : level];
}

Level level_parse(char ch) noexcept {
	for(LevelBase_t i = 0; i < __LEVEL; ++i) {
		const auto level = Level(i);
		if(ch == level_name(level)) {
			return level;
		}
	}
	return Level::__LEVEL;
}

}; // namespace dlogic
