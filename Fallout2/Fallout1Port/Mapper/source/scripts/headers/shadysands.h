/*

	Shady Sands

*/

#ifndef SHADYSANDS_H
#define SHADYSANDS_H

/************************************************
    Generic Defines
************************************************/
// Heal Jarvis quest
#define get_jarvis_healed              (global_var(GVAR_CURE_JARVIS) >= 2)

#define set_heal_jarvis                if (global_var(GVAR_CURE_JARVIS) == 0) then set_global_var(GVAR_CURE_JARVIS,1)
#define set_jarvis_healed              set_global_var(GVAR_CURE_JARVIS,2)

// Radscorpion quest
#define radscorp_quest_inactive        (global_var(GVAR_RADSCORPION_SEED) == 0)
#define radscorp_quest_active          (global_var(GVAR_RADSCORPION_SEED) == 1)
#define radscorp_quest_completed       (global_var(GVAR_RADSCORPION_SEED) == 2)

#define set_radscorp_quest_active      set_global_var(GVAR_RADSCORPION_SEED, 1)
#define set_radscorp_quest_completed   set_global_var(GVAR_RADSCORPION_SEED, 2)

// Tandi quest
#define get_tandi_returned             (global_var(GVAR_TANDI_HIRELING_STATUS) == 2)

#define tandi_quest_inactive           (global_var(GVAR_TANDI_RESCUE) == 0)
#define tandi_quest_active             (global_var(GVAR_TANDI_RESCUE) == 1)
#define tandi_quest_completed          (global_var(GVAR_TANDI_RESCUE) == 2)

#define set_tandi_quest_active         set_global_var(GVAR_TANDI_RESCUE, 1)
#define set_tandi_quest_completed      set_global_var(GVAR_TANDI_RESCUE, 2)

#endif // SHADYSANDS_H
