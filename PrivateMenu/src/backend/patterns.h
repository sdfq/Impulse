#pragma once

namespace Patterns
{
	//m_FrameCount
	//F3 0F 10 0D ? ? ? ? 44 89 6B 08

	//Is session started
	//40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE
	
	//Blip List
	//4C 8D 05 ? ? ? ? 0F B7 C1

	//Native Spoofer
	//FF 23

	//Ped factory
	//48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81

	//Network player manager
	//48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF

	//Native handlers
	//48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A

	//Fix vectors
	//83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA

	//Get TPS Camera
	//48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 48 8B F8 E8 ? ? ? ? 8B 8B ? ? ? ?

	//Game Cam Manager
	//48 8B 05 ? ? ? ? 4A 8B 1C F0

	//FOV
	//F3 0F 10 15 ? ? ? ? 0F 2F C8 72 0A

	//CWaterTune
	//0F B6 05 ? ? ? ? 0F 28 4C 24 ?

	//Water Ptr
	//48 8B D9 48 6B DB 1C 48 2B F9 48 8B 05 ? ? ? ?

	//Script threads
	//45 33 F6 8B E9 85 C9 B8

	//Script programs
	//44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1

	//Script globals
	//48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D

	//CGameScriptHandlerMgr
	//48 8B 0D ? ? ? ? 4C 8B CE E8 ? ? ? ? 48 85 C0 74 05 40 32 FF

	//Swapchain
	//48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8

	//TextInfo
	//48 8D 05 ? ? ? ? 48 89 44 24 ? 8B 05 ? ? ? ? 89 44 24 28

	//m_ownedExplosionBypass
	//3B F8 40 0F 94 C7

	//m_clockTime
	//48 8D 0D ? ? ? ? 8B FA E8 ? ? ? ? 44 8D 0C 5B

	//GetTextScreenWidth
	//40 53 48 81 EC ? ? ? ? 83 3D ? ? ? ? ? 8A D9 0F 57 C0

	//AddTextCompSubstrPlayerName
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 05 ? ? ? ? 4C 8B D1

	//fSetNotificationMessageCT2char
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 83 3D ? ? ? ? ?

	//fDrawNotification
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 83 3D ? ? ? ? ? 41 8A D8

	//BeginTextCmdDisplayText
	//48 83 EC 28 E8 ? ? ? ? E8 ? ? ? ? 33 C9 48 85 C0

	//EndTextCmdDisplayText
	//40 53 48 83 EC 40 0F 29 74 24 ? 0F 29 7C 24 ? 41 8B D8

	//fDrawRect
	//48 8B C4 48 89 58 08 57 48 83 EC 70 48 63 0D ? ? ? ?

	//GetPlayerPed one or other
	//48 83 EC 28 B2 01 E9 ? ? ? ? 8B 85 80 01 ? ?
	//48 83 EC 28 B2 01 E9 ? ? ? ? 83 45 68 FF

	//GetLabelText
	//75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9

	//GetPlayerName
	//40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9 74 1A

	//fHasStreamedTextureDictLoaded
	//48 83 EC 28 4C 8B C1 48 8D 54 24 ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 7C 24 ? ?

	//request_streamed_texture_dict
	//40 53 48 83 EC 50 8A DA 4C 8B C1

	//DrawSprite
	//48 83 EC 78 8A 84 24 ? ? ? ? F3 0F 10 84 24 ? ? ? ? F3 0F 10 8C 24 ? ? ? ? C6 44 24 ? ? 88 44 24 58 8B 84 24 ? ? ? ? 89 44 24 50 8B 84 24 ? ? ? ? 89 44 24 48 8B 84 24 ? ? ? ?

	//m_RegisterRawStreamingFile
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50

	//has_model_loaded
	//48 89 7C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 18 BF

	//player_id one or other
	//48 83 EC 28 80 3D ? ? ? ? ? 0F 84 ? ? ? ? E9 ? ? ? ? D3 E0
	//48 83 EC 28 80 3D ? ? ? ? ? 55 48 BD ? ? ? ? ? ? ? ? 48 87 2C 24 50 51 48 8B 44 24 ? 48 B9 ? ? ? ? ? ? ? ? 48 0F 44 C1

