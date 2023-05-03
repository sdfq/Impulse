#include "stdafx.h"
#include "XMLVehicleMenu.h"
#include "../loadingMenu.h"

using namespace XMLVehicleMenuVars;
using namespace pugi;

namespace XMLVehicleMenuVars {
	Vars vars;

	int spoonerInitialHandle = 0;
	int spoonerVehicleHandle = 0;

	struct SpoonerAttachments {
		struct sVehicleProperties {
			struct sColours {
				int Primary;
				int Secondary;
				int Pearl;
				int Rim;
				int Mod1_a;
				int Mod1_b;
				int Mod1_c;
				int Mod2_a;
				int Mod2_b;
				bool IsPrimaryColourCustom;
				bool IsSecondaryColourCustom;
				int Cust1_R;
				int Cust1_G;
				int Cust1_B;
				int Cust2_R;
				int Cust2_G;
				int Cust2_B;
				int TyreSmoke_R;
				int TyreSmoke_G;
				int TyreSmoke_B;
				int LrInterior;
				int LrDashboard;
			} Colours;

			struct sNeons {
				bool Left;
				bool Right;
				bool Front;
				bool Back;
				int R;
				int G;
				int B;
			} Neons;

			struct sDoorsOpen {
				bool BackLeftDoor;
				bool BackRightDoor;
				bool FrontLeftDoor;
				bool FrontRightDoor;
				bool Hood;
				bool Trunk;
				bool Trunk2;
			} DoorsOpen;

			struct sDoorsBroken {
				bool BackLeftDoor;
				bool BackRightDoor;
				bool FrontLeftDoor;
				bool FrontRightDoor;
				bool Hood;
				bool Trunk;
				bool Trunk2;
			} DoorsBroken;

			struct sTyresBursted {
				bool FrontLeft;
				bool FrontRight;
				bool _2;
				bool _3;
				bool BackLeft;
				bool BackRight;
				bool _6;
				bool _7;
				bool _8;
			} TyresBursted;

			struct sMods {
				string _0;
				string _1;
				string _2;
				string _3;
				string _4;
				string _5;
				string _6;
				string _7;
				string _8;
				string _9;
				string _10;
				string _11;
				string _12;
				string _13;
				string _14;
				string _15;
				string _16;
				bool _17;
				bool _18;
				bool _19;
				bool _20;
				bool _21;
				bool _22;
				string _23;
				string _24;
				string _25;
				string _26;
				string _27;
				string _28;
				string _29;
				string _30;
				string _31;
				string _32;
				string _33;
				string _34;
				string _35;
				string _36;
				string _37;
				string _38;
				string _39;
				string _40;
				string _41;
				string _42;
				string _43;
				string _44;
				string _45;
				string _46;
				string _47;
				string _48;
			} Mods;

			int Livery;
			string NumberPlateText;
			int NumberPlateIndex;
			int WheelType;
			bool WheensInvisible;
			string EngineSoundName;
			int WindowTint;
			bool BulletProofTyres;
			float DirtLevel;
			float PaintFade;
			int RoofState;
			bool SirenActive;
			bool EngineOn;
			int EngineHealth;
			bool LightsOn;
			int IsRadioLoud;
			int LockStatus;
			int RpmMultiplier;
			int TorqueMultiplier;
			int HeadlightIntensity;
		} VehicleProperties;

		struct sPedProperties {
			struct sPedProps {
				string _0;
				string _1;
				string _2;
				string _3;
				string _4;
				string _5;
				string _6;
				string _7;
				string _8;
				string _9;
			} PedProps;

			struct sPedComps {
				string _0;
				string _1;
				string _2;
				string _3;
				string _4;
				string _5;
				string _6;
				string _7;
				string _8;
				string _9;
				string _10;
				string _11;
			} PedComps;

			bool IsStill;
			Hash CurrentWeapon;
			bool RelationshipGroupAltered;
			Hash RelationshipGroup;
			bool ScenarioActive;
			bool AnimActive;
			string AnimDict;
			string AnimName;
		} PedProperties;

		struct sAttachment {
			bool IsAttached;
			int AttachedTo;
			int BoneIndex;
			Vector3 Position;
			Vector3 Rotation;
		} Attachment;

		struct sOriginalPlacement {
			Vector3 Position;
			Vector3 Rotation;
		} Placement;

		int InitialHandle;
		int Handle;
		int Type;
		Hash ModelHash;
		bool Dynamic;
		bool FrozenPosition;
		int OpacityLevel;
		int LodDistance;
		bool IsVisible;
		int MaxHealth;
		int Health;
		bool HasGravity;
		bool IsOnFire;
		bool IsInvincible;
		bool IsBulletProof;
		bool IsCollisionProof;
		bool IsExplosionProof;
		bool IsFireProof;
		bool IsMeleeProof;
		bool IsOnlyDamagedByPlayer;
	};

