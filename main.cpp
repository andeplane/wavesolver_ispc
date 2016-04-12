#include <iostream>
#include "wavesolver.h"
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

double run(int gridSize, int timesteps, bool serial) {
    WaveSolver solver(gridSize);
    unsigned int N = timesteps;

    double t = 1e9;
    for(unsigned int j=0; j<N; j++) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        solver.step(serial);
        gettimeofday(&end, NULL);
        double timeElapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        t = std::min(t, timeElapsed);
    }
    
    return solver.gridSize()*solver.gridSize()/t*1e-6;
}

int main(int args, char **argv)
{
    int maxGridSize = 1024;
    int timesteps = 5;
    if(args>1) maxGridSize = atoi(argv[1]);
    if(args>2) timesteps = atoi(argv[2]);

    for(int gridSize=128; gridSize<=maxGridSize; gridSize += 128) {
        double speedSerial = run(gridSize, timesteps, true);
        double speedISPC = run(gridSize, timesteps, false);
        cout << "N=" << gridSize << " speed (million grid points per second): " << speedSerial << " (SERIAL) vs " << speedISPC << " (ISPC), speedup: " << speedISPC/speedSerial << " x" << endl;
    }
    return 0;
}

