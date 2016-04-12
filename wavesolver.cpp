#include "wavesolver.h"
#include "wavesolver_ispc.h"
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;
using namespace ispc;

extern void wavesolver_serial( int nx, float c, 
                            const float u[], const float u_prev[], float u_next[]);

unsigned int WaveSolver::timesteps() const
{
    return m_timesteps;
}

WaveSolver::WaveSolver(unsigned int nx)
{
    m_nx = nx;
    m_nxPlusTwo = m_nx+2;
    int nxnx = m_nxPlusTwo*m_nxPlusTwo;

    u = new float[nxnx];
    u_next = new float[nxnx];
    u_prev = new float[nxnx];

    memset(u, 0, nxnx*sizeof(float));
    memset(u_next, 0, nxnx*sizeof(float));
    memset(u_prev, 0, nxnx*sizeof(float));

    initializeGauss(0, 0, 1.0);
}

WaveSolver::~WaveSolver()
{
    delete[] u;
    delete[] u_prev;
    delete[] u_next;
}

void WaveSolver::initializeGauss(float x0, float y0, float variance)
{
    for(unsigned int i=0; i<m_nx; i++) {
        unsigned int n = i+1;
        float x = (i - 0.5*m_nx)*DX;
        float dx = x-x0;

        for(unsigned int j=0; j<m_nx; j++) {
            unsigned int m = j+1;
            float y = (j - 0.5*m_nx)*DX;
            float dy = y-y0;
            float dr2 = dx*dx + dy*dy;
            u[index(n,m)] = exp(-0.5*dr2/variance);
            u_prev[index(n,m)] = exp(-0.5*dr2/variance);
        }
    }

    copyBoundary();
}

void WaveSolver::copyBoundary() {
    for(unsigned int i=0; i<m_nx;i++) {
        u[index(0, i+1)] = u[index(m_nx, i+1)];
        u[index(m_nx+1, i+1)] = u[index(1, i+1)];
        u[index(i+1, 0)] = u[index(i+1, m_nx)];    // y=0 row
        u[index(i+1, m_nx+1)] = u[index(i+1, 1)];  // y=n-1 row
    }
}

void WaveSolver::step(bool serial) {
    if(serial) {
        wavesolver_serial(m_nx, m_C, u, u_prev, u_next);
    } else {
        wavesolver_ispc(m_nx, m_C, u, u_prev, u_next);
    }
    
    std::swap(u_prev, u);
    std::swap(u_next, u);
    copyBoundary();
    m_timesteps++;
}
