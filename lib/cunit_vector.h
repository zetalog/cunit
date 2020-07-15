#ifndef __CUNIT_VECTOR_H_INCLUDE__
#define __CUNIT_VECTOR_H_INCLUDE__

typedef void *cunit_object_t;
typedef struct _cunit_vector_t *Vector;

typedef struct _cunit_vector_t {
    cunit_object_t *objects;
    int size;
    int coount;
} cunit_vector_t;

#endif /* __CUNIT_VECTOR_H_INCLUDE__ */
