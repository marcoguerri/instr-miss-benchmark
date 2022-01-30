# itlb-benchmark
Benchmark which tests instruction cache and iTLB behavior of x86_64 processor.

The repository contains two benchmarks:
* btp.c: focused on branch traget prediction behavior. See [related post](https://marcoguerri.github.io/2017/02/python-branch-prediction) for an example of how this was used.
* itlb.c: focused on iTLB behavior. See [Profiling CPU-bound workloads on Intel Haswell-EP
platforms](https://cds.cern.ch/record/2257973/files/Profiling_CPU_Guerri_Giordano_Cordeiro.pdf) for an example of how this was used.
