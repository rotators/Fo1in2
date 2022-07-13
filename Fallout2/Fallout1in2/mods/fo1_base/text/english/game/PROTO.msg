#
# Messages for Prototypes
#
# strings
#
{10}{}{<None>}

#
# Material Types
#
{100}{}{Glass}
{101}{}{Metal}
{102}{}{Plastic}
{103}{}{Wood}
{104}{}{Dirt}
{105}{}{Stone}
{106}{}{Cement}
{107}{}{Leather}

#
# Item Types
#
{150}{}{Armor}
{151}{}{Container}
{152}{}{Drug}
{153}{}{Weapon}
{154}{}{Ammo}
{155}{}{Misc Item}
{156}{}{Key}

#
# Scenery Types
#
{200}{}{Portal}
{201}{}{Stairs}
{202}{}{Elevator}
{203}{}{Ladder Bottom}
{204}{}{Ladder Top}
{205}{}{Generic Scenery}

#
# Damage Code Types
#
{250}{}{normal_dam}
{251}{}{laser}
{252}{}{fire}
{253}{}{plasma}
{254}{}{electrical}
{255}{}{emp}
{256}{}{explosion}

#
# Caliber Types for weapons
#
{300}{}{None}
{301}{}{Rocket}
{302}{}{Flamethrower Fuel}
{303}{}{C Energy Cell}
{304}{}{D Energy Cell}
{305}{}{.223}
{306}{}{5mm}
{307}{}{.40 cal}
{308}{}{10mm}
{309}{}{.44 cal}
{310}{}{14mm}
{311}{}{12-gauge}
{312}{}{9mm}
{313}{}{BB}
{314}{}{.45 cal}
{315}{}{2mm}
{316}{}{4.7mm caseless}
{317}{}{HN needler}
{318}{}{7.62mm}

#
# Race Types
#
{350}{}{Caucasian}
{351}{}{African}

#
# Body Types
#
{400}{}{Biped}
{401}{}{Quadruped}
{402}{}{Robotic}
#
# Kill Types names
#
# Note: These were moved to 1450+ to handle new ones!
{450}{}{Men}
{451}{}{Women}
{452}{}{Children}
{453}{}{Super Mutants}
{454}{}{Ghouls}
{455}{}{Brahmin}
{456}{}{Radscorpions}
{457}{}{Rats}
{458}{}{Floaters}
{459}{}{Centaurs}
{460}{}{Robots}
{461}{}{Dogs}
{462}{}{Manti}
{463}{}{DeathClaws}
{464}{}{Plant}
#
# Kill type info descriptions
#
{465}{}{This line shows the number of male humans you have killed during the course of your adventures.}
{466}{}{This line shows the number of female humans you have killed during the course of your adventures.}
{467}{}{This line shows the number of young human children you have killed during the course of your adventures.  You cad.}
{468}{}{The number of Super Mutants you have slain during the course of your adventures.}
{469}{}{This line shows the number of male and female ghoul mutants you have killed during the course of your adventures.}
{470}{}{This line shows the number of Brahmin (mutated cows) you have chopped up during your travels.}
{471}{}{The number of mutated Radscorpions that you have put to death during your adventure.}
{472}{}{The number of rats you have killed.  Includes all members of the rat family.}
{473}{}{This is the number of mutant Floaters that you have put to death.}
{474}{}{Your tally of dead mutant Centaurs.}
{475}{}{This is the number of robots that you have destroyed or dismantled.}
{476}{}{The total number of dogs that you have sent to the great kennel in the sky.}
{477}{}{This line shows the total number of dead Manti, or large mutated mantis-like insects, that you have squashed so far.}
{478}{}{This line shows that you have slain the Deathclaw, and any of his spawn.}
{479}{}{The number of plants whose quest for sunlight you have terminated.}

#
# Use text
#
{480}{}{You see: %s.}

#
# Use Container text
#
{485}{}{You search the %s.}
{486}{}{You close the %s.}
{487}{}{It is locked.} # new

#
# Look text
#
{490}{}{You see: %s.}
{491}{}{You see a dead: %s.}
{492}{}{You see the remains of: %s.}
{493}{}{You see nothing out of the ordinary.}

#
# Examine text
#
{500}{}{Dead}
{501}{}{Almost Dead}
{502}{}{Severely Wounded}
{503}{}{Wounded}
{504}{}{Unhurt}

#
# Examine text messages
#
{510}{}{AC Mod: %d}
{511}{}{DR Mod: %d}
{512}{}{Dmg Mod: %d/%d}
{518}{}{You look: %s }
{519}{}{%s %s }
{520}{}{You look: %s.}
{521}{}{%s %s.}
{522}{}{He looks: %s }
{523}{}{She looks: %s }
{524}{}{It looks: %s }
# (note: hps are short for hit-points)
{525}{}{%s has %d/%d hps.}
# (note: this is for guns that have ammo)
{526}{}{It has %d/%d shots of %s.}
{530}{}{and has crippled limbs.}  # These append to lines 500-504
{531}{}{but has crippled limbs.}
{532}{}{and have crippled limbs.}
{533}{}{but have crippled limbs.}
# (note: hps are short for hit-points)
{535}{}{He has %d/%d hps}
{536}{}{She has %d/%d hps}
{537}{}{It has %d/%d hps}
{540}{}{It weighs %d pounds.}
{541}{}{It weighs %d pound.}
{544}{}{, }
{545}{}{.}
{546}{}{ and is wielding a %s.}
{547}{}{ and is wielding a %s with %d/%d shots of %s.}
{548}{}{The car doesn't look like it's working right now.}
{549}{}{The car is running at %d%% power.}

