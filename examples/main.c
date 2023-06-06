/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    main.c
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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lite_shell.h"

/*============================ GLOBAL VARIABLES ==============================*/
// #define CH_INPUT_MODE

/*========================== FUNCTION PROTOTYPES =============================*/

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
int main(int argc, char *argv[])
{
    char cmd_line[256], ch;
    int ch_idx = 0;

    while (1)
    {
        ch = getc(stdin);
        cmd_line[ch_idx++] = ch;
        if (('\r' == ch) || ('\n' == ch) || (256 <= ch_idx))
        {
            if (0 == strncmp("llstop", cmd_line, 6))
                break;
#ifndef CH_INPUT_MODE
            shell_handler(&cmd_line[0], ch_idx);
            shell_main_task();
#endif
            ch_idx = 0;
            memset(cmd_line, 0, 256);
        }
#ifdef CH_INPUT_MODE
        shell_handler(&ch, 1);
        shell_main_task();
#endif
    };

    return 0;
}