	//request_model
	//48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 50 8B 45 18

	//is_model_in_cdimage
	//48 83 EC 28 8B 44 24 38 48 8D 54 24 ? C7 44 24 ? ? ? ? ? 0D ? ? ? ? 25 ? ? ? ? 89 44 24 38 E8 ? ? ? ? 0F B7 44 24 ? 66 89 44 24 ? 8B 44 24 38 0D ? ? ? ? 0F BA F0 1C 89 44 24 38

	//is_model_valid
	//48 83 EC 28 8B 44 24 38 48 8D 54 24 ? C7 44 24 ? ? ? ? ? 0D ? ? ? ? 25 ? ? ? ? 89 44 24 38 E8 ? ? ? ? 0F B7 44 24 ? 66 89 44 24 ? 8B 44 24 38 0D ? ? ? ? 0F BA F0 1C 0F B7 C8

	//get_ped_head_blend_data one or other
	//48 8D 64 24 ? 48 89 1C 24 48 83 EC 20 48 8B DA E9 ? ? ? ?
	//48 89 5C 24 ? 48 8D 64 24 ? 48 83 EC 20 52 5B

	//get_label_text
	//40 53 48 83 EC 20 48 8B D9 48 8B D1 48 8D 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 34

	//set_ped_random_props
	//48 8D 64 24 ? 48 89 1C 24 48 83 EC 60 E9 ? ? ? ? 55
	//48 8D 64 24 ? 48 89 1C 24 48 83 EC 60 E9 ? ? ? ? 8B ?

	//set_ped_head_blend_data
	//54 58 48 89 58 08 48 89 70 10 E9 ? ? ? ? CA FE 8E
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 70 20 48 89 6C 24 ? 48 8D 64 24 ? 48 8D 68 98

	//task_start_scenario_in_place
	//48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 44 8B F1 48 8B CA

	//set_anim_rate
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 0F 29 74 24 ? 41 8A D9

	//request_anim_dict
	//48 83 EC 58 48 8B D1 33 C9

	//has_anim_dict_loaded
	//48 83 EC 28 48 8B D1 33 C9 E8 ? ? ? ? 48 8D 54 24 ? 48 8D 4C 24 ? 89 44 24 40

	//ai_task_play_anim
	//48 81 EC ? ? ? ? 44 8B 8C 24

	//has_anim_set_loaded
	//40 53 48 83 EC 20 48 8B D1 33 C9 E8 ? ? ? ? 48

	//request_anim_set
	//48 89 5C 24 ? 55 48 8B EC 48 83 EC 50 48 8B D1

	//set_entity_collision
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F1 41 8A E8 40 8A FA

	//is_entity_dead
	//48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? E9 ? ? ? ? 54
	//48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 48 8D 64 24 ? 48 83 EC 20 40 8A FA

	//set_vehicle_fixed
	//40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 28 4C 8B 10
	
	//create_vehicle
	//48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 50 F3 0F 10 02

	//is_waypoint_active
	//40 53 48 83 EC 20 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 F6 04 02 01

	//get_blip_coords
	//40 53 48 83 EC 60 0F 29 74 24 ? F3 0F 10 35 ? ? ? ? 0F 29 7C 24 ?

	//set_ped_into_vehicle
	//48 89 5C 24 ? 48 89 6C 24 ? 48 8D 64 24 ? 48 89 34 24 48 8D 64 24 ? 48 89 3C 24 48 8D 64 24 ? 4C 89 34 24
	//48 89 5C 24 ? 48 89 6C 24 ? E9 ? ? ? ? 83 F8 FF

	//network_has_control_of_network_id
	//40 53 48 83 EC 20 8B D9 E8 ? ? ? ? 8B D3 48 8B C8 E8 ? ? ? ? 48 85 C0 74 33

	//network_request_control_of_network_id
	//40 53 48 83 EC 20 8B D9 E8 ? ? ? ? 8B D3 48 8B C8 E8 ? ? ? ? 48 85 C0 74 2C

	//network_is_session_started
	//48 8B 0D ? ? ? ? 33 C0 48 85 C9 74 0E 83 B9 ? ? ? ? ? 75 05

