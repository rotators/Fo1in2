
#ifndef LIB_INVEN_H
#define LIB_INVEN_H

#include "define_lite.h"
#include "define_extra.h"

#define PID_BOTTLE_CAPS                     (41)

/**
 * Inventory contents as temp array to be used in foreach
 * @arg {ObjectPtr} critter
 * @ret {list}
 */
procedure inven_as_array(variable critter) begin
   variable i := 0, list, item;
   list := temp_array(0, 4);
   item := inven_ptr(critter, i);
   while (item) do begin
      resize_array(list, i + 1);
      list[i] := item;
      i++;
      item := inven_ptr(critter, i);
   end
   return list;
end

/**
 * Adds quantity of itemPid to invenObj and returns the created item object.
 * @arg {ObjectPtr} invenObj - Object to add new item to.
 * @arg {int} itemPid - PID of item.
 * @arg {int} quantity
 * @ret {ObjectPtr} - created item
 */
procedure add_items_pid(variable invenObj, variable itemPid, variable quantity) begin
   variable item;
   item := create_object(itemPid, 0, 0);
   add_mult_objs_to_inven(invenObj, item, quantity);
   return item;
end

/**
 * Adds 1 item of a given pid to obj.
 * @arg {ObjectPtr} obj - Object to add new item to.
 * @arg {int} pid
 * @ret {ObjectPtr}
 */
#define add_item_pid(obj, pid)            add_items_pid(obj, pid, 1)

#ifndef critter_wearing_armor
#define critter_wearing_armor(x)            (obj_item_subtype(critter_inven_obj(x,INVEN_TYPE_WORN)) == item_type_armor)
#endif

/**
 * Makes critter remove his armor and put it back to his inventory.
 * @arg {ObjectPtr} critter
 */
procedure unwield_armor(variable critter) begin
   variable armor;
   if (not(critter)) then return;
   if (critter_wearing_armor(critter)) then begin
      armor := critter_inven_obj(critter,INVEN_TYPE_WORN);
      rm_obj_from_inven(critter, armor);
      add_obj_to_inven(critter, armor);
   end
end

/**
 * Makes critter put away given item if it's in armor or any item/weapon slot.
 * @arg {ObjectPtr} critter
 * @arg {ObjectPtr} item
 */
procedure inven_unwield_item(variable critter, variable item) begin
   if (obj_type(critter) != OBJ_TYPE_CRITTER) then return;

   if (critter_inven_obj(critter, INVEN_TYPE_WORN) == item) then begin
      call unwield_armor(critter);
   end else if ((critter_inven_obj(critter, INVEN_TYPE_LEFT_HAND) == item) or (critter_inven_obj(critter, INVEN_TYPE_RIGHT_HAND) == item)) then begin
      inven_unwield(critter);
   end
end

/**
 * Removes items of given pid from given object's inventory. Returns number of actually removed items.
 * @arg {ObjectPtr} invenObj - obj to remove items from
 * @arg {int} itemPid - PID of item to remove
 * @arg {int} quantity - maximum quantity of items to remove (-1 to remove all available items)
 * @ret {int}
 */
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
      call inven_unwield_item(invenObj, item);
      quantity -= rm_mult_objs_from_inven(invenObj, item, quantity);
      destroy_object(item);
   end
   return toRemoveQty;
end

/**
 * Remove one item from a given *item* stack object from *invenObj* inventory.
 * For a critter, this will correctly remove item from armor/hand slot, if it is equipped.
 * Note that *item* pointer will be invalid after this.
 * @arg {ObjectPtr} invenObj - obj to remove from
 * @arg {ObjectPtr} item - item (stack) object to remove
 */
procedure remove_item_obj(variable invenObj, variable item) begin
   call inven_unwield_item(invenObj, item);
   rm_obj_from_inven(invenObj, item);
   destroy_object(item);
end

/**
 * Remove one item of a given *pid* from *obj* inventory.
 * @arg {ObjectPtr} obj - obj to remove items from
 * @arg {int} pid - PID of item to remove
 * @ret {int}
 */
#define remove_item_pid(obj, pid)            remove_items_pid(obj, pid, 1)

/**
 * Remove all items of a given *pid* from *obj* inventory. Returns number of removed items.
 * @arg {ObjectPtr} obj - obj to remove items from
 * @arg {int} pid - PID of item to remove
 * @ret {int}
 */
#define remove_all_items_pid(obj, pid)       remove_items_pid(obj, pid, -1)

/**
 * Ensures a given *quantity* of *itemPid* in *invenObj* inventory, adding or removing items as necessary.
 * @arg {ObjectPtr} invenObj - obj to add/remove items to/from
 * @arg {int} itemPid - PID of item to add/remove
 * @arg {int} quantity
 */
procedure set_items_qty_pid(variable invenObj, variable itemPid, variable quantity)
begin
   variable begin
      count;
      obj;
   end
   count := obj_is_carrying_obj_pid(invenObj, itemPid);
   if (quantity > count) then begin
      obj := create_object_sid(itemPid, 0, 0, -1);
      add_mult_objs_to_inven(invenObj, obj, quantity - count);
   end else if (quantity < count) then begin
      call remove_items_pid(invenObj, itemPid, count - quantity);
   end
end


/**
 * Returns item in one of *critter*'s hand slots using given attack type.
 * @arg {ObjectPtr} critter
 * @arg {int} type - Attack Type, see ATKTYPE_* in define_extra.h
 * @ret {ObjectPtr}
 */
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
