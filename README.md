# Click Before Frames — iOS rebuild

## Current state: input-buffer stage slider prototype

Version **v2.79.3** replaces the mistaken TPS overlay with one **Tick rate** slider. The slider selects the input-buffer delay stage and logs the selected stage in Geode's log/console.

### Slider stages

- Stage 1: 2 ticks all / 2 ticks wave (0.5 frame at 60 FPS)
- Stage 2: 4 / 4 ticks (1 frame)
- Stage 3: 8 / 8 ticks (2 frames)
- Stage 4: 16 ticks all / 8 ticks wave (4 / 2 frames)
- Stage 5: OFF (100% raw input)

The integer slider snaps between those five stages. On startup it logs the selected stage; when changed it logs a stage message, for example `Tick rate slider -> STAGE 2: 4 Ticks All | 4 Ticks Wave (1.0f @ 60fps)`.

## Important prototype boundary

This milestone intentionally has **no gameplay hooks**. It validates the real Geode slider, stage mapping, and change-to-log path only. It does not intercept or delay inputs yet, because the iOS input-buffer engine has not been restored. Once this selector is verified, the rebuilt input scheduler will consume this same `tick-rate-stage` setting instead of inventing a separate TPS control.

## Test checklist

1. Install the new build and open Click Before Frames' Geode settings.
2. Drag **Tick rate** through all five positions.
3. Check the Geode log/console for stage messages matching the stage mapping above.
4. Restart the game and confirm your selected stage remains saved.
5. Verify the game still cold-launches; only after that should we connect the stage to actual input scheduling.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — reference only.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
