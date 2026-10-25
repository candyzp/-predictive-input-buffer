# Click Before Frames — iOS rebuild

## Current state: startup-isolation baseline

main is now an iOS-only rebuild. **This temporary v2.79.0 baseline intentionally does not buffer inputs and does not run predictions.** The active C++ source contains no gameplay hooks and no prediction engine. The purpose is to isolate the immediate launch crash before adding code back.

This is a diagnostic build, not a feature-complete release. Do not expect the Buffer pause-menu button, settings, or prediction features to appear until later rebuild stages.

## What happens next

1. Verify that this no-hook build reaches the Geometry Dash menu on the target iOS setup.
2. Add the smallest possible observation-only gameplay hook and verify launch and level entry.
3. Record real input timing, physics-step dt, mode, and player state without modifying inputs.
4. Build an iOS-focused simulator and scheduler in small, independently testable pieces.
5. Reintroduce prediction mode by mode, beginning with a simple ground mode; validate press/release ordering, portals, dual-player behavior, checkpoints, and mobile touch input before enabling each feature.

If the no-hook build still crashes before the loading screen, the prediction engine is not being executed. That would point toward the loader/mod install, another mod, or library initialization rather than prediction math.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Previous iOS-capable source snapshot](Legacy-iOS/v2.78.0/) — retained for comparison, not used by the active build.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only. Do not use for verified or leaderboard runs until the implementation has been fully tested.
