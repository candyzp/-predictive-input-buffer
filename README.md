# Click Before Frames — iOS rebuild

## Current state: real tick slider + separate debugger

Version **v2.79.6** has one **Max input delay (ticks)** slider and a separate **Input buffer debugger** toggle. The slider represents actual tick counts, not a stage index or Geometry Dash's physics tick rate.

## Max input delay (ticks)

The slider is continuous in integer steps from **0 to 64 ticks**. **0 = OFF/raw input**. Four simulation ticks equal one frame at 60 FPS.

Wave's maximum delay is derived automatically from the main value. There is no separate Wave setting:

| All / main delay | Derived Wave limit |
|---:|---:|
| 2 ticks | 2 ticks |
| 4 ticks | 4 ticks |
| 8 ticks | 8 ticks |
| 12 ticks | 8 ticks |
| 16 ticks | 8 ticks |
| 24 ticks | 12 ticks |
| 32 ticks | 16 ticks |
| 64 ticks | 32 ticks |
| OFF (0) | OFF |

This preserves the original mod's established preset mapping while allowing intermediate values such as 12 or 20 ticks.

## Separate debugger

**Input buffer debugger** independently controls diagnostic messages. When enabled, startup and slider changes log the chosen All limit and its calculated Wave limit. Turning the debugger off stops delay-setting diagnostics; turning it back on logs the current selection. It does not change the selected delay.

## Important prototype boundary

There are still **no gameplay hooks** in this iOS harness. This build verifies that the setting stores and exposes actual 0–64 tick values, derives the Wave value, and keeps the debugger separate. It does **not** delay gameplay inputs yet; the input scheduler and mode hooks must be rebuilt and validated before the value affects gameplay.

## Test checklist

1. Drag **Max input delay (ticks)** to values such as 2, 8, 12, 16, 24, 32, and 64; verify it reaches each number rather than stopping at a stage index of 4.
2. Confirm the debugger reports Wave values 2, 8, 8, 8, 12, 16, and 32 for All values 2, 8, 12, 16, 24, 32, and 64.
3. Set the slider to 0 and confirm it logs OFF/raw input.
4. Turn **Input buffer debugger** off and confirm delay-setting changes no longer create diagnostic logs; turn it back on and confirm the current value is logged.
5. Check cold launch, pause, restart, and level entry before adding gameplay hooks.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
