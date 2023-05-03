#include "stdafx.h"
#include "../src/menu/submenus/main/settingsMenu.h"
#include "menu\submenus\main\sessionMenu.h"
#include "menu/submenus/main/miscMenu.h"
#include "menu/submenus/main/session/streamermodeMenu.h"

const Texture medal = { "commonmenu", "common_medal" };
TranslationString strUnknown("~c~Unknown~s~", true, true);
TranslationString strDead("Dead", true, true);
TranslationString strFull("Full", true, true);
TranslationString strNorth("North", true, true);
TranslationString strEast("East", true, true);
TranslationString strSouth("South", true, true);
TranslationString strWest("West", true, true);
TranslationString strLeft("Player left", true, true);
TranslationString strHost("Host", true, true);
TranslationString strFriend("Friend", true, true);
TranslationString strMe("Me", true, true);
TranslationString strClient("Client", true, true);
TranslationString strModder("Modder", true, true);
TranslationString strHealth("Health", true, true);
TranslationString strArmor("Armor", true, true);
TranslationString strCash("Cash", true, true);
TranslationString strBank("Bank", true, true);
TranslationString strRank("Rank", true, true);
TranslationString strKD("K/D", true, true);
TranslationString strHeading("Heading", true, true);
TranslationString strWeapon("Weapon", true, true);
TranslationString strWanted("Wanted level", true, true);
TranslationString strAmmo("Ammo", true, true);
TranslationString strDistance("Distance", true, true);
TranslationString strSpeed("Speed (KMH)", true, true);
TranslationString strZone("Zone", true, true);
TranslationString strStreet("Street", true, true);
TranslationString strVehicle("Vehicle", true, true);
TranslationString strNotInVeh("Not in a vehicle", true, true);
TranslationString strNone("None", true, true);
TranslationString strModdedModel("Modded model", true, true);
TranslationString strPassive("Passive", true, true);
TranslationString strTyping("Typing", true, true);
TranslationString strPaused("Paused", true, true);
TranslationString strInvisible("Invisible", true, true);
TranslationString strGender("Gender", true, true);
TranslationString strIP("IP", true, true);
TranslationString strOfficeGarages("Office garages", true, true);
TranslationString strRockstarID("R* ID", true, true);
TranslationString strSC("Social Club Name", true, true);
TranslationString strYes("Yes", true, true);
TranslationString strNo("No", true, true);
TranslationString strGodmode("Godmode", true, true);
TranslationString strVehGodmode("Vehicle godmode", true, true);
TranslationString strOTR("Off the radar", true, true);
TranslationString strINT("In interior", true, true);
TranslationString strAir("In air", true, true);
TranslationString strKick("Voted for kick", true, true);
TranslationString strCutscene("Nearest to", true, true);
TranslationString strCutscene2("Cutscene", true, true);
TranslationString strFriendCount("Friend count", true, true);
TranslationString strRealName("Social club name", true, true);
TranslationString strOfficeGar("Office Garages", true, true);
TranslationString strProperty("Properties", true, true);
TranslationString strStance("Player status", true, true);
TranslationString strProperty2("Property #2", true, true);
TranslationString strProperty3("Property #3", true, true);
TranslationString strProperty4("Property #4", true, true);
TranslationString strOffice("Office", true, true);
TranslationString strClubhouse("Clubhouse", true, true);

