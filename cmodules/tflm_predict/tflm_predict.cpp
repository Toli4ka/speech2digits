#include "tflm_predict.h"
// #include "tensorflow/lite/micro/micro_op_resolver.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
// #include "tensorflow/lite/version.h"
#include "speech2digits_model.h"

constexpr int kTensorArenaSize = 16 * 1024;  // How much do i need?
uint8_t tensor_arena[kTensorArenaSize];

extern "C" {

// Initialize interpreter and model
const tflite::Model* model = nullptr;
static tflite::MicroInterpreter* interpreter = nullptr;
static TfLiteTensor* input = nullptr;
static TfLiteTensor* output = nullptr;

void tflm_init() {
    // Register only the ops used by your model: FullyConnected, Reshape, Softmax
    static tflite::MicroMutableOpResolver<3> resolver;
    resolver.AddFullyConnected();
    resolver.AddReshape();
    resolver.AddSoftmax();

    model = tflite::GetModel("g_speech2digits_model");
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize);
    interpreter = &static_interpreter;
    interpreter = new tflite::MicroInterpreter(
        model, resolver, tensor_arena, kTensorArenaSize);
    interpreter->AllocateTensors();
    input = interpreter->input(0);
    output = interpreter->output(0);
}

// Run inference
int tflm_infer(const int8_t* input_data, int input_len) {
    // copy input data to the input tensor
    for (int i = 0; i < input_len; ++i) {
        input->data.int8[i] = input_data[i];
    }
    interpreter->Invoke();
    // Find argmax
    int max_idx = 0;
    int8_t max_val = output->data.int8[0];
    for (int i = 1; i < output->dims->data[1]; ++i) {
        if (output->data.int8[i] > max_val) {
            max_val = output->data.int8[i];
            max_idx = i;
        }
    }
    return max_idx;
}

}