#ifndef DLOGIC_TTTCLI_H
#define DLOGIC_TTTCLI_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <getopt.h>
#include <vector>
#include <cstring>

struct TttCli {

	enum class Form {
		TABLE,
		FDNF,
		DNF,
		UNKNOWN
	};

	Form result_form = Form::UNKNOWN;
	std::string input = "";
	std::string output = "";
	uint16_t width = 0;
	bool verbose = false;
	bool help = false;
	bool dry_run = false;

	bool parse_args(int argc, char** argv) noexcept {
		static const char* short_options =
			"f:" // result form
			"i:" // input file
			"o:" // output file
			"w:"  // vector width
			"r"  // rainbow
			"v"  // verbose
			"h"  // help
		;

		int opt;
		bool result = true;
		while((opt = getopt(argc, argv, short_options)) != EOF) {
			switch(opt) {
				case 'f':
					result_form = parse_form(optarg);
					if(result_form == Form::UNKNOWN) {
						fprintf(stderr, "Unknown result form '%s'.\n", optarg);
						result = false;
					}
					break;
				case 'i':
					input = optarg;
					break;
				case 'o':
					output = optarg;
					break;
				case 'v':
					verbose = true;
					break;
				case 'w': {
					const auto ret = parse_u16(optarg, width, 10);
					if(not ret) {
						fprintf(stderr, "Cannot parse '%s' as a uint16 value.\n", optarg);
						result = false;
					}
				}
					break;
				case 'h':
					help = true;
					dry_run = true;
					break;

				default:
					result = false;
					break;
			}
		}
		return result && validate();
	}


	static void print_usage(FILE* out, const char* bin) noexcept {
		TttCli def;
		fprintf(out, "Truth table translator | %s\n", "0.0.0");
		fprintf(out, "usage %s -f[ioh] [<OPTIONS>]\n", bin);
		fprintf(out, "\nOptions:\n");
		fprintf(out, "\t-f  Enum {TABLE|FDNF|DNF} The result form. \n");
		fprintf(out, "\t-i  File name to read from.\n");
		fprintf(out, "\t-o  File name to write to.\n");
		fprintf(out, "\t-w  Integer [0:65535]. Vector width. (%u)\n", def.width);
		fprintf(out, "\t-h  Print this screen and exit.\n");
	}

private:

	static Form parse_form(std::string action) noexcept {
		std::transform(
			action.begin(), action.end(), action.begin(), [](char ch) { return std::tolower(ch); });

		if(action == "table") {
			return Form::TABLE;
		} else if(action == "fdnf") {
			return Form::FDNF;
		} else if(action == "dnf") {
			return Form::DNF;
		}
		return Form::UNKNOWN;
	}

	bool validate() const noexcept {
		bool result = true;
		if(not dry_run) {
//			result &= result_form != Form::UNKNOWN;
		}
		return result;
	}

	bool parse_u16(const char* arg, uint16_t& value, int base) {
		char* endptr;
		if(*arg == '-') {
			return 0;
		}
		const auto raw = strtoull(arg, &endptr, base);
		if(size_t(endptr - arg) == strlen(arg) && raw <= UINT16_MAX){
			value = raw;
			return true;
		}
		return false;
	}

};


#endif //DLOGIC_TTTCLI_H
