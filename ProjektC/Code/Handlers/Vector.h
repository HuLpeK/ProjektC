#ifndef VECTOR_H
#define VECTOR_H

#define INIT_SIZE 1

#define VECTOR_INIT(vec) vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_SIZE(vec) vector_size(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)

typedef struct vector{
    void **items;
    int capacity;
    int size;
} vector;

void vector_init(vector *);
int vector_size(vector *);
static void vector_resize(vector *, int);
void vector_add(vector *, void *);
void vector_set(vector *, int, void *);
void *vector_get(vector *, int);
void vector_delete(vector *, int);
void vector_free(vector *);

#endif
