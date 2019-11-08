#include "parse.h"
#include "parselib.h"
#include "extra.h"
#include "gencode.h"

extern int backwardcompat;

void initLibExtras(void) {
	lexAddToken(T_LOADPALETTETABLE, "loadpalettetable");
	lexAddToken(T_DISPLAYGFX, "displaygfx");
	lexAddToken(T_SELECTWIN, "selectwin");
	lexAddToken(T_CREATEWIN, "createwin");
	lexAddToken(T_DELETEWIN, "deletewin");
	lexAddToken(T_RESIZEWIN, "resizewin");
	lexAddToken(T_SCALEWIN, "scalewin");
	lexAddToken(T_SHOWWIN, "showwin");
	lexAddToken(T_FILLWIN, "fillwin");
	lexAddToken(T_FILLRECT, "fillrect");
	lexAddToken(T_FILLWIN3X3, "fillwin3x3");
	lexAddToken(T_DISPLAY, "display");
	lexAddToken(T_DISPLAYRAW, "displayraw");
	lexAddToken(T_PLAYMOVIE, "playmovie");
	if(backwardcompat) {
		lexAddToken(T_PLAYMOVIEALPHA, "playmoviealpharect");
	} else {
		lexAddToken(T_PLAYMOVIEALPHA, "playmoviealpha");
		lexAddToken(T_PLAYMOVIEALPHARECT, "playmoviealpharect");
	}
	lexAddToken(T_MOVIEFLAGS, "movieflags");
	lexAddToken(T_PLAYMOVIERECT, "playmovierect");
	lexAddToken(T_STOPMOVIE, "stopmovie");
	lexAddToken(T_PRINT, "print");
	lexAddToken(T_FORMAT, "format");
	lexAddToken(T_PRINTRECT, "printrect");
	lexAddToken(T_SETFONT, "setfont");
	lexAddToken(T_SETTEXTFLAGS, "settextflags");
	lexAddToken(T_SETTEXTCOLOR, "settextcolor");
	lexAddToken(T_SETHIGHLIGHTCOLOR, "sethighlightcolor");
	lexAddToken(T_GOTOXY, "gotoxy");
	lexAddToken(T_ADDREGION, "addregion");
	lexAddToken(T_ADDREGIONPROC, "addregionproc");
	lexAddToken(T_ADDREGIONFLAG, "addregionflag");
	lexAddToken(T_ADDREGIONRIGHTPROC, "addregionrightproc");
	lexAddToken(T_DELETEREGION, "deleteregion");
	lexAddToken(T_ACTIVATEREGION, "activateregion");
	lexAddToken(T_CHECKREGION, "checkregion");

	lexAddToken(T_FADEIN, "fadein");
	lexAddToken(T_FADEOUT, "fadeout");
	lexAddToken(T_ADDBUTTON, "addbutton");
	lexAddToken(T_ADDBUTTONTEXT, "addbuttontext");
	lexAddToken(T_ADDBUTTONGFX, "addbuttongfx");
	lexAddToken(T_ADDBUTTONPROC, "addbuttonproc");
	lexAddToken(T_ADDBUTTONFLAG, "addbuttonflag");
	lexAddToken(T_ADDBUTTONRIGHTPROC, "addbuttonrightproc");
	lexAddToken(T_DELETEBUTTON, "deletebutton");

	lexAddToken(T_SAYSTARTPOS, "saystartpos");
	lexAddToken(T_SAYSTART, "saystart");
	lexAddToken(T_SAYREPLY, "sayreply");
	lexAddToken(T_SAYGOTOREPLY, "saygotoreply");
	lexAddToken(T_SAYREPLYTITLE, "sayreplytitle");
	lexAddToken(T_SAYOPTION, "sayoption");
	lexAddToken(T_SAYEND, "sayend");
	lexAddToken(T_SAYQUIT, "sayquit");
	lexAddToken(T_SAYMESSAGE, "saymessage");
	lexAddToken(T_SAYREPLYFLAGS, "sayreplyflags");
	lexAddToken(T_SAYOPTIONFLAGS, "sayoptionflags");
	lexAddToken(T_SAYREPLYWINDOW, "sayreplywindow");
	lexAddToken(T_SAYOPTIONWINDOW, "sayoptionwindow");
	lexAddToken(T_SAYBORDER, "sayborder");
	lexAddToken(T_SAYSCROLLUP, "sayscrollup");
	lexAddToken(T_SAYSCROLLDOWN, "sayscrolldown");
	lexAddToken(T_SAYSETSPACING, "saysetspacing");
	lexAddToken(T_SAYOPTIONCOLOR, "sayoptioncolor");
	lexAddToken(T_SAYREPLYCOLOR, "sayreplycolor");
	lexAddToken(T_SAYRESTART, "sayrestart");
	lexAddToken(T_SAYGETLASTPOS, "saygetlastpos");
	lexAddToken(T_SAYMESSAGETIMEOUT, "saymessagetimeout");

	lexAddToken(T_HIDEMOUSE, "hidemouse");
	lexAddToken(T_SHOWMOUSE, "showmouse");
	lexAddToken(T_MOUSESHAPE, "mouseshape");
	lexAddToken(T_REFRESHMOUSE, "refreshmouse");
	lexAddToken(T_SETGLOBALMOUSEFUNC, "setglobalmousefunc");

	lexAddToken(T_ADDNAMEDEVENT,		"addnamedevent");
	lexAddToken(T_ADDNAMEDHANDLER,	"addnamedhandler");
	lexAddToken(T_CLEARNAMED,			"clearnamed");
	lexAddToken(T_SIGNALNAMED,			"signalnamed");

	lexAddToken(T_ADDKEY, "addkey");
	lexAddToken(T_DELETEKEY, "deletekey");

	lexAddToken(T_SOUNDPLAY,   "soundplay");
	lexAddToken(T_SOUNDPAUSE,  "soundpause");
	lexAddToken(T_SOUNDRESUME, "soundresume");
	lexAddToken(T_SOUNDSTOP,   "soundstop");
	lexAddToken(T_SOUNDREWIND, "soundrewind");
	lexAddToken(T_SOUNDDELETE, "sounddelete");
	lexAddToken(T_SETONEOPTPAUSE, "setoneoptpause");

	lexAddToken(T_SELECTFILELIST, "selectfilelist");

	if(!backwardcompat) {
		lexAddToken(T_TOKENIZE, "tokenize");
	}

	lexAddConstant(C_TEXT_SHADOW,    "textshadow",    T_INT, 0x10000);
	lexAddConstant(C_TEXT_UNDERLINE, "textunderline", T_INT, 0x20000);
	lexAddConstant(C_TEXT_MONOSPACE, "textmonospace", T_INT, 0x40000);
	lexAddConstant(C_TEXT_DIRECT,    "textdirect",    T_INT, 0x01000000);
	lexAddConstant(C_TEXT_NOFILL,    "textnofill",    T_INT, 0x02000000);
	lexAddConstant(C_TEXT_TRUNC,     "texttrunc",     T_INT, 0x04000000);

	lexAddConstant(C_JUSTIFY_LEFT,   "justifyleft",   T_INT, 0);
	lexAddConstant(C_JUSTIFY_RIGHT,  "justifyright",  T_INT, 1);
	lexAddConstant(C_JUSTIFY_CENTER, "justifycenter", T_INT, 2);

	lexAddConstant(C_SOUND_NORMAL,	"soundnormal",		T_INT, 0x0000);
	lexAddConstant(C_SOUND_LOOP,		"soundloop",		T_INT, 0x0001);
	lexAddConstant(C_SOUND_8_BIT,		"sound8bit",		T_INT, 0x0000);
	lexAddConstant(C_SOUND_16_BIT,	"sound16bit",		T_INT, 0x0002);
	lexAddConstant(C_SOUND_MEMORY,	"soundmemory",		T_INT, 0x0100);
	lexAddConstant(C_SOUND_STREAMED, "soundstreamed",	T_INT, 0x0200);
	lexAddConstant(C_SOUND_MONO,		"soundmono",		T_INT, 0x1000);
	lexAddConstant(C_SOUND_STEREO,	"soundstereo",		T_INT, 0x2000);

	// these correspond to movie.h's #defines for movie flags
	lexAddConstant(C_MOVIE_SCALE, "moviescale", T_INT, 1);
	lexAddConstant(C_MOVIE_DIRECT, "moviedirect", T_INT, 2);
	lexAddConstant(C_MOVIE_CENTER, "moviecenter", T_INT, 4);
	lexAddConstant(C_MOVIE_SUBTITLE, "moviesubtitle", T_INT, 8);

	lexAddConstant(C_MOUSE_PRESS, "mousepress", T_INT, 0);
	lexAddConstant(C_MOUSE_RELEASE, "mouserelease", T_INT, 1);
	lexAddConstant(C_MOUSE_ON, "mouseon", T_INT, 2);
	lexAddConstant(C_MOUSE_OFF, "mouseoff", T_INT, 3);
	lexAddConstant(C_MOUSE_HELD, "mouseheld", T_INT, 4);
	lexAddConstant(C_MOUSE_RIGHT, "mouseright", T_INT, 5);

	lexAddConstant(C_BUTTONTAB, "buttontab", T_INT, 1);
	lexAddConstant(C_REGIONTAB, "regiontab", T_INT, 1);

	initLexExtras();
}