	SpoonerAttachments SpawnEntityFromXmlNode(xml_node node) {
		SpoonerAttachments data;
		data.Type = node.child("Type").text().as_int();
		data.FrozenPosition = node.child("FrozenPos").text().as_bool();
		data.ModelHash = node.child("ModelHash").text().as_uint();
		data.Dynamic = node.child("Dynamic").text().as_bool();
		data.InitialHandle = node.child("InitialHandle").text().as_int();
		data.OpacityLevel = node.child("OpacityLevel").text().as_int();
		data.LodDistance = node.child("LodDistance").text().as_int();
		data.IsVisible = node.child("IsVisible").text().as_bool();
		data.Health = node.child("Health").text().as_int();
		data.MaxHealth = node.child("MaxHealth").text().as_int();
		data.IsOnFire = node.child("IsOnFire").text().as_bool();
		data.IsInvincible = node.child("IsInvincible").text().as_bool();
		data.IsBulletProof = node.child("IsBulletProof").text().as_bool();
		data.IsCollisionProof = node.child("IsCollisionProof").text().as_bool();
		data.IsExplosionProof = node.child("IsExplosionProof").text().as_bool();
		data.IsFireProof = node.child("IsFireProof").text().as_bool();
		data.IsMeleeProof = node.child("IsMeleeProof").text().as_bool();
		data.IsOnlyDamagedByPlayer = node.child("IsOnlyDamagedByPlayer").text().as_bool();
		data.HasGravity = node.child("HasGravity").text().as_bool(true);

		data.Placement.Position = Vector3(node.child("PositionRotation").child("X").text().as_float(), node.child("PositionRotation").child("Y").text().as_float(), node.child("PositionRotation").child("Z").text().as_float());
		data.Placement.Rotation = Vector3(node.child("PositionRotation").child("Pitch").text().as_float(), node.child("PositionRotation").child("Roll").text().as_float(), node.child("PositionRotation").child("Yaw").text().as_float());

		data.Attachment.IsAttached = node.child("Attachment").attribute("isAttached").as_bool();
		data.Attachment.BoneIndex = node.child("Attachment").child("BoneIndex").text().as_int();
		data.Attachment.Position = Vector3(node.child("Attachment").child("X").text().as_float(), node.child("Attachment").child("Y").text().as_float(), node.child("Attachment").child("Z").text().as_float());
		data.Attachment.Rotation = Vector3(node.child("Attachment").child("Pitch").text().as_float(), node.child("Attachment").child("Roll").text().as_float(), node.child("Attachment").child("Yaw").text().as_float());
		if (node.child("Attachment").child("AttachedTo").text().as_string() == "VEHICLE") {
			data.Attachment.AttachedTo = spoonerVehicleHandle;
		} else {
			data.Attachment.AttachedTo = node.child("Attachment").child("AttachedTo").text().as_int();
		}
		GetEntityControl()->SimpleRequestModel(data.ModelHash);

		switch (data.Type) {
			case 1: { // ped
					data.Handle = PED::CreatePed(21, data.ModelHash, data.Placement.Position.x, data.Placement.Position.y, data.Placement.Position.z, 1, 1, 0);
					if (ENTITY::DoesEntityExist(data.Handle)) {
						ENTITY::FreezeEntityPosition(data.Handle, data.FrozenPosition);

						PED::SetPedCanBeKnockedOffVehicle(data.Handle, false);
						PED::SetPedCanSwitchWeapon(data.Handle, false);

						//SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(data.Handle, true);
						PED::SetPedFleeAttributes(data.Handle, 0, 0);
						PED::SetPedCombatAttributes(data.Handle, 17, 1);

						if (data.OpacityLevel < 255) ENTITY::SetEntityAlpha(data.Handle, data.OpacityLevel, 0);
						ENTITY::SetEntityLodDist(data.Handle, data.LodDistance);
						ENTITY::SetEntityVisible(data.Handle, data.IsVisible, 1);

						if (data.MaxHealth) ENTITY::SetEntityMaxHealth(data.Handle, data.MaxHealth);
						if (data.Health) ENTITY::SetEntityHealth(data.Handle, data.Health);

						data.IsOnFire ? FIRE::StartEntityFire(data.Handle) : FIRE::StopEntityFire(data.Handle);

						ENTITY::SetEntityInvincible(data.Handle, data.IsInvincible);
						ENTITY::SetEntityProofs(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);
						ENTITY::SetEntityOnlyDamagedByPlayer(data.Handle, data.IsOnlyDamagedByPlayer);

						auto& pedProperties = node.child("PedProperties");

						if (pedProperties.child("IsStill").text().as_bool()) {
							BRAIN::TaskStandStill(data.Handle, -1);
						}

						if (pedProperties.child("CanRagdoll")) PED::SetPedCanRagdoll(data.Handle, pedProperties.child("CanRagdoll").text().as_bool());

						if (pedProperties.child("HasShortHeight").text().as_bool()) {
							*reinterpret_cast<byte*>(PoolManager::GetEntityAddress(data.Handle) + 0x8A) = 100;
						}

						PED::SetPedArmour(data.Handle, pedProperties.child("Armour").text().as_int());

						if (pedProperties.child("CurrentWeapon")) {
							WEAPON::GiveDelayedWeaponToPed(data.Handle, pedProperties.child("CurrentWeapon").text().as_uint(), 9999, 1);
						}

						if (pedProperties.child("PedProps")) {
							for (auto& nodeProps = pedProperties.child("PedProps").first_child(); nodeProps; nodeProps = nodeProps.next_sibling()) {
								int modType = stoi(string(nodeProps.name()).substr(1));
								string modValueStr = nodeProps.text().as_string();
								if (modValueStr.find(",") != string::npos) {
									//stoi(modValueStr.substr(0, modValueStr.find(","))) ------- stoi(modValueStr.substr(modValueStr.find(",") + 1))

								}
							}
						}

						if (pedProperties.child("PedComps")) {
							for (auto& nodeComps = pedProperties.child("PedComps").first_child(); nodeComps; nodeComps = nodeComps.next_sibling()) {
								int modType = stoi(string(nodeComps.name()).substr(1));
								string modValueStr = nodeComps.text().as_string();
								if (modValueStr.find(",") != string::npos) {
									PED::SetPedComponentVariation(data.Handle, modType, stoi(modValueStr.substr(0, modValueStr.find(","))), stoi(modValueStr.substr(modValueStr.find(",") + 1)), 0);
								}
							}
						}

						if (pedProperties.child("RelationshipGroupAltered").text().as_bool()) {
							PED::SetPedRelationshipGroupDefaultHash(data.Handle, pedProperties.child("RelationshipGroup").text().as_uint());
						}

						if (pedProperties.child("ScenarioActive").text().as_bool()) {
							BRAIN::TaskStartScenarioInPlace(data.Handle, (char*)pedProperties.child("ScenarioName").text().as_string(), 0, 1);
						}

						if (pedProperties.child("AnimActive").text().as_bool()) {
							char* animDict = (char*)pedProperties.child("AnimDict").text().as_string();
							char* animName = (char*)pedProperties.child("AnimName").text().as_string();

							STREAMING::RequestAnimDict(animDict);
							BRAIN::TaskPlayAnim(data.Handle, animDict, animName, 8, 0, -1, 9, 0, 0, 0, 0);
						}
					}
					break;
				}
			case 2: { // vehicle
					data.Handle = VEHICLE::CreateVehicle(data.ModelHash, data.Placement.Position.x, data.Placement.Position.y, data.Placement.Position.z, 1, 1, data.Dynamic, 1);
					if (ENTITY::DoesEntityExist(data.Handle)) {
						ENTITY::FreezeEntityPosition(data.Handle, data.FrozenPosition);

						VEHICLE::SetVehicleModKit(data.Handle, 0);
						if (data.OpacityLevel < 255) ENTITY::SetEntityAlpha(data.Handle, data.OpacityLevel, 0);
						ENTITY::SetEntityLodDist(data.Handle, data.LodDistance);
						ENTITY::SetEntityVisible(data.Handle, data.IsVisible, 1);

						if (data.MaxHealth) ENTITY::SetEntityMaxHealth(data.Handle, data.MaxHealth);
						if (data.Health) ENTITY::SetEntityHealth(data.Handle, data.Health);

						VEHICLE::SetVehicleGravity(data.Handle, data.HasGravity);

						data.IsOnFire ? FIRE::StartEntityFire(data.Handle) : FIRE::StopEntityFire(data.Handle);

						ENTITY::SetEntityInvincible(data.Handle, data.IsInvincible);
						ENTITY::SetEntityProofs(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);
						ENTITY::SetEntityOnlyDamagedByPlayer(data.Handle, data.IsOnlyDamagedByPlayer);

						auto& vehicleProperties = node.child("VehicleProperties");

						VEHICLE::SetVehicleLivery(data.Handle, vehicleProperties.child("Livery").text().as_int());

						auto& vehicleColors = vehicleProperties.child("Colours");

						int currentPrimaryColor, currentSecondaryColor;
						VEHICLE::GetVehicleColours(data.Handle, &currentPrimaryColor, &currentSecondaryColor);
						VEHICLE::SetVehicleColours(data.Handle, vehicleColors.child("Primary").text().as_int(), currentSecondaryColor);
						VEHICLE::GetVehicleColours(data.Handle, &currentPrimaryColor, &currentSecondaryColor);
						VEHICLE::SetVehicleColours(data.Handle, currentPrimaryColor, vehicleColors.child("Secondary").text().as_int());

						int currentPearlescentColor, currentWheelColor;
						VEHICLE::GetVehicleExtraColours(data.Handle, &currentPearlescentColor, &currentWheelColor);
						VEHICLE::SetVehicleExtraColours(data.Handle, vehicleColors.child("Pearl").text().as_int(), currentWheelColor);
						VEHICLE::GetVehicleExtraColours(data.Handle, &currentPearlescentColor, &currentWheelColor);
						VEHICLE::SetVehicleExtraColours(data.Handle, currentPearlescentColor, vehicleColors.child("Rim").text().as_int());

						bool isPrimaryColourCustom = vehicleColors.child("IsPrimaryColourCustom").text().as_bool();
						bool isSecondaryColourCustom = vehicleColors.child("IsSecondaryColourCustom").text().as_bool();

						Color vehicleColor;

						if (isPrimaryColourCustom) {
							vehicleColor.m_r = vehicleColors.child("Cust1_R").text().as_int();
							vehicleColor.m_g = vehicleColors.child("Cust1_G").text().as_int();
							vehicleColor.m_b = vehicleColors.child("Cust1_B").text().as_int();
							VEHICLE::SetVehicleCustomPrimaryColour(data.Handle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);
						}

						if (isSecondaryColourCustom) {
							vehicleColor.m_r = vehicleColors.child("Cust2_R").text().as_int();
							vehicleColor.m_g = vehicleColors.child("Cust2_G").text().as_int();
							vehicleColor.m_b = vehicleColors.child("Cust2_B").text().as_int();
							VEHICLE::SetVehicleCustomSecondaryColour(data.Handle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);
						}

						vehicleColor.m_r = vehicleColors.child("tyreSmoke_R").text().as_int();
						vehicleColor.m_g = vehicleColors.child("tyreSmoke_G").text().as_int();
						vehicleColor.m_b = vehicleColors.child("tyreSmoke_B").text().as_int();
						VEHICLE::SetVehicleTyreSmokeColor(data.Handle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);

						int mod1a = vehicleColors.child("Mod1_a").text().as_int();
						int mod1b = vehicleColors.child("Mod1_b").text().as_int();
						int mod1c = vehicleColors.child("Mod1_c").text().as_int();
						VEHICLE::SetVehicleModColor1(data.Handle, mod1a, mod1b, mod1c);

						int mod2a = vehicleColors.child("Mod2_a").text().as_int();
						int mod2b = vehicleColors.child("Mod2_b").text().as_int();
						VEHICLE::SetVehicleModColor2(data.Handle, mod2a, mod2b);

						VEHICLE::SetVehicleNumberPlateText(data.Handle, (char*)vehicleProperties.child("NumberPlateText").text().as_string());
						VEHICLE::SetVehicleNumberPlateTextIndex(data.Handle, vehicleProperties.child("NumberPlateIndex").text().as_int());
						VEHICLE::SetVehicleWheelType(data.Handle, vehicleProperties.child("WheelType").text().as_int());

						string engineSoundName = vehicleProperties.child("EngineSoundName").text().as_string();
						//if (!engineSoundName.empty()) _FORCE_VEHICLE_ENGINE_AUDIO(data.Handle, (char*)engineSoundName.c_str());

						VEHICLE::SetVehicleWindowTint(data.Handle, vehicleProperties.child("WindowTint").text().as_int());
						VEHICLE::SetVehicleTyresCanBurst(data.Handle, !vehicleProperties.child("BulletProofTyres").text().as_bool());
						VEHICLE::SetVehicleDirtLevel(data.Handle, vehicleProperties.child("DirtLevel").text().as_float());
						VEHICLE::SetVehicleEnveffScale(data.Handle, vehicleProperties.child("PaintFade").text().as_float());

						switch (vehicleProperties.child("RoofState").text().as_int()) {
							case 0:
							case 3:
								VEHICLE::RaiseConvertibleRoof(data.Handle, false);
								break;
							case 2:
							case 1:
								VEHICLE::LowerConvertibleRoof(data.Handle, false);
								break;
						}

						VEHICLE::SetVehicleSiren(data.Handle, vehicleProperties.child("SirenActive").text().as_bool());

						if (vehicleProperties.child("EngineOn")) VEHICLE::SetVehicleEngineOn(data.Handle, vehicleProperties.child("EngineOn").text().as_bool(), true, 0);
						if (vehicleProperties.child("EngineHealth")) VEHICLE::SetVehicleEngineHealth(data.Handle, vehicleProperties.child("EngineHealth").text().as_int());

						if (vehicleProperties.child("LightsOn")) VEHICLE::SetVehicleLights(data.Handle, vehicleProperties.child("LightsOn").text().as_bool() ? 3 : 4);
						if (vehicleProperties.child("IsRadioLoud").text().as_int(0)) {
							AUDIO::SetVehicleRadioLoud(data.Handle, vehicleProperties.child("IsRadioLoud").text().as_bool());
							AUDIO::SetVehicleRadioEnabled(data.Handle, true);
						}

						VEHICLE::SetVehicleDoorsLocked(data.Handle, vehicleProperties.child("LockStatus").text().as_int());

						auto& vehicleNeons = vehicleProperties.child("Neons");

						VEHICLE::_SetVehicleNeonLightEnabled(data.Handle, 0, vehicleNeons.child("Left").text().as_bool());
						VEHICLE::_SetVehicleNeonLightEnabled(data.Handle, 1, vehicleNeons.child("Right").text().as_bool());
						VEHICLE::_SetVehicleNeonLightEnabled(data.Handle, 2, vehicleNeons.child("Front").text().as_bool());
						VEHICLE::_SetVehicleNeonLightEnabled(data.Handle, 3, vehicleNeons.child("Back").text().as_bool());
						VEHICLE::_SetVehicleNeonLightsColour(data.Handle, vehicleNeons.child("R").text().as_int(), vehicleNeons.child("G").text().as_int(), vehicleNeons.child("B").text().as_int());

						auto& vehicleModExtras = vehicleProperties.child("ModExtras");

						for (auto& nodeVehicleModExtrasObject = vehicleModExtras.first_child(); nodeVehicleModExtrasObject; nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling()) {
							VEHICLE::SetVehicleExtra(data.Handle, stoi(string(nodeVehicleModExtrasObject.name()).substr(1)), !nodeVehicleModExtrasObject.text().as_bool());
						}

						auto& vehicleMods = vehicleProperties.child("Mods");

						for (auto& nodeVehicleModsObject = vehicleMods.first_child(); nodeVehicleModsObject; nodeVehicleModsObject = nodeVehicleModsObject.next_sibling()) {
							int modType = stoi(string(nodeVehicleModsObject.name()).substr(1));
							string modValueStr = nodeVehicleModsObject.text().as_string();
							if (modValueStr.find(",") == string::npos) {
								VEHICLE::ToggleVehicleMod(data.Handle, modType, nodeVehicleModsObject.text().as_bool());
							} else {
								VEHICLE::SetVehicleMod(data.Handle, modType, stoi(modValueStr.substr(0, modValueStr.find(","))), stoi(modValueStr.substr(modValueStr.find(",") + 1)) ? true : false);
							}
						}

						auto& vehicleDoorsOpen = vehicleProperties.child("DoorsOpen");

						if (vehicleDoorsOpen) {
							if (vehicleDoorsOpen.child("BackLeftDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 2, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 2, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("BackRightDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 3, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 3, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("FrontLeftDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 0, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 0, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("FrontRightDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 1, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 1, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("Hood").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 4, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 4, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("Trunk").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 5, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 5, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}

							if (vehicleDoorsOpen.child("Trunk2").text().as_bool()) {
								VEHICLE::SetVehicleDoorOpen(data.Handle, 6, false, true);
								AUDIO::PlayVehicleDoorOpenSound(data.Handle, 1);
							} else {
								VEHICLE::SetVehicleDoorShut(data.Handle, 6, true);
								AUDIO::PlayVehicleDoorCloseSound(data.Handle, 1);
							}
						}

						auto& vehicleDoorsBroken = vehicleProperties.child("DoorsBroken");

						if (vehicleDoorsBroken) {
							if (vehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 2, true);
							}

							if (vehicleDoorsBroken.child("BackRightDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 3, true);
							}

							if (vehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 0, true);
							}

							if (vehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 1, true);
							}

							if (vehicleDoorsBroken.child("Hood").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 4, true);
							}

							if (vehicleDoorsBroken.child("Trunk").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 5, true);
							}

							if (vehicleDoorsBroken.child("Trunk2").text().as_bool()) {
								VEHICLE::SetVehicleDoorBroken(data.Handle, 6, true);
							}
						}

						auto& vehicleTyresBursted = vehicleProperties.child("TyresBursted");

						if (vehicleTyresBursted) {
							if (vehicleTyresBursted.child("FrontLeft").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 0, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("FrontRight").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 1, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("_2").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 2, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("_3").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 3, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("BackLeft").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 4, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("BackRight").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 5, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("_6").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 6, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("_7").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 7, 1, 1000.f);
							}

							if (vehicleTyresBursted.child("_8").text().as_bool()) {
								if (!VEHICLE::GetVehicleTyresCanBurst(data.Handle)) VEHICLE::SetVehicleTyresCanBurst(data.Handle, true);
								VEHICLE::SetVehicleTyreBurst(data.Handle, 8, 1, 1000.f);
							}
						}

						auto& vehicleRpmMultiplier = vehicleProperties.child("RpmMultiplier");
						auto& vehicleTorqueMultiplier = vehicleProperties.child("TorqueMultiplier");
						auto& vehicleMaxSpeed = vehicleProperties.child("MaxSpeed");
						auto& vehicleHeadlightIntensity = vehicleProperties.child("HeadlightIntensity");

						if (vehicleRpmMultiplier) {
							VEHICLE::_SetVehicleEnginePowerMultiplier(data.Handle, vehicleRpmMultiplier.text().as_float());
						}

						if (vehicleTorqueMultiplier) {
							VEHICLE::_SetVehicleEngineTorqueMultiplier(data.Handle, vehicleTorqueMultiplier.text().as_float());
						}

						if (vehicleMaxSpeed) {
							ENTITY::SetEntityMaxSpeed(data.Handle, vehicleMaxSpeed.text().as_float());
						}

						if (vehicleHeadlightIntensity) {
							VEHICLE::SetVehicleLightMultiplier(data.Handle, vehicleHeadlightIntensity.text().as_float());
						}

					}
					break;
				}
			case 3: { // object

					data.Handle = OBJECT::CreateObject(data.ModelHash, data.Placement.Position.x, data.Placement.Position.y, data.Placement.Position.z, 1, 1, data.Dynamic);
					if (ENTITY::DoesEntityExist(data.Handle)) {
						ENTITY::FreezeEntityPosition(data.Handle, data.FrozenPosition);

						if (data.OpacityLevel < 255) ENTITY::SetEntityAlpha(data.Handle, data.OpacityLevel, 0);
						ENTITY::SetEntityLodDist(data.Handle, data.LodDistance);
						ENTITY::SetEntityVisible(data.Handle, data.IsVisible, 1);

						if (data.MaxHealth) ENTITY::SetEntityMaxHealth(data.Handle, data.MaxHealth);
						if (data.Health) ENTITY::SetEntityHealth(data.Handle, data.Health);

						data.IsOnFire ? FIRE::StartEntityFire(data.Handle) : FIRE::StopEntityFire(data.Handle);

						ENTITY::SetEntityInvincible(data.Handle, data.IsInvincible);
						ENTITY::SetEntityProofs(data.Handle, data.IsBulletProof, data.IsFireProof, data.IsExplosionProof, data.IsCollisionProof, data.IsMeleeProof, 1, 1, 1);

						ENTITY::SetEntityOnlyDamagedByPlayer(data.Handle, data.IsOnlyDamagedByPlayer);
					}
					break;
				}
		}

		vars.spoonerSpawnedAttachments.push_back(data.Handle);

		return data;
	}

	void LoadSpoonerFile(string fileName) { // LoadSpoonerFile("CoolCreation");
		ENTITY::SetEntityVisible(GetLocalPlayer().m_ped, true, true);

		if (vars.deletePreviousCreation) {
			for (auto& e : vars.spoonerSpawnedVehicles) {
				ENTITY::SetEntityAsMissionEntity(e, 1, 1);
				ENTITY::DeleteEntity(&e);
			}

			for (auto& e : vars.spoonerSpawnedAttachments) {
				ENTITY::SetEntityAsMissionEntity(e, 1, 1);
				ENTITY::DeleteEntity(&e);
			}
		}

		spoonerVehicleHandle = 0;
		spoonerInitialHandle = 0;

		xml_document doc;

		if (doc.load_file(va("%s/%s.xml", GetConfig()->GetVehiclesPath(), fileName.c_str())).status != pugi::status_ok) {
			GetRenderer()->NotifyMap("Error: Unable to load file.");
			return;
		}

#pragma region Root

		auto& root = doc.child("Vehicle");
		if (root) {
			Hash vehicleHash = root.child("ModelHash").text().as_uint();
			spoonerInitialHandle = root.child("InitialHandle").text().as_int();

			GetEntityControl()->SimpleRequestModel(vehicleHash);

			Vector3 myCoords = GetLocalPlayer().m_coordinates;

			float forward = 5.f;
			float playerHeading = ENTITY::GetEntityHeading(GetLocalPlayer().m_ped);

			float xVect = forward * sin(Utils::degToRad(playerHeading)) * -1.0f;
			float yVect = forward * cos(Utils::degToRad(playerHeading));


			spoonerVehicleHandle = VEHICLE::CreateVehicle(vehicleHash, GetLocalPlayer().m_coordinates.x + xVect, GetLocalPlayer().m_coordinates.y + yVect, GetLocalPlayer().m_coordinates.z, playerHeading, true, true, true);

			vars.spoonerSpawnedVehicles.push_back(spoonerVehicleHandle);

			DECORATOR::DecorSetInt(spoonerVehicleHandle, "MPBitset", 0);
			VEHICLE::SetVehicleIsStolen(spoonerVehicleHandle, false);

			if (GetLocalPlayer().m_isInVehicle) {
				ENTITY::SetEntityAsMissionEntity(GetLocalPlayer().m_vehicle, 1, 1);
				ENTITY::DeleteEntity(&GetLocalPlayer().m_vehicle);
			}

			PED::SetPedIntoVehicle(GetLocalPlayer().m_ped, spoonerVehicleHandle, -1);
			VEHICLE::SetVehicleModKit(spoonerVehicleHandle, 0);

			GetLocalPlayer().m_vehicle = spoonerVehicleHandle;

			int opacityLevel = root.child("OpacityLevel").text().as_int();
			if (opacityLevel < 255) ENTITY::SetEntityAlpha(spoonerVehicleHandle, opacityLevel, 0);
			ENTITY::SetEntityLodDist(spoonerVehicleHandle, root.child("LodDistance").text().as_int());

			if (!root.child("IsVisible").text().as_bool()) {
				//ENTITY::SetEntityAlpha(spoonerVehicleHandle, 255, false);
				ENTITY::SetEntityVisible(spoonerVehicleHandle, false, 1);
			}

			if (root.child("MaxHealth")) ENTITY::SetEntityMaxHealth(spoonerVehicleHandle, root.child("MaxHealth").text().as_int());
			if (root.child("Health")) ENTITY::SetEntityHealth(spoonerVehicleHandle, root.child("Health").text().as_int());

			VEHICLE::SetVehicleGravity(spoonerVehicleHandle, root.child("HasGravity").text().as_bool(true));

			root.child("IsOnFire").text().as_bool() ? FIRE::StartEntityFire(spoonerVehicleHandle) : FIRE::StopEntityFire(spoonerVehicleHandle);

			ENTITY::SetEntityInvincible(spoonerVehicleHandle, root.child("IsInvincible").text().as_bool());
			ENTITY::SetEntityProofs(spoonerVehicleHandle, root.child("IsBulletProof").text().as_bool(), root.child("IsFireProof").text().as_bool(), root.child("IsExplosionProof").text().as_bool(), root.child("IsCollisionProof").text().as_bool(), root.child("IsMeleeProof").text().as_bool(), 1, 1, 1);
			ENTITY::SetEntityOnlyDamagedByPlayer(spoonerVehicleHandle, root.child("IsOnlyDamagedByPlayer").text().as_bool());

			auto& vehicleProperties = root.child("VehicleProperties");

			VEHICLE::SetVehicleLivery(spoonerVehicleHandle, vehicleProperties.child("Livery").text().as_int());

			auto& vehicleColors = vehicleProperties.child("Colours");

			int currentPrimaryColor, currentSecondaryColor;
			VEHICLE::GetVehicleColours(spoonerVehicleHandle, &currentPrimaryColor, &currentSecondaryColor);
			VEHICLE::SetVehicleColours(spoonerVehicleHandle, vehicleColors.child("Primary").text().as_int(), currentSecondaryColor);
			VEHICLE::GetVehicleColours(spoonerVehicleHandle, &currentPrimaryColor, &currentSecondaryColor);
			VEHICLE::SetVehicleColours(spoonerVehicleHandle, currentPrimaryColor, vehicleColors.child("Secondary").text().as_int());

			int currentPearlescentColor, currentWheelColor;
			VEHICLE::GetVehicleExtraColours(spoonerVehicleHandle, &currentPearlescentColor, &currentWheelColor);
			VEHICLE::SetVehicleExtraColours(spoonerVehicleHandle, vehicleColors.child("Pearl").text().as_int(), currentWheelColor);
			VEHICLE::GetVehicleExtraColours(spoonerVehicleHandle, &currentPearlescentColor, &currentWheelColor);
			VEHICLE::SetVehicleExtraColours(spoonerVehicleHandle, currentPearlescentColor, vehicleColors.child("Rim").text().as_int());

			bool isPrimaryColourCustom = vehicleColors.child("IsPrimaryColourCustom").text().as_bool();
			bool isSecondaryColourCustom = vehicleColors.child("IsSecondaryColourCustom").text().as_bool();

			Color vehicleColor;

			if (isPrimaryColourCustom) {
				vehicleColor.m_r = vehicleColors.child("Cust1_R").text().as_int();
				vehicleColor.m_g = vehicleColors.child("Cust1_G").text().as_int();
				vehicleColor.m_b = vehicleColors.child("Cust1_B").text().as_int();
				VEHICLE::SetVehicleCustomPrimaryColour(spoonerVehicleHandle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);
			}

			if (isSecondaryColourCustom) {
				vehicleColor.m_r = vehicleColors.child("Cust2_R").text().as_int();
				vehicleColor.m_g = vehicleColors.child("Cust2_G").text().as_int();
				vehicleColor.m_b = vehicleColors.child("Cust2_B").text().as_int();
				VEHICLE::SetVehicleCustomSecondaryColour(spoonerVehicleHandle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);
			}

			vehicleColor.m_r = vehicleColors.child("tyreSmoke_R").text().as_int();
			vehicleColor.m_g = vehicleColors.child("tyreSmoke_G").text().as_int();
			vehicleColor.m_b = vehicleColors.child("tyreSmoke_B").text().as_int();
			VEHICLE::SetVehicleTyreSmokeColor(spoonerVehicleHandle, vehicleColor.m_r, vehicleColor.m_g, vehicleColor.m_b);

			int mod1a = vehicleColors.child("Mod1_a").text().as_int();
			int mod1b = vehicleColors.child("Mod1_b").text().as_int();
			int mod1c = vehicleColors.child("Mod1_c").text().as_int();
			VEHICLE::SetVehicleModColor1(spoonerVehicleHandle, mod1a, mod1b, mod1c);

			int mod2a = vehicleColors.child("Mod2_a").text().as_int();
			int mod2b = vehicleColors.child("Mod2_b").text().as_int();
			VEHICLE::SetVehicleModColor2(spoonerVehicleHandle, mod2a, mod2b);

			VEHICLE::SetVehicleNumberPlateText(spoonerVehicleHandle, (char*)vehicleProperties.child("NumberPlateText").text().as_string());
			VEHICLE::SetVehicleNumberPlateTextIndex(spoonerVehicleHandle, vehicleProperties.child("NumberPlateIndex").text().as_int());
			VEHICLE::SetVehicleWheelType(spoonerVehicleHandle, vehicleProperties.child("WheelType").text().as_int());

			string engineSoundName = vehicleProperties.child("EngineSoundName").text().as_string();
			//if (!engineSoundName.empty()) _FORCE_VEHICLE_ENGINE_AUDIO(spoonerVehicleHandle, (char*)engineSoundName.c_str());

			VEHICLE::SetVehicleWindowTint(spoonerVehicleHandle, vehicleProperties.child("WindowTint").text().as_int());
			VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, !vehicleProperties.child("BulletProofTyres").text().as_bool());
			VEHICLE::SetVehicleDirtLevel(spoonerVehicleHandle, vehicleProperties.child("DirtLevel").text().as_float());
			VEHICLE::SetVehicleEnveffScale(spoonerVehicleHandle, vehicleProperties.child("PaintFade").text().as_float());

			switch (vehicleProperties.child("RoofState").text().as_int()) {
				case 0:
				case 3:
					VEHICLE::RaiseConvertibleRoof(spoonerVehicleHandle, false);
					break;
				case 2:
				case 1:
					VEHICLE::LowerConvertibleRoof(spoonerVehicleHandle, false);
					break;
			}

			VEHICLE::SetVehicleSiren(spoonerVehicleHandle, vehicleProperties.child("SirenActive").text().as_bool());

			if (vehicleProperties.child("EngineOn")) VEHICLE::SetVehicleEngineOn(spoonerVehicleHandle, vehicleProperties.child("EngineOn").text().as_bool(), true, 0);
			if (vehicleProperties.child("EngineHealth")) VEHICLE::SetVehicleEngineHealth(spoonerVehicleHandle, vehicleProperties.child("EngineHealth").text().as_int());

			if (vehicleProperties.child("LightsOn")) VEHICLE::SetVehicleLights(spoonerVehicleHandle, vehicleProperties.child("LightsOn").text().as_bool() ? 3 : 4);
			if (vehicleProperties.child("IsRadioLoud").text().as_int(0)) {
				AUDIO::SetVehicleRadioLoud(spoonerVehicleHandle, vehicleProperties.child("IsRadioLoud").text().as_bool());
				AUDIO::SetVehicleRadioEnabled(spoonerVehicleHandle, true);
			}

			VEHICLE::SetVehicleDoorsLocked(spoonerVehicleHandle, vehicleProperties.child("LockStatus").text().as_bool());

			auto& vehicleNeons = vehicleProperties.child("Neons");

			VEHICLE::_SetVehicleNeonLightEnabled(spoonerVehicleHandle, 0, vehicleNeons.child("Left").text().as_bool());
			VEHICLE::_SetVehicleNeonLightEnabled(spoonerVehicleHandle, 1, vehicleNeons.child("Right").text().as_bool());
			VEHICLE::_SetVehicleNeonLightEnabled(spoonerVehicleHandle, 2, vehicleNeons.child("Front").text().as_bool());
			VEHICLE::_SetVehicleNeonLightEnabled(spoonerVehicleHandle, 3, vehicleNeons.child("Back").text().as_bool());
			VEHICLE::_SetVehicleNeonLightsColour(spoonerVehicleHandle, vehicleNeons.child("R").text().as_int(), vehicleNeons.child("G").text().as_int(), vehicleNeons.child("B").text().as_int());

			auto& vehicleModExtras = vehicleProperties.child("ModExtras");

			for (auto& nodeVehicleModExtrasObject = vehicleModExtras.first_child(); nodeVehicleModExtrasObject; nodeVehicleModExtrasObject = nodeVehicleModExtrasObject.next_sibling()) {
				VEHICLE::SetVehicleExtra(spoonerVehicleHandle, stoi(string(nodeVehicleModExtrasObject.name()).substr(1)), !nodeVehicleModExtrasObject.text().as_bool());
			}

			auto& vehicleMods = vehicleProperties.child("Mods");

			for (auto& nodeVehicleModsObject = vehicleMods.first_child(); nodeVehicleModsObject; nodeVehicleModsObject = nodeVehicleModsObject.next_sibling()) {
				int modType = stoi(string(nodeVehicleModsObject.name()).substr(1));
				string modValueStr = nodeVehicleModsObject.text().as_string();
				if (modValueStr.find(",") == string::npos) {
					VEHICLE::ToggleVehicleMod(spoonerVehicleHandle, modType, nodeVehicleModsObject.text().as_bool());
				} else {
					VEHICLE::SetVehicleMod(spoonerVehicleHandle, modType, stoi(modValueStr.substr(0, modValueStr.find(","))) ? true : false, stoi(modValueStr.substr(modValueStr.find(",") + 1)) ? true : false);
				}
			}

			auto& vehicleDoorsOpen = vehicleProperties.child("DoorsOpen");

			if (vehicleDoorsOpen) {
				if (vehicleDoorsOpen.child("BackLeftDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 2, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 2, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("BackRightDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 3, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 3, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("FrontLeftDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 0, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 0, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("FrontRightDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 1, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 1, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Hood").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 4, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 4, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Trunk").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 5, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 5, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}

				if (vehicleDoorsOpen.child("Trunk2").text().as_bool()) {
					VEHICLE::SetVehicleDoorOpen(spoonerVehicleHandle, 6, false, true);
					AUDIO::PlayVehicleDoorOpenSound(spoonerVehicleHandle, 1);
				} else {
					VEHICLE::SetVehicleDoorShut(spoonerVehicleHandle, 6, true);
					AUDIO::PlayVehicleDoorCloseSound(spoonerVehicleHandle, 1);
				}
			}

			auto& vehicleDoorsBroken = vehicleProperties.child("DoorsBroken");

			if (vehicleDoorsBroken) {
				if (vehicleDoorsBroken.child("BackLeftDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 2, true);
				}

				if (vehicleDoorsBroken.child("BackRightDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 3, true);
				}

				if (vehicleDoorsBroken.child("FrontLeftDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 0, true);
				}

				if (vehicleDoorsBroken.child("FrontRightDoor").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 1, true);
				}

				if (vehicleDoorsBroken.child("Hood").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 4, true);
				}

				if (vehicleDoorsBroken.child("Trunk").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 5, true);
				}

				if (vehicleDoorsBroken.child("Trunk2").text().as_bool()) {
					VEHICLE::SetVehicleDoorBroken(spoonerVehicleHandle, 6, true);
				}
			}

			auto& vehicleTyresBursted = vehicleProperties.child("TyresBursted");

			if (vehicleTyresBursted) {
				if (vehicleTyresBursted.child("FrontLeft").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 0, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("FrontRight").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 1, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_2").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 2, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_3").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 3, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("BackLeft").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 4, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("BackRight").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 5, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_6").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 6, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_7").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 7, 1, 1000.f);
				}

				if (vehicleTyresBursted.child("_8").text().as_bool()) {
					if (!VEHICLE::GetVehicleTyresCanBurst(spoonerVehicleHandle)) VEHICLE::SetVehicleTyresCanBurst(spoonerVehicleHandle, true);
					VEHICLE::SetVehicleTyreBurst(spoonerVehicleHandle, 8, 1, 1000.f);
				}
			}

			auto& vehicleRpmMultiplier = vehicleProperties.child("RpmMultiplier");
			auto& vehicleTorqueMultiplier = vehicleProperties.child("TorqueMultiplier");
			auto& vehicleMaxSpeed = vehicleProperties.child("MaxSpeed");
			auto& vehicleHeadlightIntensity = vehicleProperties.child("HeadlightIntensity");

			if (vehicleRpmMultiplier) {
				VEHICLE::_SetVehicleEnginePowerMultiplier(spoonerVehicleHandle, vehicleRpmMultiplier.text().as_float());
			}

			if (vehicleTorqueMultiplier) {
				VEHICLE::_SetVehicleEngineTorqueMultiplier(spoonerVehicleHandle, vehicleTorqueMultiplier.text().as_float());
			}

			if (vehicleMaxSpeed) {
				ENTITY::SetEntityMaxSpeed(spoonerVehicleHandle, vehicleMaxSpeed.text().as_float());
			}

			if (vehicleHeadlightIntensity) {
				VEHICLE::SetVehicleLightMultiplier(spoonerVehicleHandle, vehicleHeadlightIntensity.text().as_float());
			}
		} else {
			GetRenderer()->NotifyMap("Error: Couldn't parse root (Roots: \"Map\", \"Vehicle\").");
			return;
		}

