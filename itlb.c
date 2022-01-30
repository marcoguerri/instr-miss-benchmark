/*
 * itlb benchmark
 *
 * Copyright (C) 2017 Marco Guerri <marco.guerri.dev@fastmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */


#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

uint64_t max_ip = 0, min_ip = 0;
uint64_t ip;

#define RNG_LEN 100000
#define N_ITER 0x2FFFFFFE

#define CASE(N) \
            case N: \
            {       \
                __asm__  volatile("lea 0x0(%%rip), %%rax\n\t"  \
                  "movq %%rax, %0\n\t" \
                  : "=m" (ip)           \
                  : \
                  : "%rax"); \
                max_ip = max_ip ^ ((ip ^ max_ip) & -(ip > max_ip)); \
                break; \
            }
#define CASE2(N) \
            CASE(N) \
            CASE(N+1)

#define CASE4(N) \
            CASE2(N) \
            CASE2(N+2)

#define CASE8(N) \
            CASE4(N) \
            CASE4(N+4)

#define CASE16(N) \
            CASE8(N) \
            CASE8(N+8)

#define CASE32(N) \
            CASE16(N) \
            CASE16(N+16)

#define CASE64(N) \
            CASE32(N) \
            CASE32(N+32)

#define CASE128(N) \
            CASE64(N) \
            CASE64(N+64)

#define CASE256(N) \
            CASE128(N) \
            CASE128(N+128)

#define CASE512(N) \
            CASE256(N) \
            CASE256(N+256)

#define CASE1024(N) \
            CASE512(N) \
            CASE512(N+512)

#define CASE2048(N) \
            CASE1024(N) \
            CASE1024(N+1024)

#define CASE4096(N) \
            CASE2048(N) \
            CASE2048(N+2048)

#define CASE8192(N) \
            CASE4096(N) \
            CASE4096(N+4096)

#define CASE16384(N) \
            CASE8192(N) \
            CASE8192(N+8192)

#define CASE32768(N) \
            CASE16384(N) \
            CASE16384(N+16384)

int main(int argc, char* argv[])
{

    /* boundary is uint32 to support case statements > 65536 */
    uint32_t boundary, *random_sequence, i, opcode;
    struct timespec start, end;

    if(argc < 2) {
        printf("Code segment size must be specified.\n");
        printf("The size of the code segment is roughly switch_size*89\n");
        exit(1);
    }
    boundary = atoi(argv[1]);

    random_sequence = (uint32_t*)malloc(sizeof(uint32_t)*RNG_LEN);
    for(i=0; i< RNG_LEN; i++)
        random_sequence[i] = rand() % boundary;

    clock_gettime(CLOCK_MONOTONIC, &start);
    __asm__  volatile("lea 0x0(%%rip), %%rax\n\t"
          "movq %%rax, %0\n\t"
          : "=m" (ip)
          :
          : "%rax");
    i = 0;
    min_ip = ip;
    while(1) {
        if (i > N_ITER)
           break;
        opcode = random_sequence[i % RNG_LEN];
        switch(opcode)
        {
            CASE32768(0);
        }
    i++;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0;
    printf("%lu %f %d\n", max_ip - min_ip, time,atoi(argv[1]));
    return 0;
}
