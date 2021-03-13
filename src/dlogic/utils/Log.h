#pragma once

#include <cstdarg>
#include <cstdio>

class Log {
public:
	static void warning(const char* frm, ...) noexcept {
		va_list va_list;
		va_start (va_list, frm);
		printf("[W]: ");
		vfprintf(stdout, frm, va_list);
		printf("\n");
		va_end (va_list);
	}
};

