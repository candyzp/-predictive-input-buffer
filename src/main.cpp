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

    // Keep the original Click Before Frames All/Wave preset behavior:
    // 2/2, 4/4, 8/8, 16/8, 24/12, 32/16.
    // For values above 16, Wave receives half the All limit, never below 8.
    int waveTicksFor(int allTicks) {
        if (allTicks <= 8) {
            return allTicks;
        }
        return std::max(8, allTicks / 2);
    }

    void logDelay(int64_t rawValue, bool startup) {
        auto* mod = Mod::get();
        if (!mod->getSettingValue<bool>("debugger-enabled")) {
            return;
        }

        const int allTicks = clampInputDelay(rawValue);
        const char* origin = startup ? "Startup" : "Max input delay slider";

        if (allTicks == 0) {
            log::info("[InputBuffer] {}: Max input delay OFF (100% raw input)", origin);
            return;
        }

        const int waveTicks = waveTicksFor(allTicks);
        const float allFrames = static_cast<float>(allTicks) / 4.0f;
        const float waveFrames = static_cast<float>(waveTicks) / 4.0f;

        log::info(
            "[InputBuffer] {}: Max input delay = {} ticks ({:.2f}f) | auto Wave limit = {} ticks ({:.2f}f) @ 60fps",
            origin, allTicks, allFrames, waveTicks, waveFrames
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
