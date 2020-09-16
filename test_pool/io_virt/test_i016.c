/** @file
 * Copyright (c) 2020, Arm Limited or its affiliates. All rights reserved.
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

#include "val/include/sbsa_avs_val.h"
#include "val/include/val_interface.h"

#include "val/include/sbsa_avs_smmu.h"
#include "val/include/sbsa_avs_pcie.h"
#include "val/include/sbsa_avs_pe.h"

#define TEST_NUM   (AVS_SMMU_TEST_NUM_BASE + 16)
#define TEST_DESC  "Check SMMU DVM Capability Support "

static
void
payload()
{

  uint64_t data;
  uint64_t data_pe_tlb, data_ril;
  uint32_t num_smmu;
  uint32_t index = val_pe_get_index_mpid(val_pe_get_mpid());

  if (g_sbsa_level < 6) {
      val_set_status(index, RESULT_SKIP(g_sbsa_level, TEST_NUM, 01));
      return;
  }

  data = val_pcie_get_info(PCIE_INFO_NUM_ECAM, 0);

  if (data == 0) {
      val_print(AVS_PRINT_WARN, "\n       PCIe Subsystem not  discovered   ", 0);
      val_set_status(index, RESULT_SKIP(g_sbsa_level, TEST_NUM, 02));
      return;
  }

  num_smmu = val_smmu_get_info(SMMU_NUM_CTRL, 0);

  if (num_smmu == 0) {
      val_print(AVS_PRINT_ERR, "\n       No SMMU Controllers are discovered ", 0);
      val_set_status(index, RESULT_SKIP(g_sbsa_level, TEST_NUM, 03));
      return;
  }

  data_pe_tlb = VAL_EXTRACT_BITS(val_pe_reg_read(ID_AA64ISAR0_EL1), 56, 59);
  if (data_pe_tlb != 0x2) {
      val_print(AVS_PRINT_WARN, "\n       TLB Range Invalid Not Supported   ", 0);
      val_set_status(index, RESULT_SKIP(g_sbsa_level, TEST_NUM, 04));
      return;
  }

  while (num_smmu--) {
      if (val_smmu_get_info(SMMU_CTRL_ARCH_MAJOR_REV, num_smmu) == 2) {
          val_print(AVS_PRINT_WARN, "\n       Not valid for SMMU v2           ", 0);
          val_set_status(index, RESULT_SKIP(g_sbsa_level, TEST_NUM, 05));
          return;
      }

      data_ril = VAL_EXTRACT_BITS(val_smmu_read_cfg(SMMUv3_IDR3, num_smmu), 10, 10);

      /* If PE TLB Range Invalidation then SMMU_IDR3.RIL = 0b1 */
      if (data_pe_tlb == 0x2) {
          if (data_ril != 0x1) {
              val_set_status(index, RESULT_FAIL(g_sbsa_level, TEST_NUM, 01));
              return;
          }
      }
  }

  val_set_status(index, RESULT_PASS(g_sbsa_level, TEST_NUM, 01));
}

uint32_t
i016_entry(uint32_t num_pe)
{

  uint32_t status = AVS_STATUS_FAIL;

  num_pe = 1;  //This test is run on single processor

  status = val_initialize_test(TEST_NUM, TEST_DESC, num_pe, g_sbsa_level);
  if (status != AVS_STATUS_SKIP)
      val_run_test_payload(TEST_NUM, num_pe, payload, 0);

  /* get the result from all PE and check for failure */
  status = val_check_for_error(TEST_NUM, num_pe);

  val_report_status(0, SBSA_AVS_END(g_sbsa_level, TEST_NUM));

  return status;
}