	//network_has_control_of_entity
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 1F 48 8B 88 ? ? ? ? 48 85 C9 74 0F

	//network_request_control_of_entity
	//48 89 5C 24 ? 57 48 83 EC 20 8B D9 E8 ? ? ? ? 84 C0

	//network_get_network_id_from_entity
	//48 89 5C 24 ? 57 48 83 EC 20 E8 ? ? ? ? 33 DB 48 8B F8 48 85 C0 74 16

	//set_network_id_can_migrate
	//85 C9 0F 8E ? ? ? ? 48 89 5C 24 ? 57 48 83 EC 20 8A DA

	//_EventHandler
	//66 41 83 F9 ? 0F 83 ? ? ? ?

	//is_next_weather_type
	//48 83 EC 28 51 5A
	//48 83 EC 28 48 8B D1 48 8D 0D ? ? ? ? E9 ? ? ? ?

	//add_owned_explosion
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 70 20 55 48 8D 68 B9 48 81 EC ? ? ? ? 0F 29 70 E8 41 8B D8

	//ptr_to_handle
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB

	//get_current_ped_weapon_entity_index
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 1E 48 8B 80 ? ? ? ?

	//network_get_host_of_script
	//40 53 48 83 EC 60 48 83 CB FF

	//set_entity_coords
	//48 8B C4 48 89 58 08 E9 9E 1B C6 FF
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 48 89 6C 24 ? 48 8D 64 24 ? 48 8D 68 B9

	//NetGameEvent_vftable
	//48 89 5C 24 ? 57 48 83 EC 20 80 61 0A FE

	//JoinTransition
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 8B 84 24 ? ? ? ? 89 51 5C

	//game_transaction
	//48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8D 05 D6 CA 96 ? 8B F2 48 8B D9 48 89 01 E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 8B CB 48 89 03 E8 ? ? ? ? 48 8D BB ? ? ? ? 48 8B CF E8 ? ? ? ?

	//stat_get_int
	//48 8B C4 48 89 58 10 48 89 70 18 57 48 83 EC 30 48 8B F2

	//get_user_id
	//48 89 5C 24 08 57 48 83 EC 20 80 3D F9 6A BA 01 ? 48 8B FA 8B D9 74 1B
	//48 89 5C 24 08 57 48 83 EC 20 80 3D E1 97 BA 01

	//trigger_script_event
	//48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9

	//get_network_time
	//40 53 48 83 EC 20 48 8B 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 19

	//stat_set_int
	//48 89 5C 24 ? 48 89 74 24 ? 89 54 24 10 55 57 41 57

	//network_is_friend
	//40 53 48 83 EC 30 48 8B D9 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? 41 B8 ? ? ? ? 48 8B D3 E8 ? ? ? ? 84 C0 74 12

	//network_is_player_talking
	//40 53 48 83 EC 20 B2 01 E8 77 2E D4 FF 48 85 C0 74 28 48 8B 10 48 8B 1D ? ? ? ? 48 8B C8 FF 52 30 48 8B C8 E8 ? ? ? ? 48 8B CB 48 8B D0 48 83 C4 20 5B E9 ? ? ? ? 48 83 C4 20 5B C3
	//40 53 48 83 EC 20 B2 01 E8 4F 30 D4 FF 48 85 C0 74 28 48 8B 10 48 8B 1D ? ? ? ? 48 8B C8 FF 52 30 48 8B C8 E8 ? ? ? ? 48 8B CB 48 8B D0 48 83 C4 20 5B E9 ? ? ? ? 48 83 C4 20 5B C3

	//set_weather_remotely
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9

	//network_override_clock_time
	//80 3D ? ? ? ? ? 75 37 8B 05 ? ? ? ? C6

	//set_time_remotely
	//E9 ? ? ? ? 8B 85 ? ? ? ? 85 C0 0F 84 ? ? ? ? E9 ? ? ? ? E8 ? ? ? ? 84 C0
	//E9 ? ? ? ? 48 8B 5C 24 ? 48 83 C4 20 48 8D 64 24 ? E9 ? ? ? ? E8 ? ? ? ?

	//create_object
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 4C 89 60 20 55 41 55 41 56 48 8D 68 D9

