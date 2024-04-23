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
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "lite_shell.h"

/*============================ GLOBAL VARIABLES ==============================*/
// #define CH_INPUT_MODE

/*========================== FUNCTION PROTOTYPES =============================*/
static void *readline_test_thread(void *p_arg);

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
int main(int argc, char *argv[])
{
    bool run_ok = false;
    pthread_t rdl_th;

    shell_init();
    run_ok = true;
    pthread_create(&rdl_th, NULL, readline_test_thread, &run_ok);

    while (true == run_ok)
    {
        shell_main_task();
    }

    pthread_join(rdl_th, NULL);

    return 0;
}

/*******************************************************************************
 * @brief        None
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
static void *readline_test_thread(void *p_arg)
{
    char cmd_line[256], ch;
    int ch_idx = 0;
    bool *run_ok = (bool *)p_arg;

    while (true == *run_ok)
    {
        ch = getc(stdin);
        cmd_line[ch_idx++] = ch;
        if (('\r' == ch) || ('\n' == ch) || (256 <= ch_idx))
        {
            if (0 == strncmp("llstop", cmd_line, 6))
            {
                *run_ok = false;
                break;
            }
            shell_handler(&cmd_line[0], ch_idx);
            ch_idx = 0;
            memset(cmd_line, 0, 256);
        }
    }

    return 0;
}

