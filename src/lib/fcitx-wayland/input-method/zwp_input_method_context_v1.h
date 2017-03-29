#ifndef ZWP_INPUT_METHOD_CONTEXT_V1
#define ZWP_INPUT_METHOD_CONTEXT_V1
#include "fcitx-utils/signals.h"
#include "wayland-input-method-unstable-v1-client-protocol.h"
#include <memory>
#include <wayland-client.h>
namespace fcitx {
namespace wayland {
class WlKeyboard;
class ZwpInputMethodContextV1 {
public:
    static constexpr const char *interface = "zwp_input_method_context_v1";
    static constexpr const wl_interface *const wlInterface =
        &zwp_input_method_context_v1_interface;
    static constexpr const uint32_t version = 1;
    typedef zwp_input_method_context_v1 wlType;
    operator zwp_input_method_context_v1 *() { return data_.get(); }
    ZwpInputMethodContextV1(wlType *data);
    ZwpInputMethodContextV1(ZwpInputMethodContextV1 &&other)
        : data_(std::move(other.data_)) {}
    ZwpInputMethodContextV1 &operator=(ZwpInputMethodContextV1 &&other) {
        data_ = std::move(other.data_);
        return *this;
    }
    auto actualVersion() const { return version_; }
    void commitString(uint32_t serial, const char *text);
    void preeditString(uint32_t serial, const char *text, const char *commit);
    void preeditStyling(uint32_t index, uint32_t length, uint32_t style);
    void preeditCursor(int32_t index);
    void deleteSurroundingText(int32_t index, uint32_t length);
    void cursorPosition(int32_t index, int32_t anchor);
    void modifiersMap(wl_array *map);
    void keysym(uint32_t serial, uint32_t time, uint32_t sym, uint32_t state,
                uint32_t modifiers);
    WlKeyboard *grabKeyboard();
    void key(uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
    void modifiers(uint32_t serial, uint32_t modsDepressed,
                   uint32_t modsLatched, uint32_t modsLocked, uint32_t group);
    void language(uint32_t serial, const char *language);
    void textDirection(uint32_t serial, uint32_t direction);
    auto &surroundingText() { return surroundingTextSignal_; }
    auto &reset() { return resetSignal_; }
    auto &contentType() { return contentTypeSignal_; }
    auto &invokeAction() { return invokeActionSignal_; }
    auto &commitState() { return commitStateSignal_; }
    auto &preferredLanguage() { return preferredLanguageSignal_; }

private:
    static void destructor(zwp_input_method_context_v1 *);
    static const struct zwp_input_method_context_v1_listener listener;
    fcitx::Signal<void(const char *, uint32_t, uint32_t)>
        surroundingTextSignal_;
    fcitx::Signal<void()> resetSignal_;
    fcitx::Signal<void(uint32_t, uint32_t)> contentTypeSignal_;
    fcitx::Signal<void(uint32_t, uint32_t)> invokeActionSignal_;
    fcitx::Signal<void(uint32_t)> commitStateSignal_;
    fcitx::Signal<void(const char *)> preferredLanguageSignal_;
    uint32_t version_;
    std::unique_ptr<zwp_input_method_context_v1, decltype(&destructor)> data_;
};
}
}
#endif
