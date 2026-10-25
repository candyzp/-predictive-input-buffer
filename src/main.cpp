#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <algorithm>
#include <cstdint>
#include <string>

using namespace geode::prelude;

namespace {
    struct BufferStage {
        int ticksAll;
        int ticksWave;
        bool enabled;
    };

    // These are the input-buffer delay stages from the existing mod's stage cycle.
    // Four simulation ticks equal one frame at 60 FPS.
    constexpr BufferStage STAGES[] = {
        { 2,  2, true  },
        { 4,  4, true  },
        { 8,  8, true  },
        { 16, 8, true  },
        { 0,  0, false },
    };
    constexpr int STAGE_COUNT = static_cast<int>(std::size(STAGES));

    int clampStage(int64_t value) {
        return std::clamp(static_cast<int>(value), 0, STAGE_COUNT - 1);
    }

    void logStage(int64_t value, bool startup) {
        const int index = clampStage(value);
        const auto& stage = STAGES[index];

        if (!stage.enabled) {
            log::info("[InputBuffer] {}: STAGE 5: OFF (100% Raw Input)",
                startup ? "Starting Mode" : "Tick rate slider");
            return;
        }

        const float allFrames = static_cast<float>(stage.ticksAll) / 4.0f;
        const float waveFrames = static_cast<float>(stage.ticksWave) / 4.0f;

        if (startup) {
            log::info("[InputBuffer] Starting Mode: STAGE {} ({} All / {} Wave)",
                index + 1, stage.ticksAll, stage.ticksWave);
        }
        else if (stage.ticksAll == stage.ticksWave) {
            log::info("[InputBuffer] Tick rate slider -> STAGE {}: {} Ticks All | {} Ticks Wave ({:.1f}f @ 60fps)",
                index + 1, stage.ticksAll, stage.ticksWave, allFrames);
        }
        else {
            log::info("[InputBuffer] Tick rate slider -> STAGE {}: {} Ticks All | {} Ticks Wave ({:.1f}f / {:.1f}f @ 60fps)",
                index + 1, stage.ticksAll, stage.ticksWave, allFrames, waveFrames);
        }
    }
}

// This milestone deliberately has NO gameplay hooks and does not delay inputs yet.
// It validates the actual stage slider and logs the selected buffer window.
$on_mod(Loaded) {
    logStage(Mod::get()->getSettingValue<int64_t>("tick-rate-stage"), true);

    listenForSettingChanges<int64_t>("tick-rate-stage", [](int64_t value) {
        logStage(value, false);
    });
}