	//draw_marker
	//4C 8B DC 48 81 EC ? ? ? ? 8A 84 24 ? ? ? ?

	//attach_entity_to_entity
	//54 58 48 89 58 08 48 89 70 10 48 89 78 20

	//entity_to_net
	//48 89 5C 24 ? 57 48 83 EC 20 E8 ? ? ? ? 33 DB 48 8B F8 48 85 C0 74 16

	//does_network_id_exist
	//40 53 48 83 EC 20 8B D9 E8 ? ? ? ? 8B D3 48 8B C8 E8 ? ? ? ? 48 85 C0 0F 95 C0

	//object_spawn_check
	//40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 12

	//g_OriginalIsEntityUpsideDown
	//40 53 48 83 EC 20 33 DB 85 C9 78 10

	//set_entity_rotation
	//48 89 5C 24 ? E9 ? ? ? ? 48 8D 65 20 48 8B 2C 24
	//48 89 5C 24 ? 48 89 7C 24 ? 48 8D 64 24 ? 48 89 2C 24 E9 ? ? ? ?

	//set_vehicle_forward_speed_nat
	//48 83 EC 38 0F 29 74 24 ? 0F 28 F1 E8 ? ? ? ? 48 85 C0 74 2A F6 40 29 01 74 19 F3 0F 11 B0 ? ? ? ? 80 88 ? ? ? ? ? 0F 28 74 24 ? 48 83 C4 38 C3 0F 28 CE 48 8B C8 E8 ? ? ? ?

	//set_vehicle_on_ground_properly
	//48 89 5C 24 ? 57 48 83 EC 30 0F 29 74 24 ? 0F 28 F1 E8 ? ? ? ? 48 8B D8

	//decor_set_int
	//48 89 5C 24 ? 44 89 44 24 ? 57 48 83 EC 20 48 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 74 22 48 8B D7 33 C9 E8 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? 48 8B CB 89 44 24 48 E8 ? ? ? ? B0 01

	//get_interior_from_entity
	//40 53 48 83 EC 20 33 DB E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? F6 40 40 01

	//get_display_name_from_vehicle_model
	//48 83 EC 28 48 8D 54 24 ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 85 C0 74 16

	//get_street_name_at_coord
	//48 8B C4 48 89 58 18 57 48 83 EC 30 F3 0F 10 01 F3 0F 10 49 ? F3 0F 10 51 ? 49 8B F8 48 8B DA 4C 8D 48 10

	//get_name_of_zone
	//48 8B C4 48 83 EC 38 F3 0F 10 01 F3 0F 10 49 ? F3 0F 10 51 ? 48 8D 4C 24 ? F3 0F 11 40 ? F3 0F 11 48 ? F3 0F 11 50 ? F3 0F 10 44 24 ? F3 0F 11 40 ? 8A 05 ? ? ? ? F6 D8 45 1B C0 83 CA FF

	//get_street_name_from_hash_key
	//40 53 48 83 EC 40 8B D9 44 8B C1

	//network_set_in_spectator_mode
	//48 89 5C 24 ? 57 48 83 EC 20 41 8A F8 84 C9

	//get_water_height
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 10 48 8D 88 ? ? ? ? 48 83 C4 28 E9 ? ? ? ? F3 0F 10 05 ? ? ? ?

	//is_model_a_plane
	//40 53 48 83 EC 20 48 8D 54 24 ? 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 1D 8A 80 ? ? ? ? 24 1F 3C 05 75 11 BA

	//is_model_a_heli
	//40 53 48 83 EC 20 48 8D 54 24 ? 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 1E 8A 80 ? ? ? ? 24 1F 3C 05 75 12 83 B9 ? ? ? ? 08

	//set_vehicle_mod_kit
	//40 53 48 83 EC 20 8B DA E8 ? ? ? ? 48 85 C0 74 29 48 8B 50 20

	//set_vehicle_mod
	//48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 56 48 83 EC 30 41 8A E9

	//get_num_vehicle_mods
	//40 53 48 83 EC 20 8B DA 83 FA 0A 7E 10 8D 42 F5 83 F8 0D 77 05 83 C3 19 EB 03 83 EB 0E E8 ? ? ? ? 48 85 C0 74 2C

