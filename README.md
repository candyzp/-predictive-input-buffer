# Click Before Frames — iOS rebuild

## Current state: first isolated hook

The active branch remains iOS-only. Version v2.79.1 is the hook-free startup-isolation baseline; the next increment adds exactly one gameplay hook, `PlayerObject::update`, for read-only tick diagnostics. There is still no input interception, ghost player, or prediction engine.

## Tick rate overlay

The `Tick rate` setting controls a small overlay at the top of the screen. It reports:
- `TICK`: player-1 update count for the current gameplay layer;
- `TPS`: measured player-1 update calls per second over a rolling half-second sample;
- `DT`: the most recent update delta time in milliseconds.

This is diagnostic telemetry only. It does not change the game's tick rate, alter input, or run predictions. The text refreshes at 10 Hz, and the settings value is checked four times per second to keep work out of the hot path.

## Hook-isolation test

Only one hook is active in this increment. Test cold launch, main menu, entering and exiting a level, pause/resume, and leaving gameplay. If the game crashes at launch again, this single hook is the next variable to remove or replace. Do not add further gameplay hooks or restore prediction code until this increment is verified.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
