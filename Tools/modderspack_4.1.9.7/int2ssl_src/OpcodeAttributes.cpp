/**
 *
 * Copyright (c) 2005-2009 Anchorite (TeamX), <anchorite2001@yandex.ru>
 * Copyright (c) 2014-2015 Nirran, phobos2077
 * Copyright (c) 2015 alexeevdv <mail@alexeevdv.ru>
 * Distributed under the GNU GPL v3. For full terms see the file license.txt
 *
 */

// C++ standard includes

// int2ssl includes
#include "Opcode.h"

// Third party includes

COpcode::COpcodeAttributes::COpcodeAttributes(std::string mnemonic,
                                              std::string name,
                                              uint32_t ulNumArgs,
                                              Type type,
                                              Category category,
                                              uint32_t *procArgs,
                                              uint32_t numProcArgs) :
    m_strMnemonic(mnemonic),
    m_strName(name),
    m_ulNumArgs(ulNumArgs),
    m_Type(type),
    m_Category(category),
    m_procArgs(procArgs),
    m_numProcArgs(numProcArgs)
{
}

COpcode::COpcodeAttributes::COpcodeAttributes(const COpcodeAttributes& attributes) :
    m_strMnemonic(attributes.m_strMnemonic),
    m_strName(attributes.m_strName),
    m_ulNumArgs(attributes.m_ulNumArgs),
    m_Type(attributes.m_Type),
    m_Category(attributes.m_Category),
    m_procArgs(attributes.m_procArgs),
    m_numProcArgs(attributes.m_numProcArgs)
{
}

COpcode::COpcodeAttributes& COpcode::COpcodeAttributes::operator = (const COpcodeAttributes& attributes)
{
    if (&attributes != this)
    {
        m_strMnemonic = attributes.m_strMnemonic;
        m_strName = attributes.m_strName;
        m_ulNumArgs = attributes.m_ulNumArgs;
        m_Type = attributes.m_Type;
        m_Category = attributes.m_Category;
        m_procArgs = attributes.m_procArgs;
        m_numProcArgs = attributes.m_numProcArgs;
    }

    return (*this);
}

COpcode::CF1OpcodeAttributesMap::CF1OpcodeAttributesMap()
{
    COpcode::COpcodeAttributes::Type expression = COpcode::COpcodeAttributes::TYPE_EXPRESSION;
    //COpcode::COpcodeAttributes::Category infix = COpcode::COpcodeAttributes::CATEGORY_INFIX;

    InitHashTable(32);
    
    SetAt(O_REACTION, COpcodeAttributes("O_REACTION", "reaction", 3, expression));
    SetAt(O_ANIMATE_JUMP, COpcodeAttributes("O_ANIMATE_JUMP", "animate_jump", 0));
    SetAt(O_TURN_OFF_OBJS_IN_AREA, COpcodeAttributes("O_TURN_OFF_OBJS_IN_AREA", "turn_off_objs_in_area", 4));
    SetAt(O_TURN_ON_OBJS_IN_AREA, COpcodeAttributes("O_TURN_ON_OBJS_IN_AREA", "turn_on_objs_in_area", 4));
    SetAt(O_BARTER_OFFER, COpcodeAttributes("O_BARTER_OFFER", "barter_offer", 3));
    SetAt(O_BARTER_ASKING, COpcodeAttributes("O_BARTER_ASKING", "barter_asking", 3));
    SetAt(O_TOWN_MAP, COpcodeAttributes("O_TOWN_MAP", "town_map", 0));
}

uint32_t procArgs_register_hook_proc[1] = {2};

