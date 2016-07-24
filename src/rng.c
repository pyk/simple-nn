/* rng (random number generator)
 * A module to generate random number from various distributions
 *
 * Copyright (c) 2016, Bayu Aldi Yansyah. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE file. */
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include <pcg_variants.h>

#include "rng.h"

/* allocate_rng: Allocate new random number generator from distribution
 * dist to the heap.
 *
 * Possible dist value are:
 * RNG_UNIFORM for uniform distribution
 * RNG_NORMAL or RNG_GAUSSIAN for normal(gaussian) distribution
 *
 * It returns NULL if the malloc(3) fails and set the errno to ENOMEM.
 * It returns pointer to new allocated rng_t if success. */
rng_t *allocate_rng(rng_dist_t dist)
{
    rng_t *rng = malloc(sizeof *rng);
    if(rng == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    /* allocate pcg random number generator to the heap */
    pcg32_random_t *pcg_rng = malloc(sizeof *pcg_rng);
    if(pcg_rng == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    /* initialize the pcg random number generator */
    uint64_t initial_state = time(NULL);
    intptr_t seed_value = (intptr_t)&rng;
    pcg32_srandom_r(pcg_rng, initial_state, seed_value);

    rng->pcg_rng = pcg_rng;
    rng->pcg_initial_state = initial_state;
    rng->pcg_seed_value = seed_value;
    rng->distribution = dist;

    return rng;
}

/* free_rng: Free random number generator rng from the heap.
 * It does nothing if rng is NULL */
void free_rng(rng_t *rng)
{
    if(rng == NULL) return;
    /* free the heap */
    free(rng->pcg_rng);
    free(rng);
}

/* rng_set_seed_value: Set the seed value of random number generator rng.
 * By default the seed value is an integer value of the memory address of
 * the rng pointer itself. This function will change the default one.
 *
 * It returns non-zero value if rng is NULL otherwise it returns zero.
 * */
int rng_set_seed_value(rng_t *rng, uint64_t seed_value)
{
    if(rng == NULL) {
        errno = EINVAL;
        return -1;
    }

    rng->pcg_seed_value = seed_value;
    return 0;
}

/* rng_get_random_value: Get the next random number from random number
 * generator rng and write the result to the output.
 *
 * It returns non-zero value if output is NULL
 * It returns zero if the operation success, the random number will be
 * written into output */
int rng_get_random_value(rng_t rng, double *output)
{
    if(output == NULL) {
        errno = EINVAL;
        return -1;
    }

    if(rng.distribution == RNG_UNIFORM) {
        uint32_t random_number = pcg32_random_r(rng.pcg_rng);
        double value = ldexp(random_number, -32);
        *output = value;
        return 0;
    }

    /* TODO(pyk): implement NORMAL or GAUSSIAN distribution */

    return -1;
}

/* Test suite for this module */
#ifdef SIMPLE_NN_RNG_C_TEST
#include <assert.h>

int main(int argc, char **argv)
{
    int err = 0;

    /* Allocate random number generator in heap */
    rng_t *rng = allocate_rng(RNG_UNIFORM);

    /* Set the seed value */
    err = rng_set_seed_value(rng, 123);
    assert(err == 0);
    err = rng_set_seed_value(NULL, 123);
    assert(err != 0);
    assert(errno == EINVAL);

    /* Get random value */
    double output1, output2;
    err = rng_get_random_value(*rng, &output1);
    err = rng_get_random_value(*rng, &output2);
    assert(output1 != output2);
    err = rng_get_random_value(*rng, NULL);
    assert(err != 0);
    assert(errno == EINVAL);

    free_rng(rng);
}
#endif
