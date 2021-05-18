/*

    General Cathedral / Master's Lair header
    Used to track quest states and stuff.

*/

#ifndef CATHEDRAL_H
#define CATHEDRAL_H

/************************************************
    Generic Defines
************************************************/

// Cathedral invaders
#define FOLINVAD_FLOAT_Entrance     bit_1
#define FOLINVAD_FLOAT_Vault        bit_2
#define FOLINVAD_FLOAT_Master       bit_3
#define FOLINVAD_FLOAT_Exit         bit_4
#define BROINVASD_FLOAT_Room        bit_5
#define BROINVASD_FLOAT_Master      bit_6

#define set_invad_status(x)         set_gvar_bit_on(GVAR_FOLLOWER_MACHO_STATES, x)
#define invad_status(x)             (gvar_bit(GVAR_FOLLOWER_MACHO_STATES, x))

#define ghunters_killed             (gvar_bit(GVAR_FOLLOWER_MACHO_STATES, HUNTER_FATHER_DEAD) and gvar_bit(GVAR_GECKO_HUNTER_STATUS, HUNTER_SON_DEAD))
#define ghunters_party_killed       (gvar_bit(GVAR_FOLLOWER_MACHO_STATES, HUNTER_WAR_PARTY))
#define ghunters_pc_knows_names     (gvar_bit(GVAR_FOLLOWER_MACHO_STATES, HUNTER_PC_KNOWS_NAMES))
#define ghunters_know_pc_name       (gvar_bit(GVAR_FOLLOWER_MACHO_STATES, HUNTER_KNOWS_PC_NAME))

#endif // CATHEDRAL_H




