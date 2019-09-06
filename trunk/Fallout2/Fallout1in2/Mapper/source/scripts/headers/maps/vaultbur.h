/*

	Vault 15 - Burried Vault

*/

#ifndef VAULTBUR_H
#define VAULTBUR_H

/************************************************
    Generic Defines
************************************************/
// Respawning rats:
#define HOLE_HEX           18287
#define ROCK_HEX           18487

#define STATE_OPEN         0
#define STATE_CLOSED       1
#define STATE_LARGE        2

#define RESPAWN_TIME       (ONE_GAME_DAY)
#define MIN_RATS           5
#define MAX_RATS           15

// All Map Vars need to start w/ MVAR_
#define MVAR_RATHOLE_STATE        (0) // Is the rathole open, closed, or big?
#define MVAR_RoamingCount         (1) // How many roamers are there currently.
#define MVAR_RespawnTimer         (2) // How long until next respawn cycle?

#endif // VAULTBUR_H


