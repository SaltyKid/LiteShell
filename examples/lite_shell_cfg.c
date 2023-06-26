/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_shell_cfg.c
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

/*============================= INCLUDE FILES ================================*/
#include "lite_shell_types.h"
#include "lite_shell.h"

/*============================ GLOBAL VARIABLES =============================*/

static void shell_test_str(int argc, char *argv[]);
static void shell_test_ch(int argc, char *argv[]);
static void shell_test_num(int argc, char *argv[]);
static void shell_test_float(int argc, char *argv[]);

const SHELL_CMD_TYPE_ST shell_command_list[] = {
    {"getstr", shell_test_str, "get a string and print it"},
    {"getch", shell_test_ch, "get a char and print it"},
    {"getval", shell_test_num, "get a num and print it"},
    {"getfloat", shell_test_float, "get a float num and print it"},
    {"help", shell_help, "Print a list of all commands."},
    {(void *)0, (void *)0, (void *)0},
};

/*========================== FUNCTION PROTOTYPES ============================*/

/******************************************************************************
 * @brief        shell test str (ex: getstr asdf )
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void shell_test_str(int argc, char *argv[])
{
    (void)argc;
    SHELL_LOG("shell get str { %s }\r\n", (char *)shell_arg_parse(argv[1]));
}

/******************************************************************************
 * @brief        shell test char (ex: getch 'a )
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void shell_test_ch(int argc, char *argv[])
{
    (void)argc;
    SHELL_LOG("shell get ch { %c }\r\n", (char)shell_arg_parse(argv[1]));
}

/******************************************************************************
 * @brief        shell test num (ex: getval 16 / 0x10 / 020 / 0b00010000)
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void shell_test_num(int argc, char *argv[])
{
    (void)argc;
    SHELL_LOG("shell get val { %d }\r\n", (int)shell_arg_parse(argv[1]));
}

/*******************************************************************************
 * @brief        shell test float (ex: getfloat 1.0)
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void shell_test_float(int argc, char *argv[])
{
    (void)argc;
    union
    {
        size_t int_val;
        float flt_val;
    } num;

    num.int_val = shell_arg_parse(argv[1]);
    SHELL_LOG("shell get float { %f } \r\n", num.flt_val);
}