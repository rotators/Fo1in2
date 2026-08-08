#pragma once

#define mstr_unknown       mstr_worldmap(1004)

#define is_terrain_desert           (get_current_terrain_name == mstr_worldmap(1000) or get_current_terrain_name == mstr_worldmap(1006))
#define is_terrain_mountain         (get_current_terrain_name == mstr_worldmap(1001) or get_current_terrain_name == mstr_worldmap(1005))
#define is_terrain_city             (get_current_terrain_name == mstr_worldmap(1002))
#define is_terrain_ocean            (get_current_terrain_name == mstr_worldmap(1003))
