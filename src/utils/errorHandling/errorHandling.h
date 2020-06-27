#pragma once
#ifndef UTILS_ERRORHANDLING_H
#define UTILS_ERRORHANDLING_H

#include <stdnoreturn.h>


noreturn void showErrnoAndHalt();
void printBacktrace();

#endif /* UTILS_ERRORHANDLING_H */
