# Changelog

## v2.77.2 — 2026-10-25

- Added an iOS-only build workaround to include Geode's FMOD header for generated bindings that otherwise fail to resolve FMOD types.
- Excluded the unsupported `CCKeyboardDispatcher` modifier from iOS compilation. Prediction logic and the existing pause-menu Buffer interface are unchanged; keyboard shortcuts remain desktop-only.
- Replaced the menu's `CCPlace` floater reset with an instant callback, avoiding the unresolved iOS link symbol while preserving the animation and prediction logic.
- Added an iOS Console button wired to the existing in-game log toggle; prediction and input logic are unchanged.
- Updated iOS path-view and desktop-key settings labels and the run-check message.
- Kept the Windows build configuration and gameplay logic unchanged.

**Build verification:** The candidate passed iOS, Windows, and combined packaging jobs in GitHub Actions. On-device iOS gameplay and layout still require testing.
