/*

    General Scrapheap header
    Used to track quest states.

*/

#ifndef SCRAPHEAP_H
#define SCRAPHEAP_H

/************************************************
    Generic Defines
************************************************/

#define get_demo_gangwar_inactive   (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 0)
#define get_demo_gangwar_active     (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 1)
#define get_demo_gangwar_completed  (global_var(GVAR_QUEST_DEMO_GANG_WAR) == 2)

#define set_demo_gangwar_inactive   set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 0)
#define set_demo_gangwar_active     set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 1)
#define set_demo_gangwar_completed  set_global_var(GVAR_QUEST_DEMO_GANG_WAR, 2)

#endif // SCRAPHEAP_H




