#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include <pcg_variants.h>

#include "rng.h"

rng_t *allocate_rng(rng_dist_t rngd)
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
    rng->distribution = rngd;

    return rng;
}

void free_rng(rng_t *rng)
{
    /* free the heap */
    free(rng->pcg_rng);
    free(rng);
}

int set_seed_value_rng(rng_t *rng, uint64_t seed_value)
{
    if(rng == NULL) {
        errno = EINVAL;
        return -1;
    }

    rng->pcg_seed_value = seed_value;
    return 0;
}

int get_random_value_rng(rng_t *rng, double *output)
{
    if(rng == NULL) {
        errno = EINVAL;
        return -1;
    }

    if(rng->distribution == RNG_UNIFORM) {
        uint32_t random_number = pcg32_random_r(rng->pcg_rng);
        double value = ldexp(random_number, -32);
        *output = value;
        return 0;
    }
    return -1;
}

#ifdef SIMPLE_NN_RNG_C_TEST
#include <assert.h>

int main(int argc, char **argv)
{
    int err = 0;

    /* Allocate random number generator in heap */
    rng_t *rng = allocate_rng(RNG_UNIFORM);

    /* Set the seed value */
    err = set_seed_value_rng(rng, 123);
    assert(err == 0);
    err = set_seed_value_rng(NULL, 123);
    assert(err != 0);
    assert(errno == EINVAL);

    /* Get random value */
    double output1, output2;
    err = get_random_value_rng(rng, &output1);
    err = get_random_value_rng(rng, &output2);
    assert(output1 != output2);
    err = get_random_value_rng(NULL, &output1);
    assert(err != 0);
    assert(errno == EINVAL);

    free_rng(rng);
}
#endif
