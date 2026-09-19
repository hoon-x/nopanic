/*
 * Copyright 2026 <저작권자/조직명>
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
 * @file    template.h
 * @brief   <이 헤더가 무엇을 선언하는지 한 줄 요약>
 */

#ifndef NOPANIC_TEMPLATE_H
#define NOPANIC_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================
 * Includes
 * ==================================================================== */

#include <stdint.h>
#include <stddef.h>

/* ========================================================================
 * Macros / Constants
 * ==================================================================== */

#define TEMPLATE_MAX_LEN 256

/* ========================================================================
 * Types
 * ==================================================================== */

typedef struct template_ctx {
    int      fd;
    uint32_t flags;
} template_ctx_t;

/* ========================================================================
 * Public Functions
 * ==================================================================== */

/**
 * @brief  <함수가 하는 일>
 * @param  ctx  <설명>
 * @return 0 on success, -1 on failure (errno set)
 */
int template_init(template_ctx_t *ctx);

void template_destroy(template_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* NOPANIC_TEMPLATE_H */
