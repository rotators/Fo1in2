#pragma once

/***************************************************************************************
   If item is given to an NPC, check party inventory and remove it
****************************************************************************************/
procedure party_has_item(variable pid) begin
   variable who, count;
   foreach (who in party_member_list_critters) begin
      count += get_item_count(who, pid);
   end
   return count;
end

procedure party_remove_item_pid(variable pid) begin
   variable who;
   foreach (who in party_member_list_critters) begin
      if (get_item_count(who, pid) > 0) then begin
         remove_pid_qty(who, pid, 1);
         break;
      end
   end
end

#define party_remove_item(x) \
   call party_remove_item_pid(x)
