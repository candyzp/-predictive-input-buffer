# Click Before Frames — iOS predictive rebuild

## Current state: predictive input buffer with guarded iOS gameplay logic

Version **v2.79.15** keeps the ghost-based prediction/search engine and adds controls around its existing universal delay cap. On iOS, hooks remain registered from launch as required by the current JIT-less loader path, but their logic is inert until a live level passes the gameplay guard. If the crash guard detects an interrupted gameplay setup or run, it can force pass-through safe mode on the next launch. This preserves the v2.79.15 flag-based guard approach; it is not a claim of confirmed device-side stability.

## How the tick value actually works

**Max input delay (ticks)** is the maximum prediction search window, not a fixed delay applied to every input. The engine simulates the player's path with a candidate input at different tick offsets. If pressing now is already safe, the input goes straight through. If a candidate delay survives longer and passes the engine's save checks, the input is queued for that tick instead.

The slider exposes actual integer ticks from **0 to 64**. **0 = OFF/raw input**. Four physics ticks equal one frame at 60 FPS.

**One universal cap applies to every supported gameplay mode.** Mode-specific prediction code remains where physics differs, but the delay cap comes from the same slider. Orb alignment remains part of prediction; its search window cannot exceed the universal cap.

## New controls

- **Master tick controller + value:** when enabled, the second slider overrides the normal max-delay slider for all supported modes. Turning the controller off restores the normal slider's saved value. The value is a prediction search cap, not a delay forced onto every click.
- **Activation frequency:** optionally predict every Nth eligible new press. Other eligible presses and their releases pass through as a pair. Higher N can reduce prediction workload but also means fewer clicks can be rescued.
- **Extremely Aggressive preset:** enables a 64-tick master window. It is deliberately very forgiving and may make gameplay feel delayed.
- **Save sound:** the sound is tied to successful prediction saves, not every click. The effect is preloaded for the level and the sound setting updates live. Training mode still uses hints instead of the ding.
- **Successful-save logs:** off by default so repeated detailed save messages do not generate console work for every save. The separate in-game console and opt-in debugging tools remain available.
- The core predictor is no longer restricted to practice mode. Automatic-release features retain their own separate safety setting for normal runs.

The always-on bottom watermark and level-complete branding labels have been removed; the pause-menu console is still available when explicitly opened.

## Press/release queue

The reference engine keeps ordered input events. While a press is delayed, subsequent press/release events are shifted so a tap does not collapse and a hold keeps its length. The queue is delivered from the player update hook on physics ticks, not by changing Geometry Dash's global physics speed or the player's `dt`.

## Separate debugger

**Input buffer debugger** outputs actual gameplay press/release decisions, whether the event was handled or passed through, the universal cap, pending queue state, and setting changes to the Geode log. Prediction-specific save/miss explanations also appear in the mod's in-game console. The debugger does not change buffering.

## Crash-safety boundary

The iOS crash guard keeps diagnostics in the mod save directory under `crash-diagnostics` and records whether gameplay setup or the predictor was active when a run stopped unexpectedly. The current v2.79.15 path does not mutate TulipHook chains at runtime: hook bodies are gated by gameplay-state flags, and crash history can place the next launch into pass-through safe mode. This is intended to avoid the prior JIT-less runtime hook-mutation failure mode, but source changes and successful compilation alone do not prove the iPhone build is stable.

This is a substantial engine restoration, so compilation is not the same as confirming all gameplay modes work on-device. The build should first be exercised in practice mode with cube presses/releases, followed by ship, wave, UFO, ball, robot, spider, and swing. If anything crashes or feels wrong, use the debugger and crash-diagnostics files to identify the last active hook.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Legacy iOS v2.78.0](Legacy-iOS/v2.78.0/) — port and safety-guard reference.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Core prediction works in normal and practice runs. As with any gameplay modification, use discretion with leaderboard or verified runs; auto-release remains independently gated for normal gameplay.
