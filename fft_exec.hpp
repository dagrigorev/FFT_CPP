#ifndef FFT_EXEC_HPP
#define FFT_EXEC_HPP

#include <boost/math/constants/constants.hpp>
// using boost::math::constants::pi;

#include <boost/multiprecision/cpp_dec_float.hpp>
// using boost::multiprecision::cpp_dec_float

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <stdlib.h>
#include "fft_table.hpp"

using boost::multiprecision::cpp_dec_float_50;
using boost::math::constants::pi;
// VS 2010 (wrongly) requires these at file scope, not local scope in `main`.
// This program also requires `-std=c++11` option to compile using Clang and GCC.

/**
 * @brief gen_sine Генерирует массив синусоидальных гармоник
 */
auto gen_sine()
{
    std::size_t size = 32U;
    cpp_dec_float_50 p = pi<cpp_dec_float_50>();
    cpp_dec_float_50 p2 = boost::math::constants::pi<cpp_dec_float_50>();

    std::vector <cpp_dec_float_50> sin_values (size);
    unsigned n = 1U;
    // Генерировать значения синуса.
    std::for_each
    (
      sin_values.begin (),
      sin_values.end (),
      [&n](cpp_dec_float_50& y)
      {
        y = sin( pi<cpp_dec_float_50>() / pow(cpp_dec_float_50 (2), n));
        ++n;
      }
    );

    return sin_values;
}

/**
 * @brief output_vector Вывод вектора типа cpp_dec_float_50 на экран
 * @param input_vector Входной вектор
 */
void output_vector(std::vector<cpp_dec_float_50> &input_vector, bool show_gnuplot = false)
{
    auto precision = std::numeric_limits<cpp_dec_float_50>::digits10;
    std::cout.precision(precision);

    FILE *gp = popen("/usr/local/bin/gnuplot -persist","w"); // gp - дескриптор канала
    FILE *pf = std::fopen("fil.dat", "w");
    if (show_gnuplot && !gp && !pf)
    {
        printf("Error opening pipe to GNU plot.\n");
    }else{
        //fprintf(pf, "times\tvalues1\tvalues2\n");
        fprintf(gp, "set style data linespoints\n");
    }

    for (unsigned int i = 0U; ;)
    {
          std::cout << "  " << input_vector[i];
          if (i == input_vector.size()-1)
          {
            std::cout << "\n}};\n";
            break;
          }
          else
          {
            std::cout << ",\n";
            i++;
          }

          if(gp && show_gnuplot && pf)
          {
              fprintf(pf, "%d\t%f\t%d\n", i, input_vector[i].convert_to<double>(), i);
          }
    }

    if(show_gnuplot && gp && pf)
    {
        std::fclose(pf);
        fprintf(gp, "plot \"%s\"\n", "fil.dat");
        fflush(gp);
        //pclose(gp);
    }
}

void output_vector(std::vector<std::complex<double>> &input_vector, bool show_gnuplot = false)
{
    auto precision = std::numeric_limits<cpp_dec_float_50>::digits10;
    std::cout.precision(precision);

    FILE *gp = popen("/usr/local/bin/gnuplot -persist","w"); // gp - дескриптор канала
    FILE *pf = std::fopen("fil.dat", "w");
    if (show_gnuplot && !gp && !pf)
    {
        printf("Error opening pipe to GNU plot.\n");
    }else{
        //fprintf(pf, "times\tvalues1\tvalues2\n");
        //fprintf(gp, "set style data linespoints\n");
    }

    for (unsigned int i = 0U; ;)
    {
          std::cout << "  [" << input_vector[i].imag() << "; " << input_vector[i].real() << "]";
          if (i == input_vector.size()-1)
          {
            std::cout << "\n}};\n";
            break;
          }
          else
          {
            std::cout << ",\n";
            i++;
          }
          if(gp && show_gnuplot && pf)
          {
              fprintf(pf, "%f %f\n", input_vector[i].imag(), input_vector[i].real());
          }
    }

    if(show_gnuplot && gp && pf)
    {
        std::fclose(pf);
        fprintf(gp, "plot \"%s\"\n", "fil.dat");
        fflush(gp);
        //pclose(gp);
    }
}

/**
 * @brief boost_fft Быстрое преобразование Фурье (табличный метод)
 * @param input_vector Входной вектор
 */
std::vector<std::complex<double>> table_fft(std::vector<cpp_dec_float_50> &input_vector)
{
        int i;
        for (i = 0; i < (1 << LN_FFT); i++) {
            XY[i].r = input_vector[i].convert_to<double>();
            XY[i].i = 0;
        }
        fft_table();
        auto comp = std::vector<std::complex<double>>();
        for(i = 0; i < (1 << LN_FFT); i++) {
            comp.push_back(std::complex<double>(XY[OutOrder[i]].r, XY[OutOrder[i]].i));
        }
        return comp;
}

/**
 * @brief demo_sample_fft Демонстрирует работу оптимизированного БПФ синусоидальных гармоник
 */
void demo_sample_fft()
{
    auto sine = gen_sine();
    std::cout << "Generated sine: " << std::endl;
    output_vector(sine, true);

    auto res = table_fft(sine);
    std::cout << "Calculated FFT: " << std::endl;
    output_vector(res, true);
}

#endif // FFT_EXEC_HPP
