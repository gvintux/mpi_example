# MPI example

## Task

integrate f(x) on [a;b] using MPI

## Requirements

* MPI-сompatible C compiler
* Any MPI toolkit (MPICH for example)

## Build

* change dir to `build`
* run `cmake ..`
* run `make`

## Run

Choose one of:

* run `make mpirun`
* run `mpirun -np k+1 ./mpi_example` where k = cores count