static void parseRegion(Procedure *p, NodeList *nodes) {
	//
	// regions are defined as:
	//
	//   region "name", { x, y, x, y, x, y, x, y };
	//
	// meaning if the mouse is clicked in the region defined by the
	// list of points, procedureName is called.
	//
	// Regions are related to the currently selected window.

	if (expectToken('{') == -1)
		parseExpression(p, nodes);
	else ungetToken();

	emitOp(p, nodes, T_START_REGION);

	if (expectToken('{') == -1)
		parseError("'{' expected.");

	if (expectToken('}') == -1) {
		parseExpGroup(p, nodes, 2);

		while (expectToken('}') == -1) {
			if (expectToken(',') == -1)
				parseError("',' expected.");

			parseExpGroup(p, nodes, 2);
		}
	}

	emitOp(p, nodes, T_END_REGION);
}

void parseLibExpression(Procedure *p, NodeList* nodes, int i) {
	switch(i) {
		PARSEEXP(SOUNDPLAY, 2);
		PARSEEXP(SAYGETLASTPOS, 0);
		PARSEEXP(SELECTFILELIST, 2);
		PARSEEXP(TOKENIZE, 3);
		PARSEEXP(CHECKREGION, 1);
	default: parseExtraExpression(p, nodes, i); break;
	}
}

