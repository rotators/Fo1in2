/*

	Generic Encounters

*/

#ifndef MAPENC_H
#define MAPENC_H

/************************************************
    Generic Defines
************************************************/

// All Map Vars need to start w/ MVAR_
#define MVAR_Hostile_Total             	(0)   // Number of monsters created

//==================================================================

#define FixRotationArc(X)           while (X < 0) do begin      \
                                        X += 6;                 \
                                    end                         \
                                    if (X > 5) then             \
                                        X := X%6
										
#define enc_group_angle(x) 			if (group_angle == 0) then begin 		\
										x := 3;								\
									end										\
									else if (group_angle == 1) then begin	\
										x := 4;								\
									end										\
									else if (group_angle == 2) then begin	\
										x := 5;								\
									end										\
									else if (group_angle == 3) then begin	\
										x := 0;								\
									end										\
									else if (group_angle == 4) then begin	\
										x := 1;								\
									end										\
									else if (group_angle == 5) then begin	\
										x := 2;								\
									end



#endif // MAPENC_H
