/*
 * Copyright 2026 Nopanic Project Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file    string_util.c
 * @brief   문자열 유틸리티 기능 구현 소스 파일
 */

/* ========================================================================
 * Includes
 * ==================================================================== */

#include "utils/string_util.h"

#include <string.h>
#include <ctype.h>

/* ========================================================================
 * Local Macros / Constants
 * ==================================================================== */

/* ========================================================================
 * Static (File-local) State
 * ==================================================================== */

/* ========================================================================
 * Forward Declarations (static helpers)
 * ==================================================================== */

/* ========================================================================
 * Public Functions
 * ==================================================================== */

char *trim(char *str)
{
    if (str == NULL) {
        return NULL;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    return str;
}

/* ========================================================================
 * Static (File-local) Functions
 * ==================================================================== */
