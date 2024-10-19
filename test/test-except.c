/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2022 Keith Packard
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>

int
main(void)
{
    printf("executing invalid instructions\n");

    /*
     * ARM architecture reference says these are mostly reserved for
     * undefined instructions and should raise exceptions
     */
#ifdef __arm__

#ifdef __thumb__
    __asm__(".inst.n 0xde00");
#else
    __asm__(".inst 0xe7f000f0");
#endif

#elif defined(__riscv)

    __asm__(".word 0x00000000");

#elif defined(__aarch64__)

    __asm__(".word 0x00000000");

#elif defined(__RX__)

    __asm__(".word 0xffffffff");

#elif defined(__x86_64__) || defined(__i386__)

    __asm__("ud2");
#elif defined(__MICROBLAZE__)

    unsigned int pvr_value;

    /* Read processor version register 0 */
    __asm__ volatile ("mfs %0, rpvr0": "=r" (pvr_value));

    /* If PVR reads all zeroes, no PVR is implemented.
     * Bit 0 tells if PVR[1-12] is implemented.
     */
    if (pvr_value == 0 || ((pvr_value & 1) == 0)) {
        /* Can't tell if processor generates exceptions
         * for any illegal opcode; play it safe and return.
         */
        goto no_invalid_exception;
    }

    /* Read processor version register 2 */
    __asm__ volatile ( "mfs %0, rpvr2" : "=r" (pvr_value));

    /* Bit 27 tells if processor generates exceptions for
     * bad instructions or if it treats them as NOPs.
     */
    if (pvr_value & (1 << 27)) {
        /* All zeroes will generate illegal-opcode exception */
        __asm__ volatile (".word 0x00000000");
    }
    else {
        /* All undefined instructions are treated as NOPs */
        goto no_invalid_exception;
    }

#else

goto no_invalid_exception;

#endif

    printf("ERROR: invalid instruction worked\n");
    return 0;

no_invalid_exception:
    printf("no invalid instruction defined for target\n");
    return 77;

}