String GetPropertyLabel(int Property) {
	String Return = "";
	switch (Property) {
	case 0:
		Return = "MP_REP_PROP_1";
		break;
	case 1:
		Return = "MP_PROP_1";
		break;

	case 2:
		Return = "MP_PROP_2";
		break;

	case 3:
		Return = "MP_PROP_3";
		break;

	case 4:
		Return = "MP_PROP_4";
		break;

	case 5:
		Return = "MP_PROP_5";
		break;

	case 6:
		Return = "MP_PROP_6";
		break;

	case 7:
		Return = "MP_PROP_7";
		break;

	case 8:
		Return = "MP_PROP_8";
		break;

	case 9:
		Return = "MP_PROP_9";
		break;

	case 10:
		Return = "MP_PROP_10";
		break;

	case 11:
		Return = "MP_PROP_11";
		break;

	case 12:
		Return = "MP_PROP_12";
		break;

	case 13:
		Return = "MP_PROP_13";
		break;

	case 14:
		Return = "MP_PROP_14";
		break;

	case 15:
		Return = "MP_PROP_15";
		break;

	case 16:
		Return = "MP_PROP_16";
		break;

	case 17:
		Return = "MP_PROP_17";
		break;

	case 18:
		Return = "MP_PROP_18";
		break;

	case 19:
		Return = "MP_PROP_19";
		break;

	case 20:
		Return = "MP_PROP_20";
		break;

	case 21:
		Return = "MP_PROP_21";
		break;

	case 22:
		Return = "MP_PROP_22";
		break;

	case 23:
		Return = "MP_PROP_23";
		break;

	case 24:
		Return = "MP_PROP_24";
		break;

	case 25:
		Return = "MP_PROP_25";
		break;

	case 26:
		Return = "MP_PROP_26";
		break;

	case 27:
		Return = "MP_PROP_27";
		break;

	case 28:
		Return = "MP_PROP_28";
		break;

	case 29:
		Return = "MP_PROP_29";
		break;

	case 30:
		Return = "MP_PROP_30";
		break;

	case 31:
		Return = "MP_PROP_31";
		break;

	case 32:
		Return = "MP_PROP_32";
		break;

	case 33:
		Return = "MP_PROP_33";
		break;

	case 34:
		Return = "MP_PROP_34";
		break;

	case 35:
		Return = "MP_PROP_35";
		break;

	case 36:
		Return = "MP_PROP_36";
		break;

	case 37:
		Return = "MP_PROP_37";
		break;

	case 38:
		Return = "MP_PROP_38";
		break;

	case 39:
		Return = "MP_PROP_39";
		break;

	case 40:
		Return = "MP_PROP_40";
		break;

	case 41:
		Return = "MP_PROP_41";
		break;

	case 42:
		Return = "MP_PROP_42";
		break;

	case 43:
		Return = "MP_PROP_43";
		break;

	case 44:
		Return = "MP_PROP_44";
		break;

	case 45:
		Return = "MP_PROP_45";
		break;

	case 46:
		Return = "MP_PROP_46";
		break;

	case 47:
		Return = "MP_PROP_48";
		break;

	case 48:
		Return = "MP_PROP_49";
		break;

	case 49:
		Return = "MP_PROP_50";
		break;

	case 50:
		Return = "MP_PROP_51";
		break;

	case 51:
		Return = "MP_PROP_52";
		break;

	case 52:
		Return = "MP_PROP_57";
		break;

	case 53:
		Return = "MP_PROP_59";
		break;

	case 54:
		Return = "MP_PROP_60";
		break;

	case 55:
		Return = "MP_PROP_61";
		break;

	case 56:
		Return = "MP_PROP_62";
		break;

	case 57:
		Return = "MP_PROP_63";
		break;

	case 58:
		Return = "MP_PROP_64";
		break;

	case 59:
		Return = "MP_PROP_65";
		break;

	case 60:
		Return = "MP_PROP_66";
		break;

	case 61:
		Return = "MP_PROP_67";
		break;

	case 62:
		Return = "MP_PROP_68";
		break;

	case 63:
		Return = "MP_PROP_69";
		break;

	case 64:
		Return = "MP_PROP_70";
		break;

	case 65:
		Return = "MP_PROP_71";
		break;

	case 66:
		Return = "MP_PROP_72";
		break;

	case 67:
		Return = "MP_PROP_73";
		break;

	case 68:
		Return = "MP_PROP_74";
		break;

	case 69:
		Return = "MP_PROP_75";
		break;

	case 70:
		Return = "MP_PROP_76";
		break;

	case 71:
		Return = "MP_PROP_77";
		break;

	case 72:
		Return = "MP_PROP_78";
		break;

	case 83:
		Return = "MP_PROP_79";
		break;

	case 84:
		Return = "MP_PROP_80";
		break;

	case 85:
		Return = "MP_PROP_81";
		break;

	case 73:
		Return = "MP_PROP_83";
		break;

	case 74:
		Return = "MP_PROP_84";
		break;

	case 75:
		Return = "MP_PROP_85";
		break;

	case 76:
		Return = "MP_PROP_86";
		break;

	case 77:
		Return = "MP_PROP_87";
		break;

	case 78:
		Return = "MP_PROP_89";
		break;

	case 79:
		Return = "MP_PROP_90";
		break;

	case 80:
		Return = "MP_PROP_92";
		break;

	case 81:
		Return = "MP_PROP_94";
		break;

	case 82:
		Return = "MP_PROP_95";
		break;

	case 86:
		Return = "PM_SPAWN_Y";
		break;

	case 87:
		Return = "MP_PROP_OFF1";
		break;

	case 88:
		Return = "MP_PROP_OFF2";
		break;

	case 89:
		Return = "MP_PROP_OFF3";
		break;

	case 90:
		Return = "MP_PROP_OFF4";
		break;

	case 91:
		Return = "MP_PROP_CLUBH1";
		break;

	case 92:
		Return = "MP_PROP_CLUBH2";
		break;

	case 93:
		Return = "MP_PROP_CLUBH3";
		break;

	case 94:
		Return = "MP_PROP_CLUBH4";
		break;

	case 95:
		Return = "MP_PROP_CLUBH5";
		break;

	case 96:
		Return = "MP_PROP_CLUBH6";
		break;

	case 97:
		Return = "MP_PROP_CLUBH7";
		break;

	case 98:
		Return = "MP_PROP_CLUBH8";
		break;

	case 99:
		Return = "MP_PROP_CLUBH9";
		break;

	case 100:
		Return = "MP_PROP_CLUBH10";
		break;

	case 101:
		Return = "MP_PROP_CLUBH11";
		break;

	case 102:
		Return = "MP_PROP_CLUBH12";
		break;

	case 103:
	case 106:
	case 109:
	case 112:
		Return = "MP_PROP_OFFG1";
		break;

	case 104:
	case 107:
	case 110:
	case 113:
		Return = "MP_PROP_OFFG2";
		break;

	case 105:
	case 108:
	case 111:
	case 114:
		Return = "MP_PROP_OFFG3";
		break;

	case 115:
		Return = "IE_WARE_1";
		break;
	}
	return HUD::_GetLabelText(Return);
}