void parseLib(Procedure *p, NodeList* nodes, int i) {
	switch(i) {
		PARSE(MOUSESHAPE, 3);
		PARSEPROC(SETGLOBALMOUSEFUNC, 4, (1 | 2 | 4 | 8));
		PARSE(HIDEMOUSE, 0);
		PARSE(SHOWMOUSE, 0);
		PARSEPROC(REFRESHMOUSE, 1, 1);

		PARSE(DELETEBUTTON, 1);
		PARSE(ADDBUTTONTEXT, 2);
		PARSE(ADDBUTTONGFX, 4);
		PARSEPROC(ADDBUTTONPROC, 5, (2 | 4 | 8 | 16));
		PARSE(ADDBUTTONFLAG, 2);
		PARSEPROC(ADDBUTTONRIGHTPROC, 3, (2 | 4));
		PARSE(ADDBUTTON, 5);

		PARSE(SAYQUIT, 0);
		PARSE(SAYEND, 0);
		PARSE(SAYSTART, 0);
		PARSE(SAYSTARTPOS, 1);
		PARSE(SAYREPLYTITLE, 1);
		PARSE(SAYGOTOREPLY, 1);
		PARSE(SAYREPLY, 2);
		PARSEPROC(SAYOPTION, 2, (2));
		PARSE(SAYMESSAGE, 2);
		PARSE(SAYREPLYWINDOW, 5);
		PARSE(SAYOPTIONWINDOW, 5);
		PARSE(SAYREPLYFLAGS, 1);
		PARSE(SAYOPTIONFLAGS, 1);
		PARSE(SAYBORDER, 2);
		PARSE(SAYSCROLLUP, 6);
		PARSE(SAYSCROLLDOWN, 6);
		PARSE(SAYSETSPACING, 1);
		PARSE(SAYOPTIONCOLOR, 3);
		PARSE(SAYREPLYCOLOR, 3);
		PARSE(SAYRESTART, 0);
		PARSE(SAYMESSAGETIMEOUT, 1);

		PARSE(CREATEWIN, 5);
		PARSE(FILLWIN, 3);
		PARSE(FILLRECT, 7);
		PARSE(FILLWIN3X3, 1);
		PARSE(DELETEWIN, 1);
		PARSE(SELECTWIN, 1);
		PARSE(RESIZEWIN, 5);
		PARSE(SCALEWIN, 5);
		PARSE(DISPLAY, 1);
		PARSE(DISPLAYRAW, 1);
		PARSE(DISPLAYGFX, 5);
		PARSE(LOADPALETTETABLE, 1);
		PARSE(FADEIN, 1);
		PARSE(FADEOUT, 1);
		PARSE(SHOWWIN, 0);
		PARSE(GOTOXY, 2);
		PARSE(PRINT, 1);
		PARSE(FORMAT, 6);
		PARSE(PRINTRECT, 3);  // printrect("string", width, flags)
		PARSE(SETFONT, 1);
		PARSE(SETTEXTFLAGS, 1);
		PARSE(SETTEXTCOLOR, 3);
		PARSE(SETHIGHLIGHTCOLOR, 3);
		PARSE(STOPMOVIE, 0);
		PARSE(PLAYMOVIEALPHA, 2);
		PARSE(PLAYMOVIEALPHARECT, 6);
		PARSE(PLAYMOVIE, 1);
		PARSE(MOVIEFLAGS, 1);
		PARSE(PLAYMOVIERECT, 5);

		PARSEPROC(ADDREGIONPROC, 5, (2 | 4 | 8 | 16));
		PARSE(ADDREGIONFLAG, 2);
		PARSEPROC(ADDREGIONRIGHTPROC, 3, (2 | 4));
		PARSE(DELETEREGION, 1);
	case T_ADDREGION:
		parseRegion(p, &p->nodes);
		break;
		PARSE(ACTIVATEREGION, 2);

		PARSEPROC(ADDNAMEDEVENT, 2, (2));
		PARSEPROC(ADDNAMEDHANDLER, 2, (2));
		PARSE(CLEARNAMED, 1);
		PARSE(SIGNALNAMED, 1);

		PARSEPROC(ADDKEY, 2, (2));
		PARSE(DELETEKEY, 1);

		PARSE(SOUNDPLAY,   2);
		PARSE(SOUNDPAUSE,  1);
		PARSE(SOUNDRESUME, 1);
		PARSE(SOUNDSTOP,   1);
		PARSE(SOUNDREWIND, 1);
		PARSE(SOUNDDELETE, 1);

		PARSE(SETONEOPTPAUSE, 1);
	default:
		parseExtraStatement(p,  nodes, i);
		break;
	}
}

