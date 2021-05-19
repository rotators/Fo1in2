/*

    Brotherhood of Steel generic defines

*/

#pragma once

/************************************************
    Generic Defines
************************************************/
// Scout the area to the north
#define scout_quest_inactive            (global_var(GVAR_SCOUTED_NORTH_BRO) == 0)
#define scout_quest_active              (global_var(GVAR_SCOUTED_NORTH_BRO) == 1)
#define scout_quest_completed           (global_var(GVAR_SCOUTED_NORTH_BRO) == 2)

#define set_scout_quest_active          set_global_var(GVAR_SCOUTED_NORTH_BRO, 1)
#define set_scout_quest_completed       if scout_quest_active then set_global_var(GVAR_SCOUTED_NORTH_BRO, 2)

// Piss off important people and see yourself out
#define get_dude_kicked_out             (global_var(GVAR_QUEST_BROHOOD_1_JOIN_THEM) >= 5)
#define set_dude_kicked_out             set_global_var(GVAR_QUEST_BROHOOD_1_JOIN_THEM, 5);    \
                                        set_global_var(GVAR_MARK_BROTHER_2, 0);               \
                                        set_global_var(GVAR_MARK_BROTHER_3, 0);               \
                                        set_global_var(GVAR_MARK_BROTHER_4, 0);               \
                                        set_global_var(GVAR_MARK_BROTHER_5, 0);               \
                                        mark_map_entrance_state(MAP_BROHD12,0);               \
                                        mark_map_entrance_state(MAP_BROHD34,0);               \
                                        inc_bos_rep(REP_BONUS_KICKED_OUT);                    \
                                        load_map(MAP_BROHDENT, 1)

// Check if Brotherhood Combat Armor option is enabled
#define check_bos_ca_enabled                          \
   if (self_fid == FID_HFCMBT or self_fid == FID_HMCMBT or self_fid == FID_HFCMBL or self_fid == FID_HMCMBL) then begin \
      if fo1in2_armor_bos_ca_disabled then begin      \
         if self_is_male then                         \
            art_change_fid_num(self_obj, FID_HMCMBT); \
         else                                         \
            art_change_fid_num(self_obj, FID_HFCMBT); \
      end                                             \
      else begin                                      \
         if self_is_male then                         \
            art_change_fid_num(self_obj, FID_HMCMBL); \
         else                                         \
            art_change_fid_num(self_obj, FID_HFCMBL); \
      end                                             \
   end
