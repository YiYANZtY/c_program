
#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cpluscplus
extern "C" {
#endif
#include <stdbool.h>

#define KEY_C1_Pin GPIO_PIN_15
#define KEY_C1_GPIO_Port GPIOB
#define KEY_C2_Pin GPIO_PIN_1
#define KEY_C2_GPIO_Port GPIOF
#define KEY_C3_Pin GPIO_PIN_13
#define KEY_C3_GPIO_Port GPIOB

//#include "gpio.h"// FIXME
#include "../utils.h"

typedef enum {
    KEY_ID_NONE  = 0,
    KEY_ID_START = 1,  // start
    KEY_ID_PREV  = 1,
    KEY_ID_OK    = 2,
    KEY_ID_NEXT  = 3,
    KEY_ID_END   = 3,  // end
} key_id_t;

typedef struct {
    bool cur;
    bool last;
} key_state_t;

extern key_state_t keys[KEY_ID_END];
extern key_id_t    key_id;

void     key_init(void);
key_id_t key_scan(void);
bool     key_val(key_id_t id);

#ifdef __cpluscplus
}
#endif

#endif
