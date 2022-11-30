#include <spdlog/spdlog.h>

#include "FunctionHook.hpp"

using namespace std;

FunctionHook::FunctionHook(Address target, Address destination) {
    spdlog::info("Attempting to hook {:p}->{:p}", target.ptr(), destination.ptr());

    auto factory = SafetyHookFactory::init();
    auto builder = factory->acquire(); 

    // Create the hook.
    if (m_inline_hook = builder.create_inline(target.as<void*>(), destination.as<void*>()); m_inline_hook != nullptr) {
        spdlog::info("Hook init successful {:p}->{:p}", target.ptr(), destination.ptr());
    }
    else {
        spdlog::error("Failed to hook {:p}", target.ptr());
    }
}

FunctionHook::~FunctionHook() {
    m_inline_hook.reset();
}