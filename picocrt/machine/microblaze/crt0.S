/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright © 2023 Keith Packard
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

	.text
	.section	.text.init.enter
	.globl	_start
	.ent	_start
	.type	_start, @function
	.align	4
_start:
	bri	_start1
	. = _start + 0x8
	bri	_user_except
	. = _start + 0x10
	bri	_interrupt
	. = _start + 0x20
	bri	_hw_except
_user_except:
#ifdef CRT0_SEMIHOST
	bri _semihost_trap
#else
	bri	_user_except
#endif
_interrupt:
	bri	_interrupt
_hw_except:
#ifdef CRT0_SEMIHOST
	bri _semihost_trap
#else
	bri	_hw_except
#endif
_start1:
  la	r1, r0, __stack-16
	addi	r15, r0, 0
	bri	_cstart
	nop
	.end	_start


#ifdef CRT0_SEMIHOST
	.globl	_semihost_trap
	.ent	_semihost_trap
	.type	_semihost_trap, @function
	.align	4
	.extern _semihost_exception_coredump
_semihost_trap:
	/* Offsets here mumst match trap.c indexes */
	/* Stash r11 beforehand */
	swi r11, r0, _semihost_exception_coredump + (11 * 4)

	/* Stack MSR using r11(temp1) */
	mfs r11, rmsr
	swi r11, r0, _semihost_exception_coredump + (0 * 4)

	swi r1, r0, _semihost_exception_coredump + (1 * 4)
	/* Save the registers */
	swi r2, r0, _semihost_exception_coredump + (2 * 4)
	swi r3, r0, _semihost_exception_coredump + (3 * 4)
	swi r4, r0, _semihost_exception_coredump + (4 * 4)
	swi r5, r0, _semihost_exception_coredump + (5 * 4)
	swi r6, r0, _semihost_exception_coredump + (6 * 4)
	swi r7, r0, _semihost_exception_coredump + (7 * 4)
	swi r8, r0, _semihost_exception_coredump + (8 * 4)
	swi r9, r0, _semihost_exception_coredump + (9 * 4)
	swi r10, r0, _semihost_exception_coredump +	(10 * 4)
	/* Skip r11 because we stashed it first */
	swi r12, r0, _semihost_exception_coredump +	(12 * 4)
	swi r13, r0, _semihost_exception_coredump +	(13 * 4)
	swi r14, r0, _semihost_exception_coredump +	(14 * 4)
	swi r15, r0, _semihost_exception_coredump +	(15 * 4)
	swi r16, r0, _semihost_exception_coredump +	(16 * 4)
	swi r17, r0, _semihost_exception_coredump +	(17 * 4)
	swi r18, r0, _semihost_exception_coredump +	(18 * 4)
	swi r19, r0, _semihost_exception_coredump +	(19 * 4)
	swi r20, r0, _semihost_exception_coredump +	(20 * 4)
	swi r21, r0, _semihost_exception_coredump +	(21 * 4)
	swi r22, r0, _semihost_exception_coredump +	(22 * 4)
	swi r23, r0, _semihost_exception_coredump +	(23 * 4)
	swi r24, r0, _semihost_exception_coredump +	(24 * 4)
	swi r25, r0, _semihost_exception_coredump +	(25 * 4)
	swi r26, r0, _semihost_exception_coredump +	(26 * 4)
	swi r27, r0, _semihost_exception_coredump +	(27 * 4)
	swi r28, r0, _semihost_exception_coredump +	(28 * 4)
	swi r29, r0, _semihost_exception_coredump +	(29 * 4)
	swi r30, r0, _semihost_exception_coredump +	(30 * 4)
	swi r31, r0, _semihost_exception_coredump +	(31 * 4)

	mfs r11, resr
	swi r11, r0, _semihost_exception_coredump + (32 * 4)
	mfs r11, rear
	swi r11, r0, _semihost_exception_coredump + (33 * 4)
	mfs r11, redr
	swi r11, r0, _semihost_exception_coredump + (34 * 4)

	brai _semihost_ctrap
#endif
