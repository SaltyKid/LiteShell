/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_shell_cfg.h
 * @author  SaltyKid
 * @version 0.1.0
 * @date    2023-06-01
 * @brief   Omit
 *          This file contains:
 *              - Omit
 *
 * -----------------------------------------------------------------------------
 * Change History:
 *   <Date>      |  <Version>  |  <Author>   |  <Description>
 *   2023-06-01  |  v0.1.0     |  SaltyKid   |  Create file
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef __LITE_SHELL_CFG_H__
#define __LITE_SHELL_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ===============================*/
#include "logger.h"

/*========================= PERIPHERAL DECLARATION ==========================*/
#define CONFIG_SHELL_MAX_LINE_LEN 128         /*!< the max bytes limit for a cmd line */
#define CONFIG_SHELL_MAX_ARG_LEN  8           /*!< the max byte limit for a arg */
#define CONFIG_SHELL_MAX_ARGS_NUM 5           /*!< the max num of args supported */
#define CONFIG_SHELL_USER_NAME    "SaltyKid:" /*!< lite shell user name */

/*============================= EXPORTED MACRO ==============================*/
#define SHELL_LOG(fmt, args...)     LOG("[sh]: " fmt, ##args) /*!< lite shell public print */
#define SHELL_DISPLAY(fmt, args...) LOG(fmt, ##args)           /*!< lite shell private print */

#ifdef __cplusplus
}
#endif

#endif
