# Click Before Frames — iOS rebuild

## Current state: diagnostic harness

The active branch remains iOS-only. Version **v2.79.2** adds a read-only tick debugger and a draggable target-TPS setting so we can validate telemetry and setting updates before rebuilding the input-buffer engine.

## Tick-rate debugger

Enable **Tick-rate debugger** to show the player-1 update count, measured update calls per second (actual TPS), selected target TPS, and latest update delta time (DT). The sample rate is measured from real update calls; it is not inferred from the selected target.

## Tick-rate adjuster (probe)

The **Tick-rate adjuster (probe)** is a draggable integer setting from 30 to 480 TPS, defaulting to 240. It is read while gameplay is running, and the overlay displays the new target shortly after the value changes. This validates the setting and live read path.

Important: this probe setting does **not** modify Geometry Dash's native physics clock, player movement, or input. Do not treat the target as an achieved rate. Wiring it into an isolated prediction stepper is a later milestone, after measuring the real update cadence and validating the engine's timing model.

## Test checklist

1. Confirm the mod cold-launches to the main menu.
2. Enter a level and check that TICK increases, ACTUAL TPS settles to a measured value, and DT is reported in milliseconds.
3. Change the target-TPS slider while testing and confirm TARGET changes in the overlay without changing native gameplay physics.
4. Turn the debugger off and confirm the overlay hides; turn it back on and confirm it returns.
5. Test pause, resume, restart, level exit, and a second level before introducing more hooks.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
