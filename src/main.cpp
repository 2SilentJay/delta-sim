#include "dlogic/circuit/Circuit.h"

#include <cstdio>
#include <cstdint>
#include <cassert>

using namespace dlogic;

int main(int argc, char** argv) {

	Circuit circuit;

	circuit.wire("A");
	circuit.wire("B");
	circuit.wire("X");

	circuit.declare_supply0("A");
	circuit.declare_supply1("B");

	circuit.declare_nand("X", "A", "B");
	circuit.declare_nand("F", "X", "B");

	circuit.dump(stdout);
	unsigned cnt = 10;
	while(circuit.update() && cnt--) {
		circuit.dump(stdout);
	}
	circuit.dump(stdout);

	printf("<---- the end of main() ---->\n");
	return 0;
}
