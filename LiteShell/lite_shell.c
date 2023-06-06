/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    lite_shell.c
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

/*============================= INCLUDE FILES ===============================*/
#include "lite_shell_types.h"
#include "lite_shell.h"
#include <string.h>

/*============================ GLOBAL VARIABLES =============================*/
static SHELL_MONITOR_ST shell = {
    .state = SHELL_UNINIT,
};

/*========================== FUNCTION PROTOTYPES ============================*/
static void (*(shell_find_callback(const char *cmd_name)))(int argc, char *argv[]);

/*******************************************************************************
 * @brief        lite shell main processing function
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
void shell_main_task(void)
{
    uint32_t param_cnt = 0, buf_idx = 0, i = 0, data_len = 0;
    void (*p_func)(int argc, char *argv[]) = (void *)0;

    if (SHELL_UNINIT == shell.state)
        shell_init();
    if (SHELL_NEW_CMD == shell.state)
    {
        data_len = shell.curr_line.len > CONFIG_SHELL_MAX_LINE_LEN ? CONFIG_SHELL_MAX_LINE_LEN
                                                                   : shell.curr_line.len;
        memset(shell.argsbuf, 0, sizeof(shell.argsbuf));
        for (i = 0; (0 != shell.curr_line.data[i]) && (i < data_len); i++)
        {
            if ((' ' == shell.curr_line.data[i]) || ('\t' == shell.curr_line.data[i]) ||
                (',' == shell.curr_line.data[i]))
            {
                buf_idx = 0;
                param_cnt++;
            }
            else if (('\n' == shell.curr_line.data[i] || '\r' == shell.curr_line.data[i]))
            {
                if (((i + 1) < data_len) && ('\0' != shell.curr_line.data[i + 1]))
                {
                    if (('\n' == shell.curr_line.data[i + 1] ||
                         '\r' == shell.curr_line.data[i + 1]))
                        i += 1;
                }
                param_cnt++;
                break;
            }
            else
            {
                if (CONFIG_SHELL_MAX_ARG_LEN > buf_idx)
                    shell.argsbuf[param_cnt][buf_idx++] = shell.curr_line.data[i];
            }

            if (CONFIG_SHELL_MAX_ARGS_NUM <= param_cnt)
                break;
        }

        memset(&shell.curr_line.data[0], 0, sizeof(shell.curr_line.data));
        shell.curr_line.len = 0;
        shell.state = SHELL_IDLE;
        if (0 < param_cnt)
        {
            p_func = shell_find_callback(shell.argsbuf[0]);
            if ((void *)0 != p_func)
            {
                p_func(param_cnt, shell.argv);
            }
            else
            {
                SHELL_DISPLAY(CONFIG_SHELL_USER_NAME "~$ ");
            }
        }
    }
}

/******************************************************************************
 * @brief        lite handler
 *
 * @param[in]    data_buf: recv_data to exec
 *
 * @param[in]    data_len: recv_data length
 *
 * @return       None
 ******************************************************************************/
void shell_handler(const char *data_buf, uint32_t data_len)
{
    uint32_t i = 0;

    for (i = 0; (i < data_len) && (SHELL_IDLE == shell.state); i++)
    {
        if ((void *)0 != (data_buf + i))
        {
            shell.curr_line.data[shell.curr_line.len] = data_buf[i];
            shell.curr_line.len += 1;
            if (('\r' == data_buf[i]) || ('\n' == data_buf[i]) ||
                (CONFIG_SHELL_MAX_LINE_LEN <= shell.curr_line.len))
            {
                if ('\n' != shell.curr_line.data[CONFIG_SHELL_MAX_LINE_LEN - 1])
                    shell.curr_line.data[CONFIG_SHELL_MAX_LINE_LEN - 1] = '\0';
                shell.state = SHELL_NEW_CMD;
            }
        }
        else
            break;
    }
}

/*******************************************************************************
 * @brief        lite shell init
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
void shell_init(void)
{
    uint32_t i = 0;

    for (i = 0; i < CONFIG_SHELL_MAX_ARGS_NUM; i++) shell.argv[i] = shell.argsbuf[i];
    shell.state = SHELL_INIT_OK;
}

/*******************************************************************************
 * @brief        lite shell show a list of all commands.
 *
 * @param[in]    None
 *
 * @return       None
 ******************************************************************************/
void shell_help(int argc, char *argv[])
{
    uint32_t i = 0;
    (void)argc;
    (void)argv;

    while ((void *)0 != shell_command_list[i].name)
    {
        SHELL_DISPLAY("%-10s -- %s \r\n",
                      shell_command_list[i].name,
                      ((void *)0 == shell_command_list[i].description
                           ? shell_command_list[i].name
                           : shell_command_list[i].description));
        i++;
    }
}

/******************************************************************************
 * @brief        get the callback func
 *
 * @param[in]    cmd_name: str
 *
 * @return       p_func: a function pointer
 ******************************************************************************/
static void (*(shell_find_callback(const char *cmd_name)))(int argc, char *argv[])
{
    uint32_t i = 0;
    void (*p_func)(int argc, char *argv[]) = (void *)0;

    while ((void *)0 != shell_command_list[i].name)
    {
        if (0 == strncmp(cmd_name, shell_command_list[i].name, CONFIG_SHELL_MAX_ARG_LEN))
        {
            p_func = shell_command_list[i].func;
            break;
        }
        i++;
    }

    return p_func;
}

