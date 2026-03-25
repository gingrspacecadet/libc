#ifndef __ARRAY_H
#define __ARRAY_H

#include <types.h>
#include <malloc.h>

#include <instantiate.h>

#define ARRAY_TEMPLATE(T, N) \
typedef struct { \
    T *data; \
    size idx; \
    size cap; \
} N##_array; \
static inline N##_array N##_array##_init(void) { \
    N##_array v = {malloc(8 * sizeof(T)), 0, 8}; return v; \
} \
static inline void N##_array##_push(N##_array *v, T item) { \
    if (v->idx == v->cap) { \
        v->cap = v->cap ? v->cap * 2 : 8; \
        v->data = realloc(v->data, v->cap * sizeof(T)); \
    } \
    v->data[v->idx++] = item; \
} \
static inline void N##_array##_free(N##_array *v) { \
    free(v->data); \
    v->idx = v->cap = 0; \
} \
static inline T N##_array##_at(N##_array *v, size idx) { \
    return v->data[idx > v->cap ? (v->cap - 1) : idx]; \
} \
static inline void N##_array##_resize(N##_array *v, size elems) { \
    if (elems < v->cap) return; \
    v->data = realloc(v->data, elems * sizeof(T)); \
    v->cap = elems; \
} \

#endif