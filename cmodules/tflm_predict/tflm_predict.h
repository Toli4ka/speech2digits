#ifndef TFLM_PREDICT_H_
#define TFLM_PREDICT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void tflm_init(void);
int tflm_infer(const int8_t* input_data, int input_len);

#ifdef __cplusplus
}
#endif

#endif  // TFLM_PREDICT_H_