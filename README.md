# ImGui NED Embed Demo

A simple demo application that embeds the NED editor as an ImGui window.

## Current Setup

✅ **NED Submodule**: The demo now uses NED as a git submodule (`ned/`) instead of a local directory.

❌ **ImGui Issue**: Currently, NED is using its own ImGui (`ned/lib/imgui/`) while the demo app doesn't have its own ImGui submodule. This creates a potential version conflict.

## Plan: Fix ImGui Submodule Setup

### Current Problem
- NED submodule has its own ImGui at `ned/lib/imgui/`
- Demo app doesn't have a top-level ImGui submodule
- This could lead to version conflicts or confusion about which ImGui is being used

### Solution Plan

#### Step 1: Add ImGui as Top-Level Submodule
```bash
# Add ImGui as a submodule at the demo level
git submodule add https://github.com/ocornut/imgui.git imgui
```

#### Step 2: Modify NED's CMakeLists.txt
We need to modify `ned/CMakeLists.txt` to use the top-level ImGui instead of its own:

**Current (in ned/CMakeLists.txt):**
```cmake
# NED uses its own ImGui
lib/imgui/imgui.cpp
lib/imgui/imgui_demo.cpp
# ... etc
```

**Change to:**
```cmake
# Use top-level ImGui from parent project
${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
# ... etc
```

#### Step 3: Update Include Paths
Update `ned/CMakeLists.txt` include paths:
```cmake
# Change from:
lib/imgui
lib/imgui/backends

# To:
${CMAKE_SOURCE_DIR}/imgui
${CMAKE_SOURCE_DIR}/imgui/backends
```

#### Step 4: Remove NED's ImGui
After confirming everything works:
```bash
# Remove NED's internal ImGui
rm -rf ned/lib/imgui
```

### Potential Issues & Solutions

#### Issue 1: Version Mismatch
**Problem**: NED's internal ImGui might be a different version than the top-level one.
**Solution**: Pin both to the same commit or update NED to use the top-level version.

#### Issue 2: Build System Complexity
**Problem**: Modifying NED's CMakeLists.txt makes it less portable.
**Solution**: Use conditional compilation in NED's CMakeLists.txt:
```cmake
if(USE_EXTERNAL_IMGUI)
    # Use top-level ImGui
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
else()
    # Use internal ImGui
    lib/imgui/imgui.cpp
endif()
```

#### Issue 3: Include Path Conflicts
**Problem**: Both ImGui versions might be in the include path.
**Solution**: Ensure only one ImGui is in the include path at build time.

### Alternative Approach: Keep It Simple

If the above gets too complex, we could:
1. **Keep current setup** - NED uses its own ImGui, demo doesn't have one
2. **Document the setup** - Make it clear that NED manages its own ImGui
3. **Version pinning** - Ensure NED's ImGui is pinned to a known good version

### Current Status

✅ **Working**: NED submodule with its own ImGui  
⏳ **Planning**: Unified ImGui submodule approach  
🤔 **Decision needed**: Whether to proceed with unified ImGui or keep current setup

The current setup actually works fine - the main benefit of unified ImGui would be version consistency and potentially smaller repo size.
