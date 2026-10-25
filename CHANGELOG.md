# Changelog

## v2.77.2 — 2026-10-25

- Added an iOS-only build workaround to include Geode's FMOD header for generated bindings that otherwise fail to resolve FMOD types.
- Excluded the unsupported `CCKeyboardDispatcher` modifier from iOS compilation. Prediction logic and the existing pause-menu Buffer interface are unchanged; keyboard shortcuts remain desktop-only.
- Corrected the mod description and README so they no longer claim new touch controls were implemented.
- Kept the Windows build configuration and gameplay logic unchanged.

**Verification status:** The previous Windows build passed, but this revision still needs a fresh CI build and iOS runtime testing before it can be called a working iOS port.
