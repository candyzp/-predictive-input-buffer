# iOS prediction engine rebuild plan

## Design constraints

The old desktop-capable implementation is a useful reference, not the architecture for the new active port. Keep main iOS-only. Do not enable the prediction engine until launch, level entry, input pass-through, and mode-specific tests succeed.

The rebuild must not assume desktop keyboard events, desktop timing, or a hard-coded tick rate is equivalent to the iOS input/runtime path. Measure actual callback timing and physics-step dt on the target game/build. If game physics is identical, reuse validated physics facts; do not infer a different physics model just because the platform is iOS.

## Milestones

### 0. Startup isolation
- Minimal mod with no $modify declarations.
- No simulator, file logging, custom hooks, or file I/O.
- Acceptance: repeated cold launches reach the main menu without crashing.

### 1. Hook isolation
- Add one low-risk hook at a time; do not register the full old hook set in one commit.
- Initially observe only. Keep hooks disabled outside the context where they are needed.
- Acceptance: cold launch, menu, level entry, pause, restart, and quit survive repeated tests.

### 2. Input and timing telemetry
- Record touch press/release ordering, callback time, actual step dt, physics step count, player mode, and whether the game is paused or in a transition.
- Keep telemetry bounded and opt-in; avoid filesystem writes during static initialization.
- Acceptance: diagnostic logs show correct pairs of presses/releases in ordinary play, taps, holds, fast wave inputs, and pause/resume.

### 3. Prediction core
Separate the simulation from input interception:
- immutable input snapshot of the real player and relevant world state;
- isolated stepper that advances from the measured game state without changing the real level;
- explicit collision/portal/trigger policy;
- deterministic cancellation and restoration of any state that must be temporarily borrowed;
- bounded per-input work budget and a pass-through fallback if a prediction overruns its budget or encounters unsupported state.

Do not use UI code, disk I/O, menu work, or diagnostic formatting inside the per-click hot path.

### 4. Mode adapters
Validate each adapter independently instead of shipping a single untested all-modes path:
- cube and ground-contact modes (including ball, robot and spider transitions);
- ship, wave, UFO and swing continuous flight/control;
- orb/pad/dash interactions, gravity/speed/size/mode portals;
- dual-player control, teleport/trigger effects, moving objects, checkpoints and platformer levels.

Each adapter needs reproducible short test sections and pass-through behavior for unsupported mechanics.

### 5. Input scheduler
- Preserve touch press/release order and hold lengths.
- Express candidate delays in measured simulation steps, not wall-clock milliseconds or a presumed desktop frame count.
- Disable chained delays by default until ordering is verified.
- Use no-op/observe-only mode as a kill switch.
- Fail open: a prediction failure must send the original input unchanged.

### 6. Release gates
Before enabling a mode by default: successful iOS CI build; cold-launch tests; level entry/exit tests; deterministic replay comparisons; FPS/hitch budget measurements; and mode-specific regressions. Keep auto-release or other autonomous input manipulation off by default and limited to practice/testing.

## Current milestone

v2.79.0 is the hook-free startup-isolation baseline. No prediction or input interception is active.


## Increment 1: tick-rate probe

The current active implementation adds one `PlayerObject::update` hook and no others. It calls the original update exactly once and measures only player 1. It displays total ticks, measured update calls per second, and latest `dt`, behind the `Tick rate` setting. It must pass cold-launch and level lifecycle tests before any other hook is introduced.

Once validated, remove or replace the probe before adding the next hook; each subsequent hook must be its own separately testable increment.
