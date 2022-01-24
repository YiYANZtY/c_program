/*
 * @Author: your name
 * @Date: 2021-12-24 15:52:53
 * @LastEditTime: 2022-01-21 14:30:09
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \ESP32HoloV01\include\HoloDbg.h
 */
#ifndef _HOLODBG_H
#define _HOLODBG_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define HOLODEBUG 1
// #define HOLODISPDEBUG 1
// #define HOLOBATDEBUG 1

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

#endif //_HOLODBG_H