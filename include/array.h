#ifndef __ARRAY_H
#define __ARRAY_H

#include <types.h>
#include <malloc.h>

#define ARRAY_DECLARE(T) \
typedef struct { \
    T *data; \
    size idx; \
    size cap; \
} T##_array; \
static inline T##_array T##_array##_init(void) { \
    T##_array v = {malloc(8 * sizeof(T)), 0, 8}; return v; \
} \
static inline void T##_array##_push(T##_array *v, T item) { \
    if (v->idx == v->cap) { \
        v->cap = v->cap ? v->cap * 2 : 8; \
        v->data = realloc(v->data, v->cap * sizeof(T)); \
    } \
    v->data[v->idx++] = item; \
} \
static inline void T##_array##_free(T##_array *v) { \
    free(v->data); \
    v->idx = v->cap = 0; \
} \
static inline T T##_array##_at(T##_array *v, size idx) { \
    return v->data[idx > v->cap ? v->cap : idx]; \
} \
static inline void T##_array##_resize(T##_array *v, size elems) { \
    if (elems < v->cap) return; \
    v->data = realloc(v->data, elems * sizeof(T)); \
    v->cap = elems; \
} \

#endif