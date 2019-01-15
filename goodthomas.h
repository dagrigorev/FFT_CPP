#ifndef GOODTHOMAS_H
#define GOODTHOMAS_H

#include <complex>
#include <math.h>

std::complex<double>* DFT_naive(std::complex<double>* x, int N) {
    std::complex<double>* X = (std::complex<double>*) malloc(sizeof(struct std::complex<double>) * N);
    int k, n;
    for(k = 0; k < N; k++) {
        X[k].real(0.0);
        X[k].imag(0.0);
        for(n = 0; n < N; n++) {
            // TODO: Check std::complex constructor
            X[k] = X[k] + x[n] * std::complex<double>(1, -2*M_PI*n*k/N);
        }
    }

    return X;
}

/** Implements the Good-Thomas FFT algorithm.
  *
  * @expects: N1 and N2 must be relatively prime
  * @expects: N1*N2 = N
  */
std::complex<double>* FFT_GoodThomas(std::complex<double>* input, int N, int N1, int N2) {
    int k1, k2, z;

    /* Allocate columnwise matrix TODO: */
    std::complex<double>** columns = (std::complex<double>**) malloc(sizeof(struct std::complex<double>*) * N1);
    for(k1 = 0; k1 < N1; k1++) {
        columns[k1] = (std::complex<double>*) malloc(sizeof(struct std::complex<double>) * N2);
    }

    /* Allocate rowwise matrix */
    std::complex<double>** rows = (std::complex<double>**) malloc(sizeof(struct std::complex<double>*) * N2);
    for(k2 = 0; k2 < N2; k2++) {
        rows[k2] = (std::complex<double>*) malloc(sizeof(struct std::complex<double>_t) * N1);
    }

    /* Reshape input into N1 columns (Using Good-Thomas Indexing) */
    for(z = 0; z < 30; z++) {
        k1 = z % N1;
        k2 = z % N2;
        columns[k1][k2] = input[z];
    }

    /* Compute N1 DFTs of length N2 using naive method */
    for (k1 = 0; k1 < N1; k1++) {
        columns[k1] = DFT_naive(columns[k1], N2);
    }

    /* Transpose */
    for(k1 = 0; k1 < N1; k1++) {
        for (k2 = 0; k2 < N2; k2++) {
            rows[k2][k1] = columns[k1][k2];
        }
    }

    /* Compute N2 DFTs of length N1 using naive method */
    for (k2 = 0; k2 < N2; k2++) {
        rows[k2] = DFT_naive(rows[k2], N1);
    }

    /* Flatten into single output (Using chinese remainder theorem) */
    std::complex<double>* output = (std::complex<double>*) malloc(sizeof(struct std::complex<double>) * N);

    for(k1 = 0; k1 < N1; k1++) {
        for (k2 = 0; k2 < N2; k2++) {
            z = N1*k2 + N2*k1;
            output[z%N] = rows[k2][k1];
        }
    }

    /* Free all alocated memory except output and input arrays */
    for(k1 = 0; k1 < N1; k1++) {
        free(columns[k1]);
    }
    for(k2 = 0; k2 < N2; k2++) {
        free(rows[k2]);
    }
    free(columns);
    free(rows);
    return output;
}

#endif // GOODTHOMAS_H
