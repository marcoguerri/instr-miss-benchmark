/*
 * Branch Target Prediction benchmark
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
#include <unistd.h>
#include <time.h>
#include <memory.h>

#define CASE(N) \
            case N: \
                flag[N] = N; \
                break;

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

#define SWITCH_SIZE 512

int main(int argc, char *argv[])
{
    int c;
    uint32_t i = 0, sequence_len = 128;
    uint8_t r = 0;
    uint32_t opcode, *sequence;
    register uint32_t *flag;
    uint32_t v;
    flag = (uint32_t*)malloc(sizeof(uint32_t) * SWITCH_SIZE);

    /* 
     * -r flag generates a random opcode sequence of lenght defined by -l.
     *  If -r is not specified, then the opcode sequence is sequential 
     */
    while ( (c = getopt(argc, argv, "rl:")) != -1) {
        switch (c) {
        case 'r':
            r = 1;
            break;
        case 'l':
            sequence_len = atoi(optarg);
            break;
        default: 
            break;
        }
    }
    
    sequence = (uint32_t*)malloc(sizeof(uint32_t) * sequence_len);
    if(r)
    {
        for(i=0; i< sequence_len; i++)
            sequence[i] = rand() % SWITCH_SIZE;
    }
    else
    {
        for(i=0; i< sequence_len; i++)
            sequence[i] = i % SWITCH_SIZE;
    }

    while(1) {
        if (i > 0xFFFFFFF)
           break;
        else {
                opcode = sequence[i % sequence_len];
                switch(opcode) {
                        CASE512(0)
                }
                i++;
         }
    }
    return 0;
}
