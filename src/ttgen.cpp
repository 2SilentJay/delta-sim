#include "dlogic/SVectorIterator.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace dlogic;

Level lfunc_cascade(Level (* lfunc)(Level, Level), const SVector& lsv) noexcept {
	assert(lsv.width());
	if(lsv.width() < 2) {
		return lfunc(lsv[0], lsv[0]);
	}
	Level sig = lsv[0];
	for(size_t i = 1; i < lsv.width(); ++i) {
		sig = lfunc(sig, lsv[i]);
		if(sig >= __LEVEL) {
			break;
		}
	}
	return sig;
}

void ttgen(ComponentType lf, unsigned width) noexcept {
	SVectorIterator lvit(width);
	do {
		const auto svec = lvit.lvector();
		svec.dump(stdout);
		dlogic::Level out;
		switch(lf) {
			case ComponentType::WIRE:
				out = lfunc_cascade(LFunction::dalf_wire, svec);
				break;
			case ComponentType::OR:
				out = lfunc_cascade(LFunction::dalf_or, svec);
				break;
			case ComponentType::NOR:
				out = LFunction::salf_not(lfunc_cascade(LFunction::dalf_or, svec));
				break;
			case ComponentType::AND:
				out = lfunc_cascade(LFunction::dalf_and, svec);
				break;
			case ComponentType::NAND:
				out = LFunction::salf_not(lfunc_cascade(LFunction::dalf_and, svec));
				break;
			case ComponentType::XOR:
				out = lfunc_cascade(LFunction::dalf_xor, svec);
				break;
			case ComponentType::NXOR:
				out = LFunction::salf_not(lfunc_cascade(LFunction::dalf_xor, svec));
				break;
			default:
				assert(false);
				break;
		}
		printf(" %c\n", level_name(out));
	} while(lvit.next());
}

int main(int argc, char** argv) {
	if(argc < 3) {
		printf("usage: %s LFUNC arg-number\n", argv[0]);
		printf("LFUNC ::= ");
		ComponentType lf = lfunction_first();
		do {
			if(lf != lfunction_first()) {
				printf("|");
			}
			printf("%s", component_name(lf));
		} while(lfunction_next(lf));
		printf("\n");
		return EXIT_FAILURE;
	}
	ComponentType lf = component_parse(argv[1]);
	if(lf == ComponentType::__COMPOMENT) {
		printf("Unknown logic function '%s'.\n", argv[1]);
		return EXIT_FAILURE;
	}
	int args_nb = 0;
	try {
		args_nb = std::stoi(argv[2]);
	} catch (const std::invalid_argument& e) {
		printf("Cannot parse 'arg-number': '%s'.\n", argv[2]);
		return EXIT_FAILURE;
	}
	if(args_nb < 1) {
		printf("The number of arguments MUST BE positive.\n");
		return EXIT_FAILURE;
	}

	ttgen(lf, args_nb);
	return EXIT_SUCCESS;
}
