/*******************************************************************************
 * Copyleft (c) 2023 SaltyKid 1035183478@qq.com
 *
 * Copyright description information omitted.
 *
 * @file    logger.h
 * @author  SaltyKid
 * @version 0.1.0
 * @date    2023-05-26
 * @brief   Omit
 *          This file contains:
 *              - Omit
 *
 * -----------------------------------------------------------------------------
 * Change History:
 *   <Date>      |  <Version>  |  <Author>   |  <Description>
 *   2023-05-26  |  v0.1.0     |  SaltyKid   |  Create file
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#ifndef __LOGGER_H__
#define __LOGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ================================*/
#include <stdio.h>
#include <string.h>

/*========================= PERIPHERAL DECLARATION ===========================*/
#if defined(__WIN32)
#define FILE_NAME(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#else
#define FILE_NAME(x) strrchr(x, '/') ? strrchr(x, '/') + 1 : x
#endif

/*============================= EXPORTED MACRO ===============================*/
#define LOG(...)                                                               \
    do                                                                         \
    {                                                                          \
        printf(__VA_ARGS__);                                                   \
        fflush(stdout);                                                        \
    } while (0);

#define LOG_I(fmt, a...) LOG("I " fmt, ##a)
#define LOG_D(fmt, a...) LOG("D " fmt, ##a)
#define LOG_W(fmt, a...) LOG("W " fmt, ##a)
#define LOG_E(fmt, a...) LOG("E " fmt, ##a)
#define LOG_F(fmt, a...) LOG("F " fmt, ##a)

#ifdef __cplusplus
}
#endif

#endif