float relevateX(float x) {
	return ((0.340703125f / 10000)*x + (0.340703125f / 10000) * 4000) / 16 * 9;
}
float relevateY(float y) {
	return ((0.49f / 12000)*y + (0.49f / 12000) * 8000);
}

void DrawSprite1(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha) {
	if (!GRAPHICS::HasStreamedTextureDictLoaded(textureDict)) { GRAPHICS::RequestStreamedTextureDict(textureDict, 0); }
	GRAPHICS::DrawSprite(textureDict, textureName, screenX, screenY, scaleX / 16, scaleY / 9, heading, red, green, blue, alpha, 0);
}

void DrawSprite2(const char* textureDict, const char* textureName, float screenX, float screenY, float scaleX, float scaleY, float heading, int red, int green, int blue, int alpha) {
	if (!GRAPHICS::HasStreamedTextureDictLoaded(textureDict)) { GRAPHICS::RequestStreamedTextureDict(textureDict, 0); }
	GRAPHICS::DrawSprite(textureDict, textureName, screenX, screenY, scaleX, scaleY, heading, red, green, blue, alpha, 0);
}

void UIPlayerInfoComponent::MapPanel() {
	float temp = 14;

	// Calculate Y Coord
	float bg_Y = ((temp * 0.035f) / 2.0f) + 0.159f;
	float bg_length = temp * 0.035f;
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y;
	float offsety = -0.268f;
	float offsetx = 0.184f;

	DrawSprite2("mp_freemode_mc", "debugmap", offsetx + xPos - 0.0055f, offsety + yPos + bg_length / 2 + 0.021f - 0.008f, (0.340703125f / 16 * 9) - 0.051f, bg_length - 0.042f - 0.016f, 0, 255, 255, 255, 255);
}

void UIPlayerInfoComponent::drawInfo(float x, float width, int yOffset, String name, String value, Texture text, Color color) {
	const Color white = { GetRenderer()->m_cOption.m_r, GetRenderer()->m_cOption.m_g, GetRenderer()->m_cOption.m_b, GetRenderer()->m_cOption.m_a };
	const float offset = 0.0025f;
	float xPos = m_parent->m_position.x + x - m_parent->m_size.x / 2;
	float yPos = m_parent->m_position.y + 0.022f * yOffset - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	if (text.isEmpty()) {
		GetRenderer()->DrawString(name, xPos + offset, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyLeft, xPos + offset, xPos + width - offset);
		GetRenderer()->DrawString(value, xPos + offset, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyRight, xPos + offset, xPos + width - offset);
	} else {
		GetRenderer()->DrawSpriteAspect(text, xPos + offset * 2, yPos + 0.015f, 25, 25, 0, color);
		GetRenderer()->DrawString(name, xPos + offset + 0.005f, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyLeft, xPos + offset + 0.005f, xPos + width - offset);
		GetRenderer()->DrawString(value, xPos + offset + 0.005f, yPos, GetRenderer()->m_textFont, 0.35f, white, false, JustifyRight, xPos + offset + 0.005f, xPos + width - offset);
	}
}

void UIPlayerInfoComponent::drawMiddleLine(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, 0.022f, GetRenderer()->m_cOutline);
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth, 0.022f, { 0, 0, 0, 255 });
}

void UIPlayerInfoComponent::drawMiddleLineTop(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f - 0.022f / 2 - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_cOutline);
}
void UIPlayerInfoComponent::drawMiddleLineBottom(int yOffset) {
	float xPos = m_parent->m_position.x;
	float yPos = m_parent->m_position.y + 0.022f * yOffset + 0.015f + 0.022f / 2 - m_parent->m_size.y / 2 + m_parent->m_headerHeight;
	GetRenderer()->DrawRect(xPos, yPos, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_lineWidth * 2, GetRenderer()->m_cOutline);
}
String GetEntityHealth(SPlayer& player) {
	int health = player.m_health;
	int max = player.m_maxHealth;
	float percentage = ((float)health / (float)max) * 100;
	if (health == 0 && max == 0)
		return va("~c~%s", strUnknown.Get());
	else if (health == 0 && max != 0)
		return va("~c~%s", strDead.Get());
	else if (health == max)
		return strFull.Get();
	else return va("%.0f%%", percentage);
}

String GetPlayerHeading(SPlayer& player) {
	int heading = player.m_heading;
	if (heading >= 0 && heading <= 90) {
		return va("%s (%i)", strNorth.Get(), heading);
	} else if (heading >= 90 && heading <= 180) {
		return va("%s (%i)", strEast.Get(), heading);
	} else if (heading >= 180 && heading <= 270) {
		return va("%s (%i)", strSouth.Get(), heading);
	} else if (heading >= 270 && heading <= 360) {
		return va("%s (%i)", strWest.Get(), heading);
	} else
		return va("~c~%s", strUnknown.Get());
}

