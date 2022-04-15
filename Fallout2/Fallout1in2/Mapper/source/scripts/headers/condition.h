/*
   Copyright 1998-2003 Interplay Entertainment Corp.  All rights reserved.
*/

#pragma once

/**********************************************************
   Filename: Condition.h

   Purpose: This file is used to map the conditionals used
            within the scripting tool which the designers
            will be using.

   Structure of File
        I.      Variables
        II.     Standard Conditionals
        III.    Forked End Conditionals
        IV.     Giving Items
            A.  Armor
            B.  Weapons
            C.  Ammo
            D.  Medical
            E.  Containers
            F.  Books
            G.  Tools
            H.  Misc.

   Created: Novermber 10, 1997

   Updated:
        November 13, 1997   - rwh2
            Added In giving Inventory Items
        August 3, 2019      - Wipe
            Removed unspeakable horrors.

**********************************************************/

/************************************************************************
**********************      Variables       *****************************
************************************************************************/

#define ROLL_CRITICAL_FAILURE           0
#define ROLL_FAILURE                    1
#define ROLL_SUCCESS                    2
#define ROLL_CRITICAL_SUCCESS           3

/************************************************************************
*******************   Standard Conditionals    **************************
************************************************************************/

#ifndef day
#define day                     ((game_time_hour > 600) and (game_time_hour < 1800))
#endif
#ifndef night
#define night                   ((game_time_hour <= 600) or (game_time_hour >= 1800))
#endif
