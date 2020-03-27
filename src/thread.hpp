#ifndef WINTER_THREAD_HPP
#define WINTER_THREAD_HPP

#include "func.hpp"
#include "type.hpp"
#include "wassert.hpp"

namespace winter {

class Thread;

enum class ErrorCode {
    SUCCESS
};

struct StackFrame {
    enum Flags : uint32_t {
        JIT_FRAME  = 0x00000001,
        HOST_FRAME = 0x00000002
    };

    LinkedFuncInternal* func;
    uint32_t pc_off;
    uint32_t flags;

    Value* locals;
};

class StackFrameInfo {
    StackFrame* _frame;
public:
    StackFrameInfo(StackFrame* frame) : _frame(frame) {}

    LinkedFunc* function() const { return _frame->func->container; }
    size_t offset() const { return _frame->pc_off; }

    bool is_jit_frame() const { return (_frame->flags & StackFrame::JIT_FRAME) != 0; }
    bool is_host_frame() const { return (_frame->flags & StackFrame::HOST_FRAME) != 0; }

    // TODO: TypedValue read_local(size_t i) const
    // TODO: void write_local(size_t i, TypedValue val)
};

struct ThreadInternal {
    StackFrame* call_stack;
    StackFrame* call_stack_max;

    Thread* thread;
};

class Thread {
    ThreadInternal _internal;

    std::vector<Value> _interp_value_stack;
    size_t _interp_value_stack_top;

    std::vector<StackFrame> _call_stack;
public:
    Thread() : _interp_value_stack(1000), _interp_value_stack_top(0), _call_stack(100) {
        _internal.call_stack = _call_stack.data();
        _internal.call_stack = _call_stack.data() + _call_stack.size();
        _internal.thread = this;
    }

    Thread(const Thread&) = delete;
    Thread(Thread&&) = delete;

    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&&) = delete;

    size_t stack_depth() const {
        return _internal.call_stack - _call_stack.data();
    }

    StackFrameInfo stack_frame(size_t depth) {
        WASSERT(depth < stack_depth(), "Out of range frame depth");
        return StackFrameInfo(_internal.call_stack - depth);
    }

    ErrorCode run_interpreter(LinkedFunc* func, Value* params, Value* results);
    std::vector<TypedValue> execute(LinkedFunc* func, std::vector<TypedValue> params);
};

}

#endif