#
# Examine text error messages
#
{550}{}{\nError: lookup_val out of range!}
{551}{}{\nError: obj_examine: proto_ptr failed!}

#
# Use text messages
#
{580}{}{You use the %s.}
{581}{}{You use the %s on %s.}
{582}{}{That does nothing.}
{583}{}{To your dismay, you realize that it is already dead.}
{584}{}{As you reach down, you realize that it is already dead.}
{585}{}{Alas, you are too late.} # This is relating to a critter being dead.
{586}{}{That won't work on the dead.}
{587}{}{You light the flare.}
{588}{}{The flare is already lit.}
{589}{}{You set the timer.}
{590}{}{The timer is already ticking!}
{595}{}{You charge the car with more power.}
{596}{}{The car is already full of power.}
{597}{}{The doorway seems to be blocked.}

#
# Experience-Point messages
#
{620}{}{You gain %d experience points for killing: %s.}
{621}{}{%syou earn %d exp. points.}
{622}{}{For defeating your enemies, }  # 622-626 prepend to line 621
{623}{}{For slaying your opponents, }
{624}{}{You are victorious in combat, }
{625}{}{For crushing your enemies, }
{626}{}{For destroying your enemies without taking a scratch, }

#
# Dialog messages
#
{650}{}{[Done]}
{651}{}{[More]}
{652}{}{More}
{653}{}{[Back]}
{654}{}{Back}     # changed number from 653
{655}{}{Go on}    # new
{656}{}{Err...}   # new
{660}{}{You can't see there.}
{661}{}{Too far away.}
{670}{}{Okay.}    # F2: Used in PM: CombatAI settings
{671}{}{Sure.}    # F2: Used in PM: CombatAI settings
{672}{}{As you wish.}       # F2: Used in PM: CombatAI settings
{673}{}{Whatever you say.}  # F2: Used in PM: CombatAI settings
{674}{}{I'll try.}          # F2: Used in PM: CombatAI settings
{675}{}{I can't do that.}   # F2: Used in PM: CombatAI settings
{676}{}{I don't think I can do that.}   # F2: Used in PM: CombatAI settings
{677}{}{Arf!}   # F2: Used in PM: CombatAI settings -- RoboDog
{678}{}{Woof!}  # F2: Used in PM: CombatAI settings -- RoboDog

#
# Not Enough AP message
#
{700}{}{You don't have enough action points.}
#
# Book messages
#
{800}{}{You read the book.}
{801}{}{You learn nothing new.}
{802}{}{You learn new science information.}
{803}{}{You learn a lot about repairing broken electronics.}
{804}{}{You learn new ways to heal injury.}
{805}{}{You learn how to handle your guns better.}
{806}{}{You learn a lot about wilderness survival.}
#
# Use on messages (and some extra stuff that Jesse needed)
#
{900}{}{The supplies in the Doctor's Bag run out.}
{901}{}{The supplies in the First Aid Kit run out.}
{902}{}{You cannot do that in combat.}
{903}{}{This person will not barter with you.}
{904}{}{This person has nothing to tell you about.}
{905}{}{You cannot pick up that item. You are at your maximum weight capacity.}
{910}{}{The supplies in the Paramedic's Bag run out.}
{911}{}{The supplies in the Field Medic First Aid Kit run out.}
{913}{}{This critter can't carry anything.}


#
# Kill Types names
#
{1450}{}{Men}
{1451}{}{Women}
{1452}{}{Children}
{1453}{}{Super Mutants}
{1454}{}{Ghouls}
{1455}{}{Brahmin}
{1456}{}{Radscorpions}
{1457}{}{Rats}
{1458}{}{Floaters}
{1459}{}{Centaurs}
{1460}{}{Robots}
{1461}{}{Dogs}
{1462}{}{Manti}
{1463}{}{DeathClaws}
{1464}{}{Plants}
{1465}{}{Geckos}
{1466}{}{Aliens}
{1467}{}{Giant Ants}
{1468}{}{Big Bad Boss}
#
# Kill type info descriptions
#
{1469}{}{This line shows the number of male humans you have killed during the course of your adventures.}
{1470}{}{This line shows the number of female humans you have killed during the course of your adventures.}
{1471}{}{This line shows the number of young human children you have killed during the course of your adventures.  You cad.}
{1472}{}{The number of Super Mutants you have slain during the course of your adventures.}
{1473}{}{This line shows the number of male and female ghoul mutants you have killed during the course of your adventures.}
{1474}{}{This line shows the number of Brahmin (mutated cows) you have chopped up during your travels.}
{1475}{}{The number of mutated Radscorpions that you have put to death during your adventure.}
{1476}{}{The number of rats you have killed.  Includes all members of the rat family.}
{1477}{}{This is the number of mutant Floaters that you have put to death.}
{1478}{}{Your tally of dead mutant Centaurs.}
{1479}{}{This is the number of robots that you have destroyed or dismantled.}
{1480}{}{The total number of dogs that you have sent to the great kennel in the sky.}
{1481}{}{This line shows the total number of dead Manti, or large mutated mantis-like insects, that you have squashed so far.}
{1482}{}{This line shows that you have slain the Deathclaw, and any of his spawn.}
{1483}{}{This line shows the number of plants you have weeded out of the world.}
{1484}{}{The number of cute lizards you have wiped off the face of the planet.}
{1485}{}{A count of alien things slain by your hand.}
{1486}{}{The number of insectoids that you have exterminated in the wasteland.}
{1487}{}{The count of genetically-engineered total homicidal maniac cyborg bodyguards you have wasted.}