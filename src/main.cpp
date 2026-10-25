#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Temporary iOS startup-isolation baseline.
// Intentionally contains no $modify hooks, no prediction engine, and no file I/O.
// Keep this minimal until the iOS launch path has been verified on-device.
$on_mod(Loaded) {
    log::info("[InputBuffer] v2.79.0 iOS rebuild bootstrap loaded; gameplay hooks and prediction are disabled.");
}
