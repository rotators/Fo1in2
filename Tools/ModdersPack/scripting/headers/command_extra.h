#ifndef COMMAND_EXTRA_H
#define COMMAND_EXTRA_H

#include "define_lite.h"
#include "define_extra.h"


#define ammo_caliber(ammoPid)       get_proto_data(ammoPid, PROTO_AM_CALIBER)
#define obj_name_safe(obj)          (obj_name(obj) if obj else "(null)")
#define get_active_weapon(critter)  critter_inven_obj(critter, (2 - active_hand) if critter == dude_obj else INVEN_TYPE_RIGHT_HAND)

#endif
