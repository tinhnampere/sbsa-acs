/** @file
 * Copyright (c) 2016-2020, 2022 Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **/


#ifndef __SBSA_APP_LINUX_H__
#define __SBSA_APP_LINUX_H__


#define SBSA_APP_VERSION_MAJOR  6
#define SBSA_APP_VERSION_MINOR  1
#define SBSA_APP_VERSION_SUBMINOR  0

#include "sbsa_drv_intf.h"

typedef unsigned long int addr_t;
typedef unsigned char     char8_t;

int
execute_tests_pcie(int num_pe, int level, unsigned int print_level);

int
execute_tests_exerciser(int num_pe, int level, unsigned int print_level);

#endif
