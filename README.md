# Click Before Frames — iOS rebuild

## Current settings: one universal delay slider + separate debugger

Version **v2.79.7** has one **Max input delay (ticks)** slider shared by the entire input-buffer system, plus a separate **Input buffer debugger** toggle.

## One universal input-delay value

The slider exposes actual integer tick values from **0 to 64**. **0 = OFF/raw input**. Four simulation ticks equal one frame at 60 FPS.

The selected limit is universal: the same value applies to every gameplay mode. There are no per-mode delay values, extra delay sliders, or mode-specific formulas. The only other setting is the optional debugger, which only controls diagnostic logs.

## Separate debugger

**Input buffer debugger** independently enables or disables logs for the current universal delay value. It never changes the slider value.

## Important prototype boundary

There are still **no gameplay hooks** in this iOS harness. This build verifies the one 0–64 tick setting and separate debugger. It does **not** delay gameplay inputs yet; the input scheduler must be rebuilt and validated before the selected limit affects gameplay.

## Test checklist

1. Drag **Max input delay (ticks)** to 2, 8, 12, 16, 24, 32, and 64. It should display actual tick values, not stage numbers.
2. Set it to 0 and confirm the debugger reports OFF/raw input.
3. Turn **Input buffer debugger** off and confirm changing the delay no longer creates delay-setting diagnostics.
4. Turn it back on and confirm the current universal value is logged.
5. Check cold launch, pause, restart, and level entry before adding gameplay hooks.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
