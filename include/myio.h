#ifndef __MYIO_H
#define __MYIO_H

#include <stdarg.h>
#include "FreeRTOSConfig.h"

void _print(char *str);
void uprintf(const char *format, ...);

#endif