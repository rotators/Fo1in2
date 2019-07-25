/*

	Generic Encounters

*/

#ifndef MAPENC_H
#define MAPENC_H

/************************************************
    Generic Defines
************************************************/

#define enc_group_angle(x) 			if (group_angle == 0) then begin \
										x := 3;\
									end\
									else if (group_angle == 1) then begin\
										x := 4;\
									end\
									else if (group_angle == 2) then begin\
										x := 5;\
									end\
									else if (group_angle == 3) then begin\
										x := 0;\
									end\
									else if (group_angle == 4) then begin\
										x := 1;\
									end\
									else if (group_angle == 5) then begin\
										x := 2;\
									end



#endif // MAPENC_H
