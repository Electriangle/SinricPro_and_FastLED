#ifndef _MYLEDS_H_
#define _MYLEDS_H_

#include <SinricProDevice.h>
#include <Capabilities/PowerStateController.h>
#include <Capabilities/ModeController.h>

class Myleds 
: public SinricProDevice
, public PowerStateController<Myleds>
, public ModeController<Myleds> {
  friend class PowerStateController<Myleds>;
  friend class ModeController<Myleds>;
public:
  Myleds(const String &deviceId) : SinricProDevice(deviceId, "Myleds") {};
};

#endif
