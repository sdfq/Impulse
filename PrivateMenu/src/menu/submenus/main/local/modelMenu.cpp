#include "stdafx.h"
#include "modelMenu.h"
#include "../localMenu.h"

using namespace ModelMenuVars;

namespace ModelMenuVars {
	Vars vars;

	ModelStruct m_models[726] = {
		{ "Juggernaut", "u_m_y_juggernaut_01" },
		{ "Johnny", "ig_johnnyklebitz" },
		{ "Movspace", "s_m_m_movspace_01" },
		{ "Imporage", "u_m_y_imporage" },
		{ "Rs Ranger", "u_m_y_rsranger_01" },
		{ "Justin", "u_m_y_justin" },
		{ "Mani", "u_m_y_mani" },
		//Casino DLC
		{ "Agatha", "CSB_Agatha" },
		{ "Agatha 2", "IG_Agatha" },
		{ "Avery", "CSB_Avery" },
		{ "Avery 2", "IG_Avery" },
		{ "Brucie", "CSB_Brucie2" },
		{ "Brucie 2", "IG_Brucie2" },
		{ "TaoCheng", "IG_TaoCheng2" },
		{ "TaoCheng 2", "CS_TaoCheng2" },
		{ "TaosTranslator", "IG_TaosTranslator2" },
		{ "TaosTranslator 2", "CS_TaosTranslator2" },
		{ "Thornton", "CSB_Thornton" },
		{ "Thornton 2", "IG_Thornton" },
		{ "TomCasino", "CSB_TomCasino" },
		{ "TomCasino 2", "IG_TomCasino" },
		{ "Vincent", "CSB_Vincent" },
		{ "Vincent 2", "IG_Vincent" },
		{ "GenCasPat", "A_F_Y_GenCasPat_01" },
		{ "GenCasPat 2", "A_F_Y_SmartCasPat_01" },
		{ "MLCrisis", "A_M_M_MLCrisis_01" },
		{ "GenCasPat 3", "A_M_Y_GenCasPat_01" },
		{ "SmartCasPat", "A_M_Y_SmartCasPat_01" },
		{ "CasRN", "G_M_M_CasRN_01" },
		{ "WestSec", "S_M_Y_WestSec_01" },
		{ "Casino_01 F", "S_F_Y_Casino_01" },
		{ "Casino_01 M", "S_M_Y_Casino_01" },
		{ "Carol", "U_F_O_Carol" },
		{ "Eileen", "U_F_O_Eileen" },
		{ "CasinoCash_01", "U_F_M_CasinoCash_01" },
		{ "CasinoShop_01", "U_F_M_CasinoShop_01" },
		{ "Debbie", "U_F_M_Debbie_01" },
		{ "Beth", "U_F_Y_Beth" },
		{ "Lauren", "U_F_Y_Lauren" },
		{ "Taylor", "U_F_Y_Taylor" },
		{ "Blane", "U_M_M_Blane" },
		{ "Curtis", "U_M_M_Curtis" },
		{ "Vince", "U_M_M_Vince" },
		{ "Dean", "U_M_O_Dean" },
		{ "Caleb", "U_M_Y_Caleb" },
		{ "CroupThief_01", "U_M_Y_CroupThief_01" },
		{ "Gabriel", "U_M_Y_Gabriel" },
		{ "Ushi", "U_M_Y_Ushi" },
		//
		{ "Michael", "player_zero" },
		{ "Franklin", "player_one" },
		{ "Trevor", "player_two" },
		{ "Boar", "a_c_boar" },
		{ "Chimp", "a_c_chimp" },
		{ "Cow", "a_c_cow" },
		{ "Coyote", "a_c_coyote" },
		{ "Deer", "a_c_deer" },
		{ "Fish", "a_c_fish" },
		{ "Hen", "a_c_hen" },
		{ "Cat", "a_c_cat_01" },
		{ "Hawk", "a_c_chickenhawk" },
		{ "Cormorant", "a_c_cormorant" },
		{ "Crow", "a_c_crow" },
		{ "Dolphin", "a_c_dolphin" },
		{ "Humpback", "a_c_humpback" },
		{ "Whale", "a_c_killerwhale" },
		{ "Pigeon", "a_c_pigeon" },
		{ "Seagull", "a_c_seagull" },
		{ "Sharkhammer", "a_c_sharkhammer" },
		{ "Pig", "a_c_pig" },
		{ "Rat", "a_c_rat" },
		{ "Rhesus", "a_c_rhesus" },
		{ "Chop", "a_c_chop" },
		{ "Husky", "a_c_husky" },
		{ "Mtlion", "a_c_mtlion" },
		{ "Retriever", "a_c_retriever" },
		{ "Sharktiger", "a_c_sharktiger" },
		{ "Shepherd", "a_c_shepherd" },
		{ "Alien", "s_m_m_movalien_01" },
		{ "Beach", "a_f_m_beach_01" },
		{ "Bevhills", "a_f_m_bevhills_01" },
		{ "Bevhills", "a_f_m_bevhills_02" },
		{ "Bodybuild", "a_f_m_bodybuild_01" },
		{ "Business", "a_f_m_business_02" },
		{ "Downtown", "a_f_m_downtown_01" },
		{ "Eastsa", "a_f_m_eastsa_01" },
		{ "Eastsa", "a_f_m_eastsa_02" },
		{ "Fatbla", "a_f_m_fatbla_01" },
		{ "Fatcult", "a_f_m_fatcult_01" },
		{ "Fatwhite", "a_f_m_fatwhite_01" },
		{ "Ktown", "a_f_m_ktown_01" },
		{ "Ktown", "a_f_m_ktown_02" },
		{ "Prolhost", "a_f_m_prolhost_01" },
		{ "Salton", "a_f_m_salton_01" },
		{ "Skidrow", "a_f_m_skidrow_01" },
		{ "Soucentmc", "a_f_m_soucentmc_01" },
		{ "Soucent", "a_f_m_soucent_01" },
		{ "Soucent", "a_f_m_soucent_02" },
		{ "Tourist", "a_f_m_tourist_01" },
		{ "Trampbeac", "a_f_m_trampbeac_01" },
		{ "Tramp", "a_f_m_tramp_01" },
		{ "Genstreet", "a_f_o_genstreet_01" },
		{ "Indian", "a_f_o_indian_01" },
		{ "Ktown", "a_f_o_ktown_01" },
		{ "Salton", "a_f_o_salton_01" },
		{ "Soucent", "a_f_o_soucent_01" },
		{ "Soucent", "a_f_o_soucent_02" },
		{ "Beach", "a_f_y_beach_01" },
		{ "Bevhills", "a_f_y_bevhills_01" },
		{ "Bevhills", "a_f_y_bevhills_02" },
		{ "Bevhills", "a_f_y_bevhills_03" },
		{ "Bevhills", "a_f_y_bevhills_04" },
		{ "Business", "a_f_y_business_01" },
		{ "Business", "a_f_y_business_02" },
		{ "Business", "a_f_y_business_03" },
		{ "Business", "a_f_y_business_04" },
		{ "Eastsa", "a_f_y_eastsa_01" },
		{ "Eastsa", "a_f_y_eastsa_02" },
		{ "Eastsa", "a_f_y_eastsa_03" },
		{ "Epsilon", "a_f_y_epsilon_01" },
		{ "Fitness", "a_f_y_fitness_01" },
		{ "Fitness", "a_f_y_fitness_02" },
		{ "Genhot", "a_f_y_genhot_01" },
		{ "Golfer", "a_f_y_golfer_01" },
		{ "Hiker", "a_f_y_hiker_01" },
		{ "Hippie", "a_f_y_hippie_01" },
		{ "Hipster", "a_f_y_hipster_01" },
		{ "Hipster", "a_f_y_hipster_02" },
		{ "Hipster", "a_f_y_hipster_03" },
		{ "Hipster", "a_f_y_hipster_04" },
		{ "Indian", "a_f_y_indian_01" },
		{ "Juggalo", "a_f_y_juggalo_01" },
		{ "Runner", "a_f_y_runner_01" },
		{ "Rurmeth", "a_f_y_rurmeth_01" },
		{ "Scdressy", "a_f_y_scdressy_01" },
		{ "Skater", "a_f_y_skater_01" },
		{ "Soucent", "a_f_y_soucent_01" },
		{ "Soucent", "a_f_y_soucent_02" },
		{ "Soucent", "a_f_y_soucent_03" },
		{ "Tennis", "a_f_y_tennis_01" },
		{ "Topless", "a_f_y_topless_01" },
		{ "Tourist", "a_f_y_tourist_01" },
		{ "Tourist", "a_f_y_tourist_02" },
		{ "Vinewood", "a_f_y_vinewood_01" },
		{ "Vinewood", "a_f_y_vinewood_02" },
		{ "Vinewood", "a_f_y_vinewood_03" },
		{ "Vinewood", "a_f_y_vinewood_04" },
		{ "Yoga", "a_f_y_yoga_01" },
		{ "Acult", "a_m_m_acult_01" },
		{ "Afriamer", "a_m_m_afriamer_01" },
		{ "Beach", "a_m_m_beach_01" },
		{ "Beach", "a_m_m_beach_02" },
		{ "Bevhills", "a_m_m_bevhills_01" },
		{ "Bevhills", "a_m_m_bevhills_02" },
		{ "Business", "a_m_m_business_01" },
		{ "Eastsa", "a_m_m_eastsa_01" },
		{ "Eastsa", "a_m_m_eastsa_02" },
		{ "Farmer", "a_m_m_farmer_01" },
		{ "Fatlatin", "a_m_m_fatlatin_01" },
		{ "Genfat", "a_m_m_genfat_01" },
		{ "Genfat", "a_m_m_genfat_02" },
		{ "Golfer", "a_m_m_golfer_01" },
		{ "Hasjew", "a_m_m_hasjew_01" },
		{ "Hillbilly", "a_m_m_hillbilly_01" },
		{ "Hillbilly", "a_m_m_hillbilly_02" },
		{ "Indian", "a_m_m_indian_01" },
		{ "Ktown", "a_m_m_ktown_01" },
		{ "Malibu", "a_m_m_malibu_01" },
		{ "Mexcntry", "a_m_m_mexcntry_01" },
		{ "Mexlabor", "a_m_m_mexlabor_01" },
		{ "Og_boss", "a_m_m_og_boss_01" },
		{ "Paparazzi", "a_m_m_paparazzi_01" },
		{ "Polynesian", "a_m_m_polynesian_01" },
		{ "Prolhost", "a_m_m_prolhost_01" },
		{ "Rurmeth", "a_m_m_rurmeth_01" },
		{ "Salton", "a_m_m_salton_01" },
		{ "Salton", "a_m_m_salton_02" },
		{ "Salton", "a_m_m_salton_03" },
		{ "Salton", "a_m_m_salton_04" },
		{ "Skater", "a_m_m_skater_01" },
		{ "Skidrow", "a_m_m_skidrow_01" },
		{ "Socenlat", "a_m_m_socenlat_01" },
		{ "Soucent", "a_m_m_soucent_01" },
		{ "Soucent", "a_m_m_soucent_02" },
		{ "Soucent", "a_m_m_soucent_03" },
		{ "Soucent", "a_m_m_soucent_04" },
		{ "Stlat", "a_m_m_stlat_02" },
		{ "Tennis", "a_m_m_tennis_01" },
		{ "Tourist", "a_m_m_tourist_01" },
		{ "Trampbeac", "a_m_m_trampbeac_01" },
		{ "Tramp", "a_m_m_tramp_01" },
		{ "Tranvest", "a_m_m_tranvest_01" },
		{ "Tranvest", "a_m_m_tranvest_02" },
		{ "Acult", "a_m_o_acult_01" },
		{ "Acult", "a_m_o_acult_02" },
		{ "Beach", "a_m_o_beach_01" },
		{ "Genstreet", "a_m_o_genstreet_01" },
		{ "Ktown", "a_m_o_ktown_01" },
		{ "Salton", "a_m_o_salton_01" },
		{ "Soucent", "a_m_o_soucent_01" },
		{ "Soucent", "a_m_o_soucent_02" },
		{ "Soucent", "a_m_o_soucent_03" },
		{ "Tramp", "a_m_o_tramp_01" },
		{ "Acult", "a_m_y_acult_01" },
		{ "Acult", "a_m_y_acult_02" },
		{ "Beachvesp", "a_m_y_beachvesp_01" },
		{ "Beachvesp", "a_m_y_beachvesp_02" },
		{ "Beach", "a_m_y_beach_01" },
		{ "Beach", "a_m_y_beach_02" },
		{ "Beach", "a_m_y_beach_03" },
		{ "Bevhills", "a_m_y_bevhills_01" },
		{ "Bevhills", "a_m_y_bevhills_02" },
		{ "Breakdance", "a_m_y_breakdance_01" },
		{ "Busicas", "a_m_y_busicas_01" },
		{ "Business", "a_m_y_business_01" },
		{ "Business", "a_m_y_business_02" },
		{ "Business", "a_m_y_business_03" },
		{ "Cyclist", "a_m_y_cyclist_01" },
		{ "Dhill", "a_m_y_dhill_01" },
		{ "Downtown", "a_m_y_downtown_01" },
		{ "Eastsa", "a_m_y_eastsa_01" },
		{ "Eastsa", "a_m_y_eastsa_02" },
		{ "Epsilon", "a_m_y_epsilon_01" },
		{ "Epsilon", "a_m_y_epsilon_02" },
		{ "Gay", "a_m_y_gay_01" },
		{ "Gay", "a_m_y_gay_02" },
		{ "Genstreet", "a_m_y_genstreet_01" },
		{ "Genstreet", "a_m_y_genstreet_02" },
		{ "Golfer", "a_m_y_golfer_01" },
		{ "Hasjew", "a_m_y_hasjew_01" },
		{ "Hiker", "a_m_y_hiker_01" },
		{ "Hippy", "a_m_y_hippy_01" },
		{ "Hipster", "a_m_y_hipster_01" },
		{ "Hipster", "a_m_y_hipster_02" },
		{ "Hipster", "a_m_y_hipster_03" },
		{ "Indian", "a_m_y_indian_01" },
		{ "Jetski", "a_m_y_jetski_01" },
		{ "Juggalo", "a_m_y_juggalo_01" },
		{ "Ktown", "a_m_y_ktown_01" },
		{ "Ktown", "a_m_y_ktown_02" },
		{ "Latino", "a_m_y_latino_01" },
		{ "Methhead", "a_m_y_methhead_01" },
		{ "Mexthug", "a_m_y_mexthug_01" },
		{ "Motox", "a_m_y_motox_01" },
		{ "Motox", "a_m_y_motox_02" },
		{ "Musclbeac", "a_m_y_musclbeac_01" },
		{ "Musclbeac", "a_m_y_musclbeac_02" },
		{ "Polynesian", "a_m_y_polynesian_01" },
		{ "Roadcyc", "a_m_y_roadcyc_01" },
		{ "Runner", "a_m_y_runner_01" },
		{ "Runner", "a_m_y_runner_02" },
		{ "Salton", "a_m_y_salton_01" },
		{ "Skater", "a_m_y_skater_01" },
		{ "Skater", "a_m_y_skater_02" },
		{ "Soucent", "a_m_y_soucent_01" },
		{ "Soucent", "a_m_y_soucent_02" },
		{ "Soucent", "a_m_y_soucent_03" },
		{ "Soucent", "a_m_y_soucent_04" },
		{ "Stbla", "a_m_y_stbla_01" },
		{ "Stbla", "a_m_y_stbla_02" },
		{ "Stlat", "a_m_y_stlat_01" },
		{ "Stwhi", "a_m_y_stwhi_01" },
		{ "Stwhi", "a_m_y_stwhi_02" },
		{ "Sunbathe", "a_m_y_sunbathe_01" },
		{ "Surfer", "a_m_y_surfer_01" },
		{ "Vindouche", "a_m_y_vindouche_01" },
		{ "Vinewood", "a_m_y_vinewood_01" },
		{ "Vinewood", "a_m_y_vinewood_02" },
		{ "Vinewood", "a_m_y_vinewood_03" },
		{ "Vinewood", "a_m_y_vinewood_04" },
		{ "Yoga", "a_m_y_yoga_01" },
		{ "Proldriver", "u_m_y_proldriver_01" },
		{ "Sbike", "u_m_y_sbike" },
		{ "Staggrm", "u_m_y_staggrm_01" },
		{ "Tattoo", "u_m_y_tattoo_01" },
		{ "Abigail", "csb_abigail" },
		{ "Anita", "csb_anita" },
		{ "Anton", "csb_anton" },
		{ "Ballasog", "csb_ballasog" },
		{ "Bride", "csb_bride" },
		{ "Burgerdrug", "csb_burgerdrug" },
		{ "Car3guy1", "csb_car3guy1" },
		{ "Car3guy2", "csb_car3guy2" },
		{ "Chef", "csb_chef" },
		{ "Chin_goon", "csb_chin_goon" },
		{ "Cletus", "csb_cletus" },
		{ "Cop", "csb_cop" },
		{ "Customer", "csb_customer" },
		{ "Denise_friend", "csb_denise_friend" },
		{ "Fos_rep", "csb_fos_rep" },
		{ "G", "csb_g" },
		{ "Groom", "csb_groom" },
		{ "Dlr", "csb_grove_str_dlr" },
		{ "Hao", "csb_hao" },
		{ "Hugh", "csb_hugh" },
		{ "Imran", "csb_imran" },
		{ "Janitor", "csb_janitor" },
		{ "Maude", "csb_maude" },
		{ "Mweather", "csb_mweather" },
		{ "Ortega", "csb_ortega" },
		{ "Oscar", "csb_oscar" },
		{ "Porndudes", "csb_porndudes" },
		{ "Porndudes_p", "csb_porndudes_p" },
		{ "Prologuedriver", "csb_prologuedriver" },
		{ "Prolsec", "csb_prolsec" },
		{ "Gang", "csb_ramp_gang" },
		{ "Hic", "csb_ramp_hic" },
		{ "Hipster", "csb_ramp_hipster" },
		{ "Marine", "csb_ramp_marine" },
		{ "Mex", "csb_ramp_mex" },
		{ "Reporter", "csb_reporter" },
		{ "Roccopelosi", "csb_roccopelosi" },
		{ "Screen_writer", "csb_screen_writer" },
		{ "Stripper", "csb_stripper_01" },
		{ "Stripper", "csb_stripper_02" },
		{ "Tonya", "csb_tonya" },
		{ "Trafficwarden", "csb_trafficwarden" },
		{ "Amandatownley", "cs_amandatownley" },
		{ "Andreas", "cs_andreas" },
		{ "Ashley", "cs_ashley" },
		{ "Bankman", "cs_bankman" },
		{ "Barry", "cs_barry" },
		{ "Barry_p", "cs_barry_p" },
		{ "Beverly", "cs_beverly" },
		{ "Beverly_p", "cs_beverly_p" },
		{ "Brad", "cs_brad" },
		{ "Bradcadaver", "cs_bradcadaver" },
		{ "Carbuyer", "cs_carbuyer" },
		{ "Casey", "cs_casey" },
		{ "Chengsr", "cs_chengsr" },
		{ "Chrisformage", "cs_chrisformage" },
		{ "Clay", "cs_clay" },
		{ "Dale", "cs_dale" },
		{ "Davenorton", "cs_davenorton" },
		{ "Debra", "cs_debra" },
		{ "Denise", "cs_denise" },
		{ "Devin", "cs_devin" },
		{ "Dom", "cs_dom" },
		{ "Dreyfuss", "cs_dreyfuss" },
		{ "Drfriedlander", "cs_drfriedlander" },
		{ "Fabien", "cs_fabien" },
		{ "Fbisuit", "cs_fbisuit_01" },
		{ "Floyd", "cs_floyd" },
		{ "Guadalope", "cs_guadalope" },
		{ "Gurk", "cs_gurk" },
		{ "Hunter", "cs_hunter" },
		{ "Janet", "cs_janet" },
		{ "Jewelass", "cs_jewelass" },
		{ "Jimmyboston", "cs_jimmyboston" },
		{ "Jimmydisanto", "cs_jimmydisanto" },
		{ "Joeminuteman", "cs_joeminuteman" },
		{ "Johnnyklebitz", "cs_johnnyklebitz" },
		{ "Josef", "cs_josef" },
		{ "Josh", "cs_josh" },
		{ "Lamardavis", "cs_lamardavis" },
		{ "Lazlow", "cs_lazlow" },
		{ "Lestercrest", "cs_lestercrest" },
		{ "Lifeinvad", "cs_lifeinvad_01" },
		{ "Magenta", "cs_magenta" },
		{ "Manuel", "cs_manuel" },
		{ "Marnie", "cs_marnie" },
		{ "Martinmadrazo", "cs_martinmadrazo" },
		{ "Maryann", "cs_maryann" },
		{ "Michelle", "cs_michelle" },
		{ "Milton", "cs_milton" },
		{ "Molly", "cs_molly" },
		{ "Movpremf", "cs_movpremf_01" },
		{ "Movpremmale", "cs_movpremmale" },
		{ "Mrk", "cs_mrk" },
		{ "Mrsphillips", "cs_mrsphillips" },
		{ "Mrs_thornhill", "cs_mrs_thornhill" },
		{ "Natalia", "cs_natalia" },
		{ "Nervousron", "cs_nervousron" },
		{ "Nigel", "cs_nigel" },
		{ "Old_man1a", "cs_old_man1a" },
		{ "Old_man2", "cs_old_man2" },
		{ "Omega", "cs_omega" },
		{ "Orleans", "cs_orleans" },
		{ "Paper", "cs_paper" },
		{ "Paper_p", "cs_paper_p" },
		{ "Patricia", "cs_patricia" },
		{ "Priest", "cs_priest" },
		{ "Prolsec", "cs_prolsec_02" },
		{ "Russiandrunk", "cs_russiandrunk" },
		{ "Siemonyetarian", "cs_siemonyetarian" },
		{ "Solomon", "cs_solomon" },
		{ "Stevehains", "cs_stevehains" },
		{ "Stretch", "cs_stretch" },
		{ "Tanisha", "cs_tanisha" },
		{ "Taocheng", "cs_taocheng" },
		{ "Taostranslator", "cs_taostranslator" },
		{ "Tenniscoach", "cs_tenniscoach" },
		{ "Terry", "cs_terry" },
		{ "Tom", "cs_tom" },
		{ "Tomepsilon", "cs_tomepsilon" },
		{ "Tracydisanto", "cs_tracydisanto" },
		{ "Wade", "cs_wade" },
		{ "Zimbor", "cs_zimbor" },
		{ "Ballas", "g_f_y_ballas_01" },
		{ "Families", "g_f_y_families_01" },
		{ "Lost", "g_f_y_lost_01" },
		{ "Vagos", "g_f_y_vagos_01" },
		{ "Armboss", "g_m_m_armboss_01" },
		{ "Armgoon", "g_m_m_armgoon_01" },
		{ "Armlieut", "g_m_m_armlieut_01" },
		{ "Chemwork", "g_m_m_chemwork_01" },
		{ "Chemwork_p", "g_m_m_chemwork_01_p" },
		{ "Chiboss", "g_m_m_chiboss_01" },
		{ "Chiboss_p", "g_m_m_chiboss_01_p" },
		{ "Chicold", "g_m_m_chicold_01" },
		{ "Chicold_p", "g_m_m_chicold_01_p" },
		{ "Chigoon", "g_m_m_chigoon_01" },
		{ "Chigoon_p", "g_m_m_chigoon_01_p" },
		{ "Chigoon", "g_m_m_chigoon_02" },
		{ "Korboss", "g_m_m_korboss_01" },
		{ "Mexboss", "g_m_m_mexboss_01" },
		{ "Mexboss", "g_m_m_mexboss_02" },
		{ "Armgoon", "g_m_y_armgoon_02" },
		{ "Azteca", "g_m_y_azteca_01" },
		{ "Ballaeast", "g_m_y_ballaeast_01" },
		{ "Ballaorig", "g_m_y_ballaorig_01" },
		{ "Ballasout", "g_m_y_ballasout_01" },
		{ "Famca", "g_m_y_famca_01" },
		{ "Famdnf", "g_m_y_famdnf_01" },
		{ "Famfor", "g_m_y_famfor_01" },
		{ "Korean", "g_m_y_korean_01" },
		{ "Korean", "g_m_y_korean_02" },
		{ "Korlieut", "g_m_y_korlieut_01" },
		{ "Lost", "g_m_y_lost_01" },
		{ "Lost", "g_m_y_lost_02" },
		{ "Lost", "g_m_y_lost_03" },
		{ "Mexgang", "g_m_y_mexgang_01" },
		{ "Mexgoon", "g_m_y_mexgoon_01" },
		{ "Mexgoon", "g_m_y_mexgoon_02" },
		{ "Mexgoon", "g_m_y_mexgoon_03" },
		{ "Mexgoon_p", "g_m_y_mexgoon_03_p" },
		{ "Pologoon", "g_m_y_pologoon_01" },
		{ "Pologoon_p", "g_m_y_pologoon_01_p" },
		{ "Pologoon", "g_m_y_pologoon_02" },
		{ "Pologoon_p", "g_m_y_pologoon_02_p" },
		{ "Salvaboss", "g_m_y_salvaboss_01" },
		{ "Salvagoon", "g_m_y_salvagoon_01" },
		{ "Salvagoon", "g_m_y_salvagoon_02" },
		{ "Salvagoon", "g_m_y_salvagoon_03" },
		{ "Salvagoon_p", "g_m_y_salvagoon_03_p" },
		{ "Strpunk", "g_m_y_strpunk_01" },
		{ "Strpunk", "g_m_y_strpunk_02" },
		{ "Hc_driver", "hc_driver" },
		{ "Hc_gunman", "hc_gunman" },
		{ "Hc_hacker", "hc_hacker" },
		{ "Abigail", "ig_abigail" },
		{ "Amandatownley", "ig_amandatownley" },
		{ "Andreas", "ig_andreas" },
		{ "Ashley", "ig_ashley" },
		{ "Ballasog", "ig_ballasog" },
		{ "Bankman", "ig_bankman" },
		{ "Barry", "ig_barry" },
		{ "Barry_p", "ig_barry_p" },
		{ "Bestmen", "ig_bestmen" },
		{ "Beverly", "ig_beverly" },
		{ "Beverly_p", "ig_beverly_p" },
		{ "Brad", "ig_brad" },
		{ "Bride", "ig_bride" },
		{ "Car3guy1", "ig_car3guy1" },
		{ "Car3guy2", "ig_car3guy2" },
		{ "Casey", "ig_casey" },
		{ "Chef", "ig_chef" },
		{ "Chengsr", "ig_chengsr" },
		{ "Chrisformage", "ig_chrisformage" },
		{ "Clay", "ig_clay" },
		{ "Claypain", "ig_claypain" },
		{ "Cletus", "ig_cletus" },
		{ "Dale", "ig_dale" },
		{ "Davenorton", "ig_davenorton" },
		{ "Denise", "ig_denise" },
		{ "Devin", "ig_devin" },
		{ "Dom", "ig_dom" },
		{ "Dreyfuss", "ig_dreyfuss" },
		{ "Drfriedlander", "ig_drfriedlander" },
		{ "Fabien", "ig_fabien" },
		{ "Fbisuit", "ig_fbisuit_01" },
		{ "Floyd", "ig_floyd" },
		{ "Groom", "ig_groom" },
		{ "Hao", "ig_hao" },
		{ "Hunter", "ig_hunter" },
		{ "Janet", "ig_janet" },
		{ "Jay_norris", "ig_jay_norris" },
		{ "Jewelass", "ig_jewelass" },
		{ "Jimmyboston", "ig_jimmyboston" },
		{ "Jimmydisanto", "ig_jimmydisanto" },
		{ "Joeminuteman", "ig_joeminuteman" },
		{ "Johnnyklebitz", "ig_johnnyklebitz" },
		{ "Josef", "ig_josef" },
		{ "Josh", "ig_josh" },
		{ "Kerrymcintosh", "ig_kerrymcintosh" },
		{ "Lamardavis", "ig_lamardavis" },
		{ "Lazlow", "ig_lazlow" },
		{ "Lestercrest", "ig_lestercrest" },
		{ "Lifeinvad", "ig_lifeinvad_01" },
		{ "Lifeinvad", "ig_lifeinvad_02" },
		{ "Magenta", "ig_magenta" },
		{ "Manuel", "ig_manuel" },
		{ "Marnie", "ig_marnie" },
		{ "Maryann", "ig_maryann" },
		{ "Maude", "ig_maude" },
		{ "Michelle", "ig_michelle" },
		{ "Milton", "ig_milton" },
		{ "Molly", "ig_molly" },
		{ "Mrk", "ig_mrk" },
		{ "Mrsphillips", "ig_mrsphillips" },
		{ "Mrs_thornhill", "ig_mrs_thornhill" },
		{ "Natalia", "ig_natalia" },
		{ "Nervousron", "ig_nervousron" },
		{ "Nigel", "ig_nigel" },
		{ "Old_man1a", "ig_old_man1a" },
		{ "Old_man2", "ig_old_man2" },
		{ "Omega", "ig_omega" },
		{ "Oneil", "ig_oneil" },
		{ "Orleans", "ig_orleans" },
		{ "Ortega", "ig_ortega" },
		{ "Paper", "ig_paper" },
		{ "Patricia", "ig_patricia" },
		{ "Priest", "ig_priest" },
		{ "Prolsec", "ig_prolsec_02" },
		{ "Gang", "ig_ramp_gang" },
		{ "Hic", "ig_ramp_hic" },
		{ "Hipster", "ig_ramp_hipster" },
		{ "Mex", "ig_ramp_mex" },
		{ "Roccopelosi", "ig_roccopelosi" },
		{ "Russiandrunk", "ig_russiandrunk" },
		{ "Screen_writer", "ig_screen_writer" },
		{ "Siemonyetarian", "ig_siemonyetarian" },
		{ "Solomon", "ig_solomon" },
		{ "Stevehains", "ig_stevehains" },
		{ "Stretch", "ig_stretch" },
		{ "Talina", "ig_talina" },
		{ "Tanisha", "ig_tanisha" },
		{ "Taocheng", "ig_taocheng" },
		{ "Taostranslator", "ig_taostranslator" },
		{ "Taostranslator_p", "ig_taostranslator_p" },
		{ "Tenniscoach", "ig_tenniscoach" },
		{ "Terry", "ig_terry" },
		{ "Tomepsilon", "ig_tomepsilon" },
		{ "Tonya", "ig_tonya" },
		{ "Tracydisanto", "ig_tracydisanto" },
		{ "Trafficwarden", "ig_trafficwarden" },
		{ "Tylerdix", "ig_tylerdix" },
		{ "Wade", "ig_wade" },
		{ "Zimbor", "ig_zimbor" },
		{ "Deadhooker", "mp_f_deadhooker" },
		{ "Misty", "mp_f_misty_01" },
		{ "Stripperlite", "mp_f_stripperlite" },
		{ "Pros", "mp_g_m_pros_01" },
		{ "Mp_headtargets", "mp_headtargets" },
		{ "Claude", "mp_m_claude_01" },
		{ "Exarmy", "mp_m_exarmy_01" },
		{ "Famdd", "mp_m_famdd_01" },
		{ "Fibsec", "mp_m_fibsec_01" },
		{ "Freemode", "mp_m_freemode_01" },
		{ "Marston", "mp_m_marston_01" },
		{ "Niko", "mp_m_niko_01" },
		{ "Shopkeep", "mp_m_shopkeep_01" },
		{ "Armoured", "mp_s_m_armoured_01" },
		{ "Fembarber", "s_f_m_fembarber" },
		{ "Maid", "s_f_m_maid_01" },
		{ "Shop_high", "s_f_m_shop_high" },
		{ "Sweatshop", "s_f_m_sweatshop_01" },
		{ "Airhostess", "s_f_y_airhostess_01" },
		{ "Bartender", "s_f_y_bartender_01" },
		{ "Baywatch", "s_f_y_baywatch_01" },
		{ "Cop", "s_f_y_cop_01" },
		{ "Factory", "s_f_y_factory_01" },
		{ "Hooker", "s_f_y_hooker_01" },
		{ "Hooker", "s_f_y_hooker_02" },
		{ "Hooker", "s_f_y_hooker_03" },
		{ "Migrant", "s_f_y_migrant_01" },
		{ "Movprem", "s_f_y_movprem_01" },
		{ "Ranger", "s_f_y_ranger_01" },
		{ "Scrubs", "s_f_y_scrubs_01" },
		{ "Sheriff", "s_f_y_sheriff_01" },
		{ "Shop_low", "s_f_y_shop_low" },
		{ "Shop_mid", "s_f_y_shop_mid" },
		{ "Stripperlite", "s_f_y_stripperlite" },
		{ "Stripper", "s_f_y_stripper_01" },
		{ "Stripper", "s_f_y_stripper_02" },
		{ "Sweatshop", "s_f_y_sweatshop_01" },
		{ "Ammucountry", "s_m_m_ammucountry" },
		{ "Armoured", "s_m_m_armoured_01" },
		{ "Armoured", "s_m_m_armoured_02" },
		{ "Autoshop", "s_m_m_autoshop_01" },
		{ "Autoshop", "s_m_m_autoshop_02" },
		{ "Bouncer", "s_m_m_bouncer_01" },
		{ "Chemsec", "s_m_m_chemsec_01" },
		{ "Ciasec", "s_m_m_ciasec_01" },
		{ "Cntrybar", "s_m_m_cntrybar_01" },
		{ "Dockwork", "s_m_m_dockwork_01" },
		{ "Doctor", "s_m_m_doctor_01" },
		{ "Fiboffice", "s_m_m_fiboffice_01" },
		{ "Fiboffice", "s_m_m_fiboffice_02" },
		{ "Gaffer", "s_m_m_gaffer_01" },
		{ "Gardener", "s_m_m_gardener_01" },
		{ "Gentransport", "s_m_m_gentransport" },
		{ "Hairdress", "s_m_m_hairdress_01" },
		{ "Highsec", "s_m_m_highsec_01" },
		{ "Highsec", "s_m_m_highsec_02" },
		{ "Janitor", "s_m_m_janitor" },
		{ "Lathandy", "s_m_m_lathandy_01" },
		{ "Lifeinvad", "s_m_m_lifeinvad_01" },
		{ "Linecook", "s_m_m_linecook" },
		{ "Lsmetro", "s_m_m_lsmetro_01" },
		{ "Mariachi", "s_m_m_mariachi_01" },
		{ "Marine", "s_m_m_marine_01" },
		{ "Marine", "s_m_m_marine_02" },
		{ "Migrant", "s_m_m_migrant_01" },
		{ "Zombie", "u_m_y_zombie_01" },
		{ "Movprem", "s_m_m_movprem_01" },
		{ "Paramedic", "s_m_m_paramedic_01" },
		{ "Pilot", "s_m_m_pilot_01" },
		{ "Pilot", "s_m_m_pilot_02" },
		{ "Postal", "s_m_m_postal_01" },
		{ "Postal", "s_m_m_postal_02" },
		{ "Prisguard", "s_m_m_prisguard_01" },
		{ "Scientist", "s_m_m_scientist_01" },
		{ "Security", "s_m_m_security_01" },
		{ "Snowcop", "s_m_m_snowcop_01" },
		{ "Strperf", "s_m_m_strperf_01" },
		{ "Strpreach", "s_m_m_strpreach_01" },
		{ "Strvend", "s_m_m_strvend_01" },
		{ "Trucker", "s_m_m_trucker_01" },
		{ "Ups", "s_m_m_ups_01" },
		{ "Ups", "s_m_m_ups_02" },
		{ "Busker", "s_m_o_busker_01" },
		{ "Airworker", "s_m_y_airworker" },
		{ "Ammucity", "s_m_y_ammucity_01" },
		{ "Armymech", "s_m_y_armymech_01" },
		{ "Autopsy", "s_m_y_autopsy_01" },
		{ "Barman", "s_m_y_barman_01" },
		{ "Baywatch", "s_m_y_baywatch_01" },
		{ "Blackops", "s_m_y_blackops_01" },
		{ "Blackops", "s_m_y_blackops_02" },
		{ "Busboy", "s_m_y_busboy_01" },
		{ "Chef", "s_m_y_chef_01" },
		{ "Clown", "s_m_y_clown_01" },
		{ "Construct", "s_m_y_construct_01" },
		{ "Construct", "s_m_y_construct_02" },
		{ "Cop", "s_m_y_cop_01" },
		{ "Dealer", "s_m_y_dealer_01" },
		{ "Devinsec", "s_m_y_devinsec_01" },
		{ "Dockwork", "s_m_y_dockwork_01" },
		{ "Doorman", "s_m_y_doorman_01" },
		{ "Dwservice", "s_m_y_dwservice_01" },
		{ "Dwservice", "s_m_y_dwservice_02" },
		{ "Factory", "s_m_y_factory_01" },
		{ "Fireman", "s_m_y_fireman_01" },
		{ "Garbage", "s_m_y_garbage" },
		{ "Grip", "s_m_y_grip_01" },
		{ "Hwaycop", "s_m_y_hwaycop_01" },
		{ "Marine", "s_m_y_marine_01" },
		{ "Marine", "s_m_y_marine_02" },
		{ "Marine", "s_m_y_marine_03" },
		{ "Mime", "s_m_y_mime" },
		{ "Pestcont", "s_m_y_pestcont_01" },
		{ "Pilot", "s_m_y_pilot_01" },
		{ "Prismuscl", "s_m_y_prismuscl_01" },
		{ "Ranger", "s_m_y_ranger_01" },
		{ "Robber", "s_m_y_robber_01" },
		{ "Sheriff", "s_m_y_sheriff_01" },
		{ "Shop_mask", "s_m_y_shop_mask" },
		{ "Strvend", "s_m_y_strvend_01" },
		{ "Swat", "s_m_y_swat_01" },
		{ "Uscg", "s_m_y_uscg_01" },
		{ "Valet", "s_m_y_valet_01" },
		{ "Waiter", "s_m_y_waiter_01" },
		{ "Winclean", "s_m_y_winclean_01" },
		{ "Xmech", "s_m_y_xmech_01" },
		{ "Xmech", "s_m_y_xmech_02" },
		{ "Corpse", "u_f_m_corpse_01" },
		{ "Miranda", "u_f_m_miranda" },
		{ "Promourn", "u_f_m_promourn_01" },
		{ "Moviestar", "u_f_o_moviestar" },
		{ "Prolhost", "u_f_o_prolhost_01" },
		{ "Bikerchic", "u_f_y_bikerchic" },
		{ "Comjane", "u_f_y_comjane" },
		{ "Corpse", "u_f_y_corpse_01" },
		{ "Corpse", "u_f_y_corpse_02" },
		{ "Hotposh", "u_f_y_hotposh_01" },
		{ "Jewelass", "u_f_y_jewelass_01" },
		{ "Mistress", "u_f_y_mistress" },
		{ "Poppymich", "u_f_y_poppymich" },
		{ "Princess", "u_f_y_princess" },
		{ "Spyactress", "u_f_y_spyactress" },
		{ "Aldinapoli", "u_m_m_aldinapoli" },
		{ "Bankman", "u_m_m_bankman" },
		{ "Bikehire", "u_m_m_bikehire_01" },
		{ "Fibarchitect", "u_m_m_fibarchitect" },
		{ "Filmdirector", "u_m_m_filmdirector" },
		{ "Glenstank", "u_m_m_glenstank_01" },
		{ "Griff", "u_m_m_griff_01" },
		{ "Jesus", "u_m_m_jesus_01" },
		{ "Jewelsec", "u_m_m_jewelsec_01" },
		{ "Jewelthief", "u_m_m_jewelthief" },
		{ "Markfost", "u_m_m_markfost" },
		{ "Partytarget", "u_m_m_partytarget" },
		{ "Prolsec", "u_m_m_prolsec_01" },
		{ "Promourn", "u_m_m_promourn_01" },
		{ "Rivalpap", "u_m_m_rivalpap" },
		{ "Spyactor", "u_m_m_spyactor" },
		{ "Willyfist", "u_m_m_willyfist" },
		{ "Finguru", "u_m_o_finguru_01" },
		{ "Taphillbilly", "u_m_o_taphillbilly" },
		{ "Tramp", "u_m_o_tramp_01" },
		{ "Abner", "u_m_y_abner" },
		{ "Antonb", "u_m_y_antonb" },
		{ "Babyd", "u_m_y_babyd" },
		{ "Baygor", "u_m_y_baygor" },
		{ "Burgerdrug", "u_m_y_burgerdrug_01" },
		{ "Chip", "u_m_y_chip" },
		{ "Cyclist", "u_m_y_cyclist_01" },
		{ "Fibmugger", "u_m_y_fibmugger_01" },
		{ "Guido", "u_m_y_guido_01" },
		{ "Gunvend", "u_m_y_gunvend_01" },
		{ "Hippie", "u_m_y_hippie_01" },
		{ "Militarybum", "u_m_y_militarybum" },
		{ "Paparazzi", "u_m_y_paparazzi" },
		{ "Party", "u_m_y_party_01" },
		{ "Pogo", "u_m_y_pogo_01" },
		{ "Prisoner", "u_m_y_prisoner_01" }
	};

