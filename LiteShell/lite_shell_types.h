/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_shell_types.h
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
#ifndef __LITE_SHELL_TYPES_H__
#define __LITE_SHELL_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ===============================*/
#include <stdint.h>
#include "lite_shell_cfg.h"

/*============================ TYPE DEFINITIONS =============================*/

/*!< the max bytes limit for a cmd line */
#ifndef CONFIG_SHELL_MAX_LINE_LEN
#define CONFIG_SHELL_MAX_LINE_LEN 128
#endif

/*!< the max byte limit for a arg */
#ifndef CONFIG_SHELL_MAX_ARG_LEN
#define CONFIG_SHELL_MAX_ARG_LEN 8
#endif

/*!< the max num of args supported */
#ifndef CONFIG_SHELL_MAX_ARGS_NUM
#define CONFIG_SHELL_MAX_ARGS_NUM 5
#endif

/*!< lite shell user name */
#ifndef CONFIG_SHELL_USER_NAME
#define CONFIG_SHELL_USER_NAME "SalyKid:"
#endif

/*!< lite shell public print */
#ifndef SHELL_LOG
#define SHELL_LOG(fmt, args...)
#endif

/*!< lite shell private print */
#ifndef SHELL_DISPLAY
#define SHELL_DISPLAY(fmt, args...)
#endif

/*============================= ENUM DEFINES ================================*/

typedef enum SHELL_NUM_TYPE_ENUM
{
    NUM_TYPE_DEC,  /*<! dec num */
    NUM_TYPE_BIN,  /*<! binary num */
    NUM_TYPE_OCT,  /*<! oct num */
    NUM_TYPE_HEX,  /*<! hex num */
    NUM_TYPE_FLOAT /*<! float num */
} SHELL_NUM_TYPE_EM;

/*!< lite shell runtime status */
typedef enum SHELL_STATE_ENUM
{
    SHELL_UNINIT = 0,
    SHELL_INIT_OK = 1,
    SHELL_IDLE = 1,
    SHELL_BUSY,
    SHELL_NEW_CMD
} SHELL_STATE_EM;

/*=========================== STRUCTURE DEFINES =============================*/

typedef struct SHELL_CMD_TYPE_STRU
{
    const char *name;
    void (*func)(int argc, char *argv[]);
    const char *description;
} SHELL_CMD_TYPE_ST;

typedef struct SHELL_MONITOR_STRU
{
    SHELL_STATE_EM state;
    struct
    {
        uint32_t len;
        char data[CONFIG_SHELL_MAX_LINE_LEN];
    } curr_line;
    char argsbuf[CONFIG_SHELL_MAX_ARGS_NUM][CONFIG_SHELL_MAX_ARG_LEN + 1];
    char *argv[CONFIG_SHELL_MAX_ARGS_NUM];
} SHELL_MONITOR_ST;

/*============================ GLOBAL VARIABLES =============================*/
extern const SHELL_CMD_TYPE_ST shell_command_list[];

#ifdef __cplusplus
}
#endif

#endif
