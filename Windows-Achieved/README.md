# Windows Achieved — archived desktop reference

This folder is a **read-only reference snapshot** of the last desktop-capable implementation before the iOS-only rebuild. It is kept on `main`; no separate branch is used.

- [Archived source](src/main.cpp)
- [Archived mod manifest](mod.json)
- [Archived CMake configuration](CMakeLists.txt)
- [Archived Windows/iOS build workflow](build.yml)

The archived source contains the old shared implementation and its Windows-specific paths (desktop keyboard shortcuts and the optional native console). The active project is being switched to iOS-only builds; do not copy the Windows workflow back into the active build configuration.
