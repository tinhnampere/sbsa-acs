/** @file
 * Copyright (c) 2016-2018, Arm Limited and Contributors. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __SBSA_AVS_GIC_H__
#define __SBSA_AVS_GIC_H__

#define GICD_ISENABLER      0x100
#define GICD_ICENABLER      0x180
#define GICD_ISPENDR        0x200
#define GICD_ISACTIVER0     0x300
#define GICD_ICPENDR0       0x280
#define GICD_ICACTIVER0     0x380
#define GICD_ICFGR          0xC00
#define GICD_IROUTER        0x6000

#define GICD_ICFGR_INTR_STRIDE          16 /* (32/2) Interrupt per Register */
#define GICD_ICFGR_INTR_CONFIG1(intid)  ((1+int_id*2) % 32) /* Bit Config[2x+1] for config type level/edge */

uint32_t
g001_entry(uint32_t num_pe);
uint32_t
g002_entry(uint32_t num_pe);
uint32_t
g003_entry(uint32_t num_pe);
uint32_t
g004_entry(uint32_t num_pe);

uint32_t
val_get_max_intid(void);

addr_t
val_get_gicd_base(void);
#endif
