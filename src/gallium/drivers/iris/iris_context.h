/*
 * Copyright © 2017 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef IRIS_CONTEXT_H
#define IRIS_CONTEXT_H

#include "pipe/p_context.h"
#include "pipe/p_state.h"
#include "util/u_debug.h"
#include "intel/common/gen_debug.h"
#include "iris_screen.h"

struct iris_bo;

#define IRIS_MAX_TEXTURE_SAMPLERS 32
#define IRIS_MAX_VIEWPORTS 16

enum iris_dirty {
   IRIS_DIRTY_COLOR_CALC_STATE,
   IRIS_DIRTY_POLYGON_STIPPLE,
   IRIS_DIRTY_SCISSOR_RECT,
   IRIS_DIRTY_WM_DEPTH_STENCIL,
};

#define IRIS_NEW_COLOR_CALC_STATE (1ull << IRIS_DIRTY_COLOR_CALC_STATE)
#define IRIS_NEW_POLYGON_STIPPLE  (1ull << IRIS_DIRTY_POLYGON_STIPPLE)
#define IRIS_NEW_SCISSOR_RECT     (1ull << IRIS_DIRTY_SCISSOR_RECT)
#define IRIS_NEW_WM_DEPTH_STENCIL (1ull << IRIS_DIRTY_WM_DEPTH_STENCIL)

struct iris_context {
   struct pipe_context ctx;

   struct pipe_debug_callback dbg;

   struct {
      uint64_t dirty;
      struct pipe_blend_color blend_color;
      struct pipe_poly_stipple poly_stipple;
      struct pipe_scissor_state scissors[IRIS_MAX_VIEWPORTS];
      struct pipe_stencil_ref stencil_ref;
   } state;
};

#define perf_debug(dbg, ...) do {                      \
   if (INTEL_DEBUG & DEBUG_PERF)                       \
      dbg_printf(__VA_ARGS__);                         \
   if (unlikely(dbg))                                  \
      pipe_debug_message(dbg, PERF_INFO, __VA_ARGS__); \
} while(0)

double get_time(void);

struct pipe_context *
iris_create_context(struct pipe_screen *screen, void *priv, unsigned flags);

void iris_init_program_functions(struct pipe_context *ctx);
void iris_init_state_functions(struct pipe_context *ctx);

#endif