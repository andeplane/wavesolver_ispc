/*
  Copyright (c) 2010-2012, Intel Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.


   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
   TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
*/

static inline int index(int i, int j, int size) {
    return j * (size+2) + i;
}

export void wavesolver_ispc(uniform int size, uniform float c,
                        uniform const float u[], uniform const float u_prev[], uniform float u_next[])
{
    for (uniform int i = 0; i < size; i++) {
        foreach (j = 0 ... size) {
            int m = j+1;
            int n = i+1;
            float ddx = u[index(m+1, n, size)] + u[index(m-1, n, size)];
            float ddy = u[index(m, n+1, size)] + u[index(m, n-1, size)];
            float ddt_rest = 2.0*u[index(m, n, size)] - u_prev[index(m, n, size)];

            u_next[index(m, n, size)] = c*(ddx + ddy - 4.0*u[index(m, n, size)]) + ddt_rest;
        }
    }
}

// task void wavesolver_scanline(uniform int size, uniform float c, uniform int span, 
//                     uniform const float u[], uniform float const u_prev[], uniform float u_next[]) {

//     uniform int ystart = taskIndex * span;
//     uniform int yend = min((taskIndex+1) * span, (unsigned int)size);
//     foreach (j = ystart ... yend, i = 0 ... size) {
//         int m = i+1;
//         int n = j+1;
//         float ddx = u[index(m+1, n, size)] + u[index(m-1, n, size)];
//         float ddy = u[index(m, n+1, size)] + u[index(m, n-1, size)];
//         float ddt_rest = 2.0*u[index(m, n, size)] - u_prev[index(m, n, size)];

//         u_next[index(m, n, size)] = c*(ddx + ddy - 4.0*u[index(m, n, size)]) + ddt_rest;
//     }

// }

// export void wavesolver_ispc(uniform int size, uniform float c,
//                         uniform const float u[], uniform const float u_prev[], uniform float u_next[])
// {
//     uniform int span = 4;
//     launch[size/span] wavesolver_scanline(size, c, span, u, u_prev, u_next);
// }