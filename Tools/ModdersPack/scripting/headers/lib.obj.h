#ifndef LIB_OBJ_H
#define LIB_OBJ_H

#include "define_lite.h"
#include "define_extra.h"

#define obj_name_safe(obj)          (obj_name(obj) if obj else "(null)")
#define get_active_weapon(critter)  critter_inven_obj(critter, (2 - active_hand) if critter == dude_obj else INVEN_TYPE_RIGHT_HAND)
#define obj_can_hear_and_shoot_obj(critter, target)  (obj_can_hear_obj(critter, target) and obj_blocking_line(critter, tile_num(target), BLOCKING_TYPE_SHOOT) == target)

#endif