	//is_toggle_mod_on
	//40 53 48 83 EC 20 8B DA 83 FA 0A 7E 10 8D 42 F5 83 F8 0D 77 05 83 C3 19 EB 03 83 EB 0E E8 ? ? ? ? 48 85 C0 74 1C

	//does_extra_exist
	//40 53 48 83 EC 20 8B DA E8 ? ? ? ? 48 8B D0 33 C0 48 85 D2 74 2B

	//is_vehicle_extra_turned_on
	//40 53 48 83 EC 20 8B DA E8 ? ? ? ? 48 85 C0 74 1B 8D 4B FF

	//is_vehicle_neon_light_enabled
	//40 53 48 83 EC 20 8B DA E8 ? ? ? ? 48 85 C0 74 40

	//get_vehicle_neon_lights_color
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B D9 49 8B F8 48 8B F2 E8 ? ? ? ? 48 85 C0 74 23

	//get_vehicle_custom_primary_color
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 49 8B D9 49 8B F8 48 8B F2 E8 ? ? ? ? 48 85 C0 74 2F 48 8B 48 48 48 8D 54 24 ? 48 8B 49 20 E8 ? ? ? ? 8B 44 24 20 8B C8 C1 E9 10 0F B6 C9

	//get_vehicle_wheel_type
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 14 48 8B 48 48 48 8B D0 48 83 C1 40 48 83 C4 28 E9 ? ? ? ? 48 83 C4 28

	//get_vehicle_number_plate_text
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 11 48 8B 40 48

	//get_vehicle_number_plate_text_index
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 10 48 8B 40 48

	//get_vehicle_window_tint
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 14 48 8B 40 48

	//create_ped
	//48 8B C4 48 89 58 08 48 89 70 10 E9 ? ? ? ? 8B 45 68
	//48 8B C4 48 89 58 08 48 89 70 10 E9 ? ? ? ? 48 8D 64 24 ? 48 89 2C 24

	//get_gameplay_cam_rot
	//48 89 5C 24 ? 57 48 83 EC 30 8B DA 48 8B F9 E8 ? ? ? ? 48 8D 4C 24 ? 48 8D 90 ? ? ? ?

	//get_gameplay_cam_coord
	//40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 8B 90 ? ? ? ?

	//shoot_single_bullet_between_coords
	//48 83 EC 68 83 64 24 ? ? 83 64 24 ? ? E9 ? ? ? ?
	//48 83 EC 68 83 64 24 ? ? 83 64 24 ? ? 8A 84 24 ? ? ? ?

	//create_cam
	//40 53 48 83 EC 50 44 8A C2 48 8B D1

	//add_cam_spline_node
	//48 8B C4 48 89 58 08 48 89 70 10 57 48 81 EC ? ? ? ? F3 0F 10 02 F3 0F 10 4A ? F3 0F 10 52 ?

	//render_script_cams
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 33 DB 41 8A F9

	//does_cam_exist
	//40 53 48 83 EC 20 8B D9 85 C9 78 10

	//get_cam_spline_node_index
	//48 89 5C 24 ? 57 48 83 EC 20 8B F9 85 C9 78 13 8B D1 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 EB 02 33 DB 48 85 DB 74 30 E8 ? ? ? ? 8B D7 48 8B C8 E8 ? ? ? ? 84 C0 74 1D 48 8B 03

	//get_closest_vehicle
	//4C 8B DC 49 89 5B 08 49 89 6B 10 56 57 41 56 48 83 EC 60

	//is_ipl_active
	//48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C1 48 8D 54 24 ?

	//request_ipl
	//48 89 5C 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8B F9 4C 8B C1 48 8D 54 24 ? 48 8D 0D ? ? ? ? FF 50 10 8B 18

	//remove_ipl
	//48 89 5C 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8B F9 4C 8B C1 48 8D 54 24 ? 48 8D 0D ? ? ? ? FF 50 10 48 63 18

	//get_vehicle_ped_is_in
	//48 89 5C 24 ? 48 89 74 24 ? E9 ? ? ? ? 48 83 A3 ? ? ? ? ?
	//48 89 5C 24 ? 48 89 74 24 ? 48 8D 64 24 ? 48 89 3C 24 48 83 EC 20 40 8A F2

