#ifndef SIMPLE_NN_TENSOR_H
#define SIMPLE_NN_TENSOR_H

struct tensor {
    size_t nrows;
    size_t ncols;
    double *data;
};
typedef struct tensor tensor_t;

tensor_t *tensor_allocate(size_t nrows, size_t ncols);

void tensor_free(tensor_t *tensor);

size_t tensor_get_nrows(const tensor_t tensor);
size_t tensor_get_ncols(const tensor_t tensor);

int tensor_set_value(tensor_t *const t, size_t rowi, size_t colj, double value);
int tensor_get_value(const tensor_t t, size_t rowi, size_t colj, double *output);


#endif
