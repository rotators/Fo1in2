/*

	The Glow defines

*/

#ifndef GLOW_H
#define GLOW_H

/************************************************
    Generic Defines
************************************************/

#define play_sfx_doorcard	if (random(0,1) == 1) then 	\
							   play_sfx("SLDOORSA");	\
							else						\
							   play_sfx("SLDOORSB")
							   
#define play_sfx_doorfail 	if (random(0,1) == 1) then 	\
							   play_sfx("SNDOORSA");	\
							else						\
							   play_sfx("SNDOORSB")

#endif // GLOW_H
