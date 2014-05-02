#ifndef __MYIO_H
#define __MYIO_H

#include <stdarg.h>
#include "FreeRTOSConfig.h"

//put string into default pipe defined in _print().
void uprintf(const char *format, ...);

#endif