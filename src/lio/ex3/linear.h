/*
   Copyright 2016 Vanderbilt University

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

//***********************************************************************
// Linear exnode3 support
//***********************************************************************

#ifndef _EX3_LINEAR_H_
#define _EX3_LINEAR_H_

#include <gop/opque.h>

#ifdef __cplusplus
extern "C" {
#endif

lio_segment_t *segment_linear_new();
gop_opque_t *segment_linear_append(lio_segment_t *seg, ibp_depot_t *depot, int n_depots, int n_blocks, ex_off_t block_size);

#ifdef __cplusplus
}
#endif

#endif
