
#ifndef LIB_INVEN_H
#define LIB_INVEN_H

#include "define_lite.h"
#include "define_extra.h"
#define PID_BOTTLE_CAPS                     (41)

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


procedure add_items_pid(variable invenObj, variable itemPid, variable quantity) begin
   variable item;
   item := create_object(itemPid, 0, 0);
   add_mult_objs_to_inven(invenObj, item, quantity);
   return item;
end

// aliases:
#define add_item_pid(obj, pid)            add_items_pid(obj, pid, 1)

#ifndef critter_wearing_armor
#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)
#endif

procedure unwield_armor(variable critter) begin
   variable armor;
   if (not(critter)) then return;
   if (critter_wearing_armor(critter)) then begin
      armor := critter_inven_obj(critter,INVEN_TYPE_WORN);
      rm_obj_from_inven(critter, armor);
      add_obj_to_inven(critter, armor);
   end
end

procedure remove_items_pid(variable invenObj, variable itemPid, variable quantity) begin
   variable begin
      item;
      toRemoveQty;
      actualQty;
   end
   if (not(invenObj)) then return;
   actualQty := obj_is_carrying_obj_pid(invenObj, itemPid);
   if (quantity > actualQty or quantity < 0) then begin
      quantity := actualQty;
   end
   toRemoveQty := quantity;
   while (quantity > 0) do begin
      item := obj_carrying_pid_obj(invenObj, itemPid);
      if (obj_type(invenObj) == OBJ_TYPE_CRITTER) then begin
         if (critter_inven_obj(invenObj, INVEN_TYPE_WORN) == item) then begin
            call unwield_armor(invenObj);
         end else if ((critter_inven_obj(invenObj, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(invenObj, INVEN_TYPE_RIGHT_HAND) == item)) then begin
            inven_unwield(invenObj);
         end
      end
      quantity -= rm_mult_objs_from_inven(invenObj, item, quantity);
      destroy_object(item);
   end
   return toRemoveQty;
end

procedure remove_item_obj(variable invenObj, variable item) begin
   if (obj_type(invenObj) == 1) then begin
      if (critter_inven_obj(invenObj,INVEN_TYPE_WORN) == item) then begin
         call unwield_armor(invenObj);
      end else if ((critter_inven_obj(invenObj, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(invenObj, INVEN_TYPE_RIGHT_HAND) == item)) then begin
         inven_unwield(invenObj);
      end
   end
   rm_obj_from_inven(invenObj, item);
   destroy_object(item);
end

// aliases:
#define remove_item_pid(obj, pid)            remove_items_pid(obj, pid, 1)
#define remove_all_items_pid(obj, pid)       remove_items_pid(obj, pid, -1)

/**
 Set item quantity in inventory, by item pid
 */
procedure set_items_qty_pid(variable invenobj, variable itempid, variable quantity)
begin
   variable begin
      count;
      obj;
   end
   count := obj_is_carrying_obj_pid(invenobj, itempid);
   if (quantity > count) then begin
      obj := create_object_sid(itempid, 0, 0, -1);
      add_mult_objs_to_inven(invenobj, obj, quantity - count);
   end else if (quantity < count) then begin
      call remove_items_pid(invenobj, itempid, count - quantity);
   end
end


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
