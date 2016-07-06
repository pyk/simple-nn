#include <stdio.h>
#include <stdlib.h>

#include "tensor.h"

int
main(int argc, char **argv)
{
    /* Define dataset */
    size_t nsamples = 4;
    size_t nfeatures = 3;
    int err = 0;

    tensor_t *X = tsralloc(nsamples, nfeatures);
    if(X == NULL) {
        printf("Cannot allocate tensor X\n");
        return 1;
    }
    /* first sample */
    tsrset(X, 0, 0, 0);
    tsrset(X, 0, 1, 0);
    tsrset(X, 0, 2, 1);
    /* second sample */
    tsrset(X, 1, 0, 1);
    tsrset(X, 1, 1, 1);
    tsrset(X, 1, 2, 1);
    /* third sample */
    tsrset(X, 2, 0, 1);
    tsrset(X, 2, 1, 0);
    tsrset(X, 2, 2, 1);
    /* forth sample */
    tsrset(X, 3, 0, 0);
    tsrset(X, 3, 1, 1);
    tsrset(X, 3, 2, 1);

    tensor_t *y = tsralloc(nsamples, 1);
    if(y == NULL) {
        printf("Cannot allocate tensor y\n");
        return 1;
    }
    /* output for each sample */
    tsrset(y, 0, 0, 0);
    tsrset(y, 1, 0, 1);
    tsrset(y, 2, 0, 1);
    tsrset(y, 3, 0, 0);

    /* print dataset */
    printf("X                 y\n");
    for(int i = 0; i < nsamples; i++) {
        for(int j = 0; j < nfeatures; j++) {
            double output;

            err = tsrget(*X, i, j, &output);
            if(err != 0) {
                printf("err: index out of bound X\n");
                exit(EXIT_FAILURE);
            }

            printf("%.2f ", output);
        }

        double output;

        err = tsrget(*y, i, 0, &output);
        if(err != 0) {
            printf("err: index out of bound y\n");
            exit(EXIT_FAILURE);
        }

        printf("   %.2f\n", output);
    }

    tsrfree(y);
    tsrfree(X);
}
