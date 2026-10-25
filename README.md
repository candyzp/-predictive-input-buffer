# Click Before Frames — iOS rebuild

## Current state: one stage slider + separate debugger

Version **v2.79.5** has one **Tick rate** slider for the input-buffer All-ticks stage and a separate **Input buffer debugger** toggle.

## Tick rate slider

The slider selects only the All-ticks stage. Wave ticks are derived automatically as `min(All ticks, 8)`; there is no independent Wave-tick control.

| Stage | All ticks | Derived Wave ticks |
|---|---:|---:|
| 1 | 2 | 2 |
| 2 | 4 | 4 |
| 3 | 8 | 8 |
| 4 | 16 | 8 |
| 5 | OFF | OFF |

Four simulation ticks equal one frame at 60 FPS.

## Separate debugger

**Input buffer debugger** independently controls stage diagnostic logging. When enabled, startup and slider changes log the selected stage and its derived Wave tick count. Turning the debugger off stops stage diagnostic messages; turning it back on logs the currently selected stage. The debugger does not change the slider selection.

## Important prototype boundary

There are still **no gameplay hooks**. This build verifies the slider, derived Wave count, persistence provided by the Geode setting, and the debugger toggle. It does not delay inputs yet; that will be connected once the iOS input scheduler is rebuilt and validated.

## Test checklist

1. Move **Tick rate** through all five stages.
2. Confirm the debugger logs 2/2, 4/4, 8/8, 16/8, and OFF.
3. Turn **Input buffer debugger** off and confirm changing stages no longer creates stage logs.
4. Turn it back on and confirm the selected stage is logged again.
5. Check cold launch, pause, restart, and level entry before adding gameplay hooks.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
