#pragma once

/*
#define WORLDMAP_TERRAIN_UNKNOWN  (0)
#define WORLDMAP_TERRAIN_CITY     (1)
#define WORLDMAP_TERRAIN_DESERT   (2)
#define WORLDMAP_TERRAIN_MOUNTAIN (3)
#define WORLDMAP_TERRAIN_OCEAN    (4)

#define is_terrain_desert   (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_DESERT)
#define is_terrain_city     (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_CITY)
#define is_terrain_mountain (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_MOUNTAIN)
#define is_terrain_ocean    (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_OCEAN)
*/

#define mstr_unknown       mstr_worldmap(1004)

#define is_terrain_desert           (get_current_terrain_name == mstr_worldmap(1000) or get_current_terrain_name == mstr_worldmap(1006))
#define is_terrain_mountain         (get_current_terrain_name == mstr_worldmap(1001) or get_current_terrain_name == mstr_worldmap(1005))
#define is_terrain_city             (get_current_terrain_name == mstr_worldmap(1002))
#define is_terrain_ocean            (get_current_terrain_name == mstr_worldmap(1003))