	Hash usableWeaponHashes[85] = {
		126349499,
		2694266206,
		1233104067,
		101631238,
		911657153,
		1834241177,
		0x1B06D571,
		0x5EF9FEC4,
		0x22D8FE39,
		0x99AEEB3B,
		0x2BE6766B,
		0x13532244,
		0xBFEFFF6D,
		0x83BF0278,
		0xAF113F99,
		0x9D07F764,
		0x7FD62962,
		0x1D073A89,
		0x7846A318,
		0xE284C527,
		0xC472FE2,
		0x5FC3C11,
		0xA284510B,
		0xB1CA77B1,
		0x42BF8A85,
		0x93E220BD,
		0xFDBC8A50,
		0x2C3731D9,
		0x24B17070,
		0x34A67B97,
		0xFBAB5776,
		0x99B507EA,
		0x678B81B1,
		0x4E875F73,
		0x958A4A8F,
		0x84BD7BFD,
		0x440E4788,
		0xEFE7E2DF,
		0x9D61E50F,
		0xF9E6AA4B,
		0xC0A3098D,
		0xBFD21232,
		0x476BF155,
		0xAF3696A1,
		0xB62D1F67,
		0xD205520E,
		0x7F229F94,
		0x61012683,
		0x83839C4,
		0x92A27487,
		0xA89CB99E,
		0x7F7497E5,
		0x47757124,
		0x3AABBBAA,
		0xC734385A,
		0xAB564B93,
		0x63AB0442,
		0xF9DCBF2D,
		0xA3D4D34,
		0xD8DF3C3C,
		0xDC4DB296,
		0xDD5DF8D9,
		0xDB1AA450,
		0xEF951FBB,
		0x624FE830,
		0x8BB05FD7,
		0xC1B3C3D1,
		0xDFE37640,
		0x78A97CD0,
		0xA914799,
		0x394F415C,
		0x19044EE0,
		0x781FE4A,
		0x12E82D3D,
		0x176898A6,
		0x787F0BB,
		0xE232C28C,
		0xD04C944D,
		0x0A3D4D34,
		0x6D544C99,
		0x2C082D7D,
		0xCD274149,
		0xBD248B55,
		0xBA45E8B8,
		0x94117305,
	};

