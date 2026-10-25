# Click Before Frames — iOS predictive rebuild

## Current state: predictive tick engine + one universal max-delay slider

Version **v2.79.8** restores the predictive engine from the archived iOS-capable implementation, based on the Windows reference. The active source retains the iOS hook guard: gameplay hooks stay disabled during menu startup, the bootstrap hook starts only after the menu loads, and remaining hooks are enabled one at a time with crash quarantine.

## How the tick value actually works

**Max input delay (ticks)** is the maximum prediction search window, not a fixed delay applied to every input. The engine simulates the player's path with a candidate input at different tick offsets. If pressing now is already safe, the input goes straight through. If a candidate delay survives longer and passes the engine's save checks, the input is queued for that tick instead.

The slider exposes actual integer ticks from **0 to 64**. **0 = OFF/raw input**. Four physics ticks equal one frame at 60 FPS.

**One universal cap applies to every supported gameplay mode.** The previous independent Wave delay and ship delay settings are removed. Mode-specific prediction code remains where the physics differs (that is needed to predict wave/ship/robot inputs correctly), but the delay cap comes from the same one slider. Orb-alignment is still a prediction feature; its search window cannot exceed the universal cap.

## Press/release queue

The reference engine keeps ordered input events. While a press is delayed, subsequent press/release events are shifted so a tap does not collapse and a hold keeps its length. The queue is delivered from the player update hook on physics ticks, not by changing Geometry Dash's global physics speed or the player's `dt`.

## Separate debugger

**Input buffer debugger** outputs actual gameplay press/release decisions, whether the event was handled or passed through, the universal cap, pending queue state, and setting changes to the Geode log. Prediction-specific save/miss explanations also appear in the mod's in-game console. The debugger does not change buffering.

## Crash-safety boundary

The iOS port retains the archived crash guard. On startup, hooks are deferred until the menu finishes loading; `PlayLayer::init` is the sole bootstrap hook, and gameplay hooks are enabled incrementally. A candidate hook is marked before activation so a crash can be quarantined next launch. The crash diagnostics live in the mod's save directory under `crash-diagnostics`.

This is a substantial engine restoration, so compilation is not the same as confirming all gameplay modes work on-device. The build should first be exercised in practice mode with cube presses/releases, followed by ship, wave, UFO, ball, robot, spider, and swing. If anything crashes or feels wrong, use the debugger and crash-diagnostics files to identify the last active hook.

## References

- [Windows Achieved](Windows-Achieved.md) — frozen desktop reference.
- [Legacy iOS v2.78.0](Legacy-iOS/v2.78.0/) — port and safety-guard reference.
- [iOS engine rebuild plan](docs/IOS-ENGINE-PLAN.md).

Practice use only; do not use for verified or leaderboard runs.
