//
// Created by Dmitry on 10.02.2019.
//

#include "DFT.h"
#include <math.h>
#include <mem.h>
#include <complex.h>
#include <stdio.h>

void fill_zero(float *buf, size_t len);

void dft(float* signal_buf, size_t len){
    float _Complex temp_buffer[len];
    //memcpy(temp_buffer, signal_buf, len);
    size_t n, k;

    for(k=0; k < len; k++)
    {
        float im = 0.f, re = 0.f;
        for(n=0;n<len;n++)
        {
            float ang = 2 * M_PI * n * k / (float)len;
            // Именное такие формулы надо использовать !!!!
            // Не менять !!!!
            re += signal_buf[n] * cos(ang);
            im += -signal_buf[n] * sin(ang);
        }
        temp_buffer[k] = re + im * _Complex_I;

        printf("%.3f\t%.3f*j\n", re, im);
    }
    for(k=0; k < len; k++)
    {
        signal_buf[k] = crealf(temp_buffer[k]);
    }
}

void fill_zero(float *buf, size_t len)
{
    size_t idx;
    for(idx=0; idx < len; idx++)
    {
        buf[idx] = 0.f;
    }
}