	shared_ptr<ButtonOption> m_modelOptions[NUMOF(m_models)];
	shared_ptr<BreakOption> m_searchBreak;

	void SetModelI(Hash model) {
		if (STREAMING::IsModelInCdimage(model)) {
			if (STREAMING::IsModelValid(model)) {
				GetEntityControl()->RequestModel(model, [](int model) {
					PLAYER::SetPlayerModel(GetLocalPlayer().m_id, model);
				});
			}
		}
	}

	void SetModel(const char* model) {
		SetModelI(Utils::GetHashKey(model));
	}

	void HairRainbow() {
		static int TIMER;
		Utils::DoTimedFunction(&TIMER, 250, [] {PED::_SetPedHairColor(GetLocalPlayer().m_ped, MISC::GetRandomIntInRange(0, 64), MISC::GetRandomIntInRange(0, 5)); });
	}

}

void ModelMenu::Init() {
	setParentSubmenu<LocalMenu>();
	setName("Model", true, true);

	//addOption(NumberOption<int>(TOGGLE, "Model width") // might need to be looped
	//	.addToggle(vars.width)
	//	.addNumber(vars.editWidth, "%i", 10).addMin(0).addMax(254)
	//	.addHotkey().addTranslation()
	//	.addTooltip("Edit your models width"));

	//addOption(NumberOption<int>(TOGGLE, "Model height") // might need to be looped
	//	.addToggle(vars.height)
	//	.addNumber(vars.editHeight, "%i", 10).addMin(0).addMax(252)
	//	.addHotkey().addTranslation()
	//	.addTooltip("Edit your models height"));

	addOption(NumberOption<float>(TOGGLE, "Model width") // might need to be looped
		.addToggle(vars.width)
		.addNumber(vars.editWidth, "%0.1f", 0.1f).addMin(-400.0f).addMax(400.0f)
		.addHotkey().addTranslation()
		.addTooltip("Edit your models width"));

	addOption(NumberOption<float>(TOGGLE, "Model height") // might need to be looped
		.addToggle(vars.height)
		.addNumber(vars.editHeight, "%0.1f", 0.1f).addMin(-10.0f).addMax(400.0f)
		.addHotkey().addTranslation()
		.addTooltip("Edit your models height"));

	addOption(NumberOption<float>(TOGGLE, "Model thickness") // might need to be looped
		.addToggle(vars.tickness)
		.addNumber(vars.edittickness, "%0.1f", 0.1f).addMin(-400.0f).addMax(400.0f)
		.addHotkey().addTranslation()
		.addTooltip("Edit your models thickness"));

	addOption(ButtonOption("Random model outfit")
		.addFunction([] {
		PED::SetPedRandomComponentVariation(GetLocalPlayer().m_ped, true);
		PED::SetPedRandomProps(GetLocalPlayer().m_ped);
	})
		.addHotkey().addTranslation()
		.addTooltip("Get a random outfit"));

	addOption(ToggleOption("Rainbow hair")
		.addToggle(vars.rainbowhair).addTranslation()
		.addHotkey().canBeSaved()
		.addTooltip("Rainbow hair"));

	addOption(BreakOption("Defaults").addTranslation());

	addOption(ButtonOption("Default online male model")
		.addFunction([] {
		SetModel("mp_m_freemode_01");
		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			PED::SetPedRandomComponentVariation(GetLocalPlayer().m_ped, true);
			PED::SetPedRandomProps(GetLocalPlayer().m_ped);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
			}
		});
	})
		.addHotkey().addTranslation()
		.addTooltip("Once you have clicked this click the random model outfit skin below"));

	addOption(ButtonOption("Default online female model")
		.addFunction([] {
		SetModel("mp_f_freemode_01");
		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			PED::SetPedRandomComponentVariation(GetLocalPlayer().m_ped, true);
			PED::SetPedRandomProps(GetLocalPlayer().m_ped);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
			}
		});
	})
		.addHotkey().addTranslation()
		.addTooltip("Once you have clicked this click the random model outfit skin below"));

	addOption(ButtonOption("Michael")
		.addFunction([] {SetModel("player_zero"); })
		.addHotkey().addTranslation()
		.addTooltip("Michael"));

	addOption(ButtonOption("Franklin")
		.addFunction([] {SetModel("player_one"); })
		.addHotkey().addTranslation()
		.addTooltip("Franklin"));

	addOption(ButtonOption("Trevor")
		.addFunction([] {SetModel("player_two"); })
		.addHotkey().addTranslation()
		.addTooltip("Trevor"));

	addOption(ButtonOption("Custom model")
		.addFunction([this] {
		GetMenuInput()->AddToQueue([] {
			string inputTemp;
			if (GetMenuInput()->Text("Custom model", inputTemp, 2, 20)) {
				String input = inputTemp.c_str();
				if (input[0] == '0' && input[1] == 'x') {
					if (STREAMING::IsModelValid(_strtoui64(input, 0, 0)))SetModelI(_strtoui64(input, 0, 0));
					else GetRenderer()->NotifyBottom("Model is not valid");
				} else {
					if (STREAMING::IsModelValid(Utils::GetHashKey(input)))SetModel(input);
					else GetRenderer()->NotifyBottom("Model is not valid");
				}
			}
		}); }).addHotkey().addTranslation()
			.addTooltip("Enter a custom model name"));

	addOption(BreakOption("Models").addTranslation());

	addOption(ButtonOption("Search")
		.addFunction([] {
		GetMenuInput()->AddToQueue([] {
			string input;
			if (GetMenuInput()->Text("Search model", input, 0, 100)) {
				string lower = toLower(input);
				for (auto& op : m_modelOptions) {
					string temp = op->getName().GetOriginal();
					op.get()->setVisible(toLower(temp).find(lower) != string::npos);
				}
				if (input[0] == '\0') m_searchBreak.get()->setLine();
				else m_searchBreak.get()->setName(((string)input).c_str());
				if (GetMenu()->m_maxOptions + GetMenu()->m_scrollOffset > GetSubmenuHandler()->GetTotalOptions()) {
					int offset = GetMenu()->m_maxOptions + GetMenu()->m_scrollOffset - GetSubmenuHandler()->GetTotalOptions();
					Top();
					GetMenu()->m_currentOption = 8;
				}
			}
		}); }).addTranslation()
		.addTooltip("Search for a model name"));

	m_searchBreak = addOption(BreakOption());

	for (int i = 0; i < NUMOF(m_models); i++) {
		m_modelOptions[i] = addOption(ButtonOption(m_models[i].m_name)
			.addFunction([=] {SetModel(m_models[i].m_model); 
		GetFiberPool()->DoJob([=] {
			WAIT(1000);
			int Ammo = -1;
			for (int i = 0; i < 82; i++) {
				WEAPON::GetMaxAmmo(GetLocalPlayer().m_ped, usableWeaponHashes[i], &Ammo);
				WEAPON::GiveWeaponToPed(GetLocalPlayer().m_ped, usableWeaponHashes[i], Ammo, false, true);
			}
		});	})
			.addHotkey()
			.addTooltip(m_models[i].m_name));
	}
}

