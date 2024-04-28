#pragma once

#define WORLDMAP_TERRAIN_UNKNOWN  (0)
#define WORLDMAP_TERRAIN_CITY     (1)
#define WORLDMAP_TERRAIN_DESERT   (2)
#define WORLDMAP_TERRAIN_MOUNTAIN (3)
#define WORLDMAP_TERRAIN_OCEAN    (4)

#define is_terrain_desert   (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_DESERT)
#define is_terrain_city     (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_CITY)
#define is_terrain_mountain (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_MOUNTAIN)
#define is_terrain_ocean    (global_var(GVAR_WORLDMAP_TERRAIN) == WORLDMAP_TERRAIN_OCEAN)
