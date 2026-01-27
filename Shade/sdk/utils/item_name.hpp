#pragma once
#include "../utils/hash.hpp"

std::string_view GetItemName(const std::string_view& name) {
	hash_t name_hash = hash::Get(name);

    switch (name_hash) {
    // Pistols
    case hash::Set("weapon_glock"):                 return "Glock-18";
    case hash::Set("weapon_cz75a"):                 return "CZ75-Auto";
    case hash::Set("weapon_p250"):                  return "P250";
    case hash::Set("weapon_fiveseven"):             return "Five-SeveN";
    case hash::Set("weapon_deagle"):                return "Desert-Eagle";
    case hash::Set("weapon_revolver"):              return "R8-Revolver";
    case hash::Set("weapon_elite"):                 return "Dual-Berettas";
    case hash::Set("weapon_tec9"):                  return "Tec-9";
    case hash::Set("weapon_hkp2000"):               return "P2000";
    case hash::Set("weapon_usp_silencer"):          return "USP-S";

    // Sub Machineguns
    case hash::Set("weapon_mac10"):                 return "MAC-10";
    case hash::Set("weapon_mp9"):                   return "MP9";
    case hash::Set("weapon_mp7"):                   return "MP7";
    case hash::Set("weapon_mp5sd"):                 return "MP5-SD";
    case hash::Set("weapon_ump45"):                 return "UMP-45";
    case hash::Set("weapon_bizon"):                 return "PP-Bizon";
    case hash::Set("weapon_p90"):                   return "P90";

    // Rifles
    case hash::Set("weapon_galilar"):               return "Galil AR";
    case hash::Set("weapon_famas"):                 return "FAMAS";
    case hash::Set("weapon_ak47"):                  return "AK-47";
    case hash::Set("weapon_m4a1"):                  return "M4A1";
    case hash::Set("weapon_m4a1_silencer"):         return "M4A1-S";
    case hash::Set("weapon_sg556"):                 return "SG-553";
    case hash::Set("weapon_aug"):                   return "AUG";

    // Shotguns
    case hash::Set("weapon_nova"):                  return "Nova";
    case hash::Set("weapon_xm1014"):                return "XM1014";
    case hash::Set("weapon_sawedoff"):              return "Sawed-Off";
    case hash::Set("weapon_mag7"):                  return "MAG-7";

    // Sniper Rifles
    case hash::Set("weapon_ssg08"):                 return "SSG 08";
    case hash::Set("weapon_awp"):                   return "AWP";
    case hash::Set("weapon_g3sg1"):                 return "G3SG1";
    case hash::Set("weapon_scar20"):                return "SCAR-20";

    // Machineguns
    case hash::Set("weapon_m249"):                  return "M249";
    case hash::Set("weapon_negev"):                 return "Negev";

    // Knives
    case hash::Set("weapon_bayonet"):               return "Bayonet";
    case hash::Set("weapon_knife_css"):             return "Classic Knife";
    case hash::Set("weapon_knife_flip"):            return "Flip Knife";
    case hash::Set("weapon_knife_gut"):             return "Gut Knife";
    case hash::Set("weapon_knife_karambit"):        return "Karambit";
    case hash::Set("weapon_knife_m9_bayonet"):      return "M9 Bayonet";
    case hash::Set("weapon_knife_tactical"):        return "Huntsman Knife";
    case hash::Set("weapon_knife_falchion"):        return "Falchion Knife";
    case hash::Set("weapon_knife_survival_bowie"):  return "Bowie Knife";
    case hash::Set("weapon_knife_butterfly"):       return "Butterfly Knife";
    case hash::Set("weapon_knife_push"):            return "Shadow Daggers";
    case hash::Set("weapon_knife_cord"):            return "Paracord Knife";
    case hash::Set("weapon_knife_canis"):           return "Survival Knife";
    case hash::Set("weapon_knife_ursus"):           return "Ursus Knife";
    case hash::Set("weapon_knife_gypsy_jackknife"): return "Navaja Knife";
    case hash::Set("weapon_knife_outdoor"):         return "Nomad Knife";
    case hash::Set("weapon_knife_stiletto"):        return "Stiletto Knife";
    case hash::Set("weapon_knife_widowmaker"):      return "Talon Knife";
    case hash::Set("weapon_knife_skeleton"):        return "Skeleton Knife";
    case hash::Set("weapon_knife_kukri"):           return "Kukri Knife";

    // Grenades
    case hash::Set("weapon_flashbang"):             return "Flashbang";
    case hash::Set("weapon_smokegrenade"):          return "Smoke";
    case hash::Set("weapon_molotov"):               return "Molotov";
    case hash::Set("weapon_decoy"):                 return "Decoy";
    case hash::Set("weapon_incgrenade"):            return "Incendiary";
    case hash::Set("weapon_hegrenade"):             return "HE Grenade";

    // Others
    case hash::Set("weapon_taser"):                 return "Zeus-X27";

    default:
        if (name.starts_with("weapon_"))
            return name.substr(7);
    }

    return name;
}