#pragma once

#include "quantum.h"

#define LAYOUT( \
	K000, K001\
) \
{ \
    { K000, K001 }\
}

#define LAYOUT_SPLIT( \
	K000, K001, K002, K003\
) \
{ \
    { K000, K001 }, \
    { K002, K003 } \
}
