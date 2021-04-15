/*
  Universal weapon upgrade code
  sfall 2.0a or higher is required
  by phobos2077 & NovaRain
*/

#ifndef UPGWEAP_H
#define UPGWEAP_H

#define PROTO_WP_MAG_SIZE    (96)

// upgrade weapons but don't reload them with fresh ammo
procedure upgrade_weapon(variable oldPid, variable newPid) begin
   variable ammoCnt, ammoPid, ammoMax;

   restock_obj := obj_carrying_pid_obj(dude_obj, oldPid);
   if (restock_obj) then begin
      ammoCnt := get_weapon_ammo_count(restock_obj);
      if ((critter_inven_obj(dude_obj, INVEN_TYPE_LEFT_HAND) == restock_obj) or (critter_inven_obj(dude_obj, INVEN_TYPE_RIGHT_HAND) == restock_obj)) then begin
         inven_unwield(dude_obj);
      end
      if (obj_item_subtype(restock_obj) == item_type_weapon) then begin
         ammoPid := get_weapon_ammo_pid(restock_obj);
         ammoMax := get_proto_data(newPid, PROTO_WP_MAG_SIZE);
         if (ammoCnt > ammoMax) then ammoCnt := ammoMax; // just in case
      end
      restock_amt := rm_mult_objs_from_inven(dude_obj, restock_obj, 1);
      destroy_object(restock_obj);
   end
   restock_amt := 0;

   restock_obj := create_object(newPid, 0, 0);
   if (restock_obj) then begin
      if (ammoPid > 0) then set_weapon_ammo_pid(restock_obj, ammoPid);
      set_weapon_ammo_count(restock_obj, ammoCnt);
      add_mult_objs_to_inven(dude_obj, restock_obj, 1);
   end
end

#endif
