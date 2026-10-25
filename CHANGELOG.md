# Changelog

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
