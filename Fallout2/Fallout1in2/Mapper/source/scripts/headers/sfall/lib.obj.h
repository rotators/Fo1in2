#ifndef LIB_OBJ_H
#define LIB_OBJ_H

#include "define_lite.h"
#include "define_extra.h"

/**
 * Object name or (null) if it's 0. Helps to avoid crashes when debugging.
 * @arg {ObjectPtr} obj
 * @ret {string}
 */
#define obj_name_safe(obj)          (obj_name(obj) if obj else "(null)")

/**
 * Active weapon of a given *critter* (player or NPC).
 * @arg {ObjectPtr} critter
 * @ret {ObjectPtr}
 */
#define get_active_weapon(critter)  critter_inven_obj(critter, (2 - active_hand) if critter == dude_obj else INVEN_TYPE_RIGHT_HAND)

/**
 * Checks if given *critter* has line-of-fire to the given *target*.
 * In FO2, regular "line of sight" checks are usually unreliable, due to how scenery flags are configured. So LoF checks are a good alternative.
 * @arg {ObjectPtr} critter
 * @arg {ObjectPtr} target
 * @ret {bool}
 */
#define obj_has_lof_to_obj(critter, target)           (obj_blocking_line(critter, tile_num(target), BLOCKING_TYPE_SHOOT) == target)

/**
 * Checks if given *critter* has line-of-fire to *target* and also passes a normal perception check (can "hear" it).
 * @arg {ObjectPtr} critter
 * @arg {ObjectPtr} target
 * @ret {bool}
 */
#define obj_can_hear_and_shoot_obj(critter, target)   (obj_can_hear_obj(critter, target) and obj_has_lof_to_obj(critter, target))

#endif
