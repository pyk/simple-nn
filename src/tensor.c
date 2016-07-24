/* tensor - A memory-efficient data structure for handling numeric data
 * The tensor stores the mutimensional arrays in row-major order, it means
 * consecutive elements of the rows of the array are contiguous in
 * memory.
 *
 * Accessing array elements that are contiguous in memory are faster than
 * accessing elements which are not, due to cache in memory.
 *
 * Copyright (c) 2016, Bayu Aldi Yansyah. All rights reserved.
 * Use of this source code is governed by a BSD-style license that
 * can be found in the LICENSE file. */
#include <stdlib.h>
#include <errno.h>

#include "tensor.h"
#include "rng.h"

/* allocate_tensor: allocate new zero-initialized tensor on heap.
 * It returns NULL if alocation fails or nrows/ncols is zero
 * It returns pointer to new allocated tensor_t if operation success */
tensor_t *allocate_tensor(size_t nrows, size_t ncols)
{
    /* check the value of nrows and ncols */
    if(nrows == 0 || ncols == 0) {
        errno = EINVAL;
        return NULL;
    }

    tensor_t *tensor = malloc(sizeof *tensor);
    if(tensor == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    double *data = calloc(nrows * ncols, sizeof *data);
    if(data == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    tensor->nrows = nrows;
    tensor->ncols = ncols;
    tensor->data = data;
    return tensor;
}

/* allocate_random_tensor: Allocate random-number-initialized tensor
 * on the heap.
 * The distribution of where the random number generated from is specified
 * by random number generator rng.
 *
 * It returns NULL if allocation fails or nrows/ncols is zero.
 * It returns pointer to new allocated tensor_t if operation succeed.
 *
 * The returns value should be checked by the caller and perform error
 * handling */
tensor_t *allocate_random_tensor(size_t nrows, size_t ncols, const rng_t rng)
{
    /* check the value of nrows and ncols */
    if(nrows == 0 || ncols == 0) {
        errno = EINVAL;
        return NULL;
    }

    tensor_t *tensor = malloc(sizeof *tensor);
    if(tensor == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    double *data = malloc((nrows * ncols) * sizeof *data);
    if(data == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    tensor->nrows = nrows;
    tensor->ncols = ncols;
    tensor->data = data;

    /* populate the data */
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; i++) {
            int err = 0;

            double rand_value;
            err = rng_get_random_value(rng, &rand_value);
            if(err != 0) {
                errno = errno;
                return NULL;
            }

            err = tensor_set_value(tensor, i, j, rand_value);
            if(err != 0) {
                errno = errno;
                return NULL;
            }
        }
    }

    return tensor;
}

/* free_tensor: free tensor t from the heap */
void free_tensor(tensor_t *t)
{
    free(t->data);
    free(t);
}

/* tensor_get_nrows: get the number of rows of the tensor t */
size_t tensor_get_nrows(const tensor_t t)
{
    return t.nrows;
}

/* tensor_get_ncols: get the number of columns of the tensor t */
size_t tensor_get_ncols(const tensor_t t)
{
    return t.ncols;
}

/* tensor_get_value: get the value of tensor cell from tensor t specified by row
 * index rowi dan column index colj.
 * It returns 0 and write the value to the output if the input is valid
 * Otherwise it returns a non-zero value and set errno to EINVAL */
int tensor_get_value(const tensor_t t, size_t rowi, size_t colj, double *output)
{
    /* bound checking */
    if(rowi >= t.nrows || colj >= t.ncols) {
        errno = EINVAL;
        return -1;
    }

    /* writes the value to the output */
    *output = *(t.data + ((rowi * t.ncols) + colj));
    return 0;
}

/* tensor_set_value: Set the value of element tensor t.
 * The index of element is started from zero.
 *
 * It returns zero value if operation succeed
 * It returns non-zero value if t is NULL or trying to set the value of element
 * tensor t that doesn't exists */
int tensor_set_value(tensor_t *const t, size_t rowi, size_t colj, double value)
{
    /* NULL checking */
    if(t == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* bound checking */
    if(rowi >= t->nrows || colj >= t->ncols) {
        errno = EINVAL;
        return -1;
    }

    /* write the data */
    *(t->data + ((rowi * t->ncols) + colj)) = value;
    return 0;
}

/* UNIT TEST */
#ifdef SIMPLE_NN_TENSOR_C_TEST
#include <assert.h>
int main(int argc, char **argv)
{
    size_t nrows = 2;
    size_t ncols = 3;
    int err = 0;

    /* test tensor allocation */
    tensor_t *tensor = allocate_tensor(nrows, ncols);
    assert(tensor != NULL);
    assert(tensor_get_nrows(*tensor) == nrows);
    assert(tensor_get_ncols(*tensor) == ncols);

    /* make sure the tensor is zero-initialized */
    double zero = 0.0;
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            double output;
            err = tensor_get_value(*tensor, i, j, &output);
            assert(err == 0);
            assert(output == zero);
        }
    }

    /* it returns NULL if nrows=ncols=0 */
    tensor_t *teno = allocate_tensor(0, 0);
    assert(teno == NULL);
    assert(errno == EINVAL);

    /* test set & get */
    double input = 10.0;
    double output = 0.0;
    err = tensor_set_value(tensor, 0, 0, input);
    assert(err == 0);

    err = tensor_get_value(*tensor, 0, 0, &output);
    assert(err == 0);
    assert(output == input);

    /* setting NULL value should be error */
    err = tensor_set_value(NULL, 0, 0, input);
    assert(err != 0);
    assert(errno == EINVAL);

    /* it returns non-zero value if the user trying to access or set
     * the index that equal or larger than number of rows and columns */
    err = tensor_set_value(tensor, nrows+10, ncols+10, input);
    assert(err != 0);
    assert(errno == EINVAL);

    err = tensor_get_value(*tensor, nrows+10, ncols+10, &output);
    assert(err != 0);
    assert(errno == EINVAL);

    /* test free; checked by valgrind */
    free_tensor(tensor);
}
#endif

