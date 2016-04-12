static inline int index(int i, int j, int size) {
    return j * (size+2) + i;
}

void wavesolver_serial( int size, float c,
                        const float u[], const float u_prev[], float u_next[])
{
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            int m = j+1;
            int n = i+1;
            float ddx = u[index(m+1, n, size)] + u[index(m-1, n, size)];
            float ddy = u[index(m, n+1, size)] + u[index(m, n-1, size)];
            float ddt_rest = 2.0*u[index(m, n, size)] - u_prev[index(m, n, size)];
            
            u_next[index(m, n, size)] = c*(ddx + ddy - 4.0*u[index(m, n, size)]) + ddt_rest;
        }
    }
}

