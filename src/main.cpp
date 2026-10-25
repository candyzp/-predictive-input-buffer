#include <Geode/Geode.hpp>
#include <chrono>
#include <cstdint>

using namespace geode::prelude;

namespace {
    // Unique child tag for the optional read-only in-game tick overlay.
    constexpr int TICK_RATE_DEBUG_TAG = 0x43424654;
}

// First isolated gameplay hook: observe the real player update only.
// No input interception, ghost player, prediction, or writes to game state.
class $modify(TickRateDebuggerPlayerObject, PlayerObject) {
    void update(float dt) {
        // Preserve the game update exactly once before doing diagnostic work.
        PlayerObject::update(dt);

        auto* manager = GameManager::get();
        auto* layer = manager ? manager->m_playLayer : nullptr;
        if (!layer || layer->m_player1 != this) {
            return; // Count player 1 only, not dual-player or ghost updates.
        }

        using Clock = std::chrono::steady_clock;
        static PlayLayer* sampledLayer = nullptr;
        static uint64_t ticks = 0;
        static uint64_t sampleTicks = 0;
        static double measuredTicksPerSecond = 0.0;
        static float latestDeltaSeconds = 0.0f;
        static auto sampleStart = Clock::now();
        static auto lastTextUpdate = Clock::now();
        static auto lastSettingPoll = Clock::time_point{};
        static bool debuggerEnabled = true;

        const auto now = Clock::now();
        if (sampledLayer != layer) {
            sampledLayer = layer;
            ticks = 0;
            sampleTicks = 0;
            measuredTicksPerSecond = 0.0;
            sampleStart = now;
            lastTextUpdate = now;
        }

        ++ticks;
        ++sampleTicks;
        latestDeltaSeconds = dt;

        const double sampleSeconds = std::chrono::duration<double>(now - sampleStart).count();
        if (sampleSeconds >= 0.5) {
            // Avoid reporting a false low rate after a long pause or app suspension.
            measuredTicksPerSecond = sampleSeconds <= 1.0
                ? static_cast<double>(sampleTicks) / sampleSeconds
                : 0.0;
            sampleTicks = 0;
            sampleStart = now;
        }

        // Poll settings infrequently; do not do a settings lookup on every physics tick.
        if (lastSettingPoll.time_since_epoch().count() == 0 ||
            now - lastSettingPoll >= std::chrono::milliseconds(250)) {
            debuggerEnabled = Mod::get()->getSettingValue<bool>("tick-rate-debugger");
            lastSettingPoll = now;
        }

        auto* node = layer->getChildByTag(TICK_RATE_DEBUG_TAG);
        if (!debuggerEnabled) {
            if (node) node->setVisible(false);
            return;
        }

        auto* label = typeinfo_cast<CCLabelBMFont*>(node);
        if (!label) {
            label = CCLabelBMFont::create("", "chatFont.fnt");
            if (!label) return;
            label->setTag(TICK_RATE_DEBUG_TAG);
            label->setAnchorPoint({ 0.5f, 1.0f });
            label->setColor({ 150, 220, 255 });
            label->setOpacity(235);
            label->setScale(0.48f);
            auto size = CCDirector::get()->getWinSize();
            label->setPosition({ size.width / 2.0f, size.height - 8.0f });
            label->limitLabelWidth(size.width - 20.0f, 0.48f, 0.28f);
            layer->addChild(label, 10000);
        }
        label->setVisible(true);

        // Refresh text at 10 Hz rather than rebuilding strings every physics tick.
        if (now - lastTextUpdate >= std::chrono::milliseconds(100)) {
            auto message = fmt::format(
                "TICK {}  |  TPS {:.1f}  |  DT {:.2f} ms",
                ticks,
                measuredTicksPerSecond,
                latestDeltaSeconds * 1000.0f
            );
            label->setString(message.c_str());
            lastTextUpdate = now;
        }
    }
};
