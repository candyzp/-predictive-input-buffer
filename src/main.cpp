#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <algorithm>
#include <cstdint>

using namespace geode::prelude;

namespace {
    struct BufferStage {
        int ticksAll;
        bool enabled;
    };

    // All ticks are the only stage value. Wave delay is derived as min(All, 8).
    // Four simulation ticks equal one frame at 60 FPS.
    constexpr BufferStage STAGES[] = {
        { 2,  true  },
        { 4,  true  },
        { 8,  true  },
        { 16, true  },
        { 0,  false },
    };
    constexpr int STAGE_COUNT = static_cast<int>(std::size(STAGES));

    int clampStage(int64_t value) {
        return std::clamp(static_cast<int>(value), 0, STAGE_COUNT - 1);
    }

    int waveTicksFor(int allTicks) {
        return std::min(allTicks, 8);
    }

    void logStage(int64_t value, bool startup) {
        auto* mod = Mod::get();
        if (!mod->getSettingValue<bool>("debugger-enabled")) {
            return;
        }

        const int index = clampStage(value);
        const auto& stage = STAGES[index];

        if (!stage.enabled) {
            log::info("[InputBuffer] {}: STAGE 5: OFF (100% Raw Input)",
                startup ? "Starting Mode" : "Tick rate slider");
            return;
        }

        const int waveTicks = waveTicksFor(stage.ticksAll);
        const float allFrames = static_cast<float>(stage.ticksAll) / 4.0f;
        const float waveFrames = static_cast<float>(waveTicks) / 4.0f;

        if (startup) {
            log::info("[InputBuffer] Starting Mode: STAGE {} ({} All / {} Wave)",
                index + 1, stage.ticksAll, waveTicks);
        }
        else if (stage.ticksAll == waveTicks) {
            log::info("[InputBuffer] Tick rate slider -> STAGE {}: {} Ticks All | {} Ticks Wave ({:.1f}f @ 60fps)",
                index + 1, stage.ticksAll, waveTicks, allFrames);
        }
        else {
            log::info("[InputBuffer] Tick rate slider -> STAGE {}: {} Ticks All | {} Ticks Wave ({:.1f}f / {:.1f}f @ 60fps)",
                index + 1, stage.ticksAll, waveTicks, allFrames, waveFrames);
        }
    }
}

// This harness has no gameplay hooks and does not delay inputs.
// It validates the one All-ticks slider and the separate debugger toggle.
$on_mod(Loaded) {
    logStage(Mod::get()->getSettingValue<int64_t>("tick-rate-stage"), true);

    listenForSettingChanges<int64_t>("tick-rate-stage", [](int64_t value) {
        logStage(value, false);
    });

    listenForSettingChanges<bool>("debugger-enabled", [](bool enabled) {
        log::info("[InputBuffer] Debugger: {}", enabled ? "ON" : "OFF");
        if (enabled) {
            logStage(Mod::get()->getSettingValue<int64_t>("tick-rate-stage"), true);
        }
    });
}