String GetPlayerWeaponName(SPlayer& player) {
	switch (player.m_weaponHash) {
		case 2725352035:	return HUD::_GetLabelText("WT_UNARMED");
		case 2578778090:	return HUD::_GetLabelText("WT_KNIFE");
		case 1737195953:	return HUD::_GetLabelText("WT_NGTSTK");
		case 1317494643:	return HUD::_GetLabelText("WT_HAMMER");
		case 2508868239:	return HUD::_GetLabelText("WT_BAT");
		case 1141786504:	return HUD::_GetLabelText("WT_GOLFCLUB");
		case 2227010557:	return HUD::_GetLabelText("WT_CROWBAR");
		case 453432689:		return HUD::_GetLabelText("WT_PIST");
		case 1593441988:	return HUD::_GetLabelText("WT_PIST_CBT");
		case 584646201:		return HUD::_GetLabelText("WT_PIST_AP");
		case 2578377531:	return HUD::_GetLabelText("WT_PIST_50");
		case 324215364:		return HUD::_GetLabelText("WT_SMG_MCR");
		case 736523883:		return HUD::_GetLabelText("WT_SMG");
		case 4024951519:	return HUD::_GetLabelText("WT_SMG_ASL");
		case 3220176749:	return HUD::_GetLabelText("WT_RIFLE_ASL");
		case 2210333304:	return HUD::_GetLabelText("WT_RIFLE_CBN");
		case 2937143193:	return HUD::_GetLabelText("WT_RIFLE_ADV");
		case 2634544996:	return HUD::_GetLabelText("WT_MG");
		case 2144741730:	return HUD::_GetLabelText("WT_MG_CBT");
		case 487013001:		return HUD::_GetLabelText("WT_SG_PMP");
		case 2017895192:	return HUD::_GetLabelText("WT_SG_SOF");
		case 3800352039:	return HUD::_GetLabelText("WT_SG_ASL");
		case 2640438543:	return HUD::_GetLabelText("WT_SG_BLP");
		case 911657153:		return HUD::_GetLabelText("WT_STUN");
		case 100416529:		return HUD::_GetLabelText("WT_SNIP_RIF");
		case 205991906:		return HUD::_GetLabelText("WT_SNIP_HVY");
		case 2726580491:	return HUD::_GetLabelText("WT_GL");
		case 2982836145:	return HUD::_GetLabelText("WT_RPG");
		case 1119849093:	return HUD::_GetLabelText("WT_MINIGUN");
		case 2481070269:	return HUD::_GetLabelText("WT_GNADE");
		case 741814745:		return HUD::_GetLabelText("WT_GNADE_STK");
		case 4256991824:	return HUD::_GetLabelText("WT_GNADE_SMK");
		case 2694266206:	return HUD::_GetLabelText("WT_BZGAS");
		case 615608432:		return HUD::_GetLabelText("WT_MOLOTOV");
		case 101631238:		return HUD::_GetLabelText("WT_FIRE");
		case 883325847:		return HUD::_GetLabelText("WT_PETROL");
		case 600439132:		return HUD::_GetLabelText("WT_BALL");
		case 1233104067:	return HUD::_GetLabelText("WT_FLARE");
		case 3249783761:	return HUD::_GetLabelText("WT_REVOLVER");
		case 3756226112:	return HUD::_GetLabelText("WT_SWBLADE");
		case 940833800:		return HUD::_GetLabelText("WT_SHATCHET");
		case 4192643659:	return HUD::_GetLabelText("WT_BOTTLE");
		case 3218215474:	return HUD::_GetLabelText("WT_SNSPISTOL");
		case 317205821:		return HUD::_GetLabelText("WT_AUTOSHGN");
		case 3441901897:	return HUD::_GetLabelText("WT_BATTLEAXE");
		case 125959754:		return HUD::_GetLabelText("WT_CMPGL");
		case 3173288789:	return HUD::_GetLabelText("WT_MINISMG");
		case 3125143736:	return HUD::_GetLabelText("WT_PIPEBOMB");
		case 2484171525:	return HUD::_GetLabelText("WT_POOLCUE");
		case 419712736:		return HUD::_GetLabelText("WT_WRENCH");
		case 3523564046:	return HUD::_GetLabelText("WT_HVYPISTOL");
		case 3231910285:	return HUD::_GetLabelText("WT_SPCARBINE");
		case 2132975508:	return HUD::_GetLabelText("WT_BULLRIFLE");
		case 1672152130:	return HUD::_GetLabelText("WT_HOMLNCH");
		case 2874559379:	return HUD::_GetLabelText("WT_PRXMINE");
		case 126349499:		return HUD::_GetLabelText("WT_SNWBALL");
		case 2228681469:	return HUD::_GetLabelText("WT_BULLRIFLE2");
		case 2548703416:	return HUD::_GetLabelText("WT_REV_DA");
		case 1785463520:	return HUD::_GetLabelText("WT_MKRIFLE2");
		case 1432025498:	return HUD::_GetLabelText("WT_SG_PMP2");
		case 3415619887:	return HUD::_GetLabelText("WT_REVOLVER2");
		case 2285322324:	return HUD::_GetLabelText("WT_SNSPISTOL2");
		case 2526821735:	return HUD::_GetLabelText("WT_SPCARBINE2");
		case 961495388:		return HUD::_GetLabelText("WT_RIFLE_ASL2");
		case 4208062921:	return HUD::_GetLabelText("WT_RIFLE_CBN2");
		case 3686625920:	return HUD::_GetLabelText("WT_MG_CBT2");
		case 177293209:		return HUD::_GetLabelText("WT_SNIP_HVY2");
		case 3219281620:	return HUD::_GetLabelText("WT_PIST2");
		case 2024373456:	return HUD::_GetLabelText("WT_SMG2");
		case 2343591895:	return HUD::_GetLabelText("WT_FLASHLIGHT");
		case 1198879012:	return HUD::_GetLabelText("WT_FLAREGUN");
		case 2460120199:	return HUD::_GetLabelText("WT_DAGGER");
		case 137902532:		return HUD::_GetLabelText("WT_VPISTOL");
		case 2138347493:	return HUD::_GetLabelText("WT_FIREWRK");
		case 2828843422:	return HUD::_GetLabelText("WT_MUSKET");
		case 3713923289:	return HUD::_GetLabelText("WT_MACHETE");
		case 3675956304:	return HUD::_GetLabelText("WT_MCHPIST");
		case 1649403952:	return HUD::_GetLabelText("WT_CMPRIFLE");
		case 4019527611:	return HUD::_GetLabelText("WT_DBSHGN");
		case 984333226:		return HUD::_GetLabelText("WT_HVYSHGN");
		case 3342088282:	return HUD::_GetLabelText("WT_MKRIFLE");
		case 171789620:		return HUD::_GetLabelText("WT_COMBATPDW");
		case 3638508604:	return HUD::_GetLabelText("WT_KNUCKLE");
		case 3696079510:	return HUD::_GetLabelText("WT_MKPISTOL");
		case 1627465347:	return HUD::_GetLabelText("WT_GUSNBRG");
		case 4191993645:	return HUD::_GetLabelText("WT_HATCHET");
		case 1834241177:	return HUD::_GetLabelText("WT_RAILGUN");
		default:			return va("~c~%s", strUnknown.Get());
	}
}

