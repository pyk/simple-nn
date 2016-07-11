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

    tensor_t *X = tensor_allocate(nsamples, nfeatures);
    if(X == NULL) {
        printf("Cannot allocate tensor X\n");
        return 1;
    }
    /* first sample */
    tensor_set_value(X, 0, 0, 0);
    tensor_set_value(X, 0, 1, 0);
    tensor_set_value(X, 0, 2, 1);
    /* second sample */
    tensor_set_value(X, 1, 0, 1);
    tensor_set_value(X, 1, 1, 1);
    tensor_set_value(X, 1, 2, 1);
    /* third sample */
    tensor_set_value(X, 2, 0, 1);
    tensor_set_value(X, 2, 1, 0);
    tensor_set_value(X, 2, 2, 1);
    /* forth sample */
    tensor_set_value(X, 3, 0, 0);
    tensor_set_value(X, 3, 1, 1);
    tensor_set_value(X, 3, 2, 1);

    tensor_t *y = tensor_allocate(nsamples, 1);
    if(y == NULL) {
        printf("Cannot allocate tensor y\n");
        return 1;
    }
    /* output for each sample */
    tensor_set_value(y, 0, 0, 0);
    tensor_set_value(y, 1, 0, 1);
    tensor_set_value(y, 2, 0, 1);
    tensor_set_value(y, 3, 0, 0);

    /* print dataset */
    printf("X                 y\n");
    for(int i = 0; i < nsamples; i++) {
        for(int j = 0; j < nfeatures; j++) {
            double output;

            err = tensor_get_value(*X, i, j, &output);
            if(err != 0) {
                printf("err: index out of bound X\n");
                exit(EXIT_FAILURE);
            }

            printf("%.2f ", output);
        }

        double output;

        err = tensor_get_value(*y, i, 0, &output);
        if(err != 0) {
            printf("err: index out of bound y\n");
            exit(EXIT_FAILURE);
        }

        printf("   %.2f\n", output);
    }

    /* Implementation of Single-layer perceptron
     * X matrix 4x3 as the input, it has 3 nodes
     * W matrix 3x1 represent the weight that connect 3 nodes in input layer
     *   to one neuron in output layer
     * y_hat matrix 4x1 represent the output of the neural networks
     *
     * Formula:
     * y_hat = activation_func(X * W) */

    /* free the heap */
    tensor_free(y);
    tensor_free(X);
}
