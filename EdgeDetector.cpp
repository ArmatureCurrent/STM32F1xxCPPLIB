#include "EdgeDetector.h"

namespace STM32F107VC_DRIVER {
namespace GPIO {

EdgeDetector::EdgeDetector(PinPort pinPort, PinNumberEnum pinNumber,
                           EdgeType edgeType, PinPullMode pinPull):
    PinControl(pinPort, pinNumber, PinControl::PinModeEnum::IN,
               pinPull, STM32F107VC_DRIVER::GPIO::SPEED_LOW)
{
    setEdgeType(edgeType);
}

/*EdgeDetector::EdgeDetector()
{

}*/

void EdgeDetector::setEdgeType(EdgeType edgeType)
{
    switch(edgeType)
    {
    case STM32F107VC_DRIVER::GPIO::RISING_EDGE:
        PinControl::setPinMode(PinControl::PinModeEnum::IRQ_RISING_FRONT); break;
    case STM32F107VC_DRIVER::GPIO::FALLING_EDGE:
        PinControl::setPinMode(PinControl::PinModeEnum::IRQ_FALLING_FRONT); break;
    case STM32F107VC_DRIVER::GPIO::BOTH_EDGE:
        PinControl::setPinMode(PinControl::PinModeEnum::IRQ_ANY_FRONT); break;
    default:
        PinControl::pinControlError(STM32F107VC_DRIVER::GPIO::INCORRECT_PIN_MODE);
    }
}

EdgeType EdgeDetector::getEdgeType() const
{
    EdgeType type = STM32F107VC_DRIVER::GPIO::BOTH_EDGE;

    switch(m_pinMode)
    {
    case PinControl::PinModeEnum::IRQ_RISING_FRONT:
        type = STM32F107VC_DRIVER::GPIO::RISING_EDGE; break;
    case PinControl::PinModeEnum::IRQ_FALLING_FRONT:
        type = STM32F107VC_DRIVER::GPIO::FALLING_EDGE; break;
    case PinControl::PinModeEnum::IRQ_ANY_FRONT:
        type = STM32F107VC_DRIVER::GPIO::BOTH_EDGE; break;
    default:
        PinControl::pinControlError(STM32F107VC_DRIVER::GPIO::INCORRECT_PIN_MODE);
    }

    return type;
}

void EdgeDetector::setPinPull(PinPullMode pinPull)
{
    PinControl::setPinPull(pinPull);
}

PinState EdgeDetector::getPinState()
{
    PinControl::updatePinState();
    return m_pinState;
}

} // namespace GPIO
} // namespace STM32F107VC_DRIVER
