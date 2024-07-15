//includes the input class specific for each platform

#ifndef Input_h
#define Input_h

//keycodes
#include "Keycodes.h"

#ifdef Window_Build

#include <Platform\Window\WindowInput.h>

#elif Mac_Build

#include <stdio.h>
printf("Current Platform is not supported by the Smok engine.\n");

#elif Linux_Build

#include <stdio.h>
printf("Current Platform is not supported by the Smok engine.\n");

#elif Android_Build

#include <stdio.h>
printf("Current Platform is not supported by the Smok engine.\n");

#elif IOS_Build

#include <stdio.h>
printf("Current Platform is not supported by the Smok engine.\n");

#elif VR_Build //VR Build maybe?

#include <stdio.h>
printf("Current Platform is not supported by the Smok engine.\n");

#endif
#endif