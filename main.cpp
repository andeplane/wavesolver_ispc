#include <iostream>
#include "wavesolver.h"
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

double run(int gridSize, int timesteps, bool serial) {
    WaveSolver solver(gridSize);
    unsigned int N = timesteps;

    double t = 0;
    for(unsigned int j=0; j<N; j++) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        solver.step(serial);
        gettimeofday(&end, NULL);
        double timeElapsed = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        t += timeElapsed;
    }
    
    return t;
}

int main(int args, char **argv)
{
    int maxGridSize = 1024;
    int timesteps = 5;
    if(args>1) maxGridSize = atoi(argv[1]);
    if(args>2) timesteps = atoi(argv[2]);

    for(int gridSize=128; gridSize<=maxGridSize; gridSize += 128) {
        double timeSerial = run(gridSize, timesteps, true);
        double timeISPC = run(gridSize, timesteps, false);
        double speedSerial = gridSize*gridSize*timesteps/timeSerial*1e-6;
        double speedISPC   = gridSize*gridSize*timesteps/timeISPC*1e-6;
        double timePerTimestepSerial = timeSerial / timesteps;
        double timePerTimestepISPC = timeISPC / timesteps;
        // cout << "N=" << gridSize << " speed (million grid points per second): " << speedSerial << " (SERIAL) vs " << speedISPC << " (ISPC), speedup: " << speedISPC/speedSerial << " x" << endl;
        cout << "N=" << gridSize << "   -   Time per timestep [ms]: " << timePerTimestepSerial*1000 << " (SERIAL), " << timePerTimestepISPC*1000 << " (ISPC)   -   speed: " << speedSerial << " (SERIAL), " << speedISPC << " (ISPC), million grid points per second. Speedup: " << timeSerial / timeISPC << "x." << endl;
    }
    return 0;
}

