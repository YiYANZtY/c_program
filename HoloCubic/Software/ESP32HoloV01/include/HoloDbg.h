/*
 * @Author: your name
 * @Date: 2021-12-24 15:52:53
 * @LastEditTime: 2021-12-24 16:21:49
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloDbg.h
 */
#ifndef HOLODBG_H
#define HOLODBG_H

#include "HoloCfg.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef HOLODEBUG
    #define DebugBegin(baud_rate)     Serial.begin(baud_rate)
    #define DebugPrintln(message)     Serial.println(message)
    #define DebugPrint(message)       Serial.print(message)
#else
    #define DebugBegin(baud_rate)
    #define DebugPrintln(message)
    #define DebugPrint(message)
#endif //End HOLODEBUG

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //HOLODBG_H