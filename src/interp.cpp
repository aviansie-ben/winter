#include "thread.hpp"

namespace winter {

ErrorCode Thread::run_interpreter(LinkedFunc* func, Value* params, Value* results) {
    StackFrame* first_interp_frame = _internal.call_stack;

    WASSERT(first_interp_frame != _internal.call_stack_max, "Call stack overflow");
    first_interp_frame->func = func->internal();
    first_interp_frame->pc_off = 0;
    first_interp_frame->flags = 0;
    first_interp_frame->locals = &_interp_value_stack[_interp_value_stack_top];
    _internal.call_stack++;

    // TODO Initialize locals

    ErrorCode return_code = ErrorCode::SUCCESS;
    StackFrame* current_frame = first_interp_frame;
    InstructionCursor cursor(func->unlinked().instrs().get(), 0);

    while (true) {
        switch (cursor.read_opcode()) {
            case OpcodeValue::I32Const: {
                _interp_value_stack[_interp_value_stack_top++] = Value::for_i32(cursor.read_u32());
                break;
            }

            case OpcodeValue::Return: {
                if (current_frame == first_interp_frame) {
                    goto end;
                }

                current_frame--;
                cursor = InstructionCursor(
                    current_frame->func->container->unlinked().instrs().get(),
                    current_frame->pc_off
                );
                break;
            }
        }
    }

end:
    for (size_t i = 0; i < func->unlinked().signature().return_types.size(); i++)
        *(results++) = _interp_value_stack[--_interp_value_stack_top];

    current_frame--;

end_fail:
    _internal.call_stack = current_frame;
    return return_code;
}

std::vector<TypedValue> Thread::execute(LinkedFunc* func, std::vector<TypedValue> params) {
    std::vector<Value> results_raw;
    results_raw.resize(func->unlinked().signature().return_types.size());

    // TODO Convert params
    auto err = run_interpreter(func, nullptr, results_raw.data());
    if (err != ErrorCode::SUCCESS)
        throw err; // TODO Throw a proper exception

    std::vector<TypedValue> results;
    for (size_t i = 0; i < results_raw.size(); i++)
        results.push_back({ func->unlinked().signature().return_types[i], results_raw[i] });

    return results;
}

}
