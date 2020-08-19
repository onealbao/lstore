#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <gop/gop.h>
#include <lio/lio.h>
#include <tbx/constructor_wrapper.h>
#include <tbx/fmttypes.h>
#include <tbx/type_malloc.h>
#include "visibility.h"
#include "mongodb_lstore.h"

struct mongodb_lstore_s {
    int test;
};
