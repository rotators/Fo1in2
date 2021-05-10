/*

   Military Base generic defines

*/

#ifndef MBASE_H
#define MBASE_H

/************************************************
    Generic Defines
************************************************/
#define mbase_full_alert         (global_var(GVAR_VATS_ALERT) == 1)

#define bos_invading_cathedral   (global_var(GVAR_BROTHERHOOD_SEND_HELP) == 1)
#define bos_invading_mbase       (global_var(GVAR_BROTHERHOOD_SEND_HELP) == 2)

#define get_force_fields_on      (global_var(GVAR_MBASE_FORCE_FIELD_STATE) == 1)
#define get_force_fields_off     (global_var(GVAR_MBASE_FORCE_FIELD_STATE) == 0)

#define set_force_fields_on      set_global_var(GVAR_MBASE_FORCE_FIELD_STATE, 1)
#define set_force_fields_off     set_global_var(GVAR_MBASE_FORCE_FIELD_STATE, 0)

// Destroyed emitter:
variable ff_emitter;
#define set_emitter_destroyed    set_map_var(FField_MVAR, DISABLED);                                                   \
                                 if (FField_Ptr != 0) then begin                                                       \
                                    destroy_object(FField_Ptr);                                                        \
                                    FField_Ptr := 0;                                                                   \
                                 end                                                                                   \
                                 if (self_pid == PID_EMITTER_MBASE_NS) then begin                                      \
                                    ff_emitter := create_object(PID_EMITTER_DESTROYED_NS, self_tile, self_elevation);  \
                                    destroy_object(self_obj);                                                          \
                                 end                                                                                   \
                                 else if (self_pid == PID_EMITTER_MBASE_EW) then begin                                 \
                                    ff_emitter := create_object(PID_EMITTER_DESTROYED_EW, self_tile, self_elevation);  \
                                    destroy_object(self_obj);                                                          \
                                 end

#endif // MBASE_H
