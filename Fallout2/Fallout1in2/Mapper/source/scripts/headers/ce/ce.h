#ifndef CE_H
#define CE_H

// CE-only metarules
#define set_party_member_cc_msg_ids(pid, start_msg_id, end_msg_id) sfall_func3("set_party_member_cc_msg_ids", pid, start_msg_id, end_msg_id)
#define encounter_intros(toggle) sfall_func1("encounter_intros", toggle)
#define rest_option_msgs(base_msg_id) sfall_func1("rest_option_msgs", base_msg_id)
#define set_rest_option(rest_option, value) sfall_func2("set_rest_option", rest_option, value)

#define REST_OPTION_MORNING 8
#define REST_OPTION_NOON 9
#define REST_OPTION_EVENING 10
#define REST_OPTION_MIDNIGHT 11

#endif
