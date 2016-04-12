#include <iostream>
#include "wavesolver.h"
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

void runSerial(int max) {
    for(unsigned int i=256; i<=max; i+=128) {
        WaveSolver solver(i);
        unsigned int N = 5;

        struct timeval start, end;
        gettimeofday(&start, NULL);

        for(unsigned int j=0; j<N; j++) {
            solver.step(true);
        }
        gettimeofday(&end, NULL);
        double timeElapsed = ((end.tv_sec  - start.tv_sec) * 1000000u +
                                     end.tv_usec - start.tv_usec) / 1.e6;
        double gflops = 9.0*solver.gridSize()*solver.gridSize()*N / timeElapsed*1e-9;
        cout << "SERIAL N=" << i << " gflops: " << gflops << " after " << timeElapsed << " seconds." << endl;
    }
}

void runISPC(int max) {
    for(unsigned int i=256; i<=max; i+=128) {
        WaveSolver solver(i);
        unsigned int N = 5;

        struct timeval start, end;
        gettimeofday(&start, NULL);

        for(unsigned int j=0; j<N; j++) {
            solver.step(false);
        }
        gettimeofday(&end, NULL);
        double timeElapsed = ((end.tv_sec  - start.tv_sec) * 1000000u +
                                     end.tv_usec - start.tv_usec) / 1.e6;
        double gflops = 9.0*solver.gridSize()*solver.gridSize()*N / timeElapsed*1e-9;
        cout << "ISPC N=" << i << " gflops: " << gflops << " after " << timeElapsed << " seconds." << endl;
    }
}

int main(int args, char **argv)
{
    int maxGridSize = 1024;
    if(args>1) maxGridSize = atoi(argv[1]);

    // runSerial(maxGridSize);
    runISPC(maxGridSize);
    return 0;
}

