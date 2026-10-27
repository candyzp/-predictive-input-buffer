## v2.79.15
- Add Master Tick Controller and a 0–64 tick override for the existing predictive engine's universal search cap; switching it off restores the normal max-delay value.
- Add optional activation frequency to predict every Nth eligible new press while preserving each bypassed press/release pair.
- Add an Extremely Aggressive 64-tick preset.
- Make detailed successful-save console messages opt-in and default the high-volume input debugger to off.
- Refresh the save-ding setting live and guard sound preload/play calls; sound still indicates successful predictor saves, not every input.
- Remove the core practice-only gate, bottom watermark, and end-level branding labels while preserving the prediction engine and crash-guard path.
- Bump the mod version so the iOS crash guard resets stale quarantine history. Build success is not proof of on-device stability.

## v2.79.14
- Replace the iOS `PlayLayer::onEnterTransitionDidFinish` bootstrap with `PlayLayer::update`, a gameplay-specific method, to avoid hooking a lifecycle callback that may resolve to a shared inherited Cocos implementation on iOS.
- All Click Before Frames hooks remain disabled during app/menu startup. After Geode's menu-loaded event, only the PlayLayer update bootstrap is enabled; per-level setup runs on the first live PlayLayer update and all other hooks are queued for a later main-thread pass.
- This directly targets the recursive TulipHook dispatch signature seen in the native crash report; the JIT-less TulipHook issue remains a plausible contributing factor, not a device-confirmed diagnosis.

## v2.79.13
- Keep every Click Before Frames hook auto-disabled during app startup and menu loading.
- After Geode's `GameEventType::Loaded` event, queue activation of only `PlayLayer::onEnterTransitionDidFinish`; enable the remaining gameplay hooks only after an actual level-entry transition.
- Remove the `PlayLayer::onQuit` early-startup hook; it is enabled by the gameplay hook guard only while a level is active.
- This targets the pre-menu hook-dispatch recursion path. The stack signature resembles a known JIT-less TulipHook looping issue; a successful build is not proof of an on-device fix.

## v2.79.12
- Remove the iOS `PlayLayer::init` hook entirely; earlier project history documented repeated startup crashes with this hook used as a bootstrap.
- Keep only `PlayLayer::onEnterTransitionDidFinish` and `PlayLayer::onQuit` as lifecycle sentinels on iOS.
- Initialize per-level state and start guarded gameplay-hook activation after the level-entry transition instead of enabling `PlayLayer::init` while the main menu is loading.
- Preserve the v2.79.9 crash-diagnostics initialization-order fix.
- CI build success does not confirm device runtime; this is a source/history-based correction to the launch crash path.

## v2.79.11
- Add an iOS hook-registration bisect build using only group A hook classes: EndLevelLayer, PauseLayer, PlayLayer, LevelEditorLayer, and HardStreak.
- Exclude group B (EffectGameObject, GameObject, PlayerObject, GJBaseGameLayer) from this iOS diagnostic build; non-iOS builds keep all hook classes.
- Gameplay activation remains intentionally disabled, so this build tests whether the registered group alone reproduces the pre-menu Geode/Tulip hook-dispatch recursion crash.

## v2.79.10
- Add an iOS startup-isolation build for the pre-menu crash report showing deep recursion in Geode's Tulip hook-dispatch handler.
- Leave every gameplay hook disabled, including the PlayLayer::init bootstrap, while preserving startup checkpoints.
- Diagnostic only: gameplay input buffering is intentionally inactive. A successful menu launch would point investigation toward hook activation/interactions; a repeat crash would narrow it to earlier startup/hook setup.

## v2.79.9
- Fix iOS pre-menu crash: crash-diagnostics initialization no longer runs from the static hook-modifier registration path.
- Keep diagnostics initialization in the Geode mod `Loaded` callback.
- Predictive engine and unified max-delay behavior unchanged from v2.79.8.

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
