#include <stdio.h>
#include "signal.h"
#include "FFT/DFT.h"

/**
 * Prints greeting message
 */
void print_hello();

int main() {
    print_hello();

    printf("\nInput signal is: ");
    print_buf(signal, SIGNAL_LENGTH);

    dft(signal, SIGNAL_LENGTH);
    //printf("\nDFT: ");
    //print_buf(signal, SIGNAL_LENGTH);

    return 0;
}

void print_hello()
{
    printf("**************************************************************\n");
    printf("*Hello! This is Fast-Fourier Transform demonstration program.*\n");
    printf("**************************************************************\n");
}