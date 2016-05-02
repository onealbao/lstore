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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <tbx/assert_result.h>
#include "archive.h"

// concatenates two strings together
char* concat(char *str1, char *str2)
{
    char *res = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(res, str1);
    strcat(res, str2);
    return res;
}

// adds two paths together with separator
char* path_concat(char *str1, char *str2)
{
    char *res = malloc(strlen(str1) + strlen(str2) + 2);
    strcpy(res, concat(str1, "/"));
    strcat(res, str2);
    return res;
}
