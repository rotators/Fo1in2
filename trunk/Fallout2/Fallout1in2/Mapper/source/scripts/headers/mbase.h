/*

	Military Base generic defines

*/

#ifndef MBASE_H
#define MBASE_H

/************************************************
    Generic Defines
************************************************/

#define bos_invading_cathedral   (global_var( GVAR_BROTHERHOOD_SEND_HELP ) == 1)
#define bos_invading_mbase       (global_var( GVAR_BROTHERHOOD_SEND_HELP ) == 2)

#define get_force_fields_on 	 (global_var( GVAR_MBASE_FORCE_FIELD_STATE ) == 1)
#define get_force_fields_off 	 (global_var( GVAR_MBASE_FORCE_FIELD_STATE ) == 0)

#define set_force_fields_on 	 set_global_var(GVAR_MBASE_FORCE_FIELD_STATE, 1)
#define set_force_fields_off 	 set_global_var(GVAR_MBASE_FORCE_FIELD_STATE, 0)

#endif // MBASE_H