/******************************************************************************
 * @brief        judge the numeric base
 *
 * @param[in]    p_arg: a point to parameters to be resolved
 *
 * @return       (SHELL_NUM_TYPE_EM ) num type
 ******************************************************************************/
static SHELL_NUM_TYPE_EM shell_ext_numtype(char *p_arg)
{
    char *p = p_arg;
    SHELL_NUM_TYPE_EM type = NUM_TYPE_DEC;

    if ((*p == '0') && ((*(p + 1) == 'x') || (*(p + 1) == 'X')))
    {
        type = NUM_TYPE_HEX;
    }
    else if ((*p == '0') && ((*(p + 1) == 'b') || (*(p + 1) == 'B')))
    {
        type = NUM_TYPE_BIN;
    }
    else if (*p == '0')
    {
        type = NUM_TYPE_OCT;
    }

    while (*p++)
    {
        if (*p == '.' && *(p + 1) != 0)
        {
            type = NUM_TYPE_FLOAT;
            break;
        }
    }

    return type;
}

/******************************************************************************
 * @brief        char to num
 *
 * @param[in]    ch: a char
 *
 * @return       (char ) num
 ******************************************************************************/
static char shell_ext_tonum(char ch)
{
    if ((ch >= '0') && (ch <= '9'))
    {
        return ch - '0';
    }
    else if ((ch >= 'a') && (ch <= 'f'))
    {
        return ch - 'a' + 10;
    }
    else if ((ch >= 'A') && (ch <= 'F'))
    {
        return ch - 'A' + 10;
    }
    else
    {
        return 0;
    }
}

/******************************************************************************
 * @brief        parse char
 *
 * @param[in]    p_arg: a point to parameters to be resolved
 *
 * @return       (char ) parsed char
 ******************************************************************************/
static char shell_ext_parsech(char *string)
{
    char *p = string + 1;
    char value = 0;

    if (*p == '\\')
    {
        switch (*(p + 1))
        {
        case 'b': value = '\b'; break;
        case 'r': value = '\r'; break;
        case 'n': value = '\n'; break;
        case 't': value = '\t'; break;
        case '0': value = 0; break;
        default: value = *(p + 1); break;
        }
    }
    else
    {
        value = *p;
    }

    return value;
}

/******************************************************************************
 * @brief        parse string
 *
 * @param[in]    p_arg: a point to parameters to be resolved
 *
 * @return       (char *) parsed string
 ******************************************************************************/
static char *shell_ext_parsestr(char *p_arg)
{
    char *p = p_arg;
    unsigned short index = 0;

    if (*p_arg == '\"')
    {
        p = ++p_arg;
    }

    while (*p)
    {
        if (*p == '\\')
        {
            *(p_arg + index) = shell_ext_parsech(p - 1);
            p++;
        }
        else if (*p == '\"')
        {
            *(p_arg + index) = 0;
        }
        else
        {
            *(p_arg + index) = *p;
        }
        p++;
        index++;
    }
    *(p_arg + index) = 0;

    return p_arg;
}

/******************************************************************************
 * @brief        parse numeric parameter
 *
 * @param[in]    p_arg: a point to parameters to be resolved
 *
 * @return       (size_t) parsed number
 ******************************************************************************/
static size_t shell_ext_parsenum(char *p_arg)
{
    SHELL_NUM_TYPE_EM type = NUM_TYPE_DEC;
    uint8_t radix = 10, offset = 0;
    char *p = p_arg;
    char sign = 1;
    size_t value_int = 0, devide = 0;
    float value_float = 0.0;

    if (*p_arg == '-')
    {
        sign = -1;
    }

    type = shell_ext_numtype(p_arg + ((sign == -1) ? 1 : 0));

    switch ((char)type)
    {
    case NUM_TYPE_HEX:
        radix = 16;
        offset = 2;
        break;

    case NUM_TYPE_OCT:
        radix = 8;
        offset = 1;
        break;

    case NUM_TYPE_BIN:
        radix = 2;
        offset = 2;
        break;

    default: break;
    }

    p = p_arg + offset + ((sign == -1) ? 1 : 0);

    while (*p)
    {
        if (*p == '.')
        {
            devide = 1;
            p++;
            continue;
        }
        value_int = value_int * radix + shell_ext_tonum(*p);
        devide *= 10;
        p++;
    }
    if (type == NUM_TYPE_FLOAT && devide != 0)
    {
        value_float = (float)value_int / (float)devide * sign;
        return *(size_t *)&value_float;
    }
    else
    {
        return value_int * sign;
    }
}

/******************************************************************************
 * @brief        parse args
 *
 * @param[in]    p_arg: a point to args to be resolved
 *
 * @return       (size_t) parsed result
 ******************************************************************************/
size_t shell_arg_parse(char *p_arg)
{
    if (*p_arg == '\'' && *(p_arg + 1))
    {
        return (size_t)shell_ext_parsech(p_arg);
    }
    else if (*p_arg == '-' || (*p_arg >= '0' && *p_arg <= '9'))
    {
        return (size_t)shell_ext_parsenum(p_arg);
    }
    else if (*p_arg)
    {
        return (size_t)shell_ext_parsestr(p_arg);
    }

    return 0;
}
