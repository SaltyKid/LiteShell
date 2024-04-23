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
#include "lite_shell_cfg.h"

/*=========================== STRUCTURE DEFINES =============================*/

typedef struct SHELL_CMD_TYPE_STRU
{
    const char *name;
    void (*func)(int argc, char *argv[]);
    const char *description;
} SHELL_CMD_TYPE_ST, lsh_tbl_t;

/*============================= EXPORTED MACRO ===============================*/
#if defined(__TASKING__)
#define CMD_LINK_ENTRY_DECLARE(_section, _class, _type, _id)                   \
    _type lsh##_##_id                                                          \
        __attribute__((protect, section("." #_section "." #_class "." #_id)))
#elif (defined(__ghs__) || defined(__GNUC__))
#define CMD_LINK_ENTRY_DECLARE(_section, _class, _type, _id)                   \
    _type lsh##_##_id                                                          \
        __attribute__((section("." #_section "." #_class "." #_id)))
#else
#define CMD_LINK_ENTRY_DECLARE(_section, _class, _type, _id)
#endif

#define CMD_MKENT_COMPLETE(_cmd, _callback, _help_info)                        \
    {                                                                          \
        (char *)#_cmd, _callback, (char *)_help_info                           \
    }

#define SHELL_CMD_REGISTER(_cmd, _callback, _help_info)                        \
    CMD_LINK_ENTRY_DECLARE(rodata, lite_shell, lsh_tbl_t, _cmd) =           \
        CMD_MKENT_COMPLETE(_cmd, _callback, _help_info)

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
