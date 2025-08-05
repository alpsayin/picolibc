/*
 * Copyright (c) 2023 Advanced Micro Devices, Inc. (AMD)
 * Copyright (c) 2023 Alp Sayin <alpsayin@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef CRT0_SEMIHOST
#include <unistd.h>
#include <stdio.h>

/* Used by assembly routine _semihost_exception_handler to store sp */
unsigned _semihost_exception_coredump[35];

__attribute__((__noreturn__)) void _semihost_ctrap()
{
	/* Indexes here must match offsets in crt0.S */
	printf("MSR:\t0x%08x\t(exc)\n", _semihost_exception_coredump[0]);
	printf("r1:\t0x%08x\t(sp)\n", _semihost_exception_coredump[1]);
	printf("r2:\t0x%08x\t(small data area)\n", _semihost_exception_coredump[2]);
	printf("r3:\t0x%08x\t(retval 1)\n", _semihost_exception_coredump[3]);
	printf("r4:\t0x%08x\t(retval 2)\n", _semihost_exception_coredump[4]);
	printf("r5:\t0x%08x\t(arg1)\n", _semihost_exception_coredump[5]);
	printf("r6:\t0x%08x\t(arg2)\n", _semihost_exception_coredump[6]);
	printf("r7:\t0x%08x\t(arg3)\n", _semihost_exception_coredump[7]);
	printf("r8:\t0x%08x\t(arg4)\n", _semihost_exception_coredump[8]);
	printf("r9:\t0x%08x\t(arg5)\n", _semihost_exception_coredump[9]);
	printf("r10:\t0x%08x\t(arg6)\n", _semihost_exception_coredump[10]);
	printf("r11:\t0x%08x\t(temp1)\n", _semihost_exception_coredump[11]);
	printf("r12:\t0x%08x\t(temp2)\n", _semihost_exception_coredump[12]);
	printf("r13:\t0x%08x\t(rw small data area)\n", _semihost_exception_coredump[13]);
	printf("r14:\t0x%08x\t(return from interrupt)\n", _semihost_exception_coredump[14]);
	printf("r15:\t0x%08x\t(return from subroutine)\n", _semihost_exception_coredump[15]);
	printf("r16:\t0x%08x\t(return from trap)\n", _semihost_exception_coredump[16]);
	printf("r17:\t0x%08x\t(return from exception)\n", _semihost_exception_coredump[17]);
	printf("r18:\t0x%08x\t(compiler/assembler temp)\n", _semihost_exception_coredump[18]);
	printf("r19:\t0x%08x\t(global offset table ptr)\n", _semihost_exception_coredump[19]);
	printf("r20:\t0x%x\n", _semihost_exception_coredump[20]);
	printf("r21:\t0x%x\n", _semihost_exception_coredump[21]);
	printf("r22:\t0x%x\n", _semihost_exception_coredump[22]);
	printf("r23:\t0x%x\n", _semihost_exception_coredump[23]);
	printf("r24:\t0x%x\n", _semihost_exception_coredump[24]);
	printf("r25:\t0x%x\n", _semihost_exception_coredump[25]);
	printf("r26:\t0x%x\n", _semihost_exception_coredump[26]);
	printf("r27:\t0x%x\n", _semihost_exception_coredump[27]);
	printf("r28:\t0x%x\n", _semihost_exception_coredump[28]);
	printf("r29:\t0x%x\n", _semihost_exception_coredump[29]);
	printf("r30:\t0x%x\n", _semihost_exception_coredump[30]);
	printf("r31:\t0x%x\n", _semihost_exception_coredump[31]);


	printf("ESR:\t0x%08x\n", _semihost_exception_coredump[32]);
	printf("EAR:\t0x%x\n", _semihost_exception_coredump[33]);
	printf("EDR:\t0x%x\n", _semihost_exception_coredump[34]);

	_exit(1);
}

#endif
