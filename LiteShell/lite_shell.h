/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_shell.h
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
#ifndef __LITE_SHELL_H__
#define __LITE_SHELL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ================================*/
#include <stdint.h>
#include <stddef.h>

/*========================== FUNCTION PROTOTYPES =============================*/

extern void shell_init(void);
extern void shell_main_task(void);
extern void shell_handler(const char *data_buf, uint32_t data_len);
extern size_t shell_arg_parse(char *p_arg);
extern void shell_help(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif
