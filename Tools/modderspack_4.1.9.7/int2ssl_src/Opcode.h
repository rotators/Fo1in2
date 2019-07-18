/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

#ifndef OPCODE_H
#define OPCODE_H

// C++ standard includes
#include <vector>
#include <string>

// int2ssl includes
#include "Hacks/CMap.h"

// Third party includes

class COpcode
{
public:
    enum Size {
        OPERATOR_SIZE = 2,
        ARGUMENT_SIZE = 4
    };

    enum O_Base {
        O_STRING    = 0x1000,
        O_FLOAT     = 0x2000,
        O_INT       = 0x4000,
        O_OPERATOR  = 0x8000
    };

    enum O_Core {
        O_NOOP = O_OPERATOR,
        O_CONST,
        O_CRITICAL_START,
        O_CRITICAL_DONE,
        O_JMP,
        O_CALL,
        O_CALL_AT,                  // timed function calls
        O_CALL_CONDITION,
        O_CALLSTART,
        O_EXEC,
        O_SPAWN,
        O_FORK,
        O_A_TO_D,
        O_D_TO_A,
        O_EXIT,                     // exit prog and purge it from process queue
        O_DETACH,                   // detach spawned process from its parent.
        O_EXIT_PROG,                // exit program but leave it in process queue
        O_STOP_PROG,
        O_FETCH_GLOBAL,
        O_STORE_GLOBAL,
        O_FETCH_EXTERNAL,
        O_STORE_EXTERNAL,
        O_EXPORT_VAR,
        O_EXPORT_PROC,
        O_SWAP,
        O_SWAPA,
        O_POP,
        O_DUP,
        O_POP_RETURN,
        O_POP_EXIT,
        O_POP_ADDRESS,
        O_POP_FLAGS,
        O_POP_FLAGS_RETURN,
        O_POP_FLAGS_EXIT,
        O_POP_FLAGS_RETURN_EXTERN,
        O_POP_FLAGS_EXIT_EXTERN,
        O_POP_FLAGS_RETURN_VAL_EXTERN,

        // return from a procedure called from C, leaving the return value
        // on the stack.
        O_POP_FLAGS_RETURN_VAL_EXIT,
        O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN,

        O_CHECK_ARG_COUNT,          // call to do a run-time check of arguments to functions
        O_LOOKUP_STRING_PROC,       // call to lookup a procedure index given a string
        O_POP_BASE,
        O_POP_TO_BASE,
        O_PUSH_BASE,
        O_SET_GLOBAL,
        O_FETCH_PROC_ADDRESS,
        O_DUMP,
        O_IF,
        O_WHILE,
        O_STORE,
        O_FETCH,
        O_EQUAL,
        O_NOT_EQUAL,
        O_LESS_EQUAL,
        O_GREATER_EQUAL,
        O_LESS,
        O_GREATER,
        O_ADD,
        O_SUB,
        O_MUL,
        O_DIV,
        O_MOD,
        O_AND,
        O_OR,
        O_BWAND,
        O_BWOR,
        O_BWXOR,
        O_BWNOT,
        O_FLOOR,
        O_NOT,
        O_NEGATE,
        O_WAIT,
        O_CANCEL,
        O_CANCELALL,

        O_STARTCRITICAL,
        O_ENDCRITICAL,

        O_END_CORE                  // don't use this anywhere, or you'll die
    };

    enum O_Lib {
        O_SAYQUIT = O_END_CORE,
        O_SAYEND,
        O_SAYSTART,
        O_SAYSTARTPOS,
        O_SAYREPLYTITLE,
        O_SAYGOTOREPLY,
        O_SAYREPLY,
        O_SAYOPTION,
        O_SAYMESSAGE,
        O_SAYREPLYWINDOW,           // sayreplywindow(sx, sy, w, h, "fill3x3 pattern");
        O_SAYOPTIONWINDOW,          // sayoptionwindow ''
        O_SAYBORDER,                // sayoptionborder(x, y)
        O_SAYSCROLLUP,
        O_SAYSCROLLDOWN,
        O_SAYSETSPACING,
        O_SAYOPTIONCOLOR,
        O_SAYREPLYCOLOR,
        O_SAYRESTART,
        O_SAYGETLASTPOS,
        O_SAYREPLYFLAGS,
        O_SAYOPTIONFLAGS,
        O_SAYMESSAGETIMEOUT,        // removes sayMsg in x time, unless x = 0

        O_CREATEWIN,
        O_DELETEWIN,
        O_SELECTWIN,
        O_RESIZEWIN,
        O_SCALEWIN,
        O_SHOWWIN,
        O_FILLWIN,
        O_FILLRECT,
        O_FILLWIN3X3,
        O_DISPLAY,
        O_DISPLAYGFX,
        O_DISPLAYRAW,
        O_LOADPALETTETABLE,
        O_FADEIN,
        O_FADEOUT,
        O_GOTOXY,
        O_PRINT,
        O_FORMAT,
        O_PRINTRECT,
        O_SETFONT,
        O_SETTEXTFLAGS,
        O_SETTEXTCOLOR,
        O_SETHIGHLIGHTCOLOR,
        O_STOPMOVIE,
        O_PLAYMOVIE,
        O_MOVIEFLAGS,
        O_PLAYMOVIERECT,
        O_PLAYMOVIEALPHA,
        O_PLAYMOVIEALPHARECT,
        O_ADDREGION,
        O_ADDREGIONFLAG,
        O_ADDREGIONPROC,
        O_ADDREGIONRIGHTPROC,
        O_DELETEREGION,
        O_ACTIVATEREGION,
        O_CHECKREGION,              // returns if a region exists or not

        O_ADDBUTTON,
        O_ADDBUTTONTEXT,
        O_ADDBUTTONFLAG,
        O_ADDBUTTONGFX,
        O_ADDBUTTONPROC,
        O_ADDBUTTONRIGHTPROC,
        O_DELETEBUTTON,

        O_HIDEMOUSE,
        O_SHOWMOUSE,
        O_MOUSESHAPE,
        O_REFRESHMOUSE,
        O_SETGLOBALMOUSEFUNC,

        O_ADDNAMEDEVENT,
        O_ADDNAMEDHANDLER,
        O_CLEARNAMED,
        O_SIGNALNAMED,

        O_ADDKEY,
        O_DELETEKEY,

        O_SOUNDPLAY,
        O_SOUNDPAUSE,
        O_SOUNDRESUME,
        O_SOUNDSTOP,
        O_SOUNDREWIND,
        O_SOUNDDELETE,
        O_SETONEOPTPAUSE,

        O_SELECTFILELIST,

        O_TOKENIZE,
        O_END_LIB                   // don't use this anywhere or your head will explode
    };

    enum O_Extra {
        // define any user-specific opcodes here, starting at O_END_LIB
        // ending with O_END_OP
        O_GIVE_EXP_POINTS = O_END_LIB,
        O_SCR_RETURN,
        O_PLAY_SFX,
        O_OBJ_NAME,
        O_SFX_BUILD_OPEN_NAME,
        O_GET_PC_STAT,
        O_TILE_CONTAINS_PID_OBJ,
        O_SET_MAP_START,
        O_OVERRIDE_MAP_START,
        O_HAS_SKILL,
        O_USING_SKILL,
        O_ROLL_VS_SKILL,
        O_SKILL_CONTEST,
        O_DO_CHECK,
        O_IS_SUCCESS,
        O_IS_CRITICAL,
        O_HOW_MUCH,
        O_MARK_AREA_KNOWN,
        O_REACTION_INFLUENCE,
        O_RANDOM,
        O_ROLL_DICE,
        O_MOVE_TO,
        O_CREATE_OBJECT_SID,
        O_DISPLAY_MSG,
        O_SCRIPT_OVERRIDES,
        O_OBJ_IS_CARRYING_OBJ_PID,
        O_TILE_CONTAINS_OBJ_PID,
        O_SELF_OBJ,
        O_SOURCE_OBJ,
        O_TARGET_OBJ,
        O_DUDE_OBJ,
        O_OBJ_BEING_USED_WITH,
        O_LOCAL_VAR,
        O_SET_LOCAL_VAR,
        O_MAP_VAR,
        O_SET_MAP_VAR,
        O_GLOBAL_VAR,
        O_SET_GLOBAL_VAR,
        O_SCRIPT_ACTION,
        O_OBJ_TYPE,
        O_OBJ_ITEM_SUBTYPE,
        O_GET_CRITTER_STAT,
        O_SET_CRITTER_STAT,
        O_ANIMATE_STAND_OBJ,
        O_ANIMATE_STAND_REVERSE_OBJ,
        O_ANIMATE_MOVE_OBJ_TO_TILE,
        O_TILE_IN_TILE_RECT,
        O_ATTACK_COMPLEX,
        O_MAKE_DAYTIME,
        O_TILE_DISTANCE,
        O_TILE_DISTANCE_OBJS,
        O_TILE_NUM,
        O_TILE_NUM_IN_DIRECTION,
        O_PICKUP_OBJ,
        O_DROP_OBJ,
        O_ADD_OBJ_TO_INVEN,
        O_RM_OBJ_FROM_INVEN,
        O_WIELD_OBJ_CRITTER,
        O_USE_OBJ,
        O_OBJ_CAN_SEE_OBJ,
        O_ATTACK,
        O_START_GDIALOG,
        O_END_DIALOGUE,
        O_DIALOGUE_REACTION,
        O_METARULE3,
        O_SET_MAP_MUSIC,
        O_SET_OBJ_VISIBILITY,
        O_LOAD_MAP,
        O_WM_AREA_SET_POS,
        O_SET_EXIT_GRIDS,
        O_ANIM_BUSY,
        O_CRITTER_HEAL,
        O_SET_LIGHT_LEVEL,
        O_GAME_TIME,
        O_GAME_TIME_IN_SECONDS,
        O_ELEVATION,
        O_KILL_CRITTER,
        O_KILL_CRITTER_TYPE,
        O_CRITTER_DMG,
        O_ADD_TIMER_EVENT,
        O_RM_TIMER_EVENT,
        O_GAME_TICKS,
        O_HAS_TRAIT,
        O_DESTROY_OBJECT,
        O_OBJ_CAN_HEAR_OBJ,
        O_GAME_TIME_HOUR,
        O_FIXED_PARAM,
        O_TILE_IS_VISIBLE,
        O_DIALOGUE_SYSTEM_ENTER,
        O_ACTION_BEING_USED,
        O_CRITTER_STATE,
        O_GAME_TIME_ADVANCE,
        O_RADIATION_INC,
        O_RADIATION_DEC,
        O_CRITTER_ATTEMPT_PLACEMENT,
        O_OBJ_PID,
        O_CUR_MAP_INDEX,
        O_CRITTER_ADD_TRAIT,
        O_CRITTER_RM_TRAIT,
        O_PROTO_DATA,
        O_MESSAGE_STR,
        O_CRITTER_INVEN_OBJ,
        O_OBJ_SET_LIGHT_LEVEL,
        O_WORLD_MAP,
        O_INVEN_CMDS,
        O_FLOAT_MSG,
        O_METARULE,
        O_ANIM,
        O_OBJ_CARRYING_PID_OBJ,
        O_REG_ANIM_FUNC,
        O_REG_ANIM_ANIMATE,
        O_REG_ANIM_ANIMATE_REVERSE,
        O_REG_ANIM_OBJ_MOVE_TO_OBJ,
        O_REG_ANIM_OBJ_RUN_TO_OBJ,
        O_REG_ANIM_OBJ_MOVE_TO_TILE,
        O_REG_ANIM_OBJ_RUN_TO_TILE,
        O_PLAY_GMOVIE,
        O_ADD_MULT_OBJS_TO_INVEN,
        O_RM_MULT_OBJS_FROM_INVEN,
        O_GET_MONTH,
        O_GET_DAY,
        O_EXPLOSION,
        O_DAYS_SINCE_VISITED,
        O_GSAY_START,
        O_GSAY_END,
        O_GSAY_REPLY,
        O_GSAY_OPTION,
        O_GSAY_MESSAGE,
        O_GIQ_OPTION,
        O_POISON,
        O_GET_POISON,
        O_PARTY_ADD,
        O_PARTY_REMOVE,
        O_REG_ANIM_ANIMATE_FOREVER,
        O_CRITTER_INJURE,
        O_COMBAT_IS_INITIALIZED,
        O_GDIALOG_MOD_BARTER,
        O_DIFFICULTY_LEVEL,
        O_RUNNING_BURNING_GUY,
        O_INVEN_UNWIELD,
        O_OBJ_IS_LOCKED,
        O_OBJ_LOCK,
        O_OBJ_UNLOCK,
        O_OBJ_IS_OPEN,
        O_OBJ_OPEN,
        O_OBJ_CLOSE,
        O_GAME_UI_DISABLE,
        O_GAME_UI_ENABLE,
        O_GAME_UI_IS_DISABLED,
        O_GFADE_OUT,
        O_GFADE_IN,
        O_ITEM_CAPS_TOTAL,
        O_ITEM_CAPS_ADJUST,
        O_ANIM_ACTION_FRAME,
        O_REG_ANIM_PLAY_SFX,
        O_CRITTER_MOD_SKILL,
        O_SFX_BUILD_CHAR_NAME,
        O_SFX_BUILD_AMBIENT_NAME,
        O_SFX_BUILD_INTERFACE_NAME,
        O_SFX_BUILD_ITEM_NAME,
        O_SFX_BUILD_WEAPON_NAME,
        O_SFX_BUILD_SCENERY_NAME,
        O_ATTACK_SETUP,
        O_DESTROY_MULT_OBJS,
        O_USE_OBJ_ON_OBJ,
        O_ENDGAME_SLIDESHOW,
        O_MOVE_OBJ_INVEN_TO_OBJ,
        O_ENDGAME_MOVIE,
        O_OBJ_ART_FID,
        O_ART_ANIM,
        O_PARTY_MEMBER_OBJ,
        O_ROTATION_TO_TILE,
        O_JAM_LOCK,
        O_GDIALOG_SET_BARTER_MOD,
        O_COMBAT_DIFFICULTY,
        O_OBJ_ON_SCREEN,
        O_CRITTER_IS_FLEEING,
        O_CRITTER_SET_FLEE_STATE,
        O_TERMINATE_COMBAT,
        O_DEBUG_MSG,
        O_CRITTER_STOP_ATTACKING,

//sfall start
        O_READ_BYTE,
        O_READ_SHORT,
        O_READ_INT,
        O_READ_STRING,
        O_SET_PC_BASE_STAT,
        O_SET_PC_EXTRA_STAT,
        O_GET_PC_BASE_STAT,
        O_GET_PC_EXTRA_STAT,
        O_SET_CRITTER_BASE_STAT,
        O_SET_CRITTER_EXTRA_STAT,
        O_GET_CRITTER_BASE_STAT,
        O_GET_CRITTER_EXTRA_STAT,
        O_TAP_KEY,
        O_GET_YEAR,
        O_GAME_LOADED,
        O_GRAPHICS_FUNCS_AVAILABLE,
        O_LOAD_SHADER,
        O_FREE_SHADER,
        O_ACTIVATE_SHADER,
        O_DEACTIVATE_SHADER,
        O_SET_GLOBAL_SCRIPT_REPEAT,
        O_INPUT_FUNCS_AVAILABLE,
        O_KEY_PRESSED,

        O_SET_SHADER_INT,
        O_SET_SHADER_FLOAT,
        O_SET_SHADER_VECTOR,
        O_IN_WORLD_MAP,
        O_FORCE_ENCOUNTER,
        O_SET_WORLD_MAP_POS,
        O_GET_WORLD_MAP_X_POS,
        O_GET_WORLD_MAP_Y_POS,

        O_SET_DM_MODEL,
        O_SET_DF_MODEL,
        O_SET_MOVIE_PATH,

        O_SET_PERK_IMAGE,
        O_SET_PERK_RANKS,
        O_SET_PERK_LEVEL,
        O_SET_PERK_STAT,
        O_SET_PERK_STAT_MAG,
        O_SET_PERK_SKILL1,
        O_SET_PERK_SKILl1_MAG,
        O_SET_PERK_TYPE,
        O_SET_PERK_SKILL2,
        O_SET_PERK_SKILL2_MAG,
        O_SET_PERK_STR,
        O_SET_PERK_PER,
        O_SET_PERK_END,
        O_SET_PERK_CHR,
        O_SET_PERK_INT,
        O_SET_PERK_AGL,
        O_SET_PERK_LCK,
        O_SET_PERK_NAME,
        O_SET_PERK_DESC,

        O_SET_PIPBOY_AVAILABLE,

        O_GET_KILL_COUNTER,
        O_MOD_KILL_COUNTER,

        O_GET_PERK_OWED,
        O_SET_PERK_OWED,
        O_GET_PERK_AVAILABLE,

        O_GET_CRITTER_AP,
        O_SET_CRITTER_AP,

        O_GET_ACTIVE_HAND,
        O_TOGGLE_ACTIVE_HAND,

        O_SET_WEAPON_KNOCKBACK,
        O_SET_TARGET_KNOCKBACK,
        O_SET_ATTACKER_KNOCKBACK,
        O_REMOVE_WEAPON_KNOCKBACK,
        O_REMOVE_TARGET_KNOCKBACK,
        O_REMOVE_ATTACKER_KNOCKBACK,

        O_SET_GLOBAL_SCRIPT_TYPE,
        O_AVAILABLE_GLOBAL_SCRIPT_TYPES,

        O_SET_SFALL_GLOBAL,
        O_GET_SFALL_GLOBAL_INT,
        O_GET_SFALL_GLOBAL_FLOAT,

        O_SET_PICKPOCKET_MAX,
        O_SET_HIT_CHANCE_MAX,
        O_SET_SKILL_MAX,

        O_EAX_AVAILABLE,
        O_SET_EAX_ENVIRONMENT,

        O_INC_NPC_LEVEL,

        O_GET_VIEWPORT_X,
        O_GET_VIEWPORT_Y,
        O_SET_VIEWPORT_X,
        O_SET_VIEWPORT_Y,

        O_SET_XP_MOD,
        O_SET_PERK_LEVEL_MOD,

        O_GET_INI_SETTING,

        O_GET_SHADER_VERSION,
        O_SET_SHADER_MODE,

        O_GET_GAME_MODE,

        O_FORCE_GRAPHICS_REFRESH,
        O_GET_SHADER_TEXTURE,
        O_SET_SHADER_TEXTURE,

        O_GET_UPTIME,

        O_SET_STAT_MAX,
        O_SET_STAT_MIN,

        O_SET_CAR_CURRENT_TOWN,

        O_SET_PC_STAT_MAX,
        O_SET_PC_STAT_MIN,
        O_SET_NPC_STAT_MAX,
        O_SET_NPC_STAT_MIN,

        O_SET_FAKE_PERK,
        O_SET_FAKE_TRAIT,
        O_SET_SELECTABLE_PERK,
        O_SET_PERKBOX_TITLE,
        O_HIDE_REAL_PERKS,
        O_SHOW_REAL_PERKS,
        O_HAS_FAKE_PERK,
        O_HAS_FAKE_TRAIT,
        O_PERK_ADD_MODE,
        O_CLEAR_SELECTABLE_PERKS,

        O_SET_CRITTER_HIT_CHANCE_MOD,
        O_SET_BASE_HIT_CHANCE_MOD,
        O_SET_CRITTER_SKILL_MOD,
        O_SET_BASE_SKILL_MOD,
        O_SET_CRITTER_PICKPOCKET_MOD,
        O_SET_BASE_PICKPOCKET_MOD,

        O_SET_PYROMANIAC_MOD,
        O_APPLY_HEAVEHO_FIX,
        O_SET_SWIFTLEARNER_MOD,
        O_SET_HP_LEVEL_MOD,

        O_WRITE_BYTE,
        O_WRITE_SHORT,
        O_WRITE_INT,

        O_CALL_OFFSET_V0,
        O_CALL_OFFSET_V1,
        O_CALL_OFFSET_V2,
        O_CALL_OFFSET_V3,
        O_CALL_OFFSET_V4,
        O_CALL_OFFSET_R0,
        O_CALL_OFFSET_R1,
        O_CALL_OFFSET_R2,
        O_CALL_OFFSET_R3,
        O_CALL_OFFSET_R4,

        O_SHOW_IFACE_TAG,
        O_HIDE_IFACE_TAG,
        O_IS_IFACE_TAG_ACTIVE,
        O_GET_BODYPART_HIT_MODIFIER,
        O_SET_BODYPART_HIT_MODIFIER,

        O_SET_CRITICAL_TABLE,
        O_GET_CRITICAL_TABLE,
        O_RESET_CRITICAL_TABLE,
        O_GET_SFALL_ARG,
        O_SET_SFALL_RETURN,
        O_SET_UNSPENT_AP_BONUS,
        O_GET_UNSPENT_AP_BONUS,
        O_SET_UNSPENT_AP_PERK_BONUS,
        O_GET_UNSPENT_AP_PERK_BONUS,
        O_INIT_HOOK,
        O_GET_INI_STRING,

        O_SQRT,
        O_ABS,
        O_SIN,
        O_COS,
        O_TAN,
        O_ARCTAN,
        O_SET_PALETTE,

        O_REMOVE_SCRIPT,
        O_SET_SCRIPT,
        O_GET_SCRIPT,
        O_NB_CREATE_CHAR,
        O_FS_CREATE,
        O_FS_COPY,
        O_FS_FIND,
        O_FS_WRITE_BYTE,
        O_FS_WRITE_SHORT,
        O_FS_WRITE_INT,
        O_FS_WRITE_FLOAT,
        O_FS_WRITE_STRING,
        O_FS_DELETE,
        O_FS_SIZE,
        O_FS_POS,
        O_FS_SEEK,
        O_FS_RESIZE,
        O_GET_PROTO_DATA,

        O_SET_PROTO_DATA,
        O_SET_SELF,
        O_REGISTER_HOOK,
        O_FS_WRITE_BSTRING,
        O_FS_READ_BYTE,
        O_FS_READ_SHORT,
        O_FS_READ_INT,
        O_FS_READ_FLOAT,
        O_LIST_BEGIN,
        O_LIST_NEXT,
        O_LIST_END,

        O_SFALL_VER_MAJOR,
        O_SFALL_VER_MINOR,
        O_SFALL_VER_BUILD,

        O_HERO_SELECT_WIN,
        O_SET_HERO_RACE,
        O_SET_HERO_STYLE,

        O_SET_CRITTER_BURST_DISABLE,

        O_GET_WEAPON_AMMO_PID,
        O_SET_WEAPON_AMMO_PID,
        O_GET_WEAPON_AMMO_COUNT,
        O_SET_WEAPON_AMMO_COUNT,
        O_WRITE_STRING,
        O_GET_MOUSE_X,
        O_GET_MOUSE_Y,
        O_GET_MOUSE_BUTTONS,
        O_GET_WINDOW_UNDER_MOUSE,
        O_GET_SCREEN_WIDTH,
        O_GET_SCREEN_HEIGHT,
        O_STOP_GAME,
        O_RESUME_GAME,
        O_CREATE_MESSAGE_WINDOW,
        O_REMOVE_TRAIT,
        O_GET_LIGHT_LEVEL,
        O_REFRESH_PC_ART,
        O_GET_ATTACK_TYPE,
        O_FORCE_ENCOUNTER_WITH_FLAGS,
        O_SET_MAP_TIME_MULTI,
        O_PLAY_SFALL_SOUND,
        O_STOP_SFALL_SOUND,
        O_CREATE_ARRAY,
        O_SET_ARRAY,
        O_GET_ARRAY,
        O_FREE_ARRAY,

        O_TS_LEN_ARRAY,
        O_TS_RESIZE_ARRAY,
        O_TS_TEMP_ARRAY,
        O_TS_FIX_ARRAY,

        O_TS_STRING_SPLIT,

        O_TS_LIST_AS_ARRAY,

        O_TS_ATOI,
        O_TS_ATOF,

        O_TS_SCAN_ARRAY,

        O_TS_TILE_PID,

        O_TS_MODIFIED_INI,

        O_TS_GET_SFALL_ARGS,

        O_TS_SET_SFALL_ARG,

        O_TS_FORCE_AIMED_SHOTS,
        O_TS_DISABLE_AIMED_SHOTS,

        O_TS_MARK_MOVIE_PLAYED,

        O_TS_GET_NPC_LEVEL,

       O_TS_SET_CRITTER_SKILL_POINTS,
       O_TS_GET_CRITTER_SKILL_POINTS,
       O_TS_SET_AVAILABLE_SKILL_POINTS,
       O_TS_GET_AVAILABLE_SKILL_POINTS,
        O_TS_MOD_SKILL_POINTS_PER_LEVEL,
        O_TS_SET_PERK_FREQ,

        O_TS_GET_LAST_ATTACKER,
        O_TS_GET_LAST_TARGET,
        O_TS_BLOCK_COMBAT,

        O_TS_TILE_UNDER_CURSOR,
        O_TS_GET_BARTER_MOD,
        O_TS_SET_INVEN_AP_COST,

        O_TS_SUBSTR,
        O_TS_STRLEN,
        O_TS_SPRINTF,
        O_TS_ORD,
        O_TS_RESERVD2,
        O_TS_TYPEOF,

        O_TS_SAVE_ARRAY,
        O_TS_LOAD_ARRAY,
        O_TS_GET_ARRAY_KEY,
        O_TS_STACK_ARRAY,

        O_TS_RESERVD3,
        O_TS_RESERVD4,

        O_TS_REG_ANIM_DESTROY,
        O_TS_REG_ANIM_ANIMATE_AND_HIDE,
        O_TS_REG_ANIM_COMBAT_CHECK,
        O_TS_REG_ANIM_LIGHT,
        O_TS_REG_ANIM_CHANGE_FID,
        O_TS_REG_ANIM_TAKE_OUT,
        O_TS_REG_ANIM_TURN_TOWARDS,

        O_TS_EXPLOSIONS_METARULE,
        O_TS_REGISTER_HOOK_PROC,
        
        O_TS_POW,
        O_TS_LOG,
        O_TS_EXP,
        O_TS_CEIL,
        O_TS_ROUND,

        O_TS_RESERVD5,
        O_TS_RESERVD6,
        O_TS_RESERVD7,

        O_TS_MESSAGE_STR_GAME,
        O_TS_SNEAK_SUCCESS,
        O_TS_TILE_LIGHT,

        O_TS_MAKE_STRAIGHT_PATH,
        O_TS_OBJ_BLOCKING_AT,
        O_TS_TILE_GET_OBJECTS,
        O_TS_GET_PARTY_MEMBERS,
        O_TS_PATH_FIND,
        O_TS_CREATE_SPATIAL,
        O_TS_ART_EXISTS,
        O_TS_OBJ_IS_CARRYING_OBJ,

		O_TS_SFALL_METARULE0,
		O_TS_SFALL_METARULE1,
		O_TS_SFALL_METARULE2,
		O_TS_SFALL_METARULE3,
		O_TS_SFALL_METARULE4,
		O_TS_SFALL_METARULE5,
		O_TS_SFALL_METARULE6,

//sfall end
        O_END_OP
    };

    enum O_DataType {
        O_STRINGOP  = (O_CONST | O_STRING),     // 0x9001
        O_FLOATOP   = (O_CONST | O_FLOAT),      // 0xA001
        O_INTOP     = (O_CONST | O_INT)         // 0xC001
    };

    enum O_F1_Specific {
        O_REACTION              = 0x80B2,
        O_ANIMATE_JUMP          = 0x80CF,
        O_TURN_OFF_OBJS_IN_AREA = 0x80E1,
        O_TURN_ON_OBJS_IN_AREA  = 0x80E2,
        O_BARTER_OFFER          = 0x80E5,
        O_BARTER_ASKING         = 0x80E6,
        O_TOWN_MAP              = 0x8109
    };

    // COpcodeAttributes
    class COpcodeAttributes
    {
    public:
        enum Type {
            TYPE_STATEMENT,
            TYPE_EXPRESSION
        };

        enum Category {
            CATEGORY_PREFIX,
            CATEGORY_INFIX
        };

    public:
        COpcodeAttributes(std::string mnemonic = "",
                          std::string name = "",
                          uint32_t ulNumArgs = 0,
                          Type type = TYPE_STATEMENT,
                          Category category = CATEGORY_PREFIX,
                          uint32_t* procArgs = NULL,
                          uint32_t numProcArgs = 0);
        COpcodeAttributes(const COpcodeAttributes& attributes);
        COpcodeAttributes& operator = (const COpcodeAttributes& attributes);
        void InitAttributes();

    public:
        std::string m_strMnemonic;
        std::string m_strName;
        uint32_t m_ulNumArgs;
        Type m_Type;
        Category m_Category;
        uint32_t *m_procArgs;
        uint32_t m_numProcArgs;
    };

    // CF2OpcodeAttributesMap
    class CF2OpcodeAttributesMap : public CMap<uint16_t, uint16_t, COpcodeAttributes, const COpcodeAttributes&>
    {
    public:
        CF2OpcodeAttributesMap();
    };

    // C12OpcodeAttributesMap
    class CF1OpcodeAttributesMap : public CMap<uint16_t, uint16_t, COpcodeAttributes, const COpcodeAttributes&>
    {
    public:
        CF1OpcodeAttributesMap();
    };

public:
    COpcode();
    COpcode(const COpcode& opcode);
    virtual ~COpcode();

public:
    COpcode& operator = (const COpcode& opcode);

public:
    virtual void Serialize();
    void Expect(uint16_t wOperator, bool bArgumentFound = false, uint32_t ulArgument = 0);
    void Expect(int nCount, uint16_t pwOperators[]);

    bool HasArgument() const;
    int GetSize() const;

    uint16_t GetOperator() const;
    void SetOperator(uint16_t op);
    uint32_t GetArgument() const;

    const COpcodeAttributes GetAttributes() const;

private:
    uint16_t  m_wOperator;
    uint32_t m_ulArgument;
};

typedef std::vector<COpcode> COpcodeArray;

#endif // OPCODE_H
