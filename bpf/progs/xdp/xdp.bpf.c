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
 * @file    xdp.bpf.c
 * @brief   eBPF XDP 프로그램 소스 파일
 */

/* ========================================================================
 * Includes
 * ==================================================================== */

#include "vmlinux.h"
#include <bpf/bpf_helpers.h>

/* ========================================================================
 * Maps
 * ==================================================================== */

/* CPU마다 독립 카운터 — 동시성 걱정 없이 가장 빠르게 카운트하는 방식 */
struct {
    __uint(type, BPF_MAP_TYPE_PERCPU_ARRAY);
    __type(key, __u32);
    __type(value, __u64);
    __uint(max_entries, 1);
} pkt_count SEC(".maps");

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

/* ========================================================================
 * Static (File-local) Functions
 * ==================================================================== */

/* ========================================================================
 * Program
 * ==================================================================== */

SEC("xdp")
int xdp_pass_prog(struct xdp_md *ctx)
{
    __u32 key = 0;
    __u64 *count;

    count = bpf_map_lookup_elem(&pkt_count, &key);
    if (count) {
        __sync_fetch_and_add(count, 1);
    }

    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";
