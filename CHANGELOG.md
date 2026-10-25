# Changelog

## v2.77.7 — 2026-10-25

- Remove the standalone `PlayLayer::init` sentinel hook; the v2.77.6 log showed that hook was still enabled during startup while the crash recurred.
- Defer all mod hooks on iOS until Geode's `GameEventType::Loaded` fires after `MenuLayer::init` returns, then queue activation for the following main-thread pass.
- Runtime launch behavior still requires device verification; build success alone is not proof of a crash fix.

## v2.77.6 — 2026-10-25

- Remove Click Before Frames' iOS `MenuLayer::init` hook, which added another hook to the launch-time menu initialization chain.
- Defer gameplay hooks until `PlayLayer::init` has returned, then enable them on the next Cocos frame instead of during an active hook callback.
- Keep the supported Geode hook APIs and standard `Priority::First` ordering.
- Build success does not confirm runtime behavior; verify that the game reaches the main menu and can enter a level.

## v2.77.5 — 2026-10-25

- Use Geode's supported `Hook::setAutoEnable(false)` API to defer all iOS hooks except a `MenuLayer::init` sentinel until startup/resource loading is finished.
- Enable deferred hooks through Geode's supported `Hook::enable()` API after the main menu initializes successfully.
- Switch priority declarations to the documented `setHookPriorityPre` API while keeping the standard `Priority::First` ordering.
- CI validates compilation only; this specifically targets the startup crash window and is not represented as a confirmed runtime fix.

## v2.77.4 — 2026-10-25

- Replace the extreme raw hook priority with Geode's standard `Priority::First` for shared gameplay hooks, preserving first-in-chain intent with a documented priority.
- This is a hook-compatibility mitigation for the iOS mod stack; successful compilation alone does not confirm a runtime crash is fixed.

## v2.77.3 — 2026-10-25

- Limit input-buffer bookkeeping to the active PlayLayer; non-level GJBaseGameLayer scenes now pass input through untouched.
- Added iOS startup checkpoints to the Geode log for crash localization.

## v2.77.2 — 2026-10-25

- Added an iOS-only build workaround to include Geode's FMOD header for generated bindings that otherwise fail to resolve FMOD types.
- Excluded the unsupported `CCKeyboardDispatcher` modifier from iOS compilation. Prediction logic and the existing pause-menu Buffer interface are unchanged; keyboard shortcuts remain desktop-only.
- Replaced the menu's `CCPlace` floater reset with an instant callback, avoiding the unresolved iOS link symbol while preserving the animation and prediction logic.
- Added an iOS Console button wired to the existing in-game log toggle; prediction and input logic are unchanged.
- Updated iOS path-view and desktop-key settings labels and the run-check message.
- Updated settings descriptions so iOS users are directed to the touch-menu controls instead of unavailable function keys.
- Fixed Copy log status reporting when the text file cannot be written, and made stage-change logs accurate for menu arrows as well as keyboard shortcuts.
- Kept the Windows build configuration and gameplay logic unchanged.

**Build verification:** The candidate passed iOS, Windows, and combined packaging jobs in GitHub Actions. On-device iOS gameplay and layout still require testing.
