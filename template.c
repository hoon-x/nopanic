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
 * @file    template.c
 * @brief   <이 파일이 무엇을 구현하는지 한 줄 요약>
 */

/* ========================================================================
 * Includes
 * ==================================================================== */

#include "template.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

/* ========================================================================
 * Local Macros / Constants
 * ==================================================================== */

#define LOCAL_BUF_SIZE 128

/* ========================================================================
 * Static (File-local) State
 * ==================================================================== */

static int g_template_initialized = 0;

/* ========================================================================
 * Forward Declarations (static helpers)
 * ==================================================================== */

static int template_validate(const template_ctx_t *ctx);

/* ========================================================================
 * Public Functions
 * ==================================================================== */

int template_init(template_ctx_t *ctx)
{
    if (ctx == NULL) {
        errno = EINVAL;
        return -1;
    }

    memset(ctx, 0, sizeof(*ctx));
    ctx->fd = -1;

    if (template_validate(ctx) != 0) {
        return -1;
    }

    g_template_initialized = 1;
    return 0;
}

void template_destroy(template_ctx_t *ctx)
{
    if (ctx == NULL) {
        return;
    }

    if (ctx->fd >= 0) {
        close(ctx->fd);
        ctx->fd = -1;
    }
}

/* ========================================================================
 * Static (File-local) Functions
 * ==================================================================== */

static int template_validate(const template_ctx_t *ctx)
{
    if (ctx->flags & ~0xFFu) {
        errno = EINVAL;
        return -1;
    }
    return 0;
}
