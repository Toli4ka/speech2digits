extern "C" {
#include "py/obj.h"
#include "py/runtime.h"
#include "tflm_predict.h"

static mp_obj_t mp_tflm_init(void) {
    tflm_init();
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(mp_tflm_init_obj, mp_tflm_init);

static mp_obj_t mp_tflm_infer(mp_obj_t input_obj) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(input_obj, &bufinfo, MP_BUFFER_READ);
    int result = tflm_infer((const int8_t*)bufinfo.buf, bufinfo.len);
    return mp_obj_new_int(result);
}
static MP_DEFINE_CONST_FUN_OBJ_1(mp_tflm_infer_obj, mp_tflm_infer);

static const mp_rom_map_elem_t tflm_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mp_tflm_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_infer), MP_ROM_PTR(&mp_tflm_infer_obj) },
};

static MP_DEFINE_CONST_DICT(tflm_module_globals, tflm_module_globals_table);

const mp_obj_module_t tflm_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&tflm_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_tflm, tflm_user_cmodule);
} // extern "C"