String GetAmmoInPlayerWeapon(SPlayer& player) {
	int ammo = WEAPON::GetAmmoInPedWeapon(player.m_ped, player.m_weaponHash);
	return ammo > 0 ? va("%d", ammo) : va("~c~%s", strNone.Get());
}

String GetPlayerStreetName(Vector3 Coords) {
	Hash Street;
	Hash Crossing;
	PATHFIND::GetStreetNameAtCoord(Coords.x, Coords.y, Coords.z, &Street, &Crossing);
	String StreetLabel = HUD::GetStreetNameFromHashKey(Street);
	String CrossingLabel = HUD::GetStreetNameFromHashKey(Crossing);
	String output;
	if (strlen(StreetLabel) != 0) output = StreetLabel;
	else if (strlen(CrossingLabel) != 0) output = CrossingLabel;
	else output = va("~c~%s", strUnknown.Get());
	return output;
}

bool DoesPlayerHaveModdedModel(SPlayer& player) {
	Hash model = ENTITY::GetEntityModel(player.m_ped);
	return model != Utils::GetHashKey("MP_F_Freemode_01") && model != Utils::GetHashKey("MP_M_Freemode_01");
}

bool GetNameFromHandle(SPlayer& player) {
	/*int handle[76];
	NETWORK::NetworkHandleFromPlayer(player, &handle[0], 13);
	if (NETWORK::NetworkIsHandleValid(&handle[0], 13)) {
		return NETWORK::NetworkGetGamertagFromHandle(handle);
	}

	return NULL;*/


	int Handle[13];
	NETWORK::NetworkHandleFromPlayer(player.m_id, &Handle[0], 13);
	if (NETWORK::NetworkIsHandleValid(&Handle[0], 13)) {
		string RealName = NETWORK::NetworkGetGamertagFromHandle(&Handle[0]);
		string nameOfPlayer = PLAYER::GetPlayerName(player.m_id);
		if (!strcmp(RealName.c_str(), nameOfPlayer.c_str())) {
			return true;
		} else {
			return false;
		}
	}

}

String GetPlayerIP(SPlayer& player) {
	if (player.m_id == GetLocalPlayer().m_id) return "255.255.255.255";
	if (player.m_isEvolveUserBlock) return "Impulse Block";
	CNetworkPlayerManager* playerManager = ReClass::GetNetworkPlayerManager();
	BYTE* ExternalIP = reinterpret_cast<BYTE*>(&playerManager->m_players[player.m_id]->PlayerInfo->ExternalIP);
	return va("%d.%d.%d.%d - P: %d", *(ExternalIP + 3), *(ExternalIP + 2), *(ExternalIP + 1), *ExternalIP, 6672);
}

