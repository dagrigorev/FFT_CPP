//
// Created by Dmitry on 10.02.2019.
//

#include "signal.h"
#include <stdio.h>

void print_buf(float *buffer, size_t buffer_length)
{
    int idx = 0;
    for(idx = 0; idx < buffer_length; idx++)
        printf("%.3f,", buffer[idx]);
    printf("\n");
}

