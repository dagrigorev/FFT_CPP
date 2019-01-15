#include <iostream>
#include "fft_exec.hpp"
#include <signal.h>

using namespace std;

volatile sig_atomic_t flag = 0;
void my_function(int sig){ // can be called asynchronously
  flag = 1; // set flag
}

int main()
{
    // Регистрируем обработчик сигнала на нажатие Ctrl-Z или Ctrl-C
    //signal(SIGINT, my_function);

    demo_sample_fft();

    while (/*getchar() != '\n'*/1) {
        /*if(flag){
            break;
        }*/
        // ждать пока не нажата комбинация Ctrl-Z или Ctrl-C
    }
    return 0;
}
