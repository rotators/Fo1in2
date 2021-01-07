
#ifndef LIB_INVEN_H
#define LIB_INVEN_H

#include "define_lite.h"

/**
  Inventory contents as temp array to be used in foreach
*/
procedure inven_as_array(variable critter) begin
   variable i:=0, list;
   list := temp_array(100, 4);
   while (inven_ptr(critter, i)) do begin
      if (i>=len_array(list)) then
         resize_array(list, len_array(list) + 100);
      list[i] := inven_ptr(critter, i);
      i++;
   end
   resize_array(list, i);
   return list;
end


procedure add_items_pid(variable who_obj, variable the_pid, variable pid_qty) begin
   variable item;
   item := create_object(the_pid,0,0);
   add_mult_objs_to_inven(who_obj, item, (pid_qty));
   return item;
end

// aliases:
#define add_item_pid(obj, pid)            add_items_pid(obj, pid, 1)

#ifndef critter_wearing_armor
#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)
#endif

procedure unwield_armor(variable who_obj) begin
   variable armor;
   if (not(who_obj)) then return;
   if (critter_wearing_armor(who_obj)) then begin
      armor := critter_inven_obj(who_obj,INVEN_TYPE_WORN);
      rm_obj_from_inven(who_obj, armor);
      add_obj_to_inven(who_obj, armor);
   end
end

procedure remove_items_pid(variable who_obj, variable the_pid, variable pid_qty) begin
   variable begin
      item;
      removed_qty;
      tmp;
   end
   if (not(who_obj)) then return;
   removed_qty := obj_is_carrying_obj_pid(who_obj,the_pid);
   if (pid_qty < removed_qty and pid_qty != -1) then begin
      removed_qty := pid_qty;
   end
   if (removed_qty > 0) then begin
      item := obj_carrying_pid_obj(who_obj, the_pid);
      if (obj_type(who_obj) == 1) then begin
         if (critter_inven_obj(who_obj,INVEN_TYPE_WORN) == item) then begin
            call unwield_armor(who_obj);
         end else if ((critter_inven_obj(who_obj, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(who_obj, INVEN_TYPE_RIGHT_HAND) == item)) then begin
            inven_unwield(who_obj);
         end
      end
      tmp := rm_mult_objs_from_inven(who_obj, item, removed_qty);
      destroy_object(item);
   end
end

procedure remove_item_obj(variable who_obj, variable item) begin
   if (obj_type(who_obj) == 1) then begin
      if (critter_inven_obj(who_obj,INVEN_TYPE_WORN) == item) then begin
         call unwield_armor(who_obj);
      end else if ((critter_inven_obj(who_obj, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(who_obj, INVEN_TYPE_RIGHT_HAND) == item)) then begin
         inven_unwield(who_obj);
      end
   end
   rm_obj_from_inven(who_obj, item);
   destroy_object(item);
end

// aliases:
#define remove_item_pid(obj, pid)            remove_items_pid(obj, pid, 1)
#define remove_all_items_pid(obj, pid)       remove_items_pid(obj, pid, -1)

/**
 Set item quantity in inventory, by item pid
 */
procedure set_items_qty_pid(variable invenobj, variable itempid, variable newcount)
begin
   variable begin
      count;
      obj;
   end
   count := obj_is_carrying_obj_pid(invenobj, itempid);
   if (newcount > count) then begin
      obj := create_object_sid(itempid, 0, 0, -1);
      add_mult_objs_to_inven(invenobj, obj, newcount - count);
   end else if (newcount < count) then begin
      call remove_items_pid(invenobj, itempid, count - newcount);
   end
end

/*

procedure check_restock_item(the_item, min_amt, max_amt, res_perc)
      restock_amt := random(min_amt, max_amt);
      if (obj_is_carrying_obj_pid(self_obj, the_item) < restock_amt) then begin
         if (res_perc >= random(1,100)) then begin
            stock_pid_qty(self_obj, the_item, restock_amt)
         end
      end else begin
         stock_pid_qty(self_obj, the_item, restock_amt)
      end
procedure check_restock_item_min_limit(the_item, min_amt, max_amt, res_perc)
      if (obj_is_carrying_obj_pid(self_obj, the_item) < min_amt) then begin
         check_restock_item(the_item, min_amt, max_amt, res_perc)
      end
*/


procedure reduce_merchant_loot(variable critter, variable moneyPercent, variable probArmor, variable probDrugs, variable probWeapons, variable probAmmo, variable probMisc) begin
   variable inv, item, it, prob, tmp;
   inv := inven_as_array(critter);
   item_caps_adjust(critter, -(item_caps_total(critter) * moneyPercent / 100));
   //display_msg("total items "+len_array(inv));
   foreach item in inv begin
      if (obj_pid(item) != PID_BOTTLE_CAPS) then begin
         it := obj_item_subtype(item);
         if (it == item_type_armor) then
            prob := probArmor;
         else if (it == item_type_drug) then
            prob := probDrugs;
         else if (it == item_type_weapon) then
            prob := probWeapons;
         else if (it == item_type_ammo) then
            prob := probAmmo;
         else
            prob := probMisc;
         if (random(0, 99) < prob) then begin
            //display_msg("remove "+obj_name(item));
            call remove_all_items_pid(critter, obj_pid(item));
         end
      end
   end
end

procedure item_by_attack_type(variable critter, variable type) begin
   variable slot;
   if (type > 3 and type != ATKTYPE_LWEP_RELOAD and type != ATKTYPE_RWEP_RELOAD) then
      return 0;
   if (type < 2 or type == ATKTYPE_LWEP_RELOAD) then
      slot := INVEN_TYPE_LEFT_HAND;
   else
      slot := INVEN_TYPE_RIGHT_HAND;
   return critter_inven_obj(critter, slot);
end

#endif
