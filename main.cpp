#include "plugin.h"
#include "RenderWare.h"
#include "CAutomobile.h"
#include "CTimer.h"

using namespace plugin;

class FPSSteerFix {
public:
    FPSSteerFix() {
        Events::initGameRegisterEvent [] {
            Events::vehicleRenderEvent += [](CVehicle* vehicle) {
                if (vehicle && vehicle->m_pDriver == FindPlayerPed()) {
                    // Yüksek FPS'te kilitlenen direksiyon açısını 30 FPS normuna böler
                    if (CTimer::ms_fTimeStep < 1.0f && CTimer::ms_fTimeStep > 0.0f) {
                        vehicle->m_fSteerAngle *= (1.0f / CTimer::ms_fTimeStep) * 0.85f;
                    }
                }
            };
        };
    }
} fpsSteerFix;
