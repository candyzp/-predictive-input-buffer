#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <algorithm>
#include <cstdint>

using namespace geode::prelude;

namespace {
    constexpr int MAX_INPUT_DELAY_TICKS = 64;

    int clampInputDelay(int64_t value) {
        return std::clamp(static_cast<int>(value), 0, MAX_INPUT_DELAY_TICKS);
    }

    void logDelay(int64_t rawValue, bool startup) {
        auto* mod = Mod::get();
        if (!mod->getSettingValue<bool>("debugger-enabled")) {
            return;
        }

        const int ticks = clampInputDelay(rawValue);
        const char* origin = startup ? "Startup" : "Max input delay slider";

        if (ticks == 0) {
            log::info("[InputBuffer] {}: Universal max input delay OFF (raw input)", origin);
            return;
        }

        const float frames = static_cast<float>(ticks) / 4.0f;
        log::info(
            "[InputBuffer] {}: Universal max input delay = {} ticks ({:.2f}f @ 60fps); one shared value for all modes",
            origin, ticks, frames
        );
    }
}

// Startup-safe settings harness only: no gameplay hooks and no delayed inputs yet.
$on_mod(Loaded) {
    auto* mod = Mod::get();
    logDelay(mod->getSettingValue<int64_t>("max-delay-ticks"), true);

    listenForSettingChanges<int64_t>("max-delay-ticks", [](int64_t value) {
        logDelay(value, false);
    });

    listenForSettingChanges<bool>("debugger-enabled", [](bool enabled) {
        log::info("[InputBuffer] Debugger: {}", enabled ? "ON" : "OFF");
        if (enabled) {
            logDelay(Mod::get()->getSettingValue<int64_t>("max-delay-ticks"), true);
        }
    });
}
