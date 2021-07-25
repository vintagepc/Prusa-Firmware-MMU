#pragma once
#include <stdint.h>
#include "axis.h"

/// Wrangler for assorted compile-time configuration and constants.
namespace config {

static constexpr const uint8_t toolCount = 5U; ///< Max number of extruders/tools/slots

// Idler's setup
static constexpr uint16_t idlerSlotPositions[toolCount + 1] = { 1, 2, 3, 4, 5, 0 }; ///< slots 0-4 are the real ones, the 5th is the idle position

// Selector's setup
static constexpr uint16_t selectorSlotPositions[toolCount + 1] = { 1, 2, 3, 4, 5, 6 }; ///< slots 0-4 are the real ones, the 5th is the farthest parking positions

// Printer's filament sensor setup
static constexpr const uint16_t fsensorDebounceMs = 10;

// FINDA setup
static constexpr const uint16_t findaDebounceMs = 100;
static constexpr const uint8_t findaADCIndex = 6; ///< ADC index of FINDA input
static constexpr const uint16_t findaADCDecisionLevel = 512; ///< ADC decision level when a FINDA is considered pressed/not pressed

// Buttons setup
static constexpr const uint8_t buttonCount = 3; ///< number of buttons currently supported
static constexpr const uint16_t buttonsDebounceMs = 100;
static constexpr const uint16_t buttonADCLimits[buttonCount][2] = { { 0, 50 }, { 80, 100 }, { 160, 180 } };
static constexpr const uint8_t buttonsADCIndex = 5; ///< ADC index of buttons input

/// Do not plan moves equal or shorter than the requested steps
static constexpr uint8_t dropSegments = 0;

/// Max step frequency 40KHz
static constexpr uint16_t maxStepFrequency = 40000;

/// Minimum stepping rate 120Hz
static constexpr uint16_t minStepRate = 120;

/// Size for the motion planner block buffer size
static constexpr uint8_t blockBufferSize = 2;

/// Step timer frequency divider (F = F_CPU / divider)
static constexpr uint8_t stepTimerFrequencyDivider = 8;

/// Smallest stepping ISR scheduling slice (T = F_CPU / divider * quantum)
/// 16 = 8us (25us is the max frequency interval per maxStepFrequency)
static constexpr uint8_t stepTimerQuantum = 16;

/// Pulley axis configuration
static constexpr AxisConfig pulley = {
    .dirOn = true,
    .vSense = false,
    .iRun = 20,
    .iHold = 20,
    .stealth = false,
    .uSteps = 16,
    .stepsPerUnit = 100,
};

/// Pulley motion limits
static constexpr PulleyLimits pulleyLimits = {
    .lenght = 100.0_mm,
    .jerk = 10.0_mm_s,
    .accel = 1000.0_mm_s2,
};

/// Selector configuration
static constexpr AxisConfig selector = {
    .dirOn = true,
    .vSense = false,
    .iRun = 20,
    .iHold = 20,
    .stealth = false,
    .uSteps = 16,
    .stepsPerUnit = 100,
};

/// Selector motion limits
static constexpr SelectorLimits selectorLimits = {
    .lenght = 100.0_mm,
    .jerk = 10.0_mm_s,
    .accel = 1000.0_mm_s2,
};

/// Idler configuration
static constexpr AxisConfig idler = {
    .dirOn = true,
    .vSense = false,
    .iRun = 20,
    .iHold = 20,
    .stealth = false,
    .uSteps = 16,
    .stepsPerUnit = 100,
};

/// Idler motion limits
static constexpr IdlerLimits idlerLimits = {
    .lenght = 360.0_deg,
    .jerk = 10.0_deg_s,
    .accel = 1000.0_deg_s2,
};

} // namespace config
