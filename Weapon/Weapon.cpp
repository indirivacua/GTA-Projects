#include "plugin.h"
#include "extensions\KeyCheck.h"
#include "CMessages.h"

using namespace plugin;

class PlayerCoors {
public:
    PlayerCoors() {
        Events::drawingEvent += [] {
            CPed *player = FindPlayerPed();
            KeyCheck::Update();
            if (KeyCheck::CheckWithDelay('M', 200) && player) {
                static char message[256];
                snprintf(message, 256, "x = %.2f; y = %.2f; z = %.2f;", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
                CMessages::AddMessageJumpQ(message, 5000, 3, false);
            }
        };
    }
} playerCoors;


//#include "plugin.h"
//#include <vector>
//#include <string>
//#include <sstream>
//#include <fstream>
//#include "CModelInfo.h"
//#include "CAutomobile.h"
//#include "CCoronas.h"
//
//using namespace plugin;
//
//std::vector<unsigned int> truckIDs;
//
//#define Z_POS_FOR_MODELS_WITHOUT_NODE 1.3f
//
//#define g_TOWTRUCK_HOIST_DOWN_LIMIT *(unsigned short *)0x8D313C
//
//class VehicleAdvanced {
//public:
//    static void ReadSettingsFile() {
//        std::ifstream stream("vehicle_advanced.dat");
//        for (std::string line; getline(stream, line); ) {
//            if (line[0] != ';' && line[0] != '#') {
//                if (!line.compare("trucks")) {
//                    while (line.compare("end") && getline(stream, line)) {
//                        if (line[0] != ';' && line[0] != '#') {
//                            std::stringstream ss(line);
//                            int i;
//                            while (ss >> i) {
//                                truckIDs.push_back(i);
//                                if (ss.peek() == ',')
//
//
//                                    ss.ignore();
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    static bool IsTruckModel(unsigned int modelId) {
//        for (unsigned int i : truckIDs) {
//            if (i == modelId)
//                return true;
//        }
//        return false;
//    }
//
//    static bool __fastcall MyGetTowBarPos(CAutomobile *automobile, int, CVector &outPos, bool ignoreModelType, CVehicle *attachTo) {
//        if (automobile->m_nModelIndex == MODEL_TOWTRUCK || automobile->m_nModelIndex == MODEL_TRACTOR) {
//            float yOffset = -1.05f;
//            if (automobile->m_nModelIndex == MODEL_TRACTOR) {
//                if (attachTo && attachTo->m_nVehicleSubClass == VEHICLE_TRAILER && attachTo->m_nModelIndex != MODEL_FARMTR1)
//                    return false;
//                yOffset = -0.6f;
//            }
//            else if (attachTo && attachTo->m_nVehicleSubClass == VEHICLE_TRAILER)
//                return false;
//            outPos.x = 0.0f;
//            outPos.y = yOffset + CModelInfo::ms_modelInfoPtrs[automobile->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin.y;
//            outPos.z = (1.0f - static_cast<float>(automobile->m_wMiscComponentAngle) / static_cast<float>(g_TOWTRUCK_HOIST_DOWN_LIMIT)) * 0.5f + 0.5f - automobile->m_fFrontHeightAboveRoad;
//            outPos = *automobile->m_matrix * outPos;
//            return true;
//        }
//        if (IsTruckModel(automobile->m_nModelIndex)
//            || automobile->m_nModelIndex == MODEL_UTILITY && attachTo && attachTo->m_nModelIndex == MODEL_UTILTR1
//            || (automobile->m_nModelIndex == MODEL_BAGGAGE || automobile->m_nModelIndex == MODEL_TUG || automobile->m_nModelIndex == MODEL_BAGBOXA || automobile->m_nModelIndex == MODEL_BAGBOXB)
//            && attachTo
//            && (attachTo->m_nModelIndex == MODEL_BAGBOXA
//                || attachTo->m_nModelIndex == MODEL_BAGBOXB
//                || attachTo->m_nModelIndex == MODEL_TUGSTAIR))
//        {
//            if (automobile->m_aCarNodes[CAR_MISC_A]) {
//                RwMatrix *ltm = RwFrameGetLTM(automobile->m_aCarNodes[CAR_MISC_A]);
//                outPos.x = ltm->pos.x;
//                outPos.y = ltm->pos.y;
//                outPos.z = ltm->pos.z;
//            }
//            else {
//                outPos.x = 0.0f;
//                outPos.y = CModelInfo::ms_modelInfoPtrs[automobile->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin.y - 0.5f;
//                outPos.z = Z_POS_FOR_MODELS_WITHOUT_NODE - automobile->m_fFrontHeightAboveRoad;
//                outPos = *automobile->m_matrix * outPos;
//            }
//            return true;
//        }
//        if (ignoreModelType) {
//            outPos.x = 0.0f;
//            outPos.y = CModelInfo::ms_modelInfoPtrs[automobile->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin.y - 0.5f;
//            outPos.z = 0.5f - automobile->m_fFrontHeightAboveRoad;
//            outPos = *automobile->m_matrix * outPos;
//            return true;
//        }
//        return false;
//    }
//
//    static void Test() {
//        for (int i = 0; i < CPools::ms_pVehiclePool->m_nSize; i++) {
//            CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt(i);
//            if (vehicle) {
//                if (IsTruckModel(vehicle->m_nModelIndex)) {
//                    if (vehicle->m_nVehicleSubClass == VEHICLE_AUTOMOBILE && reinterpret_cast<CAutomobile *>(vehicle)->m_aCarNodes[CAR_MISC_A]) {
//                        CVector *posn = reinterpret_cast<CVector *>(&RwFrameGetLTM(reinterpret_cast<CAutomobile *>(vehicle)->m_aCarNodes[CAR_MISC_A])->pos);
//                        CCoronas::RegisterCorona(reinterpret_cast<unsigned int>(vehicle) + 100, 0, 0, 255, 0, 255, *posn, 1.0f, 150.0f, CORONATYPE_SHINYSTAR,
//                            0, false, false, 0, 0.0f, false, 0.1f, 0, 15.0f, false, false);
//                    }
//                    else {
//                        CCoronas::RegisterCorona(reinterpret_cast<unsigned int>(vehicle) + 100, vehicle, 255, 0, 0, 255, CVector(0.0f,
//                            CModelInfo::ms_modelInfoPtrs[vehicle->m_nModelIndex]->m_pColModel->m_boundBox.m_vecMin.y - 0.5f,
//                            1.3f - reinterpret_cast<CAutomobile *>(vehicle)->m_fFrontHeightAboveRoad), 1.0f, 150.0f, CORONATYPE_SHINYSTAR,
//                            0, false, false, 0, 0.0f, false, 0.1f, 0, 15.0f, false, false);
//                    }
//                }
//            }
//        }
//    }
//
//    VehicleAdvanced() {
//        patch::RedirectJump(0x6AF250, MyGetTowBarPos);
//        Events::gameProcessEvent += Test;
//        ReadSettingsFile();
//    }
//} vehAdv;





//#include "plugin.h"
//#include "common.h"
//#include "CTimer.h"
//#include "CStreaming.h"
//
//using namespace plugin;
//
//class Test {
//public:
//    Test() {
//        static int keyPressTime = 0;
//        Events::gameProcessEvent += [] {
//            CVehicle *vehicle = FindPlayerVehicle(0, false);
//            if (vehicle && vehicle->m_nVehicleClass == VEHICLE_AUTOMOBILE) {
//                CAutomobile *automobile = reinterpret_cast<CAutomobile *>(vehicle);
//                if (KeyPressed(49) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
//                    keyPressTime = CTimer::m_snTimeInMilliseconds;
//                    vehicle->SetWindowOpenFlag(9);
//                }
//                if (KeyPressed(50) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
//                    keyPressTime = CTimer::m_snTimeInMilliseconds;
//                    vehicle->ClearWindowOpenFlag(9);
//                }
//            }
//        };
//    }
//} test;

//class PlayerWeapon {
//public:
//    PlayerWeapon() {
//        static int keyPressTime = 0;
//        Events::gameProcessEvent += [] {
//            CPed *playa = FindPlayerPed();
//            if (playa && KeyPressed(VK_TAB) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
//                keyPressTime = CTimer::m_snTimeInMilliseconds;
//                CStreaming::RequestModel(MODEL_M4, 2);
//                CStreaming::LoadAllRequestedModels(false);
//                playa->GiveWeapon(WEAPON_M4, 10, true);
//                playa->SetCurrentWeapon(WEAPON_M4);
//                CStreaming::SetModelIsDeletable(MODEL_M4);
//            }
//        };
//    }
//} playerWeapon;