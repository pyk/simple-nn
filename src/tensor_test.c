#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "tensor.h"

int
main(int argc, char **argv)
{
    /* test tensor allocation */
    size_t nrows = 2;
    size_t ncols = 3;
    tensor_t *tensor = tsralloc(nrows, ncols);
    assert(tensor != NULL);
    assert(tsrnrows(*tensor) == nrows);
    assert(tsrncols(*tensor) == ncols);

    /* test set & get */
    int err = 0;
    double input = 10.0;
    double output = 0.0;
    err = tsrset(tensor, 0, 0, input);
    assert(err == 0);

    err = tsrget(*tensor, 0, 0, &output);
    assert(err == 0);
    assert(output == input);

    /* test EINVAL */
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