	//smash_vehicle_window
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 63 FA

	//detach_vehicle_windscreen
	//48 83 EC 28 E8 ? ? ? ? 48 85 C0 74 20 48 8B 48 20

	//remove_vehicle_window
	//48 89 5C 24 ? 57 48 83 EC 20 48 63 DA E8 ? ? ? ?

	//roll_up_window
	//40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 17 48 8D 15 ? ? ? ?

	//roll_down_window
	//40 53 48 83 EC 20 48 63 DA E8 ? ? ? ? 48 85 C0 74 1A 48 8D 15 ? ? ? ? 8B 14 9A

	//roll_down_windows
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 E8 ? ? ? ? 48 8B F8 48 85 C0 74 51

	//set_vehicle_door_broken
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A E8 48 63 FA

	//set_vehicle_doors_shut
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 40 8A F2 E8 ? ? ? ? 48 8B F8

	//set_vehicle_door_shut
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F0 48 63 FA E8 ? ? ? ? 48 8B D8 48 85 C0 74 7A

	//set_vehicle_door_open
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F1 41 8A E8 48 63 DA E8 ? ? ? ? 48 8B F8 48 85 C0 0F 84 ? ? ? ?

	//set_vehicle_enveff_scale
	//48 83 EC 38 0F 29 74 24 ? 0F 28 F1 E8 ? ? ? ? 48 85 C0 74 2E 48 8B 40 48

	//get_mod_text_label
	//48 89 5C 24 ? 57 48 83 EC 20 41 8B F8 8B DA 83 FA 0A 7E 10 8D 42 F5 83 F8 0D 77 05 83 C3 19 EB 03 83 EB 0E E8 ? ? ? ? 48 85 C0 74 2C

	//set_vehicle_tyre_smoke_color
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8B D9 41 8B F8 8B F2 E8 ? ? ? ? 48 85 C0 74 18

	//is_this_model_a_bicycle
	//40 53 48 83 EC 20 48 8D 54 24 38 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 1E 8A 80 ? ? ? ? 24 1F 3C 05 75 12 83 B9 ? ? ? ? ? 0F B6 DB BA ? ? ? ? 0F 44 DA

	//is_vehicle_on_all_wheels
	//48 89 5C 24 ? 57 48 83 EC 20 E8 ? ? ? ? 33 FF 48 85 C0 74 1C

	//is_this_model_a_bike
	//40 53 48 83 EC 20 48 8D 54 24 ? 33 DB C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 8B C8 48 85 C0 74 22

	//apply_force_to_entity
	//54 58 48 89 58 08 48 89 70 10 E9 ? ? ? ? 54
	//54 58 48 89 58 08 48 89 70 10 48 89 78 20

	//is_vehicle_damaged
	//48 83 EC 28 48 8D 54 24 ? C7 44 24 ? ? ? ? ? E8 ? ? ? ? 48 85 C0 74 16

	//get_water_height_no_waves
	//48 89 5C 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? F3 0F 10 01 F3 0F 10 51 ?

	//set_ped_shoots_at_coord
	//54 58 48 89 58 08 48 89 70 10 48 89 78 18 48 8D 64 24 ? 48 89 2C 24 48 8D 64 24 ?
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 48 8D 64 24 ? 48 89 2C 24 4C 89 74 24 ? 48 8D 64 24 ? 48 8D 64 24 ? 4C 89 3C 24 48 8D 68 C8

	//start_shape_test_capsule
	//48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 33 DB 4C 8B F1 8B 8D ? ? ? ? 0F 29 70 D8 45 8B F9 48 8B F2 0F 28 F2 8B FB 85 C9 74 08

	//get_shape_test_result
	//48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8B EC 48 83 EC 60 33 DB

	//set_entity_as_no_longer_needed
	//48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 48 8D 64 24 ? E9 ? ? ? ? 83 A5 ? ? ? ? ?
	//48 89 5C 24 ? E9 ? ? ? ? AE

