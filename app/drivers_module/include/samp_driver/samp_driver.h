#ifndef SAMP_DRIVER_H
#define SAMP_DRIVER_H
#include <zephyr/kernel.h>


#ifdef __cplusplus                          
extern "C" {
#endif

void change_param(const struct device *dev, int value);
void read_param(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif

/*Here, our application is C++ but the driver is C. C and C++ store function names differently
For Example,
C keeps the name as-is : change_param
C++ mangles the name to encode parameter type, support overloading and becomes _Z12change_paramPK6devicei

Our driver compiled as C so object file contains change_param but main compiles as CPP so linker asks for mangled name
They do not match.

extern C tells CPP compiler to not mangle the name and do the plain C way so that names match
--------------------------------------------------------------------------------------------------
#ifdef __cplusplus                          
extern "C" {
#endif
means "if a C++ compiler is reading this, add extern "C" {. If a C compiler is reading it, skip that line"
----------------------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
closes the brace, again only for C++.
------------------------------------------------
*/