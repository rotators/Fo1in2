/*

   .h Title

*/

#pragma once

/************************************************
    Generic Defines
************************************************/

// All Map Vars need to start w/ MVAR_
#define MVAR_NORTH_BEFORE            (0)
#define MVAR_SOUTH_BEFORE            (1)
#define MVAR_EAST_BEFORE             (2)
#define MVAR_WEST_BEFORE             (3)
#define MVAR_COUNT                   (4)
#define MVAR_TOUCHING                (5)
#define MVAR_REWARD_ONE              (6) //  These vars are for communication with
#define MVAR_REWARD_TWO              (7) //    Garret about the reward player should recieve.
#define MVAR_SET_GONE                (8) //  Is Set gone ...must remove on map exit.
#define MVAR_SET_DEAD                (9) //  Is Set dead ...then genghouls check this.
#define MVAR_INVADED                 (10)//  Has this map been invaded by Super Mutants?
#define MVAR_Fixt_DOOR_LOCKED        (11)//  Is the entrance locked? Starts as YES.
#define MVAR_FIxt_CHARMED_IN_DOOR    (12)//  Has the player talked their way into unlocking the door?
#define MVAR_SET_DOOR_STATUS         (13)//   Adding for ass-covering and future-proofing
#define MVAR_Fixt_HALLDED_PLACEHOLDER_1      (14)//   Adding for ass-covering and future-proofing
#define MVAR_Fixt_HALLDED_PLACEHOLDER_2      (15)//   Adding for ass-covering and future-proofing
#define MVAR_Fixt_HALLDED_PLACEHOLDER_3      (16)//   Adding for ass-covering and future-proofing
#define MVAR_Fixt_HALLDED_PLACEHOLDER_4      (17)//   Adding for ass-covering and future-proofing

