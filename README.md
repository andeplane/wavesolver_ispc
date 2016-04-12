# Wavesolver ISPC #
A simple example solving the wave equation with a finite difference scheme using Intel's ISPC compiler. It shows how easy it is to write two versions of the solver that requires high performance - one serial and one ISPC version. On my Macbook Pro Retina i get a speedup ~4x with almost the same code. 

## What is ISPC ##
ISPC is an open source compiler written by Intel (https://ispc.github.io/). They introduced a new language (extension to C) to simplify writing SPMD (Single Program Multiple Data) programs. The idea is to write small programs that will run independently in parallel (like on the GPU) enabling easier use of SIMD (Single Instruction Multiple Data). ISPC also supports using multiple cores so that parallelization on a single machine with full SIMD support is trivial.

## How to use ##
You need to have the ISPC compiler (download compiled binaries from https://ispc.github.io/downloads.html) and the compiler directory added in $PATH. Then simply clone this repository and run 'make' in the terminal. Run with ./wavesolver [maxGridSize] [timesteps] to get output like this:

Macbook:wavesolver_ispc anderhaf$ ./wavesolver 2048 100

N=128 speed (million grid points per second): 321.255 (SERIAL) vs 1820.44 (ISPC), speedup: 5.66667x

N=256 speed (million grid points per second): 312.076 (SERIAL) vs 1489.45 (ISPC), speedup: 4.77273x

N=384 speed (million grid points per second): 313.736 (SERIAL) vs 1694.9 (ISPC), speedup: 5.4023x

N=512 speed (million grid points per second): 226.572 (SERIAL) vs 1213.63 (ISPC), speedup: 5.35648x

N=640 speed (million grid points per second): 250.673 (SERIAL) vs 1308.63 (ISPC), speedup: 5.22045x

N=768 speed (million grid points per second): 265.567 (SERIAL) vs 1302.04 (ISPC), speedup: 4.90287x

N=896 speed (million grid points per second): 275.977 (SERIAL) vs 1214.55 (ISPC), speedup: 4.40091x

N=1024 speed (million grid points per second): 274.856 (SERIAL) vs 1079.89 (ISPC), speedup: 3.92894x

N=1152 speed (million grid points per second): 287.003 (SERIAL) vs 1099.51 (ISPC), speedup: 3.83099x

N=1280 speed (million grid points per second): 291.219 (SERIAL) vs 1119.89 (ISPC), speedup: 3.84552x

N=1408 speed (million grid points per second): 294.44 (SERIAL) vs 1166.84 (ISPC), speedup: 3.96292x

N=1536 speed (million grid points per second): 296.916 (SERIAL) vs 1114.45 (ISPC), speedup: 3.75342x

N=1664 speed (million grid points per second): 298.244 (SERIAL) vs 1086.27 (ISPC), speedup: 3.64221x

N=1792 speed (million grid points per second): 300.146 (SERIAL) vs 1134.72 (ISPC), speedup: 3.78057x

N=1920 speed (million grid points per second): 300 (SERIAL) vs 1087.11 (ISPC), speedup: 3.62371x

N=2048 speed (million grid points per second): 294.358 (SERIAL) vs 1050.68 (ISPC), speedup: 3.56939x

It chooses the best run time of the 100 runs.