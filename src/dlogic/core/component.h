#pragma once

#include <string>
#include <algorithm>

namespace dlogic {

using ComponentBase_t = unsigned char;

enum ComponentType : ComponentBase_t {
	WIRE,
	OR,
	NOR,
	AND,
	NAND,
	XOR,
	NXOR,
	__COMPOMENT
};

const char* component_name(ComponentType comp) noexcept {
	static const char* map[] = {
		"wire", "or", "nor", "and", "nand", "xor", "nxor", "UNKNOWN", nullptr
	};
	return map[comp > __COMPOMENT ? __COMPOMENT : comp];
}

ComponentType component_parse(std::string lfunc) noexcept {
	std::transform(
		lfunc.begin(), lfunc.end(), lfunc.begin(), [](char ch) { return std::tolower(ch); });

	for(ComponentBase_t i = 0; i < __COMPOMENT; ++i) {
		const auto func = ComponentType(i);
		if(lfunc == component_name(func)) {
			return func;
		}
	}
	return ComponentType::__COMPOMENT;
}

}; // namespace dlogic
