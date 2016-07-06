#include <stdlib.h>
#include <errno.h>

#include "tensor.h"

/* tsralloc: allocate new zero-initialized tensor on heap.
 * It returns NULL if malloc(3) fails and nrows/ncols is zero, otherwise it
 * returns pointer to new allocated tensor. */
tensor_t *
tsralloc(size_t nrows, size_t ncols)
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

/* tsrnrows: get the number of rows */
size_t
tsrnrows(const tensor_t tensor)
{
    return tensor.nrows;
}

/* tsrncols: get the number of cols */
size_t
tsrncols(const tensor_t tensor)
{
    return tensor.ncols;
}

/* tsrfree: free tensor from heap */
void
tsrfree(tensor_t *tensor)
{
    free(tensor->data);
    free(tensor);
}

/* tsrget: get the value from the row i-th and column j-th.
 * if rowi < number of rows and colj < number of columns of tensor t it returns
 * 0 and writes the value to the output.
 * Otherwise it returns a non-zero value and set errno to EINVAL */
int
tsrget(const tensor_t t, size_t rowi, size_t colj, double *output)
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

/* tsrset: set the value of the row i-th and column j-th.
 * if rowi < number of rows and colj < number of columns of tensor t it returns
 * 0 and writes the value to the row i-th and column j-th.
 * Otherwise it returns a negative value and set errno to EINVAL */
int
tsrset(tensor_t *const t, size_t rowi, size_t colj, double value)
{
    /* bound checking */
    if(rowi >= t->nrows || colj >= t->ncols) {
        errno = EINVAL;
        return -1;
    }

    /* write the data */
    *(t->data + ((rowi * t->ncols) + colj)) = value;
    return 0;
}