String GetPlayerStance(SPlayer& player) {
	
	if (BRAIN::IsPedStill(player.m_ped)) {
		return va("Player is still");
	} else if (BRAIN::IsPedRunning(player.m_ped)) {
		return va("Player is running");
	} else if (BRAIN::IsPedSprinting(player.m_ped)) {
		return va("Player is sprinting");
	} else if (BRAIN::IsPedStrafing(player.m_ped)) {
		return va("Player is strafing");
	} else if (BRAIN::IsPedWalking(player.m_ped)) {
		return va("Player is walking");
	} else if (PED::IsPedClimbing(player.m_ped)) {
		return va("Player is climbing");
	} else if (PED::IsPedDiving(player.m_ped)) {
		return va("Player is diving");
	} else if (PED::IsPedFalling(player.m_ped)) {
		return va("Player is falling");
	} else if (PED::IsPedSwimming(player.m_ped)) {
		return va("Player is swimming");
	} else if (PED::IsPedShooting(player.m_ped)) {
		return va("Player is shooting");
	} else
		return va("~c~%s", strUnknown.Get());
}

void UIPlayerInfoComponent::update() {}
void UIPlayerInfoComponent::ASyncUpdate() {};
void UIPlayerInfoComponent::render() {
	using namespace Globals;
	if (!ENTITY::DoesEntityExist(PLAYER::GetPlayerPedScriptIndex(m_player))) {
		m_parent->setName(strLeft.Get());
		return;
	}
	SPlayer* player = &GetPlayer(m_player);
	m_parent->setName(player->m_name);

	try {
		if (player->m_isHost || player->m_isScriptHost) drawInfo(0, m_half, 0, strHost.Get(), "", medal, { 240, 200, 80, 255 });
		else if (player->m_id == GetLocalPlayer().m_id) drawInfo(0, m_half, 0, strMe.Get(), "", medal, { 194, 80, 80, 255 });
		else if (player->m_isFriend)drawInfo(0, m_half, 0, strFriend.Get(), "", medal, { 102, 152, 104, 255 });
		else if (GetPlayerManager()->IsModder(*player)) drawInfo(0, m_half, 0, strModder.Get(), "", medal, { 255, 133, 85, 255 });
		else drawInfo(0, m_half, 0, strClient.Get(), "", medal, { 255, 255, 255, 255 });

		drawInfo(0, m_half, 1, strHealth.Get(), GetEntityHealth(*player));
		drawMiddleLineTop(0);
		drawMiddleLine(0);

		const auto cash = Global(PLAYER_BASE).At(player->m_id, PLAYER_PADDING).At(PLAYER_OFFSET).At(PLAYER_OFFSET_WALLET).As<uint64_t>();
		drawInfo(m_half, m_half, 0, strCash.Get(), va("$%llu", cash));
		drawInfo(m_half, m_half, 1, strBank.Get(), va("$%llu", Global(PLAYER_BASE).At(player->m_id, PLAYER_PADDING).At(PLAYER_OFFSET).At(PLAYER_OFFSET_TOTAL).As<uint64_t>() - cash));
		drawInfo(m_half, m_half, 2, strArmor.Get(), va("%d", PED::GetPedArmour(player->m_ped)));
		drawMiddleLine(1);

		drawInfo(0, m_half, 2, strRank.Get(), va("%d", Global(PLAYER_BASE).At(player->m_id, PLAYER_PADDING).At(PLAYER_OFFSET).At(PLAYER_OFFSET_LEVEL).As<int>()));
		//drawInfo(m_half, m_half, 3, strKD.Get(), va("%.2f", Global(PLAYER_BASE).At(player->m_id, PLAYER_PADDING).At(PLAYER_EXTRA).As<float>()));
		drawInfo(m_half, m_half, 3, strKD.Get(), va("%.2f", Global(PLAYER_BASE).At(player->m_id, PLAYER_PADDING).At(PLAYER_OFFSET).At(PLAYER_OFFSET_KD).As<float>()));
		drawMiddleLine(2);

		drawInfo(0, m_half, 3, strHeading.Get(), GetPlayerHeading(*player));
		drawMiddleLine(3);
		drawMiddleLineBottom(3);

		drawInfo(0, m_whole, 4, strWeapon.Get(), GetPlayerWeaponName(*player));

		drawInfo(0, m_half, 5, strAmmo.Get(), GetAmmoInPlayerWeapon(*player));;
		drawInfo(m_half, m_half, 5, strWanted.Get(), va("%d/5", PLAYER::GetPlayerWantedLevel(player->m_id)));
		drawMiddleLineTop(5);
		drawMiddleLineTop(5);
		drawMiddleLine(5);

		drawInfo(0, m_half, 6, strDistance.Get(), va("%.3f", player->m_coordinates.Distance(GetLocalPlayer().m_coordinates)));
		drawInfo(m_half, m_half, 6, strSpeed.Get(), va("%.0f", ENTITY::GetEntitySpeed(player->m_ped) * 3.6f));;
		drawMiddleLine(6);
		drawMiddleLineBottom(6);

		drawInfo(0, m_whole, 7, strZone.Get(), HUD::_GetLabelText(ZONE::GetNameOfZone(player->m_coordinates.x, player->m_coordinates.y, player->m_coordinates.z)));
		drawInfo(0, m_whole, 8, strStreet.Get(), GetPlayerStreetName(player->m_coordinates));
		drawInfo(0, m_whole, 9, strVehicle.Get(), player->m_isInVehicle ? HUD::_GetLabelText(VEHICLE::GetDisplayNameFromVehicleModel(ENTITY::GetEntityModel(player->m_vehicle))) : va("~c~%s", strNotInVeh.Get()));

		drawInfo(0, m_half, 10, "X", va("%.3f", player->m_coordinates.x));
		drawInfo(0, m_half, 11, "Y", va("%.3f", player->m_coordinates.y));
		drawInfo(0, m_half, 12, "Z", va("%.3f", player->m_coordinates.z));
		drawMiddleLineTop(10);
		drawMiddleLine(10);
		drawMiddleLine(11);
		drawMiddleLine(12);
		drawMiddleLine(13);
		drawMiddleLine(14);
		//drawMiddleLineBottom(14);

		drawInfo(m_half, m_half, 10, strModdedModel.Get(), DoesPlayerHaveModdedModel(*player) ? strYes.Get() : strNo.Get());

		uint64_t pedClass = PoolManager::GetEntityAddress(player->m_ped);
		if (pedClass != 0) {
			CPed* ped = (CPed*)pedClass;

			if (NetEvent::vars.rockstarid && player->m_id == GetLocalPlayer().m_id) {
				drawInfo(m_half, m_half, 11, strRockstarID.Get(), va("%i | [S] %i", Backend::m_originalRID, Backend::m_spoofingRID));
			} else if (StreamerModeMenuVars::vars.StreamerMode || SettingsMenuVars::vars.hideplayerrids) {
				drawInfo(m_half, m_half, 11, strRockstarID.Get(), "Blocked");
			} else {
				drawInfo(m_half, m_half, 11, strRockstarID.Get(), va("%i", ped->PlayerInfo->RockstarID));
			}
		} else drawInfo(m_half, m_half, 11, strRockstarID.Get(), strUnknown.Get());

		if (!SettingsMenuVars::vars.hideplayerips) {
			drawInfo(m_half, m_half, 12, strIP.Get(), GetPlayerIP(*player));
		} else {
			drawInfo(m_half, m_half, 12, strIP.Get(), "Blocked");
		}

		if (pedClass != 0) {
			drawInfo(0, m_half, 13, strGodmode.Get(), player->m_isGod ? strYes.Get() : strNo.Get());
		} else drawInfo(0, m_half, 13, strGodmode.Get(), strNo.Get());

		uint64_t vehicleClass = 0;
		if (player->m_isInVehicle) {
			vehicleClass = PoolManager::GetEntityAddress(player->m_vehicle);
		}

		if (vehicleClass != 0) {
			drawInfo(m_half, m_half, 13, strVehGodmode.Get(), player->m_isInVehicle ? ((*(BYTE*)(vehicleClass + 0x0189)) ? strYes.Get() : strNo.Get()) : strUnknown.Get());
		} else drawInfo(m_half, m_half, 13, strVehGodmode.Get(), player->m_isInVehicle ? strNo.Get() : strUnknown.Get());

		drawInfo(0, m_half, 14, strOTR.Get(), player->m_isOTR ? strYes.Get() : strNo.Get());
		drawInfo(m_half, m_half, 14, strINT.Get(), player->m_isInInt ? strYes.Get() : strNo.Get());

		drawInfo(0, m_half, 15, strPassive.Get(), HUD::GetBlipSprite(HUD::GetBlipFromEntity(player->m_ped)) == 163 ? strYes.Get() : strNo.Get());

		Hash model = ENTITY::GetEntityModel(player->m_ped);
		if (model != Utils::GetHashKey("MP_F_Freemode_01")) {
			drawInfo(m_half, m_half, 15, strGender.Get(), "Male");
		}
		else drawInfo(m_half, m_half, 15, strGender.Get(), "Female");

		drawInfo(0, m_half, 16, strInvisible.Get(), ENTITY::IsEntityVisibleToScript(player->m_ped) ? strNo.Get() : strYes.Get());
		drawInfo(m_half, m_half, 16, strKick.Get(), NETWORK::_NetworkSessionIsPlayerVotedToKick(player->m_id) ? strYes.Get() : strNo.Get());

		drawInfo(0, m_half, 17, strCutscene2.Get(), NETWORK::NetworkIsPlayerInMpCutscene(player->m_id) ? strYes.Get() : strNo.Get());
		drawInfo(m_half, m_half, 17, strAir.Get(), ENTITY::IsEntityInAir(player->m_ped) || ENTITY::IsEntityInAir(player->m_vehicle) ? strYes.Get() : strNo.Get());

		drawMiddleLine(15);
		drawMiddleLine(16);
		drawMiddleLine(17);
		drawMiddleLineBottom(17);

		/*bool hasGarage1 = Global(1589819).At(player->m_id, 818).At(275).As<int>();
		bool hasGarage2 = Global(1589819).At(player->m_id, 818).At(276).As<int>();
		bool hasGarage3 = Global(1589819).At(player->m_id, 818).At(277).As<int>();
		int totalGarageCount = (int)hasGarage1 + (int)hasGarage2 + (int)hasGarage3;

		bool hasApartment1 = Global(1589819).At(player->m_id, 818).At(267).As<int>();
		bool hasApartment2 = Global(1589819).At(player->m_id, 818).At(268).As<int>();
		bool hasApartment3 = Global(1589819).At(player->m_id, 818).At(269).As<int>();
		bool hasApartment4 = Global(1589819).At(player->m_id, 818).At(270).As<int>();
		bool hasOffice = Global(1589819).At(player->m_id, 818).At(272).As<int>();
		bool hasClubhouse = Global(1589819).At(player->m_id, 818).At(273).As<int>();
		int totalPropertyCount = (int)hasApartment1 + (int)hasApartment2 + (int)hasApartment3 + (int)hasApartment4;*/

		//drawInfo(0, m_half, 18, strCutscene2.Get(), NETWORK::NetworkIsPlayerInMpCutscene(player->m_id) ? strYes.Get() : strNo.Get());
		//drawInfo(m_half, m_half, 18, strCutscene2.Get(), NETWORK::NetworkIsPlayerInMpCutscene(player->m_id) ? strYes.Get() : strNo.Get());
		
		//drawInfo(0, m_half, 19, strOfficeGar.Get(), va("%i", totalGarageCount));
		//drawInfo(m_half, m_half, 19, strProperty.Get(), va("%i", totalPropertyCount));

		//drawMiddleLine(18);
		//drawMiddleLine(19);
		//drawMiddleLineBottom(19);

		drawInfo(0, m_whole, 18, strStance.Get(), GetPlayerStance(*player));
		

		//if (pedClass != 0) {
		//	CPed* ped = (CPed*)pedClass;

		//	auto rId = ped->PlayerInfo->RockstarID;

		//	if (AccountData.find(rId) == AccountData.end()) {
		//		AccountData[rId] = {}; // insert empty rockstaracc so we dont spam getprofile

		//		Socialclub::GetProfile(rId, [=](bool success, SocialclubData::RockstarAccount account) {
		//			if (!success) {
		//				LOG_DEVERROR("Failed to load profile for %d", rId);
		//				AccountData.erase(AccountData.find(rId));
		//				return;
		//			}

		//			LOG_PRINT("Received profile for %d", rId);

		//			AccountData[rId] = account;
		//		});
		//	}

		//	
		//	if (!AccountData[rId].isPlaceholder()) {
		//		drawInfo(m_half, m_half, 18, strRealName.Get(), va("Real name: %s", AccountData[rId].getName())); // will be 0 if profile or friends are set to hidden
		//	} // if you want you can add else and print that its still loading
		//}


		/*
		uint64_t pedClass = PoolManager::GetEntityAddress(player->m_ped);
		if (pedClass != 0) {
			CPed* ped = (CPed*)pedClass;
			Socialclub::GetProfile(ped->PlayerInfo->RockstarID, [](bool success, SocialclubData::RockstarAccount account) {
			if (!success) return;

			account.getFriendCount(); // etc
		});

		}

		Socialclub::GetProfile(1337, [](bool success, SocialclubData::RockstarAccount account) {
			if (!success) return;

			account.getFriendCount(); // etc
		});
		*/

		if (SessionMenuVars::vars.showmarkeronselectedbydefault) {
			GRAPHICS::DrawMarker(21, player->m_coordinates.x, player->m_coordinates.y, player->m_coordinates.z + 1.5f, 0.0f, 0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.9f, 0.9f, 0.9f, 0, 255, 255, 200, true, false, 2, true, nullptr, nullptr, false);
		}

		if (!SettingsMenuVars::vars.hidemap) {
			float yPos = m_parent->m_position.y;
			float xPos = m_parent->m_position.x;
			float offsety = -0.268f;
			float offsetx = 0.184f;
			MapPanel();
			for (int i = 0; i < MAXPLAYERS; i++)
			{
				if (ENTITY::DoesEntityExist(PLAYER::GetPlayerPedScriptIndex(i))) {
					Vector3 player = ENTITY::GetEntityCoords(PLAYER::GetPlayerPedScriptIndex(i), 0);
					DrawSprite1("shared", "menuplus_32", offsetx + xPos - 0.09f + relevateX(player.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f - relevateY(player.y), 0.25f, 0.25f, 0, 255, 255, 255, 180);
				}
			}
			Vector3 playerSelected = ENTITY::GetEntityCoords(PLAYER::GetPlayerPedScriptIndex(player->m_id), 0);
			DrawSprite1("shared", "menuplus_32", offsetx + xPos - 0.09f + relevateX(playerSelected.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f - relevateY(playerSelected.y), 0.25f, 0.25f, 0, 255, 0, 0, 255);

			DrawSprite1("shared", "newstar_32", offsetx + xPos - 0.09f + relevateX(GetLocalPlayer().m_coordinates.x), offsety + yPos - 0.083f / 2 + 0.49f + 0.208f - relevateY(GetLocalPlayer().m_coordinates.y), 0.25f, 0.25f, 0, 255, 0, 0, 200);
		}

	} catch (...) {}
}