#pragma endregion

#pragma region Attachments

		auto& attachments = root.child("SpoonerAttachments");
		if (attachments) {
			vector<Hash> usedModels;
			vector<SpoonerAttachments> attachmentData;

			for (auto& nodeAttachment = attachments.first_child(); nodeAttachment; nodeAttachment = nodeAttachment.next_sibling()) {
				GetEntityControl()->SimpleRequestModel(nodeAttachment.child("ModelHash").text().as_uint());
				if (nodeAttachment.child("Type").text().as_int() == 1) { // ped
					if (nodeAttachment.child("PedProperties").child("AnimActive").text().as_bool()) {
						STREAMING::RequestAnimDict((char*)nodeAttachment.child("PedProperties").child("AnimDict").text().as_string());
					}
				}

				usedModels.push_back(nodeAttachment.child("ModelHash").text().as_uint());
			}

			for (auto& nodeAttachment = attachments.first_child(); nodeAttachment; nodeAttachment = nodeAttachment.next_sibling()) {
				SpoonerAttachments e = SpawnEntityFromXmlNode(nodeAttachment);
				attachmentData.push_back(e);
			}

			if (!spoonerInitialHandle) {
				for (auto& e : attachmentData) {
					ENTITY::AttachEntityToEntity(e.Handle, spoonerVehicleHandle, e.Attachment.BoneIndex, e.Attachment.Position.x, e.Attachment.Position.y, e.Attachment.Position.z, e.Attachment.Rotation.x, e.Attachment.Rotation.y, e.Attachment.Rotation.z, 1, 0, vars.spawnWithCollision, 1, 2, 1);
				}
			} else {
				SpoonerAttachments temp;
				temp.Handle = spoonerVehicleHandle;
				temp.InitialHandle = spoonerInitialHandle; // ?
				attachmentData.push_back(temp);

				for (auto& e : attachmentData) {
					if (e.Attachment.IsAttached) {
						for (auto& b : attachmentData) {
							if (e.Handle != b.Handle && e.Attachment.AttachedTo == b.InitialHandle) {
								/*---->*/	ENTITY::AttachEntityToEntity(e.Handle, b.Handle, e.Attachment.BoneIndex, e.Attachment.Position.x, e.Attachment.Position.y, e.Attachment.Position.z, e.Attachment.Rotation.x, e.Attachment.Rotation.y, e.Attachment.Rotation.z, 1, 0, vars.spawnWithCollision, 1, 2, 1);
								break;
							}
						}
					}
				}
			}
			for (auto&e : usedModels) {
				STREAMING::SetModelAsNoLongerNeeded(e);
			}
			for (auto&e : attachmentData) {
				ENTITY::SetEntityAsNoLongerNeeded(&e.Handle);
			}
		}

