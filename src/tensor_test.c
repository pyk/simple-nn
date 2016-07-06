#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "tensor.h"

int
main(int argc, char **argv)
{
    size_t nrows = 2;
    size_t ncols = 3;
    int err = 0;

    /* test tensor allocation */
    tensor_t *tensor = tsralloc(nrows, ncols);
    assert(tensor != NULL);
    assert(tsrnrows(*tensor) == nrows);
    assert(tsrncols(*tensor) == ncols);

    /* make sure the tensor is zero-initialized */
    double zero = 0.0;
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            double output;
            err = tsrget(*tensor, i, j, &output);
            assert(err == 0);
            assert(output == zero);
        }
    }

    /* it returns NULL if nrows=ncols=0 */
    tensor_t *teno = tsralloc(0, 0);
    assert(teno == NULL);
    assert(errno == EINVAL);

    /* test set & get */
    double input = 10.0;
    double output = 0.0;
    err = tsrset(tensor, 0, 0, input);
    assert(err == 0);

    err = tsrget(*tensor, 0, 0, &output);
    assert(err == 0);
    assert(output == input);

    /* it returns non-zero value if the user trying to access or set
     * the index that equal or larger than number of rows and columns */
    err = tsrset(tensor, nrows+10, ncols+10, input);
    assert(err != 0);
    assert(errno == EINVAL);

    err = tsrget(*tensor, nrows+10, ncols+10, &output);
    assert(err != 0);
    assert(errno == EINVAL);

    /* test free */
    tsrfree(tensor);

    printf("ALL TESTS PASS\n");
}
