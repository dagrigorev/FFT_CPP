//
// Created by Dmitry on 10.02.2019.
//

#ifndef C_SIGNAL_H
#define C_SIGNAL_H

#include <complex.h>
#include <stddef.h>

#define SIGNAL_LENGTH 9

static float signal[SIGNAL_LENGTH] = {
    1.f, 0.75f, 0.5f, 0.25f, 0.f, -0.25f, -0.5f, -0.75f, -1.f
};

/**
 * Prints input buffer
 * @param buffer input buffer pointer
 * @param *format
 */
void print_buf(float *buffer, size_t buffer_length);

#endif //C_SIGNAL_H
