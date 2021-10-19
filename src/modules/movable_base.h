/// @file movable_base.h
#pragma once
#include <stdint.h>
#include "../config/axis.h"
#include "../hal/tmc2130.h"

namespace modules {
namespace motion {

/// Base class for movable modules - #modules::idler::Idler and #modules::selector::Selector contains the common code
class MovableBase {
public:
    /// Internal states of the state machine
    enum {
        Ready = 0, // intentionally set as zero in order to allow zeroing the Idler structure upon startup -> avoid explicit initialization code
        Moving,
        Homing,
        Failed
    };

    /// Operation (Engage/Disengage/MoveToSlot) return values
    enum class OperationResult : uint8_t {
        Accepted, ///< the operation has been successfully started
        Refused, ///< another operation is currently underway, cannot start a new one
        Failed ///< the operation could not been started due to HW issues
    };

    inline constexpr MovableBase()
        : state(Ready)
        , plannedSlot(-1)
        , currentSlot(-1) {}

    /// virtual ~MovableBase(); intentionally disabled, see description in logic::CommandBase

    /// @returns currently active slot
    /// this state is updated only when a planned move is successfully finished, so it is safe for higher-level
    /// state machines to use this call as a waiting condition for the desired state of the derive class (idler/selector)
    inline uint8_t Slot() const { return currentSlot; }

    /// @returns internal state of the state machine
    inline uint8_t State() const { return state; }

    inline hal::tmc2130::ErrorFlags TMCErrorFlags() const { return tmcErrorFlags; }

    /// Prepare a homing move of the axis
    void PlanHome(config::Axis axis);

protected:
    /// internal state of the automaton
    uint8_t state;

    /// planned slot - where to move to
    uint8_t plannedSlot;

    /// current slot
    uint8_t currentSlot;

    /// cached TMC2130 error flags - being read only if the axis is enabled and doing something (moving)
    hal::tmc2130::ErrorFlags tmcErrorFlags;

    virtual void PrepareMoveToPlannedSlot() = 0;
    virtual void PlanHomingMove() = 0;
    virtual void FinishHomingAndPlanMoveToParkPos() = 0;
    virtual void FinishMove() = 0;

    OperationResult InitMovement(config::Axis axis);

    void PerformMove(config::Axis axis);

    void PerformHome(config::Axis axis);
};

} // namespace motion
} // namespace modules