#pragma endregion
	}
}

void XMLVehicleMenu::Init() {
	setParentSubmenu<LoadingMenu>();
	setName("XML vehicles", true, false);

	addOption(ToggleOption("Delete last creation")
		.addToggle(vars.deletePreviousCreation)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Delete the previously created XML creation"));

	addOption(ToggleOption("Spawn objects with collision")
		.addToggle(vars.spawnWithCollision)
		.addTranslation().canBeSaved().addHotkey()
		.addTooltip("Spawn the creation with collision"));
}

/*Update once when submenu is opened*/
void XMLVehicleMenu::UpdateOnce() {}

/*Update while submenu is active*/
void XMLVehicleMenu::Update() {
	static int TIMER;
	static bool shouldUpdate = false;

	Utils::DoTimedFunction(&TIMER, 2500, [] {shouldUpdate = true; });
	if (shouldUpdate) {
		clearOptionsOffset(2);
		GetConfig()->GetFilesFromDirectory(vars.fileNames, GetConfig()->GetVehiclesPath(), ".xml");
		if (!vars.fileNames.empty()) {
			if (vars.fileNames.size() > 0) {
				for (auto& e : vars.fileNames) {
					addOption(ButtonOption(e.c_str())
						.addFunction([=] { GetFiberPool()->DoJob([e] {LoadSpoonerFile(e); }); })
						.addTooltip("Spawn this vehicle"));
				}
			}
		}
		shouldUpdate = false;
	}
}

/*Background update*/
void XMLVehicleMenu::FeatureUpdate() {}

/*Singleton*/
XMLVehicleMenu* _instance;
XMLVehicleMenu* XMLVehicleMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new XMLVehicleMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
XMLVehicleMenu::~XMLVehicleMenu() { delete _instance; }