COpcode::CF2OpcodeAttributesMap::CF2OpcodeAttributesMap()
{
    COpcode::COpcodeAttributes::Type expression = COpcode::COpcodeAttributes::TYPE_EXPRESSION;
    COpcode::COpcodeAttributes::Category infix = COpcode::COpcodeAttributes::CATEGORY_INFIX;

    InitHashTable(512);

    SetAt(O_NOOP, COpcodeAttributes("O_NOOP", "/* O_NOOP */", 0));
    SetAt(O_CONST, COpcodeAttributes("O_CONST", "/* O_CONST */", 0));
    SetAt(O_CRITICAL_START, COpcodeAttributes("O_CRITICAL_START", "/* O_CRITICAL_START */", 0));
    SetAt(O_CRITICAL_DONE, COpcodeAttributes("O_CRITICAL_DONE", "/* O_CRITICAL_START */", 0));
    SetAt(O_JMP, COpcodeAttributes("O_JMP", "// O_JMP ", 1));
    SetAt(O_CALL, COpcodeAttributes("O_CALL", "/* O_CALL */", 0, expression));
    SetAt(O_CALL_AT, COpcodeAttributes("O_CALL_AT", "/* O_CALL_AT */", 2));
    SetAt(O_CALL_CONDITION, COpcodeAttributes("O_CALL_CONDITION", "/* O_CALL_CONDITION */", 2));
    SetAt(O_CALLSTART, COpcodeAttributes("O_CALLSTART", "callStart", 1));
    SetAt(O_EXEC, COpcodeAttributes("O_EXEC", "exec", 1));
    SetAt(O_SPAWN, COpcodeAttributes("O_SPAWN", "spawn", 1));
    SetAt(O_FORK, COpcodeAttributes("O_FORK", "fork", 1));
    SetAt(O_A_TO_D, COpcodeAttributes("O_A_TO_D", "/* O_A_TO_D */", 0));
    SetAt(O_D_TO_A, COpcodeAttributes("O_D_TO_A", "/* O_D_TO_A */", 0));
    SetAt(O_EXIT, COpcodeAttributes("O_EXIT", "exit", 0));
    SetAt(O_DETACH, COpcodeAttributes("O_DETACH", "detach", 0));
    SetAt(O_EXIT_PROG, COpcodeAttributes("O_EXIT_PROG", "/* O_EXIT_PROG */", 0));
    SetAt(O_STOP_PROG, COpcodeAttributes("O_STOP_PROG", "/* O_STOP_PROG */", 0));
    SetAt(O_FETCH_GLOBAL, COpcodeAttributes("O_FETCH_GLOBAL", "/* O_FETCH_GLOBAL */", 1, expression));
    SetAt(O_STORE_GLOBAL, COpcodeAttributes("O_STORE_GLOBAL", ":=", 2));
    SetAt(O_FETCH_EXTERNAL, COpcodeAttributes("O_FETCH_EXTERNAL", "/* O_FETCH_EXTERNAL */", 1, expression));
    SetAt(O_STORE_EXTERNAL, COpcodeAttributes("O_STORE_EXTERNAL", ":=", 2));
    SetAt(O_EXPORT_VAR, COpcodeAttributes("O_EXPORT_VAR", "/* O_EXPORT_VAR */", 0));
    SetAt(O_EXPORT_PROC, COpcodeAttributes("O_EXPORT_PROC", "/* O_EXPORT_PROC */", 0));
    SetAt(O_SWAP, COpcodeAttributes("O_SWAP", "/* O_SWAP */", 0));
    SetAt(O_SWAPA, COpcodeAttributes("O_SWAPA", "/* O_SWAPA */", 0));
    SetAt(O_POP, COpcodeAttributes("O_POP", "/* O_POP */", 1));
    SetAt(O_DUP, COpcodeAttributes("O_DUP", "/* O_DUP */", 0));
    SetAt(O_POP_RETURN, COpcodeAttributes("O_POP_RETURN", "return", 1));
    SetAt(O_POP_EXIT, COpcodeAttributes("O_POP_EXIT", "/* O_POP_EXIT */", 0));
    SetAt(O_POP_ADDRESS, COpcodeAttributes("O_POP_ADDRESS", "/* O_POP_ADDRESS */", 0));
    SetAt(O_POP_FLAGS, COpcodeAttributes("O_POP_FLAGS", "/* O_POP_FLAGS */", 0));
    SetAt(O_POP_FLAGS_RETURN, COpcodeAttributes("O_POP_FLAGS_RETURN", "/* O_POP_FLAGS_RETURN */", 0));
    SetAt(O_POP_FLAGS_EXIT, COpcodeAttributes("O_POP_FLAGS_EXIT", "/* O_POP_FLAGS_EXIT */", 0));
    SetAt(O_POP_FLAGS_RETURN_EXTERN, COpcodeAttributes("O_POP_FLAGS_RETURN_EXTERN", "/* O_POP_FLAGS_RETURN_EXTERN */", 0));
    SetAt(O_POP_FLAGS_EXIT_EXTERN, COpcodeAttributes("O_POP_FLAGS_EXIT_EXTERN", "/* O_POP_FLAGS_EXIT_EXTERN */", 0));
    SetAt(O_POP_FLAGS_RETURN_VAL_EXTERN, COpcodeAttributes("O_POP_FLAGS_RETURN_VAL_EXTERN", "/* O_POP_FLAGS_RETURN_VAL_EXTERN */", 0));
    SetAt(O_POP_FLAGS_RETURN_VAL_EXIT, COpcodeAttributes("O_POP_FLAGS_RETURN_VAL_EXIT", "/* O_POP_FLAGS_RETURN_VAL_EXIT */", 0));
    SetAt(O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN, COpcodeAttributes("O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN", "/* O_POP_FLAGS_RETURN_VAL_EXIT_EXTERN */", 0));
    SetAt(O_CHECK_ARG_COUNT, COpcodeAttributes("O_CHECK_ARG_COUNT", "/* O_CHECK_ARG_COUNT */", 0));
    SetAt(O_LOOKUP_STRING_PROC, COpcodeAttributes("O_LOOKUP_STRING_PROC", "/* O_LOOKUP_STRING_PROC */", 1, expression));
    SetAt(O_POP_BASE, COpcodeAttributes("O_POP_BASE", "/* O_POP_BASE */", 0));
    SetAt(O_POP_TO_BASE, COpcodeAttributes("O_POP_TO_BASE", "/* O_POP_TO_BASE */", 0));
    SetAt(O_PUSH_BASE, COpcodeAttributes("O_PUSH_BASE", "/* O_PUSH_BASE */", 0));
    SetAt(O_SET_GLOBAL, COpcodeAttributes("O_SET_GLOBAL", "/* O_SET_GLOBAL */", 0));
    SetAt(O_FETCH_PROC_ADDRESS, COpcodeAttributes("O_FETCH_PROC_ADDRESS", "/* O_FETCH_PROC_ADDRESS */", 0));
    SetAt(O_DUMP, COpcodeAttributes("O_DUMP", "/* O_DUMP */", 0));
    SetAt(O_IF, COpcodeAttributes("O_IF", "if", 2));
    SetAt(O_WHILE, COpcodeAttributes("O_WHILE", "while", 2));
    SetAt(O_STORE, COpcodeAttributes("O_STORE", ":=", 2));
    SetAt(O_FETCH, COpcodeAttributes("O_FETCH", "/* O_FETCH */", 1, expression));
    SetAt(O_EQUAL, COpcodeAttributes("O_EQUAL", "==", 2, expression, infix));
    SetAt(O_NOT_EQUAL, COpcodeAttributes("O_NOT_EQUAL", "!=", 2, expression, infix));
    SetAt(O_LESS_EQUAL, COpcodeAttributes("O_LESS_EQUAL", "<=", 2, expression, infix));
    SetAt(O_GREATER_EQUAL, COpcodeAttributes("O_GREATER_EQUAL", ">=", 2, expression, infix));
    SetAt(O_LESS, COpcodeAttributes("O_LESS", "<", 2, expression, infix));
    SetAt(O_GREATER, COpcodeAttributes("O_GREATER", ">", 2, expression, infix));
    SetAt(O_ADD, COpcodeAttributes("O_ADD", "+", 2, expression, infix));
    SetAt(O_SUB, COpcodeAttributes("O_SUB", "-", 2, expression, infix));
    SetAt(O_MUL, COpcodeAttributes("O_MUL", "*", 2, expression, infix));
    SetAt(O_DIV, COpcodeAttributes("O_DIV", "/", 2, expression, infix));
    SetAt(O_MOD, COpcodeAttributes("O_MOD", "%", 2, expression, infix));
    SetAt(O_AND, COpcodeAttributes("O_AND", "and", 2, expression, infix));
    SetAt(O_OR, COpcodeAttributes("O_OR", "or", 2, expression, infix));
    SetAt(O_BWAND, COpcodeAttributes("O_BWAND", "bwand", 2, expression, infix));
    SetAt(O_BWOR, COpcodeAttributes("O_BWOR", "bwor", 2, expression, infix));
    SetAt(O_BWXOR, COpcodeAttributes("O_BWXOR", "bwxor", 2, expression, infix));
    SetAt(O_BWNOT, COpcodeAttributes("O_BWNOT", "bwnot", 1, expression));
    SetAt(O_FLOOR, COpcodeAttributes("O_FLOOR", "floor", 1, expression));
    SetAt(O_NOT, COpcodeAttributes("O_NOT", "not", 1, expression));
    SetAt(O_NEGATE, COpcodeAttributes("O_NEGATE", "-", 1, expression));
    SetAt(O_WAIT, COpcodeAttributes("O_WAIT", "wait", 1));
    SetAt(O_CANCEL, COpcodeAttributes("O_CANCEL", "cancel", 1));
    SetAt(O_CANCELALL, COpcodeAttributes("O_CANCELALL", "cancelAll", 0));
    SetAt(O_STARTCRITICAL, COpcodeAttributes("O_STARTCRITICAL", "startCritical", 0));
    SetAt(O_ENDCRITICAL, COpcodeAttributes("O_ENDCRITICAL", "endCritical", 0));
    SetAt(O_SAYQUIT, COpcodeAttributes("O_SAYQUIT", "sayQuit", 0));
    SetAt(O_SAYEND, COpcodeAttributes("O_SAYEND", "sayEnd", 0));
    SetAt(O_SAYSTART, COpcodeAttributes("O_SAYSTART", "sayStart", 0));
    SetAt(O_SAYSTARTPOS, COpcodeAttributes("O_SAYSTARTPOS", "sayStartPos", 1));
    SetAt(O_SAYREPLYTITLE, COpcodeAttributes("O_SAYREPLYTITLE", "sayReplyTitle", 1));
    SetAt(O_SAYGOTOREPLY, COpcodeAttributes("O_SAYGOTOREPLY", "sayGotoReply", 1));
    SetAt(O_SAYREPLY, COpcodeAttributes("O_SAYREPLY", "sayReply", 2));
    SetAt(O_SAYOPTION, COpcodeAttributes("O_SAYOPTION", "sayOption", 2));
    SetAt(O_SAYMESSAGE, COpcodeAttributes("O_SAYMESSAGE", "sayMessage", 2));
    SetAt(O_SAYREPLYWINDOW, COpcodeAttributes("O_SAYREPLYWINDOW", "sayReplyWindow", 5));
    SetAt(O_SAYOPTIONWINDOW, COpcodeAttributes("O_SAYOPTIONWINDOW", "sayOptionWindow", 5));
    SetAt(O_SAYBORDER, COpcodeAttributes("O_SAYBORDER", "sayBorder", 2));
    SetAt(O_SAYSCROLLUP, COpcodeAttributes("O_SAYSCROLLUP", "sayScrollUp", 6));
    SetAt(O_SAYSCROLLDOWN, COpcodeAttributes("O_SAYSCROLLDOWN", "sayScrollDown", 6));
    SetAt(O_SAYSETSPACING, COpcodeAttributes("O_SAYSETSPACING", "saySetSpacing", 1));
    SetAt(O_SAYOPTIONCOLOR, COpcodeAttributes("O_SAYOPTIONCOLOR", "sayOptionColor", 3));
    SetAt(O_SAYREPLYCOLOR, COpcodeAttributes("O_SAYREPLYCOLOR", "sayReplyColor", 3));
    SetAt(O_SAYRESTART, COpcodeAttributes("O_SAYRESTART", "sayRestart", 0));
    SetAt(O_SAYGETLASTPOS, COpcodeAttributes("O_SAYGETLASTPOS", "sayGetLastPos", 0, expression));
    SetAt(O_SAYREPLYFLAGS, COpcodeAttributes("O_SAYREPLYFLAGS", "sayReplyFlags", 1));
    SetAt(O_SAYOPTIONFLAGS, COpcodeAttributes("O_SAYOPTIONFLAGS", "sayOptionFlags", 1));
    SetAt(O_SAYMESSAGETIMEOUT, COpcodeAttributes("O_SAYMESSAGETIMEOUT", "sayMessageTimeout", 1));
    SetAt(O_CREATEWIN, COpcodeAttributes("O_CREATEWIN", "createWin", 5));
    SetAt(O_DELETEWIN, COpcodeAttributes("O_DELETEWIN", "deleteWin", 1));
    SetAt(O_SELECTWIN, COpcodeAttributes("O_SELECTWIN", "selectWin", 1));
    SetAt(O_RESIZEWIN, COpcodeAttributes("O_RESIZEWIN", "resizeWin", 5));
    SetAt(O_SCALEWIN, COpcodeAttributes("O_SCALEWIN", "scaleWin", 5));
    SetAt(O_SHOWWIN, COpcodeAttributes("O_SHOWWIN", "showWin", 0));
    SetAt(O_FILLWIN, COpcodeAttributes("O_FILLWIN", "fillWin", 3));
    SetAt(O_FILLRECT, COpcodeAttributes("O_FILLRECT", "fillRect", 7));
    SetAt(O_FILLWIN3X3, COpcodeAttributes("O_FILLWIN3X3", "fillWin3x3", 1));
    SetAt(O_DISPLAY, COpcodeAttributes("O_DISPLAY", "display", 1));
    SetAt(O_DISPLAYGFX, COpcodeAttributes("O_DISPLAYGFX", "displayGfx", 5));
    SetAt(O_DISPLAYRAW, COpcodeAttributes("O_DISPLAYRAW", "displayRaw", 1));
    SetAt(O_LOADPALETTETABLE, COpcodeAttributes("O_LOADPALETTETABLE", "loadPaletteTable", 1));
    SetAt(O_FADEIN, COpcodeAttributes("O_FADEIN", "fadeIn", 1));
    SetAt(O_FADEOUT, COpcodeAttributes("O_FADEOUT", "fadeOut", 1));
    SetAt(O_GOTOXY, COpcodeAttributes("O_GOTOXY", "gotoXY", 2));
    SetAt(O_PRINT, COpcodeAttributes("O_PRINT", "print", 1));
    SetAt(O_FORMAT, COpcodeAttributes("O_FORMAT", "format", 6));
    SetAt(O_PRINTRECT, COpcodeAttributes("O_PRINTRECT", "printRect", 3));
    SetAt(O_SETFONT, COpcodeAttributes("O_SETFONT", "setFont", 1));
    SetAt(O_SETTEXTFLAGS, COpcodeAttributes("O_SETTEXTFLAGS", "setTextFlags", 1));
    SetAt(O_SETTEXTCOLOR, COpcodeAttributes("O_SETTEXTCOLOR", "setTextColor", 3));
    SetAt(O_SETHIGHLIGHTCOLOR, COpcodeAttributes("O_SETHIGHLIGHTCOLOR", "setHighlightColor", 3));
    SetAt(O_STOPMOVIE, COpcodeAttributes("O_STOPMOVIE", "stopMovie", 0));
    SetAt(O_PLAYMOVIE, COpcodeAttributes("O_PLAYMOVIE", "playMovie", 1));
    SetAt(O_MOVIEFLAGS, COpcodeAttributes("O_MOVIEFLAGS", "movieFlags", 1));
    SetAt(O_PLAYMOVIERECT, COpcodeAttributes("O_PLAYMOVIERECT", "playMovieRect", 5));
    SetAt(O_PLAYMOVIEALPHA, COpcodeAttributes("O_PLAYMOVIEALPHA", "playmoviealpha", 2));
    SetAt(O_PLAYMOVIEALPHARECT, COpcodeAttributes("O_PLAYMOVIEALPHARECT", "playMovieAlphaRect", 6));
    SetAt(O_ADDREGION, COpcodeAttributes("O_ADDREGION", "addRegion", 5, expression));
    SetAt(O_ADDREGIONFLAG, COpcodeAttributes("O_ADDREGIONFLAG", "addRegionFlag", 2));
    SetAt(O_ADDREGIONPROC, COpcodeAttributes("O_ADDREGIONPROC", "addRegionProc", 5));
    SetAt(O_ADDREGIONRIGHTPROC, COpcodeAttributes("O_ADDREGIONRIGHTPROC", "addRegionRightProc", 3));
    SetAt(O_DELETEREGION, COpcodeAttributes("O_DELETEREGION", "deleteRegion", 1));
    SetAt(O_ACTIVATEREGION, COpcodeAttributes("O_ACTIVATEREGION", "activateRegion", 2));
    SetAt(O_CHECKREGION, COpcodeAttributes("O_CHECKREGION", "checkRegion", 1, expression));
    SetAt(O_ADDBUTTON, COpcodeAttributes("O_ADDBUTTON", "addButton", 5));
    SetAt(O_ADDBUTTONTEXT, COpcodeAttributes("O_ADDBUTTONTEXT", "addButtonText", 2));
    SetAt(O_ADDBUTTONFLAG, COpcodeAttributes("O_ADDBUTTONFLAG", "addButtonFlag", 2));
    SetAt(O_ADDBUTTONGFX, COpcodeAttributes("O_ADDBUTTONGFX", "addButtonGfx", 4));
    SetAt(O_ADDBUTTONPROC, COpcodeAttributes("O_ADDBUTTONPROC", "addButtonProc", 5));
    SetAt(O_ADDBUTTONRIGHTPROC, COpcodeAttributes("O_ADDBUTTONRIGHTPROC", "addButtonRightProc", 3));
    SetAt(O_DELETEBUTTON, COpcodeAttributes("O_DELETEBUTTON", "deleteButton", 1));
    SetAt(O_HIDEMOUSE, COpcodeAttributes("O_HIDEMOUSE", "hideMouse", 0));
    SetAt(O_SHOWMOUSE, COpcodeAttributes("O_SHOWMOUSE", "showMouse", 0));
    SetAt(O_MOUSESHAPE, COpcodeAttributes("O_MOUSESHAPE", "mouseShape", 3));
    SetAt(O_REFRESHMOUSE, COpcodeAttributes("O_REFRESHMOUSE", "refreshMouse", 1));
    SetAt(O_SETGLOBALMOUSEFUNC, COpcodeAttributes("O_SETGLOBALMOUSEFUNC", "setGlobalMouseFunc", 4));
    SetAt(O_ADDNAMEDEVENT, COpcodeAttributes("O_ADDNAMEDEVENT", "addNamedEvent", 2));
    SetAt(O_ADDNAMEDHANDLER, COpcodeAttributes("O_ADDNAMEDHANDLER", "addNamedHandler", 2));
    SetAt(O_CLEARNAMED, COpcodeAttributes("O_CLEARNAMED", "clearNamed", 1));
    SetAt(O_SIGNALNAMED, COpcodeAttributes("O_SIGNALNAMED", "signalNamed", 1));
    SetAt(O_ADDKEY, COpcodeAttributes("O_ADDKEY", "addKey", 2));
    SetAt(O_DELETEKEY, COpcodeAttributes("O_DELETEKEY", "deleteKey", 1));
    SetAt(O_SOUNDPLAY, COpcodeAttributes("O_SOUNDPLAY", "soundPlay", 2, expression));
    SetAt(O_SOUNDPAUSE, COpcodeAttributes("O_SOUNDPAUSE", "soundPause", 1));
    SetAt(O_SOUNDRESUME, COpcodeAttributes("O_SOUNDRESUME", "soundResume", 1));
    SetAt(O_SOUNDSTOP, COpcodeAttributes("O_SOUNDSTOP", "soundStop", 1));
    SetAt(O_SOUNDREWIND, COpcodeAttributes("O_SOUNDREWIND", "soundRewind", 1));
    SetAt(O_SOUNDDELETE, COpcodeAttributes("O_SOUNDDELETE", "soundDelete", 1));
    SetAt(O_SETONEOPTPAUSE, COpcodeAttributes("O_SETONEOPTPAUSE", "setOneOptPause", 1));
    SetAt(O_SELECTFILELIST, COpcodeAttributes("O_SELECTFILELIST", "selectFileList", 2, expression));
    SetAt(O_TOKENIZE, COpcodeAttributes("O_TOKENIZE", "tokenize", 3, expression));
    SetAt(O_GIVE_EXP_POINTS, COpcodeAttributes("O_GIVE_EXP_POINTS", "give_exp_points", 1));
    SetAt(O_SCR_RETURN, COpcodeAttributes("O_SCR_RETURN", "scr_return", 1));
    SetAt(O_PLAY_SFX, COpcodeAttributes("O_PLAY_SFX", "play_sfx", 1));
    SetAt(O_OBJ_NAME, COpcodeAttributes("O_OBJ_NAME", "obj_name", 1, expression));
    SetAt(O_SFX_BUILD_OPEN_NAME, COpcodeAttributes("O_SFX_BUILD_OPEN_NAME", "sfx_build_open_name", 2, expression));
    SetAt(O_GET_PC_STAT, COpcodeAttributes("O_GET_PC_STAT", "get_pc_stat", 1, expression));
    SetAt(O_TILE_CONTAINS_PID_OBJ, COpcodeAttributes("O_TILE_CONTAINS_PID_OBJ", "tile_contains_pid_obj", 3, expression));
    SetAt(O_SET_MAP_START, COpcodeAttributes("O_SET_MAP_START", "set_map_start", 4));
    SetAt(O_OVERRIDE_MAP_START, COpcodeAttributes("O_OVERRIDE_MAP_START", "override_map_start", 4));
    SetAt(O_HAS_SKILL, COpcodeAttributes("O_HAS_SKILL", "has_skill", 2, expression));
    SetAt(O_USING_SKILL, COpcodeAttributes("O_USING_SKILL", "using_skill", 2, expression));
    SetAt(O_ROLL_VS_SKILL, COpcodeAttributes("O_ROLL_VS_SKILL", "roll_vs_skill", 3, expression));
    SetAt(O_SKILL_CONTEST, COpcodeAttributes("O_SKILL_CONTEST", "skill_contest", 3, expression));
    SetAt(O_DO_CHECK, COpcodeAttributes("O_DO_CHECK", "do_check", 3, expression));
    SetAt(O_IS_SUCCESS, COpcodeAttributes("O_IS_SUCCESS", "is_success", 1, expression));
    SetAt(O_IS_CRITICAL, COpcodeAttributes("O_IS_CRITICAL", "is_critical", 1, expression));
    SetAt(O_HOW_MUCH, COpcodeAttributes("O_HOW_MUCH", "how_much", 1, expression));
    SetAt(O_MARK_AREA_KNOWN, COpcodeAttributes("O_MARK_AREA_KNOWN", "mark_area_known", 3));
    SetAt(O_REACTION_INFLUENCE, COpcodeAttributes("O_REACTION_INFLUENCE", "reaction_influence", 3, expression));
    SetAt(O_RANDOM, COpcodeAttributes("O_RANDOM", "random", 2, expression));
    SetAt(O_ROLL_DICE, COpcodeAttributes("O_ROLL_DICE", "roll_dice", 2, expression));
    SetAt(O_MOVE_TO, COpcodeAttributes("O_MOVE_TO", "move_to", 3, expression));
    SetAt(O_CREATE_OBJECT_SID, COpcodeAttributes("O_CREATE_OBJECT_SID", "create_object_sid", 4, expression));
    SetAt(O_DISPLAY_MSG, COpcodeAttributes("O_DISPLAY_MSG", "display_msg", 1));
    SetAt(O_SCRIPT_OVERRIDES, COpcodeAttributes("O_SCRIPT_OVERRIDES", "script_overrides", 0));
    SetAt(O_OBJ_IS_CARRYING_OBJ_PID, COpcodeAttributes("O_OBJ_IS_CARRYING_OBJ_PID", "obj_is_carrying_obj_pid", 2, expression));
    SetAt(O_TILE_CONTAINS_OBJ_PID, COpcodeAttributes("O_TILE_CONTAINS_OBJ_PID", "tile_contains_obj_pid", 3, expression));
    SetAt(O_SELF_OBJ, COpcodeAttributes("O_SELF_OBJ", "self_obj", 0, expression));
    SetAt(O_SOURCE_OBJ, COpcodeAttributes("O_SOURCE_OBJ", "source_obj", 0, expression));
    SetAt(O_TARGET_OBJ, COpcodeAttributes("O_TARGET_OBJ", "target_obj", 0, expression));
    SetAt(O_DUDE_OBJ, COpcodeAttributes("O_DUDE_OBJ", "dude_obj", 0, expression));
    SetAt(O_OBJ_BEING_USED_WITH, COpcodeAttributes("O_OBJ_BEING_USED_WITH", "obj_being_used_with", 0, expression));
    SetAt(O_LOCAL_VAR, COpcodeAttributes("O_LOCAL_VAR", "local_var", 1, expression));
    SetAt(O_SET_LOCAL_VAR, COpcodeAttributes("O_SET_LOCAL_VAR", "set_local_var", 2));
    SetAt(O_MAP_VAR, COpcodeAttributes("O_MAP_VAR", "map_var", 1, expression));
    SetAt(O_SET_MAP_VAR, COpcodeAttributes("O_SET_MAP_VAR", "set_map_var", 2));
    SetAt(O_GLOBAL_VAR, COpcodeAttributes("O_GLOBAL_VAR", "global_var", 1, expression));
    SetAt(O_SET_GLOBAL_VAR, COpcodeAttributes("O_SET_GLOBAL_VAR", "set_global_var", 2));
    SetAt(O_SCRIPT_ACTION, COpcodeAttributes("O_SCRIPT_ACTION", "script_action", 0, expression));
    SetAt(O_OBJ_TYPE, COpcodeAttributes("O_OBJ_TYPE", "obj_type", 1, expression));
    SetAt(O_OBJ_ITEM_SUBTYPE, COpcodeAttributes("O_OBJ_ITEM_SUBTYPE", "obj_item_subtype", 1, expression));
    SetAt(O_GET_CRITTER_STAT, COpcodeAttributes("O_GET_CRITTER_STAT", "get_critter_stat", 2, expression));
    SetAt(O_SET_CRITTER_STAT, COpcodeAttributes("O_SET_CRITTER_STAT", "set_critter_stat", 3, expression));
    SetAt(O_ANIMATE_STAND_OBJ, COpcodeAttributes("O_ANIMATE_STAND_OBJ", "animate_stand_obj", 1));
    SetAt(O_ANIMATE_STAND_REVERSE_OBJ, COpcodeAttributes("O_ANIMATE_STAND_REVERSE_OBJ", "animate_stand_reverse_obj", 1));
    SetAt(O_ANIMATE_MOVE_OBJ_TO_TILE, COpcodeAttributes("O_ANIMATE_MOVE_OBJ_TO_TILE", "animate_move_obj_to_tile", 3));
    SetAt(O_TILE_IN_TILE_RECT, COpcodeAttributes("O_TILE_IN_TILE_RECT", "tile_in_tile_rect", 5, expression));
    SetAt(O_ATTACK_COMPLEX, COpcodeAttributes("O_ATTACK_COMPLEX", "attack_complex", 8));
    SetAt(O_MAKE_DAYTIME, COpcodeAttributes("O_MAKE_DAYTIME", "make_daytime", 0));
    SetAt(O_TILE_DISTANCE, COpcodeAttributes("O_TILE_DISTANCE", "tile_distance", 2, expression));
    SetAt(O_TILE_DISTANCE_OBJS, COpcodeAttributes("O_TILE_DISTANCE_OBJS", "tile_distance_objs", 2, expression));
    SetAt(O_TILE_NUM, COpcodeAttributes("O_TILE_NUM", "tile_num", 1, expression));
    SetAt(O_TILE_NUM_IN_DIRECTION, COpcodeAttributes("O_TILE_NUM_IN_DIRECTION", "tile_num_in_direction", 3, expression));
    SetAt(O_PICKUP_OBJ, COpcodeAttributes("O_PICKUP_OBJ", "pickup_obj", 1));
    SetAt(O_DROP_OBJ, COpcodeAttributes("O_DROP_OBJ", "drop_obj", 1));
    SetAt(O_ADD_OBJ_TO_INVEN, COpcodeAttributes("O_ADD_OBJ_TO_INVEN", "add_obj_to_inven", 2));
    SetAt(O_RM_OBJ_FROM_INVEN, COpcodeAttributes("O_RM_OBJ_FROM_INVEN", "rm_obj_from_inven", 2));
    SetAt(O_WIELD_OBJ_CRITTER, COpcodeAttributes("O_WIELD_OBJ_CRITTER", "wield_obj_critter", 2));
    SetAt(O_USE_OBJ, COpcodeAttributes("O_USE_OBJ", "use_obj", 1));
    SetAt(O_OBJ_CAN_SEE_OBJ, COpcodeAttributes("O_OBJ_CAN_SEE_OBJ", "obj_can_see_obj", 2, expression));
    SetAt(O_ATTACK, COpcodeAttributes("O_ATTACK", "attack", 8));
    SetAt(O_START_GDIALOG, COpcodeAttributes("O_START_GDIALOG", "start_gdialog", 5));
    SetAt(O_END_DIALOGUE, COpcodeAttributes("O_END_DIALOGUE", "end_dialogue", 0));
    SetAt(O_DIALOGUE_REACTION, COpcodeAttributes("O_DIALOGUE_REACTION", "dialogue_reaction", 1));
    SetAt(O_METARULE3, COpcodeAttributes("O_METARULE3", "metarule3", 4, expression));
    SetAt(O_SET_MAP_MUSIC, COpcodeAttributes("O_SET_MAP_MUSIC", "set_map_music", 2));
    SetAt(O_SET_OBJ_VISIBILITY, COpcodeAttributes("O_SET_OBJ_VISIBILITY", "set_obj_visibility", 2));
    SetAt(O_LOAD_MAP, COpcodeAttributes("O_LOAD_MAP", "load_map", 2));
    SetAt(O_WM_AREA_SET_POS, COpcodeAttributes("O_WM_AREA_SET_POS", "wm_area_set_pos", 3));
    SetAt(O_SET_EXIT_GRIDS, COpcodeAttributes("O_SET_EXIT_GRIDS", "set_exit_grids", 5));
    SetAt(O_ANIM_BUSY, COpcodeAttributes("O_ANIM_BUSY", "anim_busy", 1, expression));
    SetAt(O_CRITTER_HEAL, COpcodeAttributes("O_CRITTER_HEAL", "critter_heal", 2, expression));
    SetAt(O_SET_LIGHT_LEVEL, COpcodeAttributes("O_SET_LIGHT_LEVEL", "set_light_level", 1));
    SetAt(O_GAME_TIME, COpcodeAttributes("O_GAME_TIME", "game_time", 0, expression));
    SetAt(O_GAME_TIME_IN_SECONDS, COpcodeAttributes("O_GAME_TIME_IN_SECONDS", "game_time_in_seconds", 0, expression));
    SetAt(O_ELEVATION, COpcodeAttributes("O_ELEVATION", "elevation", 1, expression));
    SetAt(O_KILL_CRITTER, COpcodeAttributes("O_KILL_CRITTER", "kill_critter", 2));
    SetAt(O_KILL_CRITTER_TYPE, COpcodeAttributes("O_KILL_CRITTER_TYPE", "kill_critter_type", 2));
    SetAt(O_CRITTER_DMG, COpcodeAttributes("O_CRITTER_DMG", "critter_dmg", 3));
    SetAt(O_ADD_TIMER_EVENT, COpcodeAttributes("O_ADD_TIMER_EVENT", "add_timer_event", 3));
    SetAt(O_RM_TIMER_EVENT, COpcodeAttributes("O_RM_TIMER_EVENT", "rm_timer_event", 1));
    SetAt(O_GAME_TICKS, COpcodeAttributes("O_GAME_TICKS", "game_ticks", 1, expression));
    SetAt(O_HAS_TRAIT, COpcodeAttributes("O_HAS_TRAIT", "has_trait", 3, expression));
    SetAt(O_DESTROY_OBJECT, COpcodeAttributes("O_DESTROY_OBJECT", "destroy_object", 1));
    SetAt(O_OBJ_CAN_HEAR_OBJ, COpcodeAttributes("O_OBJ_CAN_HEAR_OBJ", "obj_can_hear_obj", 2, expression));
    SetAt(O_GAME_TIME_HOUR, COpcodeAttributes("O_GAME_TIME_HOUR", "game_time_hour", 0, expression));
    SetAt(O_FIXED_PARAM, COpcodeAttributes("O_FIXED_PARAM", "fixed_param", 0, expression));
    SetAt(O_TILE_IS_VISIBLE, COpcodeAttributes("O_TILE_IS_VISIBLE", "tile_is_visible", 1, expression));
    SetAt(O_DIALOGUE_SYSTEM_ENTER, COpcodeAttributes("O_DIALOGUE_SYSTEM_ENTER", "dialogue_system_enter", 0));
    SetAt(O_ACTION_BEING_USED, COpcodeAttributes("O_ACTION_BEING_USED", "action_being_used", 0, expression));
    SetAt(O_CRITTER_STATE, COpcodeAttributes("O_CRITTER_STATE", "critter_state", 1, expression));
    SetAt(O_GAME_TIME_ADVANCE, COpcodeAttributes("O_GAME_TIME_ADVANCE", "game_time_advance", 1));
    SetAt(O_RADIATION_INC, COpcodeAttributes("O_RADIATION_INC", "radiation_inc", 2));
    SetAt(O_RADIATION_DEC, COpcodeAttributes("O_RADIATION_DEC", "radiation_dec", 2));
    SetAt(O_CRITTER_ATTEMPT_PLACEMENT, COpcodeAttributes("O_CRITTER_ATTEMPT_PLACEMENT", "critter_attempt_placement", 3, expression));
    SetAt(O_OBJ_PID, COpcodeAttributes("O_OBJ_PID", "obj_pid", 1, expression));
    SetAt(O_CUR_MAP_INDEX, COpcodeAttributes("O_CUR_MAP_INDEX", "cur_map_index", 0, expression));
    SetAt(O_CRITTER_ADD_TRAIT, COpcodeAttributes("O_CRITTER_ADD_TRAIT", "critter_add_trait", 4, expression));
    SetAt(O_CRITTER_RM_TRAIT, COpcodeAttributes("O_CRITTER_RM_TRAIT", "critter_rm_trait", 4, expression));
    SetAt(O_PROTO_DATA, COpcodeAttributes("O_PROTO_DATA", "proto_data", 2, expression));
    SetAt(O_MESSAGE_STR, COpcodeAttributes("O_MESSAGE_STR", "message_str", 2, expression));
    SetAt(O_CRITTER_INVEN_OBJ, COpcodeAttributes("O_CRITTER_INVEN_OBJ", "critter_inven_obj", 2, expression));
    SetAt(O_OBJ_SET_LIGHT_LEVEL, COpcodeAttributes("O_OBJ_SET_LIGHT_LEVEL", "obj_set_light_level", 3));
    SetAt(O_WORLD_MAP, COpcodeAttributes("O_WORLD_MAP", "world_map", 0));
    SetAt(O_INVEN_CMDS, COpcodeAttributes("O_INVEN_CMDS", "inven_cmds", 3, expression));
    SetAt(O_FLOAT_MSG, COpcodeAttributes("O_FLOAT_MSG", "float_msg", 3));
    SetAt(O_METARULE, COpcodeAttributes("O_METARULE", "metarule", 2, expression));
    SetAt(O_ANIM, COpcodeAttributes("O_ANIM", "anim", 3));
    SetAt(O_OBJ_CARRYING_PID_OBJ, COpcodeAttributes("O_OBJ_CARRYING_PID_OBJ", "obj_carrying_pid_obj", 2, expression));
    SetAt(O_REG_ANIM_FUNC, COpcodeAttributes("O_REG_ANIM_FUNC", "reg_anim_func", 2));
    SetAt(O_REG_ANIM_ANIMATE, COpcodeAttributes("O_REG_ANIM_ANIMATE", "reg_anim_animate", 3));
    SetAt(O_REG_ANIM_ANIMATE_REVERSE, COpcodeAttributes("O_REG_ANIM_ANIMATE_REVERSE", "reg_anim_animate_reverse", 3));
    SetAt(O_REG_ANIM_OBJ_MOVE_TO_OBJ, COpcodeAttributes("O_REG_ANIM_OBJ_MOVE_TO_OBJ", "reg_anim_obj_move_to_obj", 3));
    SetAt(O_REG_ANIM_OBJ_RUN_TO_OBJ, COpcodeAttributes("O_REG_ANIM_OBJ_RUN_TO_OBJ", "reg_anim_obj_run_to_obj", 3));
    SetAt(O_REG_ANIM_OBJ_MOVE_TO_TILE, COpcodeAttributes("O_REG_ANIM_OBJ_MOVE_TO_TILE", "reg_anim_obj_move_to_tile", 3));
    SetAt(O_REG_ANIM_OBJ_RUN_TO_TILE, COpcodeAttributes("O_REG_ANIM_OBJ_RUN_TO_TILE", "reg_anim_obj_run_to_tile", 3));
    SetAt(O_PLAY_GMOVIE, COpcodeAttributes("O_PLAY_GMOVIE", "play_gmovie", 1));
    SetAt(O_ADD_MULT_OBJS_TO_INVEN, COpcodeAttributes("O_ADD_MULT_OBJS_TO_INVEN", "add_mult_objs_to_inven", 3));
    SetAt(O_RM_MULT_OBJS_FROM_INVEN, COpcodeAttributes("O_RM_MULT_OBJS_FROM_INVEN", "rm_mult_objs_from_inven", 3, expression));
    SetAt(O_GET_MONTH, COpcodeAttributes("O_GET_MONTH", "get_month", 0, expression));
    SetAt(O_GET_DAY, COpcodeAttributes("O_GET_DAY", "get_day", 0, expression));
    SetAt(O_EXPLOSION, COpcodeAttributes("O_EXPLOSION", "explosion", 3));
    SetAt(O_DAYS_SINCE_VISITED, COpcodeAttributes("O_DAYS_SINCE_VISITED", "days_since_visited", 0, expression));
    SetAt(O_GSAY_START, COpcodeAttributes("O_GSAY_START", "gsay_start", 0));
    SetAt(O_GSAY_END, COpcodeAttributes("O_GSAY_END", "gsay_end", 0));
    SetAt(O_GSAY_REPLY, COpcodeAttributes("O_GSAY_REPLY", "gsay_reply", 2));
    SetAt(O_GSAY_OPTION, COpcodeAttributes("O_GSAY_OPTION", "gsay_option", 4));
    SetAt(O_GSAY_MESSAGE, COpcodeAttributes("O_GSAY_MESSAGE", "gsay_message", 3));
    SetAt(O_GIQ_OPTION, COpcodeAttributes("O_GIQ_OPTION", "giq_option", 5));
    SetAt(O_POISON, COpcodeAttributes("O_POISON", "poison", 2));
    SetAt(O_GET_POISON, COpcodeAttributes("O_GET_POISON", "get_poison", 1, expression));
    SetAt(O_PARTY_ADD, COpcodeAttributes("O_PARTY_ADD", "party_add", 1));
    SetAt(O_PARTY_REMOVE, COpcodeAttributes("O_PARTY_REMOVE", "party_remove", 1));
    SetAt(O_REG_ANIM_ANIMATE_FOREVER, COpcodeAttributes("O_REG_ANIM_ANIMATE_FOREVER", "reg_anim_animate_forever", 2));
    SetAt(O_CRITTER_INJURE, COpcodeAttributes("O_CRITTER_INJURE", "critter_injure", 2));
    SetAt(O_COMBAT_IS_INITIALIZED, COpcodeAttributes("O_COMBAT_IS_INITIALIZED", "combat_is_initialized", 0, expression));
    SetAt(O_GDIALOG_MOD_BARTER, COpcodeAttributes("O_GDIALOG_MOD_BARTER", "gdialog_mod_barter", 1));
    SetAt(O_DIFFICULTY_LEVEL, COpcodeAttributes("O_DIFFICULTY_LEVEL", "difficulty_level", 0, expression));
    SetAt(O_RUNNING_BURNING_GUY, COpcodeAttributes("O_RUNNING_BURNING_GUY", "running_burning_guy", 0, expression));
    SetAt(O_INVEN_UNWIELD, COpcodeAttributes("O_INVEN_UNWIELD", "inven_unwield", 0));
    SetAt(O_OBJ_IS_LOCKED, COpcodeAttributes("O_OBJ_IS_LOCKED", "obj_is_locked", 1, expression));
    SetAt(O_OBJ_LOCK, COpcodeAttributes("O_OBJ_LOCK", "obj_lock", 1));
    SetAt(O_OBJ_UNLOCK, COpcodeAttributes("O_OBJ_UNLOCK", "obj_unlock", 1));
    SetAt(O_OBJ_IS_OPEN, COpcodeAttributes("O_OBJ_IS_OPEN", "obj_is_open", 1, expression));
    SetAt(O_OBJ_OPEN, COpcodeAttributes("O_OBJ_OPEN", "obj_open", 1));
    SetAt(O_OBJ_CLOSE, COpcodeAttributes("O_OBJ_CLOSE", "obj_close", 1));
    SetAt(O_GAME_UI_DISABLE, COpcodeAttributes("O_GAME_UI_DISABLE", "game_ui_disable", 0));
    SetAt(O_GAME_UI_ENABLE, COpcodeAttributes("O_GAME_UI_ENABLE", "game_ui_enable", 0));
    SetAt(O_GAME_UI_IS_DISABLED, COpcodeAttributes("O_GAME_UI_IS_DISABLED", "game_ui_is_disabled", 0, expression));
    SetAt(O_GFADE_OUT, COpcodeAttributes("O_GFADE_OUT", "gfade_out", 1));
    SetAt(O_GFADE_IN, COpcodeAttributes("O_GFADE_IN", "gfade_in", 1));
    SetAt(O_ITEM_CAPS_TOTAL, COpcodeAttributes("O_ITEM_CAPS_TOTAL", "item_caps_total", 1, expression));
    SetAt(O_ITEM_CAPS_ADJUST, COpcodeAttributes("O_ITEM_CAPS_ADJUST", "item_caps_adjust", 2, expression));
    SetAt(O_ANIM_ACTION_FRAME, COpcodeAttributes("O_ANIM_ACTION_FRAME", "anim_action_frame", 2, expression));
    SetAt(O_REG_ANIM_PLAY_SFX, COpcodeAttributes("O_REG_ANIM_PLAY_SFX", "reg_anim_play_sfx", 3));
    SetAt(O_CRITTER_MOD_SKILL, COpcodeAttributes("O_CRITTER_MOD_SKILL", "critter_mod_skill", 3));
    SetAt(O_SFX_BUILD_CHAR_NAME, COpcodeAttributes("O_SFX_BUILD_CHAR_NAME", "sfx_build_char_name", 3, expression));
    SetAt(O_SFX_BUILD_AMBIENT_NAME, COpcodeAttributes("O_SFX_BUILD_AMBIENT_NAME", "sfx_build_ambient_name", 1, expression));
    SetAt(O_SFX_BUILD_INTERFACE_NAME, COpcodeAttributes("O_SFX_BUILD_INTERFACE_NAME", "sfx_build_interface_name", 1, expression));
    SetAt(O_SFX_BUILD_ITEM_NAME, COpcodeAttributes("O_SFX_BUILD_ITEM_NAME", "sfx_build_item_name", 1, expression));
    SetAt(O_SFX_BUILD_WEAPON_NAME, COpcodeAttributes("O_SFX_BUILD_WEAPON_NAME", "sfx_build_weapon_name", 4, expression));
    SetAt(O_SFX_BUILD_SCENERY_NAME, COpcodeAttributes("O_SFX_BUILD_SCENERY_NAME", "sfx_build_scenery_name", 3, expression));
    SetAt(O_ATTACK_SETUP, COpcodeAttributes("O_ATTACK_SETUP", "attack_setup", 2));
    SetAt(O_DESTROY_MULT_OBJS, COpcodeAttributes("O_DESTROY_MULT_OBJS", "destroy_mult_objs", 2, expression));
    SetAt(O_USE_OBJ_ON_OBJ, COpcodeAttributes("O_USE_OBJ_ON_OBJ", "use_obj_on_obj", 2));
    SetAt(O_ENDGAME_SLIDESHOW, COpcodeAttributes("O_ENDGAME_SLIDESHOW", "endgame_slideshow", 0));
    SetAt(O_MOVE_OBJ_INVEN_TO_OBJ, COpcodeAttributes("O_MOVE_OBJ_INVEN_TO_OBJ", "move_obj_inven_to_obj", 2));
    SetAt(O_ENDGAME_MOVIE, COpcodeAttributes("O_ENDGAME_MOVIE", "endgame_movie", 0));
    SetAt(O_OBJ_ART_FID, COpcodeAttributes("O_OBJ_ART_FID", "obj_art_fid", 1, expression));
    SetAt(O_ART_ANIM, COpcodeAttributes("O_ART_ANIM", "art_anim", 1, expression));
    SetAt(O_PARTY_MEMBER_OBJ, COpcodeAttributes("O_PARTY_MEMBER_OBJ", "party_member_obj", 1, expression));
    SetAt(O_ROTATION_TO_TILE, COpcodeAttributes("O_ROTATION_TO_TILE", "rotation_to_tile", 2, expression));
    SetAt(O_JAM_LOCK, COpcodeAttributes("O_JAM_LOCK", "jam_lock", 1));
    SetAt(O_GDIALOG_SET_BARTER_MOD, COpcodeAttributes("O_GDIALOG_SET_BARTER_MOD", "gdialog_set_barter_mod", 1));
    SetAt(O_COMBAT_DIFFICULTY, COpcodeAttributes("O_COMBAT_DIFFICULTY", "combat_difficulty", 0, expression));
    SetAt(O_OBJ_ON_SCREEN, COpcodeAttributes("O_OBJ_ON_SCREEN", "obj_on_screen", 1, expression));
    SetAt(O_CRITTER_IS_FLEEING, COpcodeAttributes("O_CRITTER_IS_FLEEING", "critter_is_fleeing", 1, expression));
    SetAt(O_CRITTER_SET_FLEE_STATE, COpcodeAttributes("O_CRITTER_SET_FLEE_STATE", "critter_set_flee_state", 2));
    SetAt(O_TERMINATE_COMBAT, COpcodeAttributes("O_TERMINATE_COMBAT", "terminate_combat", 0));
    SetAt(O_DEBUG_MSG, COpcodeAttributes("O_DEBUG_MSG", "debug_msg", 1));
    SetAt(O_CRITTER_STOP_ATTACKING, COpcodeAttributes("O_CRITTER_STOP_ATTACKING", "critter_stop_attacking", 1));

    //sall start

    SetAt(O_READ_BYTE, COpcodeAttributes("O_READ_BYTE", "read_byte", 1, expression));
    SetAt(O_READ_SHORT, COpcodeAttributes("O_READ_SHORT", "read_short", 1, expression));
    SetAt(O_READ_INT, COpcodeAttributes("O_READ_INT", "read_int", 1, expression));
    SetAt(O_READ_STRING, COpcodeAttributes("O_READ_STRING", "read_string", 1, expression));

    SetAt(O_SET_PC_BASE_STAT, COpcodeAttributes("O_SET_PC_BASE_STAT", "set_pc_base_stat", 2));
    SetAt(O_SET_PC_EXTRA_STAT, COpcodeAttributes("O_SET_PC_EXTRA_STAT", "set_pc_extra_stat", 2));
    SetAt(O_GET_PC_BASE_STAT, COpcodeAttributes("O_GET_PC_BASE_STAT", "get_pc_base_stat", 1, expression));
    SetAt(O_GET_PC_EXTRA_STAT, COpcodeAttributes("O_GET_PC_EXTRA_STAT", "get_pc_extra_stat", 1, expression));

    SetAt(O_SET_CRITTER_BASE_STAT, COpcodeAttributes("O_SET_CRITTER_BASE_STAT", "set_critter_base_stat", 3));
    SetAt(O_SET_CRITTER_EXTRA_STAT, COpcodeAttributes("O_SET_CRITTER_EXTRA_STAT", "set_critter_extra_stat", 3));
    SetAt(O_GET_CRITTER_BASE_STAT, COpcodeAttributes("O_GET_CRITTER_BASE_STAT", "get_critter_base_stat", 2, expression));
    SetAt(O_GET_CRITTER_EXTRA_STAT, COpcodeAttributes("O_GET_CRITTER_EXTRA_STAT", "get_critter_extra_stat", 2, expression));

    SetAt(O_TAP_KEY, COpcodeAttributes("O_TAP_KEY", "tap_key", 1));
    SetAt(O_GET_YEAR, COpcodeAttributes("O_GET_YEAR", "get_year", 0, expression));

    SetAt(O_GAME_LOADED, COpcodeAttributes("O_GAME_LOADED", "game_loaded", 0, expression));
    SetAt(O_GRAPHICS_FUNCS_AVAILABLE, COpcodeAttributes("O_GRAPHICS_FUNCS_AVAILABLE", "graphics_funcs_available", 0, expression));
    SetAt(O_LOAD_SHADER, COpcodeAttributes("O_LOAD_SHADER", "load_shader", 1, expression));
    SetAt(O_FREE_SHADER, COpcodeAttributes("O_FREE_SHADER", "free_shader", 1));
    SetAt(O_ACTIVATE_SHADER, COpcodeAttributes("O_ACTIVATE_SHADER", "activate_shader", 1));
    SetAt(O_DEACTIVATE_SHADER, COpcodeAttributes("O_DEACTIVATE_SHADER", "deactivate_shader", 1));
    SetAt(O_SET_GLOBAL_SCRIPT_REPEAT, COpcodeAttributes("O_SET_GLOBAL_SCRIPT_REPEAT", "set_global_script_repeat", 1));
    SetAt(O_INPUT_FUNCS_AVAILABLE, COpcodeAttributes("O_INPUT_FUNCS_AVAILABLE", "input_funcs_available", 0, expression));
    SetAt(O_KEY_PRESSED, COpcodeAttributes("O_KEY_PRESSED", "key_pressed", 1, expression));

    SetAt(O_SET_SHADER_INT, COpcodeAttributes("O_SET_SHADER_INT", "set_shader_int", 3));
    SetAt(O_SET_SHADER_FLOAT, COpcodeAttributes("O_SET_SHADER_FLOAT", "set_shader_float", 3));
    SetAt(O_SET_SHADER_VECTOR, COpcodeAttributes("O_SET_SHADER_VECTOR", "set_shader_vector", 6));
    SetAt(O_IN_WORLD_MAP, COpcodeAttributes("O_IN_WORLD_MAP", "in_world_map", 0, expression));
    SetAt(O_FORCE_ENCOUNTER, COpcodeAttributes("O_FORCE_ENCOUNTER", "force_encounter", 1));
    SetAt(O_SET_WORLD_MAP_POS, COpcodeAttributes("O_SET_WORLD_MAP_POS", "set_world_map_pos", 2));
    SetAt(O_GET_WORLD_MAP_X_POS, COpcodeAttributes("O_GET_WORLD_MAP_X_POS", "get_world_map_x_pos", 0, expression));
    SetAt(O_GET_WORLD_MAP_Y_POS, COpcodeAttributes("O_GET_WORLD_MAP_Y_POS", "get_world_map_y_pos", 0, expression));

    SetAt(O_SET_DM_MODEL, COpcodeAttributes("O_SET_DM_MODEL", "set_dm_model", 1));
    SetAt(O_SET_DF_MODEL, COpcodeAttributes("O_SET_DF_MODEL", "set_df_model", 1));
    SetAt(O_SET_MOVIE_PATH, COpcodeAttributes("O_SET_MOVIE_PATH", "set_movie_path", 2));

    SetAt(O_SET_PERK_IMAGE, COpcodeAttributes("O_SET_PERK_IMAGE", "set_perk_image", 2));
    SetAt(O_SET_PERK_RANKS, COpcodeAttributes("O_SET_PERK_RANKS", "set_perk_ranks", 2));
    SetAt(O_SET_PERK_LEVEL, COpcodeAttributes("O_SET_PERK_LEVEL", "set_perk_level", 2));
    SetAt(O_SET_PERK_STAT, COpcodeAttributes("O_SET_PERK_STAT", "set_perk_stat", 2));
    SetAt(O_SET_PERK_STAT_MAG, COpcodeAttributes("O_SET_PERK_STAT_MAG", "set_perk_stat_mag", 2));
    SetAt(O_SET_PERK_SKILL1, COpcodeAttributes("O_SET_PERK_SKILL1", "set_perk_skill1", 2));
    SetAt(O_SET_PERK_SKILl1_MAG, COpcodeAttributes("O_SET_PERK_SKILl1_MAG", "set_perk_skill1_mag", 2));
    SetAt(O_SET_PERK_TYPE, COpcodeAttributes("O_SET_PERK_TYPE", "set_perk_type", 2));
    SetAt(O_SET_PERK_SKILL2, COpcodeAttributes("O_SET_PERK_SKILL2", "set_perk_skill2", 2));
    SetAt(O_SET_PERK_SKILL2_MAG, COpcodeAttributes("O_SET_PERK_SKILL2_MAG", "set_perk_skill2_mag", 2));
    SetAt(O_SET_PERK_STR, COpcodeAttributes("O_SET_PERK_STR", "set_perk_str", 2));
    SetAt(O_SET_PERK_PER, COpcodeAttributes("O_SET_PERK_PER", "set_perk_per", 2));
    SetAt(O_SET_PERK_END, COpcodeAttributes("O_SET_PERK_END", "set_perk_end", 2));
    SetAt(O_SET_PERK_CHR, COpcodeAttributes("O_SET_PERK_CHR", "set_perk_chr", 2));
    SetAt(O_SET_PERK_INT, COpcodeAttributes("O_SET_PERK_INT", "set_perk_int", 2));
    SetAt(O_SET_PERK_AGL, COpcodeAttributes("O_SET_PERK_AGL", "set_perk_agl", 2));
    SetAt(O_SET_PERK_LCK, COpcodeAttributes("O_SET_PERK_LCK", "set_perk_lck", 2));
    SetAt(O_SET_PERK_NAME, COpcodeAttributes("O_SET_PERK_NAME", "set_perk_name", 2));
    SetAt(O_SET_PERK_DESC, COpcodeAttributes("O_SET_PERK_DESC", "set_perk_desc", 2));

    SetAt(O_SET_PIPBOY_AVAILABLE, COpcodeAttributes("O_SET_PIPBOY_AVAILABLE", "set_pipboy_available", 1));

    SetAt(O_GET_KILL_COUNTER, COpcodeAttributes("O_GET_KILL_COUNTER", "get_kill_counter", 1, expression));
    SetAt(O_MOD_KILL_COUNTER, COpcodeAttributes("O_MOD_KILL_COUNTER", "mod_kill_counter", 2));

    SetAt(O_GET_PERK_OWED, COpcodeAttributes("O_GET_PERK_OWED", "get_perk_owed", 0, expression));
    SetAt(O_SET_PERK_OWED, COpcodeAttributes("O_SET_PERK_OWED", "set_perk_owed", 1));
    SetAt(O_GET_PERK_AVAILABLE, COpcodeAttributes("O_GET_PERK_AVAILABLE", "get_perk_available", 1, expression));

    SetAt(O_GET_CRITTER_AP, COpcodeAttributes("O_GET_CRITTER_AP", "get_critter_current_ap", 1, expression));
    SetAt(O_SET_CRITTER_AP, COpcodeAttributes("O_SET_CRITTER_AP", "set_critter_current_ap", 2));

    SetAt(O_GET_ACTIVE_HAND, COpcodeAttributes("O_GET_ACTIVE_HAND", "active_hand", 0, expression));
    SetAt(O_TOGGLE_ACTIVE_HAND, COpcodeAttributes("O_TOGGLE_ACTIVE_HAND", "toggle_active_hand", 0));

    SetAt(O_SET_WEAPON_KNOCKBACK, COpcodeAttributes("O_SET_WEAPON_KNOCKBACK", "set_weapon_knockback", 3));
    SetAt(O_SET_TARGET_KNOCKBACK, COpcodeAttributes("O_SET_TARGET_KNOCKBACK", "set_target_knockback", 3));
    SetAt(O_SET_ATTACKER_KNOCKBACK, COpcodeAttributes("O_SET_ATTACKER_KNOCKBACK", "set_attacker_knockback", 3));
    SetAt(O_REMOVE_WEAPON_KNOCKBACK, COpcodeAttributes("O_REMOVE_WEAPON_KNOCKBACK", "remove_weapon_knockback", 1));
    SetAt(O_REMOVE_TARGET_KNOCKBACK, COpcodeAttributes("O_REMOVE_TARGET_KNOCKBACK", "remove_target_knockback", 1));
    SetAt(O_REMOVE_ATTACKER_KNOCKBACK, COpcodeAttributes("O_REMOVE_ATTACKER_KNOCKBACK", "remove_attacker_knockback", 1));

    SetAt(O_SET_GLOBAL_SCRIPT_TYPE, COpcodeAttributes("O_SET_GLOBAL_SCRIPT_TYPE", "set_global_script_type", 1));
    SetAt(O_AVAILABLE_GLOBAL_SCRIPT_TYPES, COpcodeAttributes("O_AVAILABLE_GLOBAL_SCRIPT_TYPES", "available_global_script_types", 0, expression));

    SetAt(O_SET_SFALL_GLOBAL, COpcodeAttributes("O_SET_SFALL_GLOBAL", "set_sfall_global", 2));
    SetAt(O_GET_SFALL_GLOBAL_INT, COpcodeAttributes("O_GET_SFALL_GLOBAL_INT", "get_sfall_global_int", 1, expression));
    SetAt(O_GET_SFALL_GLOBAL_FLOAT, COpcodeAttributes("O_GET_SFALL_GLOBAL_FLOAT", "get_sfall_global_float", 1, expression));

    SetAt(O_SET_PICKPOCKET_MAX, COpcodeAttributes("O_SET_PICKPOCKET_MAX", "set_pickpocket_max", 1));
    SetAt(O_SET_HIT_CHANCE_MAX, COpcodeAttributes("O_SET_HIT_CHANCE_MAX", "set_hit_chance_max", 1));
    SetAt(O_SET_SKILL_MAX, COpcodeAttributes("O_SET_SKILL_MAX", "set_skill_max", 1));

    SetAt(O_EAX_AVAILABLE, COpcodeAttributes("O_EAX_AVAILABLE", "eax_available", 0, expression));
    SetAt(O_SET_EAX_ENVIRONMENT, COpcodeAttributes("O_SET_EAX_ENVIRONMENT", "set_eax_environment", 1));

    SetAt(O_INC_NPC_LEVEL, COpcodeAttributes("O_INC_NPC_LEVEL", "inc_npc_level", 1));

    SetAt(O_GET_VIEWPORT_X, COpcodeAttributes("O_GET_VIEWPORT_X", "get_viewport_x", 0, expression));
    SetAt(O_GET_VIEWPORT_Y, COpcodeAttributes("O_GET_VIEWPORT_Y", "get_viewport_y", 0, expression));
    SetAt(O_SET_VIEWPORT_X, COpcodeAttributes("O_SET_VIEWPORT_X", "set_viewport_x", 1));
    SetAt(O_SET_VIEWPORT_Y, COpcodeAttributes("O_SET_VIEWPORT_Y", "set_viewport_y", 1));

    SetAt(O_SET_XP_MOD, COpcodeAttributes("O_SET_XP_MOD", "set_xp_mod", 1));
    SetAt(O_SET_PERK_LEVEL_MOD, COpcodeAttributes("O_SET_PERK_LEVEL_MOD", "set_perk_level_mod", 1));

    SetAt(O_GET_INI_SETTING, COpcodeAttributes("O_GET_INI_SETTING", "get_ini_setting", 1, expression));

    SetAt(O_GET_SHADER_VERSION, COpcodeAttributes("O_GET_SHADER_VERSION", "get_shader_version", 0, expression));
    SetAt(O_SET_SHADER_MODE, COpcodeAttributes("O_SET_SHADER_MODE", "set_shader_mode", 2));

    SetAt(O_GET_GAME_MODE, COpcodeAttributes("O_GET_GAME_MODE", "get_game_mode", 0, expression));

    SetAt(O_FORCE_GRAPHICS_REFRESH, COpcodeAttributes("O_FORCE_GRAPHICS_REFRESH", "force_graphics_refresh", 1));
    SetAt(O_GET_SHADER_TEXTURE, COpcodeAttributes("O_GET_SHADER_TEXTURE", "get_shader_texture", 2, expression));
    SetAt(O_SET_SHADER_TEXTURE, COpcodeAttributes("O_SET_SHADER_TEXTURE", "set_shader_texture", 3));

    SetAt(O_GET_UPTIME, COpcodeAttributes("O_GET_UPTIME", "get_uptime", 0, expression));

    SetAt(O_SET_STAT_MAX, COpcodeAttributes("O_SET_STAT_MAX", "set_stat_max", 2));
    SetAt(O_SET_STAT_MIN, COpcodeAttributes("O_SET_STAT_MIN", "set_stat_min", 2));

    SetAt(O_SET_CAR_CURRENT_TOWN, COpcodeAttributes("O_SET_CAR_CURRENT_TOWN", "set_car_current_town", 1));

    SetAt(O_SET_PC_STAT_MAX, COpcodeAttributes("O_SET_PC_STAT_MAX", "set_pc_stat_max", 2));
    SetAt(O_SET_PC_STAT_MIN, COpcodeAttributes("O_SET_PC_STAT_MIN", "set_pc_stat_min", 2));
    SetAt(O_SET_NPC_STAT_MAX, COpcodeAttributes("O_SET_NPC_STAT_MAX", "set_npc_stat_max", 2));
    SetAt(O_SET_NPC_STAT_MIN, COpcodeAttributes("O_SET_NPC_STAT_MIN", "set_npc_stat_min", 2));

    SetAt(O_SET_FAKE_PERK, COpcodeAttributes("O_SET_FAKE_PERK", "set_fake_perk", 4));
    SetAt(O_SET_FAKE_TRAIT, COpcodeAttributes("O_SET_FAKE_TRAIT", "set_fake_trait", 4));
    SetAt(O_SET_SELECTABLE_PERK, COpcodeAttributes("O_SET_SELECTABLE_PERK", "set_selectable_perk", 4));
    SetAt(O_SET_PERKBOX_TITLE, COpcodeAttributes("O_SET_PERKBOX_TITLE", "set_perkbox_title", 1));
    SetAt(O_HIDE_REAL_PERKS, COpcodeAttributes("O_HIDE_REAL_PERKS", "hide_real_perks", 0));
    SetAt(O_SHOW_REAL_PERKS, COpcodeAttributes("O_SHOW_REAL_PERKS", "show_real_perks", 0));
    SetAt(O_HAS_FAKE_PERK, COpcodeAttributes("O_HAS_FAKE_PERK", "has_fake_perk", 1, expression));
    SetAt(O_HAS_FAKE_TRAIT, COpcodeAttributes("O_HAS_FAKE_TRAIT", "has_fake_trait", 1, expression));
    SetAt(O_PERK_ADD_MODE, COpcodeAttributes("O_PERK_ADD_MODE", "perk_add_mode", 1));
    SetAt(O_CLEAR_SELECTABLE_PERKS, COpcodeAttributes("O_CLEAR_SELECTABLE_PERKS", "clear_selectable_perks", 0));

    SetAt(O_SET_CRITTER_HIT_CHANCE_MOD, COpcodeAttributes("O_SET_CRITTER_HIT_CHANCE_MOD", "set_critter_hit_chance_mod", 3));
    SetAt(O_SET_BASE_HIT_CHANCE_MOD, COpcodeAttributes("O_SET_BASE_HIT_CHANCE_MOD", "set_base_hit_chance_mod", 2));
    SetAt(O_SET_CRITTER_SKILL_MOD, COpcodeAttributes("O_SET_CRITTER_SKILL_MOD", "set_critter_skill_mod", 2));
    SetAt(O_SET_BASE_SKILL_MOD, COpcodeAttributes("O_SET_BASE_SKILL_MOD", "set_base_skill_mod", 1));
    SetAt(O_SET_CRITTER_PICKPOCKET_MOD, COpcodeAttributes("O_SET_CRITTER_PICKPOCKET_MOD", "set_critter_pickpocket_mod", 3));
    SetAt(O_SET_BASE_PICKPOCKET_MOD, COpcodeAttributes("O_SET_BASE_PICKPOCKET_MOD", "set_base_pickpocket_mod", 2));

    SetAt(O_SET_PYROMANIAC_MOD, COpcodeAttributes("O_SET_PYROMANIAC_MOD", "set_pyromaniac_mod", 1));
    SetAt(O_APPLY_HEAVEHO_FIX, COpcodeAttributes("O_APPLY_HEAVEHO_FIX", "apply_heaveho_fix", 0));
    SetAt(O_SET_SWIFTLEARNER_MOD, COpcodeAttributes("O_SET_SWIFTLEARNER_MOD", "set_swiftlearner_mod", 1));
    SetAt(O_SET_HP_LEVEL_MOD, COpcodeAttributes("O_SET_HP_LEVEL_MOD", "set_hp_per_level_mod", 1));

    SetAt(O_WRITE_BYTE, COpcodeAttributes("O_WRITE_BYTE", "write_byte", 2));
    SetAt(O_WRITE_SHORT, COpcodeAttributes("O_WRITE_SHORT", "write_short", 2));
    SetAt(O_WRITE_INT, COpcodeAttributes("O_WRITE_INT", "write_int", 2));

    SetAt(O_CALL_OFFSET_V0, COpcodeAttributes("O_CALL_OFFSET_V0", "call_offset_v0", 1));
    SetAt(O_CALL_OFFSET_V1, COpcodeAttributes("O_CALL_OFFSET_V1", "call_offset_v1", 2));
    SetAt(O_CALL_OFFSET_V2, COpcodeAttributes("O_CALL_OFFSET_V2", "call_offset_v2", 3));
    SetAt(O_CALL_OFFSET_V3, COpcodeAttributes("O_CALL_OFFSET_V3", "call_offset_v3", 4));
    SetAt(O_CALL_OFFSET_V4, COpcodeAttributes("O_CALL_OFFSET_V4", "call_offset_v4", 5));
    SetAt(O_CALL_OFFSET_R0, COpcodeAttributes("O_CALL_OFFSET_R0", "call_offset_r0", 1, expression));
    SetAt(O_CALL_OFFSET_R1, COpcodeAttributes("O_CALL_OFFSET_R1", "call_offset_r1", 2, expression));
    SetAt(O_CALL_OFFSET_R2, COpcodeAttributes("O_CALL_OFFSET_R2", "call_offset_r2", 3, expression));
    SetAt(O_CALL_OFFSET_R3, COpcodeAttributes("O_CALL_OFFSET_R3", "call_offset_r3", 4, expression));
    SetAt(O_CALL_OFFSET_R4, COpcodeAttributes("O_CALL_OFFSET_R4", "call_offset_r4", 5, expression));

    SetAt(O_SHOW_IFACE_TAG, COpcodeAttributes("O_SHOW_IFACE_TAG", "show_iface_tag", 1));
    SetAt(O_HIDE_IFACE_TAG, COpcodeAttributes("O_HIDE_IFACE_TAG", "hide_iface_tag", 1));
    SetAt(O_IS_IFACE_TAG_ACTIVE, COpcodeAttributes("O_IS_IFACE_TAG_ACTIVE", "is_iface_tag_active", 1, expression));

    SetAt(O_GET_BODYPART_HIT_MODIFIER, COpcodeAttributes("O_GET_BODYPART_HIT_MODIFIER", "get_bodypart_hit_modifier", 1, expression));
    SetAt(O_SET_BODYPART_HIT_MODIFIER, COpcodeAttributes("O_SET_BODYPART_HIT_MODIFIER", "set_bodypart_hit_modifier", 2));



    //1.41
    SetAt(O_SET_CRITICAL_TABLE, COpcodeAttributes("O_SET_CRITICAL_TABLE", "set_critical_table", 5));
    SetAt(O_GET_CRITICAL_TABLE, COpcodeAttributes("O_GET_CRITICAL_TABLE", "get_critical_table", 4, expression));
    SetAt(O_RESET_CRITICAL_TABLE, COpcodeAttributes("O_RESET_CRITICAL_TABLE", "reset_critical_table", 4));
    SetAt(O_GET_SFALL_ARG, COpcodeAttributes("O_GET_SFALL_ARG", "get_sfall_arg", 0, expression));
    SetAt(O_SET_SFALL_RETURN, COpcodeAttributes("O_SET_SFALL_RETURN", "set_sfall_return", 1));
    SetAt(O_SET_UNSPENT_AP_BONUS, COpcodeAttributes("O_SET_UNSPENT_AP_BONUS", "set_unspent_ap_bonus", 1));
    SetAt(O_GET_UNSPENT_AP_BONUS, COpcodeAttributes("O_GET_UNSPENT_AP_BONUS", "get_unspent_ap_bonus", 0, expression));
    SetAt(O_SET_UNSPENT_AP_PERK_BONUS, COpcodeAttributes("O_SET_UNSPENT_AP_PERK_BONUS", "set_unspent_ap_perk_bonus", 1));
    SetAt(O_GET_UNSPENT_AP_PERK_BONUS, COpcodeAttributes("O_GET_UNSPENT_AP_PERK_BONUS", "get_unspent_ap_perk_bonus", 0, expression));
    SetAt(O_INIT_HOOK, COpcodeAttributes("O_INIT_HOOK", "init_hook", 0, expression));
    SetAt(O_GET_INI_STRING, COpcodeAttributes("O_GET_INI_STRING", "get_ini_string", 1, expression));

    //1.42
    SetAt(O_SQRT, COpcodeAttributes("O_SQRT", "sqrt", 1, expression));
    SetAt(O_ABS, COpcodeAttributes("O_ABS", "abs", 1, expression));
    SetAt(O_SIN, COpcodeAttributes("O_SIN", "sin", 1, expression));
    SetAt(O_COS, COpcodeAttributes("O_COS", "cos", 1, expression));
    SetAt(O_TAN, COpcodeAttributes("O_TAN", "tan", 1, expression));
    SetAt(O_ARCTAN, COpcodeAttributes("O_ARCTAN", "arctan", 2, expression));
    SetAt(O_SET_PALETTE, COpcodeAttributes("O_SET_PALETTE", "set_palette", 1));

    //1.46b
    SetAt(O_REMOVE_SCRIPT,  COpcodeAttributes("O_REMOVE_SCRIPT",  "remove_script",  1));
    SetAt(O_SET_SCRIPT,     COpcodeAttributes("O_SET_SCRIPT",     "set_script",     2));
    SetAt(O_GET_SCRIPT,     COpcodeAttributes("O_GET_SCRIPT",     "get_script",     1, expression));
    SetAt(O_NB_CREATE_CHAR, COpcodeAttributes("O_NB_CREATE_CHAR", "nb_create_char", 0, expression));
    SetAt(O_FS_CREATE,      COpcodeAttributes("O_FS_CREATE",      "fs_create",      2, expression));
    SetAt(O_FS_COPY,        COpcodeAttributes("O_FS_COPY",        "fs_copy",        2, expression));
    SetAt(O_FS_FIND,        COpcodeAttributes("O_FS_FIND",        "fs_find",        1, expression));
    SetAt(O_FS_WRITE_BYTE,  COpcodeAttributes("O_FS_WRITE_BYTE",  "fs_write_byte",  2));
    SetAt(O_FS_WRITE_SHORT, COpcodeAttributes("O_FS_WRITE_SHORT", "fs_write_short", 2));
    SetAt(O_FS_WRITE_INT,   COpcodeAttributes("O_FS_WRITE_INT",   "fs_write_int",   2));
    SetAt(O_FS_WRITE_FLOAT, COpcodeAttributes("O_FS_WRITE_FLOAT", "fs_write_float", 2));
    SetAt(O_FS_WRITE_STRING,COpcodeAttributes("O_FS_WRITE_STRING","fs_write_string",2));
    SetAt(O_FS_DELETE,      COpcodeAttributes("O_FS_DELETE",      "fs_delete",      1));
    SetAt(O_FS_SIZE,        COpcodeAttributes("O_FS_SIZE",        "fs_size",        1, expression));
    SetAt(O_FS_POS,         COpcodeAttributes("O_FS_POS",         "fs_pos",         1, expression));
    SetAt(O_FS_SEEK,        COpcodeAttributes("O_FS_SEEK",        "fs_seek",        2));
    SetAt(O_FS_RESIZE,      COpcodeAttributes("O_FS_RESIZE",      "fs_resize",      2));
    SetAt(O_GET_PROTO_DATA, COpcodeAttributes("O_GET_PROTO_DATA", "get_proto_data", 2, expression));

    //1.47b
    SetAt(O_SET_PROTO_DATA, COpcodeAttributes("O_SET_PROTO_DATA", "set_proto_data", 3));
    SetAt(O_SET_SELF,       COpcodeAttributes("O_SET_SELF",       "set_self",       1));
    SetAt(O_REGISTER_HOOK,  COpcodeAttributes("O_REGISTER_HOOK",  "register_hook",  1));

    SetAt(O_FS_WRITE_BSTRING, COpcodeAttributes("O_FS_WRITE_BSTRING", "fs_write_bstring", 2));
    SetAt(O_FS_READ_BYTE,    COpcodeAttributes("O_FS_READ_BYTE",   "fs_read_byte",    1, expression));
    SetAt(O_FS_READ_SHORT,   COpcodeAttributes("O_FS_READ_SHORT",  "fs_read_short",   1, expression));
    SetAt(O_FS_READ_INT,     COpcodeAttributes("O_FS_READ_INT",    "fs_read_int",     1, expression));
    SetAt(O_FS_READ_FLOAT,   COpcodeAttributes("O_FS_READ_FLOAT",  "fs_read_float",   1, expression));


    SetAt(O_LIST_BEGIN,     COpcodeAttributes("O_LIST_BEGIN",     "list_begin",     1, expression));
    SetAt(O_LIST_NEXT,      COpcodeAttributes("O_LIST_NEXT",      "list_next",      1, expression));
    SetAt(O_LIST_END,       COpcodeAttributes("O_LIST_END",       "list_end",       1));

    //1.49d
    SetAt(O_SFALL_VER_MAJOR,     COpcodeAttributes("O_SFALL_VER_MAJOR",     "sfall_ver_major",     0, expression));
    SetAt(O_SFALL_VER_MINOR,     COpcodeAttributes("O_SFALL_VER_MINOR",     "sfall_ver_minor",     0, expression));
    SetAt(O_SFALL_VER_BUILD,     COpcodeAttributes("O_SFALL_VER_BUILD",     "sfall_ver_build",     0, expression));

    SetAt(O_HERO_SELECT_WIN, COpcodeAttributes("O_HERO_SELECT_WIN",  "hero_select_win",  1));
    SetAt(O_SET_HERO_RACE,   COpcodeAttributes("O_SET_HERO_RACE",    "set_hero_race",    1));
    SetAt(O_SET_HERO_STYLE,  COpcodeAttributes("O_SET_HERO_STYLE",   "set_hero_style",   1));

    SetAt(O_SET_CRITTER_BURST_DISABLE,  COpcodeAttributes("O_SET_CRITTER_BURST_DISABLE",  "set_critter_burst_disable",  2));



    SetAt(O_GET_WEAPON_AMMO_PID,        COpcodeAttributes("O_GET_WEAPON_AMMO_PID", "get_weapon_ammo_pid",               1, expression));
    SetAt(O_SET_WEAPON_AMMO_PID,        COpcodeAttributes("O_SET_WEAPON_AMMO_PID", "set_weapon_ammo_pid",               2));
    SetAt(O_GET_WEAPON_AMMO_COUNT,      COpcodeAttributes("O_GET_WEAPON_AMMO_COUNT", "get_weapon_ammo_count",           1, expression));
    SetAt(O_SET_WEAPON_AMMO_COUNT,      COpcodeAttributes("O_SET_WEAPON_AMMO_COUNT", "set_weapon_ammo_count",           2));
    SetAt(O_WRITE_STRING,               COpcodeAttributes("O_WRITE_STRING", "write_String",                             2));
    SetAt(O_GET_MOUSE_X,                COpcodeAttributes("O_GET_MOUSE_X", "get_mouse_x",                               0, expression));
    SetAt(O_GET_MOUSE_Y,                COpcodeAttributes("O_GET_MOUSE_Y", "get_mouse_y",                               0, expression));
    SetAt(O_GET_MOUSE_BUTTONS,          COpcodeAttributes("O_GET_MOUSE_BUTTONS", "get_mouse_buttons",                   0, expression));
    SetAt(O_GET_WINDOW_UNDER_MOUSE,     COpcodeAttributes("O_GET_WINDOW_UNDER_MOUSE", "get_window_under_mouse",         0, expression));
    SetAt(O_GET_SCREEN_WIDTH,           COpcodeAttributes("O_GET_SCREEN_WIDTH", "get_screen_width",                     0, expression));
    SetAt(O_GET_SCREEN_HEIGHT,          COpcodeAttributes("O_GET_SCREEN_HEIGHT", "get_screen_height",                   0, expression));
    SetAt(O_STOP_GAME,                  COpcodeAttributes("O_STOP_GAME", "stop_game",                                   0));
    SetAt(O_RESUME_GAME,                COpcodeAttributes("O_RESUME_GAME", "resume_game",                               0));
    SetAt(O_CREATE_MESSAGE_WINDOW,      COpcodeAttributes("O_CREATE_MESSAGE_WINDOW", "create_message_window",           1));
    SetAt(O_REMOVE_TRAIT,               COpcodeAttributes("O_REMOVE_TRAIT", "remove_trait",                             1));
    SetAt(O_GET_LIGHT_LEVEL,            COpcodeAttributes("O_GET_LIGHT_LEVEL", "get_light_level",                       0, expression));
    SetAt(O_REFRESH_PC_ART,             COpcodeAttributes("O_REFRESH_PC_ART", "refresh_pc_art",                         0));
    SetAt(O_GET_ATTACK_TYPE,            COpcodeAttributes("O_GET_ATTACK_TYPE", "get_attack_type",                       0, expression));
    SetAt(O_FORCE_ENCOUNTER_WITH_FLAGS, COpcodeAttributes("O_FORCE_ENCOUNTER_WITH_FLAGS", "force_encounter_with_flags", 2));
    SetAt(O_SET_MAP_TIME_MULTI,         COpcodeAttributes("O_SET_MAP_TIME_MULTI", "set_map_time_multi",                 1));
    SetAt(O_PLAY_SFALL_SOUND,           COpcodeAttributes("O_PLAY_SFALL_SOUND", "play_sfall_sound",                     2, expression));
    SetAt(O_STOP_SFALL_SOUND,           COpcodeAttributes("O_STOP_SFALL_SOUND", "stop_sfall_sound",                     1));
    SetAt(O_CREATE_ARRAY,               COpcodeAttributes("O_CREATE_ARRAY", "create_array",                             2, expression));
    SetAt(O_SET_ARRAY,                  COpcodeAttributes("O_SET_ARRAY", "set_array",                                   3));
    SetAt(O_GET_ARRAY,                  COpcodeAttributes("O_GET_ARRAY", "get_array",                                   2, expression));
    SetAt(O_FREE_ARRAY,                 COpcodeAttributes("O_FREE_ARRAY", "free_array",                                 1));

    //sfall vrs 2.8
    SetAt(O_TS_LEN_ARRAY,              COpcodeAttributes("O_TS_LEN_ARRAY", "len_array",                                 1, expression));
    SetAt(O_TS_RESIZE_ARRAY,           COpcodeAttributes("O_TS_RESIZE_ARRAY", "resize_array",                           2));
    SetAt(O_TS_TEMP_ARRAY,             COpcodeAttributes("O_TS_TEMP_ARRAY", "temp_array",                               2, expression));
    SetAt(O_TS_FIX_ARRAY,              COpcodeAttributes("O_TS_FIX_ARRAY", "fix_array",                                 1));
    SetAt(O_TS_STRING_SPLIT,           COpcodeAttributes("O_TS_STRING_SPLIT", "string_split",                           2, expression));
    SetAt(O_TS_LIST_AS_ARRAY,          COpcodeAttributes("O_TS_LIST_AS_ARRAY", "list_as_array",                         1, expression));

    // sfall 2.8b
    SetAt(O_TS_ATOI,                   COpcodeAttributes("O_TS_ATOI", "atoi",                                           1, expression));
    SetAt(O_TS_ATOF,                   COpcodeAttributes("O_TS_ATOF", "atof",                                           1, expression));

    // sfall 2.9a 
    SetAt(O_TS_SCAN_ARRAY,             COpcodeAttributes("O_TS_SCAN_ARRAY", "scan_array",                               2, expression));
    SetAt(O_TS_TILE_PID,               COpcodeAttributes("O_TS_TILE_PID", "get_tile_fid",                               1, expression));
    SetAt(O_TS_MODIFIED_INI,           COpcodeAttributes("O_TS_MODIFIED_INI", "modified_ini",                           0, expression));
    SetAt(O_TS_GET_SFALL_ARGS,         COpcodeAttributes("O_TS_GET_SFALL_ARGS", "get_sfall_args",                       0, expression));

    // sfall 2.12
    SetAt(O_TS_SET_SFALL_ARG,          COpcodeAttributes("O_TS_GET_SFALL_ARG", "set_sfall_arg",                         2));

    // sfall 2.16   
    SetAt(O_TS_FORCE_AIMED_SHOTS,      COpcodeAttributes("O_TS_FORCE_AIMED_SHOTS", "force_aimed_shots",                 1));
    SetAt(O_TS_DISABLE_AIMED_SHOTS,    COpcodeAttributes("O_TS_DISABLE_AIMED_SHOTS", "disable_aimed_shots",             1));
    SetAt(O_TS_MARK_MOVIE_PLAYED,      COpcodeAttributes("O_TS_MARK_MOVIE_PLAYED", "mark_movie_played",                 1));

    // sfall 2.17   
    SetAt(O_TS_GET_NPC_LEVEL,          COpcodeAttributes("O_TS_GET_NPC_LEVEL", "get_npc_level",                         1, expression));

    // sfall 3.0   
    SetAt(O_TS_SET_CRITTER_SKILL_POINTS,    COpcodeAttributes("O_TS_SET_CRITTER_SKILL_POINTS", "set_critter_skill_points",      3));
    SetAt(O_TS_GET_CRITTER_SKILL_POINTS,    COpcodeAttributes("O_TS_GET_CRITTER_SKILL_POINTS", "get_critter_skill_points",      2, expression));
    SetAt(O_TS_SET_AVAILABLE_SKILL_POINTS,  COpcodeAttributes("O_TS_SET_AVAILABLE_SKILL_POINTS", "set_available_skill_points",  1));
    SetAt(O_TS_GET_AVAILABLE_SKILL_POINTS,  COpcodeAttributes("O_TS_GET_AVAILABLE_SKILL_POINTS", "get_available_skill_points",  0, expression));
    SetAt(O_TS_MOD_SKILL_POINTS_PER_LEVEL,  COpcodeAttributes("O_TS_MOD_SKILL_POINTS_PER_LEVEL", "mod_skill_points_per_level",  1));
    SetAt(O_TS_SET_PERK_FREQ,               COpcodeAttributes("O_TS_SET_PERK_FREQ", "set_perk_freq",                            1));
    SetAt(O_TS_GET_LAST_TARGET,             COpcodeAttributes("O_TS_GET_LAST_TARGET", "get_last_attacker",                      1, expression));
    SetAt(O_TS_GET_LAST_ATTACKER,           COpcodeAttributes("O_TS_GET_LAST_ATTACKER", "get_last_target",                      1, expression));
    SetAt(O_TS_BLOCK_COMBAT,                COpcodeAttributes("O_TS_BLOCK_COMBAT", "block_combat",                              1));

    // sfall 3.3   
    SetAt(O_TS_TILE_UNDER_CURSOR,               COpcodeAttributes("O_TS_TILE_UNDER_CURSOR", "tile_under_cursor",                             0, expression));
    SetAt(O_TS_GET_BARTER_MOD,                   COpcodeAttributes("O_TS_GET_BARTER_MOD", "gdialog_get_barter_mod",                      0, expression));
    SetAt(O_TS_SET_INVEN_AP_COST,                COpcodeAttributes("O_TS_SET_INVEN_AP_COST", "set_inven_ap_cost",                            1));

    // sfall 3.4
    SetAt(O_TS_SUBSTR,                    COpcodeAttributes("O_TS_SUBSTR", "substr",             3, expression));
    SetAt(O_TS_STRLEN,                    COpcodeAttributes("O_TS_STRLEN", "strlen",             1, expression));
    SetAt(O_TS_SPRINTF,                   COpcodeAttributes("O_TS_SPRINTF", "sprintf",       2, expression));
    SetAt(O_TS_ORD,                       COpcodeAttributes("O_TS_ORD", "charcode",     1, expression)); // sfall 3.5
    //SetAt(O_TS_RESERVD2,                COpcodeAttributes("O_TS_RESERVD2", "substr",      3, expression));
    SetAt(O_TS_TYPEOF,                    COpcodeAttributes("O_TS_TYPEOF", "typeof",             1, expression));
    SetAt(O_TS_LOG,                       COpcodeAttributes("O_TS_LOG", "log",           1, expression)); // sfall 3.5
    SetAt(O_TS_EXP,                       COpcodeAttributes("O_TS_EXP", "exponent",      1, expression)); // sfall 3.5
    SetAt(O_TS_CEIL,                      COpcodeAttributes("O_TS_CEIL", "ceil",         1, expression)); // sfall 3.5
    SetAt(O_TS_ROUND,                     COpcodeAttributes("O_TS_ROUND", "round",       1, expression)); // sfall 3.5
    SetAt(O_TS_SAVE_ARRAY,                COpcodeAttributes("O_TS_SAVE_ARRAY", "save_array",     2));
    SetAt(O_TS_LOAD_ARRAY,                COpcodeAttributes("O_TS_LOAD_ARRAY", "load_array",     1, expression));
    SetAt(O_TS_GET_ARRAY_KEY,             COpcodeAttributes("O_TS_GET_ARRAY_KEY", "array_key", 2, expression));
    SetAt(O_TS_STACK_ARRAY,               COpcodeAttributes("O_TS_STACK_ARRAY", "arrayexpr",     2, expression));

    SetAt(O_TS_REG_ANIM_DESTROY,          COpcodeAttributes("O_TS_REG_ANIM_DESTROY", "reg_anim_destroy", 1));
    SetAt(O_TS_REG_ANIM_ANIMATE_AND_HIDE, COpcodeAttributes("O_TS_REG_ANIM_ANIMATE_AND_HIDE", "reg_anim_animate_and_hide", 3));
    SetAt(O_TS_REG_ANIM_COMBAT_CHECK,     COpcodeAttributes("O_TS_REG_ANIM_COMBAT_CHECK", "reg_anim_combat_check", 1));
    SetAt(O_TS_REG_ANIM_LIGHT,            COpcodeAttributes("O_TS_REG_ANIM_LIGHT", "reg_anim_light",     3));
    SetAt(O_TS_REG_ANIM_CHANGE_FID,       COpcodeAttributes("O_TS_REG_ANIM_CHANGE_FID", "reg_anim_change_fid",   3));
    SetAt(O_TS_REG_ANIM_TAKE_OUT,         COpcodeAttributes("O_TS_REG_ANIM_TAKE_OUT", "reg_anim_take_out",  3));
    SetAt(O_TS_REG_ANIM_TURN_TOWARDS,     COpcodeAttributes("O_TS_REG_ANIM_TURN_TOWARDS", "reg_anim_turn_towards",  3));

    SetAt(O_TS_EXPLOSIONS_METARULE, COpcodeAttributes("O_TS_EXPLOSIONS_METARULE", "metarule2_explosions",    3, expression));

    // sfall 3.5
    SetAt(O_TS_REGISTER_HOOK_PROC, COpcodeAttributes("O_TS_REGISTER_HOOK_PROC", "register_hook_proc",    2, COpcodeAttributes::TYPE_STATEMENT, COpcodeAttributes::CATEGORY_PREFIX, procArgs_register_hook_proc, 1));
    SetAt(O_TS_POW, COpcodeAttributes("O_POW", "^", 2, expression, infix));
    SetAt(O_TS_MESSAGE_STR_GAME, COpcodeAttributes("O_TS_MESSAGE_STR_GAME", "message_str_game",  2, expression));
    SetAt(O_TS_SNEAK_SUCCESS, COpcodeAttributes("O_TS_SNEAK_SUCCESS", "sneak_success",   0, expression));
    SetAt(O_TS_TILE_LIGHT, COpcodeAttributes("O_TS_SNEAK_SUCCESS", "tile_light",     2, expression));
    SetAt(O_TS_MAKE_STRAIGHT_PATH, COpcodeAttributes("O_TS_MAKE_STRAIGHT_PATH", "obj_blocking_line",     3, expression));
    SetAt(O_TS_OBJ_BLOCKING_AT, COpcodeAttributes("O_TS_OBJ_BLOCKING_AT", "obj_blocking_tile",   3, expression));
    SetAt(O_TS_TILE_GET_OBJECTS, COpcodeAttributes("O_TS_TILE_GET_OBJECTS", "tile_get_objs",     2, expression));
    SetAt(O_TS_GET_PARTY_MEMBERS, COpcodeAttributes("O_TS_GET_PARTY_MEMBERS", "party_member_list",   1, expression));
    SetAt(O_TS_PATH_FIND, COpcodeAttributes("O_TS_PATH_FIND", "path_find_to",    3, expression));
    SetAt(O_TS_CREATE_SPATIAL, COpcodeAttributes("O_TS_CREATE_SPATIAL", "create_spatial",    4, expression));
    SetAt(O_TS_ART_EXISTS, COpcodeAttributes("O_TS_ART_EXISTS", "art_exists",    1, expression));
    SetAt(O_TS_OBJ_IS_CARRYING_OBJ, COpcodeAttributes("O_TS_OBJ_IS_CARRYING_OBJ", "obj_is_carrying_obj",     2, expression));

	// sfall 3.8
	SetAt(O_TS_SFALL_METARULE0, COpcodeAttributes("O_TS_SFALL_METARULE0", "sfall_func0", 1, expression));
	SetAt(O_TS_SFALL_METARULE1, COpcodeAttributes("O_TS_SFALL_METARULE1", "sfall_func1", 2, expression));
	SetAt(O_TS_SFALL_METARULE2, COpcodeAttributes("O_TS_SFALL_METARULE2", "sfall_func2", 3, expression));
	SetAt(O_TS_SFALL_METARULE3, COpcodeAttributes("O_TS_SFALL_METARULE3", "sfall_func3", 4, expression));
	SetAt(O_TS_SFALL_METARULE4, COpcodeAttributes("O_TS_SFALL_METARULE4", "sfall_func4", 5, expression));
	SetAt(O_TS_SFALL_METARULE5, COpcodeAttributes("O_TS_SFALL_METARULE5", "sfall_func5", 6, expression));
	SetAt(O_TS_SFALL_METARULE6, COpcodeAttributes("O_TS_SFALL_METARULE6", "sfall_func6", 7, expression));
    // sfall end

    SetAt(O_STRINGOP, COpcodeAttributes("O_STRINGOP", "", 0, expression));
    SetAt(O_FLOATOP, COpcodeAttributes("O_FLOATOP", "", 0, expression));
    SetAt(O_INTOP,  COpcodeAttributes("O_INTOP", "", 0, expression));
}