int writeLibStatement(NodeList *n, int i, FILE *f) {
	switch(n->nodes[i].token) {
		ST(HIDEMOUSE);
		ST(SHOWMOUSE);
		EXP(MOUSESHAPE, 3);
		EXPPROC(REFRESHMOUSE, 1);

		EXPPROC(SETGLOBALMOUSEFUNC, 4);

		EXP(DELETEBUTTON, 1);
		EXP(ADDBUTTON, 5);
		EXP(ADDBUTTONGFX, 4);
		EXP(ADDBUTTONTEXT, 2);

		EXPPROC(ADDBUTTONPROC, 5);
		EXPPROC(ADDBUTTONRIGHTPROC, 3);

		ST(SAYQUIT);
		ST(SAYEND);
		ST(SAYSTART);
		EXP(SAYSTARTPOS, 1);

		EXP(SAYREPLYTITLE, 1);
		EXP(SAYGOTOREPLY, 1);
		EXP(SAYREPLY, 2);
		EXP(SAYREPLYWINDOW, 5);
		EXP(SAYOPTIONWINDOW, 5);
		EXP(SAYREPLYFLAGS, 1);
		EXP(SAYOPTIONFLAGS, 1);
		EXP(SAYBORDER, 2);
		EXP(SAYSCROLLUP, 6);
		EXP(SAYSCROLLDOWN, 6);
		EXP(SAYSETSPACING, 1);
		EXP(SAYOPTIONCOLOR, 3);
		EXP(SAYREPLYCOLOR, 3);
		EXP(SAYRESTART, 0);
		EXP(SAYMESSAGETIMEOUT, 1);

		EXPPROC(SAYOPTION, 2);
		EXP(SAYMESSAGE, 2);

		EXP(CREATEWIN, 5);
		EXP(DELETEWIN, 1);
		EXP(SELECTWIN, 1);
		EXP(RESIZEWIN, 5);
		EXP(SCALEWIN, 5);
		EXP(FILLWIN, 3);
		EXP(FILLRECT, 7);
		EXP(FILLWIN3X3, 1);
		EXP(DISPLAY, 1);
		EXP(DISPLAYRAW, 1);
		EXP(DISPLAYGFX, 5);
		EXP(LOADPALETTETABLE, 1);
		EXP(FADEIN, 1);
		EXP(FADEOUT, 1);
		EXP(GOTOXY, 2);
		EXP(PRINT, 1);
		EXP(PRINTRECT, 3);
		EXP(FORMAT, 6);
		EXP(SETFONT, 1);
		EXP(SETTEXTFLAGS, 1);
		EXP(SETTEXTCOLOR, 3);
		EXP(SETHIGHLIGHTCOLOR, 3);
		EXP(SHOWWIN, 0);
		EXP(STOPMOVIE, 0);
		EXP(MOVIEFLAGS, 1);
		EXP(PLAYMOVIE, 1);
		EXP(PLAYMOVIERECT, 5);
		EXP(PLAYMOVIEALPHA, 2);
		EXP(PLAYMOVIEALPHARECT, 6);

		EXPPROC(ADDREGIONPROC, 5);
		EXPPROC(ADDREGIONRIGHTPROC, 3);

	case T_ADDREGION: {
		int num = 0;

		i++;
		if (n->nodes[i].token != T_START_REGION) {
			i = writeExpression(n, i, f);
			num++;
			if (n->nodes[i].token != T_START_REGION)
				parseError("No starting region.");
		}

		i++;

		while(n->nodes[i].token != T_END_REGION) {
			i = writeExpression(n, i, f);
			num++;
		}

		i++;
		writeInt(num, f);        // write number of points
		writeOp(O_ADDREGION, f);    // write op code
		break;
					  }
					  EXP(DELETEREGION, 1);
					  EXP(ACTIVATEREGION, 2);

					  EXPPROC( ADDNAMEDEVENT, 2);
					  EXPPROC( ADDNAMEDHANDLER, 2);
					  EXP( CLEARNAMED, 1);
					  EXP( SIGNALNAMED, 1);

					  EXPPROC(ADDKEY, 2);
					  EXP(DELETEKEY, 1);

	case T_SOUNDPLAY:
		WEXP(O_SOUNDPLAY, 2);
		writeOp(O_POP, f);
		break;

		EXP(SOUNDPAUSE,  1);
		EXP(SOUNDRESUME, 1);
		EXP(SOUNDSTOP,   1);
		EXP(SOUNDREWIND, 1);
		EXP(SOUNDDELETE, 1);
		EXP(SETONEOPTPAUSE, 1);
	case T_ADDBUTTONFLAG:
		if(!backwardcompat) {
			WEXP(O_ADDBUTTONFLAG, 2);
			break;
		}
	default: i = writeExtraStatement(n, i, f); break;
	}
	return i;
}

int writeLibExpression(NodeList *n, int i, FILE *f) {
	switch(n->nodes[i].token) {
		EXP(SOUNDPLAY, 2);
		EXP(SAYGETLASTPOS, 0);
		EXP(SELECTFILELIST, 2);
		EXP(TOKENIZE, 3);
		EXP(CHECKREGION, 1);

	default: i = writeExtraExpression(n, i, f); break;
	}
	return i;
}
