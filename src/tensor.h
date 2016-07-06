#ifndef TENSOR_H
#define TENSOR_H

struct tensor {
    size_t nrows;
    size_t ncols;
    double *data;
};
typedef struct tensor tensor_t;

tensor_t *tsralloc(size_t nrows, size_t ncols);

void tsrfree(tensor_t *tensor);

int tsrset(tensor_t *const t, size_t rowi, size_t colj, double value);
int tsrget(const tensor_t t, size_t rowi, size_t colj, double *output);

size_t tsrnrows(const tensor_t tensor);
size_t tsrncols(const tensor_t tensor);

#endif
