#pragma once

#include <windows.h>
#include <cstdint>
#include <memory>

#include <SafetyHook.hpp>
#include <utility/Address.hpp>

class FunctionHook {
public:
    FunctionHook() = delete;
    FunctionHook(const FunctionHook& other) = delete;
    FunctionHook(FunctionHook&& other) = delete;
    FunctionHook(Address target, Address destination);
    virtual ~FunctionHook();

    auto get_original() const {
        return (uintptr_t)m_inline_hook->trampoline();
    }

    template <typename T>
    T* get_original() const {
        return m_inline_hook->original<T>();
    }

    auto is_valid() const {
        return m_inline_hook != nullptr;
    }

    FunctionHook& operator=(const FunctionHook& other) = delete;
    FunctionHook& operator=(FunctionHook&& other) = delete;

private:
    SafetyInlineHook m_inline_hook{};
};