#ifndef CE_H
#define CE_H

// CE-only metarules
#define set_npc_reaction_thresholds(neutral, good)                 sfall_func2("set_npc_reaction_thresholds", neutral, good)
#define set_party_member_cc_msg_ids(pid, start_msg_id, end_msg_id) sfall_func3("set_party_member_cc_msg_ids", pid, start_msg_id, end_msg_id)

#endif