/*Update once when submenu is opened*/
void ModelMenu::UpdateOnce() {}

/*Update while submenu is active*/
void ModelMenu::Update() {}

/*Background update*/
void ModelMenu::FeatureUpdate() {
	//ReClass :thinking:
	//if (vars.width) *reinterpret_cast<byte*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), { 0x8, 0x62 })) = (byte)vars.editWidth;
	//if (vars.height)*reinterpret_cast<byte*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), { 0x8, 0x8A })) = (byte)vars.editHeight;
	if (vars.width)*reinterpret_cast<float*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), { 0x8, 0x0064 })) = (float)vars.editWidth;
	if (vars.height)*reinterpret_cast<float*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), { 0x8, 0x88 })) = (float)vars.editHeight;
	if (vars.tickness)*reinterpret_cast<float*>(Pattern::getMultilayerPointer(Backend::GetWorldPtr(), { 0x8, 0x70 })) = (float)vars.edittickness;

	if (vars.rainbowhair)HairRainbow();
}

/*Singleton*/
ModelMenu* _instance;
ModelMenu* ModelMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new ModelMenu();
		_instance->Init();
		GetSubmenuHandler()->addSubmenu(_instance);
	}
	return _instance;
}
ModelMenu::~ModelMenu() { delete _instance; }