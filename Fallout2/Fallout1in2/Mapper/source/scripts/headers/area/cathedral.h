/*

    General Cathedral / Master's Lair header
    Used to track quest states and stuff.

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

// Cathedral invaders
#define FOLINVAD_FLOAT_Entrance     bit_1
#define FOLINVAD_FLOAT_Vault        bit_2
#define FOLINVAD_FLOAT_Master       bit_3
#define FOLINVAD_FLOAT_Exit         bit_4
#define BROINVAD_FLOAT_Room         bit_5
#define BROINVAD_FLOAT_Master       bit_6

#define set_invad_status(x)         set_gvar_bit_on(GVAR_CATHEDRAL_INVADER_STATES, x)
#define invad_status(x)             (gvar_bit(GVAR_CATHEDRAL_INVADER_STATES, x))
