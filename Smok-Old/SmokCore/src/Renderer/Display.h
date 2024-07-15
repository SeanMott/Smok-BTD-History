//base Display class

#ifndef Display_h
#define Display_h

//#include <smpch.h>

#ifdef Window_Build

#include <Platform\Window\WindowDisplay.h>
#define DisplayI WindowDisplay::Instance()

#elif Mac_Build

//printf("Mac is currently not supported, check GitHub for updates or help with development.\n");
//#include <Platform\Mac\MacDisplay.h>
//#define DisplayI MacDisplay::Instance()

#elif Linux_Build

//printf("Linux is currently not supported, check GitHub for updates or help with development.\n");
//#include <Platform\Linux\LinuxDisplay.h>
//#define DisplayI LinuxDisplay::Instance()

#elif Android_Build

//printf("Android is currently not supported, check GitHub for updates or help with development.\n");
//#include <Platform\Android\AndroidDisplay.h>
//#define DisplayI AndroidDisplay::Instance()

#elif IOS_Build

//printf("IOS is currently not supported, check GitHub for updates or help with development.\n");
//#include <Platform\Android\AndroidDisplay.h>
//#define DisplayI AndroidDisplay::Instance()

#endif

#endif