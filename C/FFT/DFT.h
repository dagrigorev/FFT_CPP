//
// Created by Dmitry on 10.02.2019.
//

#ifndef C_DFT_H
#define C_DFT_H
#include <stddef.h>

/**
 * Discrete Fourier-Transform implementation
 * @author: Dmitry Grigorev
 * @date: 10.02.2019
 */

/**
 * DFT on specified signal
 * @param signal_buf Input signal buffer
 * @param len length of input signal buffer
 */
void dft(float* signal_buf, size_t len);

#endif //C_DFT_H
