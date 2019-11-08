/*

    General Vault 13 header
    Used to track quest states and stuff.

*/

#ifndef VAULT13_H
#define VAULT13_H

/************************************************
    Generic Defines
************************************************/

// Fixt uses different code in V13. Maybe it can / should be consolidated with fo1.h define.
#define invasion_kill_critter_V13   variable DeathType;                             \
                                    variable id := random(0, 18);                   \
                                    if id <= 2 then begin                           \
                                        DeathType := ANIM_exploded_to_nothing_sf;   \
                                    end                                             \
                                    else if id <= 10 then begin                     \
                                        DeathType := ANIM_burned_to_nothing_sf;     \
                                    end                                             \
                                    else if id <= 15 then begin                     \
                                        DeathType := ANIM_melted_to_nothing_sf;     \
                                    end                                             \
                                    else begin                                      \
                                        DeathType := ANIM_fall_front_blood_sf;      \
                                    end                                             \
                                    kill_critter(self_obj, DeathType)


#endif // VAULT13_H