	//set_player_weapon_damage_modifier
	//48 83 EC 38 B2 01 0F 29 74 24 20 0F 28 F1 E9 26 EA 7D FC
	//48 83 EC 38 B2 01 0F 29 74 24 ? 0F 28 F1 E9 ? ? ? ? 48 89 5C 24 ? 48 8B 04 24

	//set_ped_current_weapon_visible
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A F8 40 8A F2 E8 ? ? ? ? 48 8B D8

	//set_player_melee_weapon_modifier
	//48 8D 64 24 F8 E9 7F 2B 82 02
	//48 8D 64 24 F8 48 89 1C 24 48 83 EC 30 B2 01 E9 8F FF 2A 01

	//set_heli_blades_full_speed
	//40 53 48 83 EC 30 0F 29 74 24 ? 0F 28 F1 0F 2F 35

	//set_vehicle_lights
	//40 53 48 83 EC 20 8B DA E8 ? ? ? ? 48 85 C0 74 42 8D 4B FD

	//set_vehicle_indicator_lights
	//48 89 5C 24 ? 57 48 83 EC 20 41 8A D8 40 8A FA E8 ? ? ? ? 48 85 C0 74 20

	//set_vehicle_brake_lights
	//40 53 48 83 EC 20 8A DA E8 ? ? ? ? 48 85 C0 74 14 84 DB 74 09 80 88 ? ? ? ? ? EB 07 80 88 ? ? ? ? ?

	//set_vehicle_siren
	//40 53 48 83 EC 20 8A DA E8 ? ? ? ? 48 85 C0 74 15 45 33 C0

	//set_draw_origin
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F9 48 63 0D ? ? ? ?

	//memory_region_check_byte_string
	//70 0D 96 51

	//create_lightning_thunder
	//C6 05 ? ? ? ? ? C3 B8 ? ? ? ?

	//set_weather_type_persist
	//48 8D 64 24 ? 48 89 1C 24 48 83 EC 20 48 8B D9 E9 93 33 23 FD
	//48 89 5C 24 ? E9 ? ? ? ? 6A 18 E9 ? ? ? ? 48 89 4D 30

	//modify_water
	//48 89 5C 24 ? 57 48 83 EC 40 0F 29 74 24 ? 33 C9

	//is_player_playing
	//48 83 EC 28 33 D2 E9 ? ? ? ? 48 89 5C 24 10
	//48 83 EC 28 33 D2 E9 ? ? ? ? 48 8D 64 24 ? 48 8B 14 24

	//request_cutscene
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 50 8B FA 48 8B F1

	//start_cutscene
	//48 89 5C 24 ? 57 48 83 EC 20 8B F9 E8 ? ? ? ? 8B 58 08

	//set_mobile_radio
	//40 53 48 83 EC 20 8A D9 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 8B D0 E8 ? ? ? ? 48 85 C0 74 10

	//next_radio_station
	//48 83 EC 28 33 C9 E8 ? ? ? ? 80 3D ? ? ? ? ? 75 15 48 85 C0 74 3D

	//prev_radio_station
	//48 83 EC 28 33 C9 E8 ? ? ? ? 80 3D ? ? ? ? ? 75 15 48 85 C0 74 43

	//set_current_ped_weapon
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A F0 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84 ? ? ? ?

	//disable_control_action
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 41 8A F0 8B DA 8B F9

	//get_entity_bone_index_by_name
	//48 89 5C 24 ? 48 8D 64 24 ? 48 89 3C 24 E9 ? ? ? ? 48 8D 64 24 ? E9 ? ? ? ?
	//48 89 5C 24 ? 48 89 7C 24 ? E9 ? ? ? ? 59

	//48 83 EC 28 F3 0F 11 44 24 ?
	//animate_gameplay_cam_zoom

	//is_dlc_present
	//84 C0 74 0D 8D 53 0C

	//stat_set_bool
	//48 89 5C 24 ? 88 54 24 10 57 48 83 EC 40

	//stat_set_float
	//48 89 5C 24 ? F3 0F 11 4C 24 ? 57 48 83 EC 40

	//stat_set_date
	//48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 60 48 8B DA 8B F9

	//give_achievement_to_player
	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 20 8B FA

	//memory_checks_byte_str
	//48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 41 57 FF 41 0C


}