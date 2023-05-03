#include "stdafx.h"
#include "VFX.h"

VFX g_VFX;

VFXVehicleHeadlights* VFX::m_VFXVehicleHeadlights;
VFXVehicleHeadlights VFX::m_OVFXVehicleHeadlights;
VFXPuddlesRipples VFX::m_OVFXPuddlesRipples;
VFXDistantLights* VFX::m_VFXDistantLights;
VFXDistantLights VFX::m_OVFXDistantLights;
VFXTrafficLight* VFX::m_VFXTrafficlights;
VFXTrafficLight VFX::m_OVFXTrafficlights;
VFXVehicleNeon* VFX::m_VFXVehicleNeon;
VFXVehicleNeon VFX::m_OVFXVehicleNeon;
VFXToneMapping* VFX::m_VFXToneMapping;
VFXToneMapping VFX::m_OVFXToneMapping;
VFXVehicleFade* VFX::m_VFXVehicleFade;
VFXVehicleFade VFX::m_OVFXVehicleFade;
VFXVehicle*	VFX::m_VFXVehicle;
VFXVehicle	VFX::m_OVFXVehicle;;
VFXPuddles* VFX::m_VFXPuddles;
VFXPuddles VFX::m_OVFXPuddles;
VFXCorona* VFX::m_VFXCoronas;
VFXCorona VFX::m_OVFXCoronas;
VFXTrain* VFX::m_VFXTrains;
VFXTrain VFX::m_OVFXTrains;
VFXSky* VFX::m_VFXSky;
VFXSky VFX::m_OVFXSky;

bool VFX::Initialize() {

	PatternBatch batch("VFX");

	batch.Submit("VFX_C", [](DWORD64 address) {
		uint64_t addr = GetAddressFromInstruction(GetAddressFromInstruction((char*)address, 0, 1, 5), 0x496) + 0x8;
		m_VFXCoronas = (VFXCorona*)addr;
		m_OVFXCoronas = *m_VFXCoronas;
		return true;
	});

	batch.Submit("VFX_P", [](DWORD64 address) {
		m_VFXPuddles = (VFXPuddles*)*(uint64_t*)GetAddressFromInstruction(address);
		m_OVFXPuddles = *m_VFXPuddles;
		m_OVFXPuddlesRipples = *m_VFXPuddles->m_ripples;
		return true;
	});

	batch.Submit("VFX_S", [](DWORD64 address) {
		m_VFXSky = (VFXSky*)GetAddressFromInstruction(GetAddressFromInstruction(address, 0, 1, 5), 0x5A);
		m_OVFXSky = *m_VFXSky;
		return true;
	});

	batch.Submit("VFX_T", [](DWORD64 address) {
		m_VFXTrains = (VFXTrain*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXTrains = *m_VFXTrains;
		return true;
	});

	batch.Submit("VFX_V", [](DWORD64 address) {
		m_VFXVehicle = (VFXVehicle*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXVehicle = *m_VFXVehicle;
		return true;
	});

	batch.Submit("VFX_VN", [](DWORD64 address) {
		m_VFXVehicleNeon = (VFXVehicleNeon*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXVehicleNeon = *m_VFXVehicleNeon;
		return true;
	});

	batch.Submit("VFX_VF", [](DWORD64 address) {
		m_VFXVehicleFade = (VFXVehicleFade*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXVehicleFade = *m_VFXVehicleFade;
		return true;
	});

	batch.Submit("VFX_VH", [](DWORD64 address) {
		m_VFXVehicleHeadlights = (VFXVehicleHeadlights*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXVehicleHeadlights = *m_VFXVehicleHeadlights;
		return true;
	});

	batch.Submit("VFX_TM", [](DWORD64 address) {
		m_VFXToneMapping = (VFXToneMapping*)GetAddressFromInstruction(address, 0, 4, 8);
		m_OVFXToneMapping = *m_VFXToneMapping;
		return true;
	});

	batch.Submit("VFX_DL", [](DWORD64 address) {
		m_VFXDistantLights = (VFXDistantLights*)GetAddressFromInstruction(GetAddressFromInstruction(address, 0, 1, 5), 0x41, 4, 8);
		m_OVFXDistantLights = *m_VFXDistantLights;
		return true;
	});

	batch.Submit("VFX_TL", [](DWORD64 address) {
		m_VFXTrafficlights = (VFXTrafficLight*)GetAddressFromInstruction(address);
		m_OVFXTrafficlights = *m_VFXTrafficlights;
		return true;
	});

	batch.Flush();
	return true;
}

VFX* GetVFX() { return &g_VFX; }