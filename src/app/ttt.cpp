#include "../dlogic/SVectorIterator.h"
#include "TttCli.h"

#include <tio/StreamTokenizer.h>
#include <tio/stream/FileInputStream.h>

#include <cstdio>

using namespace dlogic;

int to_table(FILE* input, FILE* output, const TttCli& cli) noexcept {

//	enum Token : tio::StreamTokenizer::Token_t {
//		UNKNOWN,
//		SEP,
//		EOL,
//		EOS
//	};
//
//	tio::FileInputStream fis(input);
//	tio::StreamTokenizer stk(&fis, UNKNOWN, EOS);
//	stk.map_chars(Token::SEP, " ().,;:\t");
//	stk.map_chars(Token::EOL, " \n");
//
//	bool running = true;
//	while (running) {
//		switch(stk.next()) {
//			case Token::UNKNOWN:
//				printf("[%s]\n", stk.cstring());
//				break;
//
//			case Token::SEP:
//				printf("~");
//				break;
//
//			case Token::EOL:
////				printf("");
//				break;
//
//			case Token::EOS:
//				printf(">END_OF_STREAM:\n");
//				running = false;
//				break;
//		}
//	}

	printf("to_table()\n");
	return EXIT_SUCCESS;
}

int to_fdnf(const TttCli& cli) noexcept {
	printf("to_fdnf()\n");
	return EXIT_SUCCESS;
}

int to_dnf(const TttCli& cli) noexcept {
	printf("to_dnf(%u)\n", cli.width);
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	TttCli cli;
	if(not cli.parse_args(argc, argv)) {
		TttCli::print_usage(stderr, argv[0]);
		return EXIT_FAILURE;
	}
	if(cli.help) {
		TttCli::print_usage(stdout, argv[0]);
		return EXIT_SUCCESS;
	}

	FILE* input = stdin;
	if(not cli.input.empty()) {
		input = fopen(cli.input.c_str(), "r");
		if(input == nullptr) {
			fprintf(stderr, "Cannot open input file '%s'\n", cli.input.c_str());
			return EXIT_FAILURE;
		}
	}

	FILE* output = stdout;
	if(not cli.output.empty()) {
		input = fopen(cli.output.c_str(), "w");
		if(input == nullptr) {
			fprintf(stderr, "Cannot open output file '%s'\n", cli.output.c_str());
			return EXIT_FAILURE;
		}
	}


	int result = to_table(input, output, cli);;
//
//	switch(cli.result_form) {
//		case TttCli::Form::TABLE:
//			result = to_table(input, output, cli);
//			break;
//
//		case TttCli::Form::FDNF:
//			result = to_fdnf(cli);
//			break;
//
//		case TttCli::Form::DNF:
//			result = to_dnf(cli);
//			break;
//
//		default:
//			assert(false);
//	}

	fclose(input);
	fclose(output);

	return result;
}

