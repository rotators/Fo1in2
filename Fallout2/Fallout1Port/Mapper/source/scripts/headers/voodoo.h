#ifndef VOODOO_H
#define VOODOO_H
//
// memory editing macros
//

// This will disable running the credits after the endgame slides:
#define VOODOO_mode_fo1_ending						\
               write_int( 0x4A4343, 0x90909090); 	\
               write_byte(0x4A4347, 0x90)

// This will disable the "You encounter: ..." message:
#define VOODOO_disable_YouEncounter_message 		\
               write_int( 0x4C1011,  0x90909090); 	\
               write_byte(0x4C1015, 0x90); 			\
               write_int( 0x4C1042,  0x90909090); 	\
               write_byte(0x4C1046, 0x90)

#endif // VOODOO_H //
