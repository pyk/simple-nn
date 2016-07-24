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
#ifndef SIMPLE_NN_TENSOR_H
#define SIMPLE_NN_TENSOR_H

struct tensor {
    size_t nrows;
    size_t ncols;
    double *data;
};
typedef struct tensor tensor_t;

tensor_t *allocate_tensor(size_t nrows, size_t ncols);

void free_tensor(tensor_t *tensor);

size_t tensor_get_nrows(const tensor_t tensor);
size_t tensor_get_ncols(const tensor_t tensor);

int tensor_set_value(tensor_t *const t, size_t rowi, size_t colj, double value);
int tensor_get_value(const tensor_t t, size_t rowi, size_t colj, double *output);


#endif
