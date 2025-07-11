// C++ sum function
int cpp_sum(int a, int b) {
    return a + b + 1;
}

// MicroPython wrapper
extern "C" {
#include "py/obj.h"
#include "py/runtime.h"

// Convert C++ function to MicroPython function
static mp_obj_t mp_sum(mp_obj_t a_obj, mp_obj_t b_obj) {
    int a = mp_obj_get_int(a_obj);
    int b = mp_obj_get_int(b_obj);
    return mp_obj_new_int(cpp_sum(a, b));
}
// Define the function object
static MP_DEFINE_CONST_FUN_OBJ_2(mp_sum_obj, mp_sum);

// Module globals table
// MP_ROM_QSTR = read-only MicroPython string key. 
// _sum is the name of the function in Python.
// MP_ROM_PTR = read-only pointer to a MicroPython object
static const mp_rom_map_elem_t sum_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_sum), MP_ROM_PTR(&mp_sum_obj) },
};

static MP_DEFINE_CONST_DICT(sum_module_globals, sum_module_globals_table);

// Define module object
// Add extern to ensure C linkage for the symbol
extern const mp_obj_module_t sum_user_cmodule;
const mp_obj_module_t sum_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&sum_module_globals,
};

// Register module to MicroPython
MP_REGISTER_MODULE(MP_QSTR_sum_module, sum_user_cmodule);

} // extern "C"