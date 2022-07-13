# For lines 177 and 180 and 181, spaces are intentional.
# Line 177 is prepended to encounter type. (they begin at 183 below)
{177}{}{You encounter }
{178}{}{Yes.}
{179}{}{No.}
{180}{}{You earn }
{181}{}{ experience for successful use of your Outdoorsman skill.}
# Line 182 is appended after 177 and the encounter type. Period and space is intentional.
{182}{}{. Do you wish to engage?}
# These are apended to line 177.
{183}{}{Floaters}
{184}{}{Manti}
{185}{}{Rats}
{186}{}{Peasants attacked by Raiders}

{289}{}{You stumble across a pack of hungry geckos.}
{290}{}{You are attacked by fire geckos!}
{291}{}{You stumble across vicious fire geckos.}

#
# 100 to 103 are NOT USED, looks like it was old code for finding the Radscorpion Cave from the worldmap.
#
{100}{}{From the look of things, they can't have traveled very far. They must have a lair nearby.}
{101}{}{They appear to have traveled here from somewhere nearby.}
{102}{}{It looks like they traveled from somewhere far north of here.}
{103}{}{Apparently, they were just wandering the wastes.}

{106}{}{You have stumbled upon a large pack of radscorpions!}
{107}{}{You have stumbled upon a pack of Rad Scorpions.}
{108}{}{You have stumbled upon a family of Mole Rats.}

# DEHYDRATION ENCOUNTERS
{109}{}{You manage to avoid a serious case of dehydration by searching for water. The search takes an additional hour.}
{110}{}{You manage to avoid a serious case of dehydration by searching for water. The search takes an additional }
{111}{}{ hours.}
{112}{}{Your water supply runs low, and your search of an hour fails to locate more water. Severe dehydration sets in, causing you }
{113}{}{ points of health damage.}
{114}{}{Your water supply runs low, and your search of }
{115}{}{ hours fails to locate more water. Severe dehydration sets in causing you }
{116}{}{ points of health damage.}
{117}{}{You search for water in the high desert landscape for an hour, but you do not find enough to fully satisfy your thirst. You have sustained a point of  health damage.}
{118}{}{You search for water in the high desert landscape for an hour, but you do not find enough to fully satisfy your thirst. You have sustained }
{119}{}{ points of health damage.}
{120}{}{You search for water in the high desert landscape for }
{121}{}{ hours, but you do not find enough to fully satisfy your thirst. You have sustained a point of health damage.}
{122}{}{You search for water in the high desert landscape for }
{123}{}{ hours, but you do not find enough to fully satisfy your thirst. You have sustained }
{124}{}{ points of health damage.}

{125}{}{You manage to avoid dehydration due to your supplies of water.}

{1250}{}{You manage to avoid dehydration due to your supplies of }
{1251}{}{.}
{1160}{}{one point of health damage.}

# CRITICAL SUCCESS ON OUTDOORSMAN CHECK
{147}{}{You manage to avoid dehydration by searching for water. The search takes 1 hour.}
{138}{}{ You refill your }
{159}{}{flasks}
{160}{}{ with the drinkable water.}
{165}{}{You earn }
{166}{}{ experience for successful use of your Outdoorsman skill.}

# NORTH_TABLE ENCOUNTERS
#
#
# North1
#
# if pass Perception check or have Awareness:
#   197 Uh-oh... a raiding party!
# else is:
{105}{}{AMBUSH!!!}
#
# North2
#
{104}{}{You have stumbled into a fierce battle between radscorpions and mole rats.}
#
# North3
#
#
# North6
#
# -Dehydration-
#
# SOUTH_TABLE ENCOUNTERS
#
# South1 -- change this encounter to something else??
#
{131}{}{STAMPEDE!!!}
#
# South2
#
{132}{}{You stumble onto a very large pack of radscorpions!}
#
# South3
#
# -Dehydration-
#
# South4 -- change this encounter to something else
#
# 143 "Raiders!!!"
#
# South5
#
{144}{}{You have stumbled into a large gathering of mole rats.}
#
# South6
#
{145}{}{You encounter a band of wild radscorpions.}
#
#
# SHADY ENCOUNTERS
#
#
# Shady1
#
{146}{}{You encounter some peasants under attack.}
#
# Shady2
#
# -Dehydration-
#
# Shady3
#
{169}{}{You stumble into a family of radscorpions.}
#
# Shady4
#
{170}{}{You come across a traveling merchant and guards.}
#
# unless he's dead, then you get
#
{305}{}{You come across what's left of merchant Duc's hostile guards.}
#
# once that has been seen, call Shady3
#
# Shady5
#
{175}{}{You encounter a traveler.}
# or if killed,
{171}{}{You encounter a dead traveler.}
#
# else call Shady2
#
# Shady
#
{126}{}{You've run into some radscorpions hunting mole rats.}
{127}{}{Skinny hostile humanoids with greenish skin approach.}
{128}{}{Junk and rocks are scattered about. You wonder if anything of value could remain...}
#
# UNUSED ENTRY:
{129}{}{A lone radscorpion ambushes you!}
#
{130}{}{You note a partially-eaten corpse here.}
{134}{}{A pack of nasty radscorpions strikes from the desert!}
{135}{}{You encounter a group of guardsmen on patrol.}
{136}{}{You come across a merchant with several guards.}
{174}{}{You come across the remnants of a merchant and his guards.}
{137}{}{You see a peasant herding several brahmin.}
{139}{}{Radscorpions hunt mole rats among the ruined city walls.} # Sduibek, Fallout ''Fixt''
{172}{}{You have stumbled across some items laying on the ground.}
{176}{}{You have stumbled across a small patch of ruined and deserted buildings.}
#
#
# RAIDER_TABLE ENCOUNTERS
#
#
# Raider1
#
{133}{}{Raiders ambush you!}
#
# Raider2 - half chance of either msg displayed, but encounter the same
#
{143}{}{Raiders!!!}
{197}{}{Uh-oh... a raiding party!}
#
# Raider3
#
{173}{}{You spot the remains of a caravan, being looted by raiders.}
#
# Raider4
#
{310}{}{A small group of raiders attack!}
#
# Raider5 - 198 always, plus 196 half the time
#
{198}{}{You see a lone raider in the distance.}
{196}{}{Radscorpions, incoming!}
#
# Raider6 - displays and runs both (because bodies are empty)
#
{199}{}{You come upon the remains of a battlefield, with bodies strewn about.}
#plus 196
#
#
{223}{}{You spot a wandering pack of wild coyotes.}
{200}{}{Radscorpions, incoming!}
{224}{}{You notice several individuals scouting about.}
{225}{}{You come across a small party of merchants and guards.}
{226}{}{You see a small war going on - men versus mutants!}
{227}{}{A tremendous horde of radscorpions is coming this way!}
#
{250}{}{Several men in Power Armor are approaching you.}
{251}{}{You see a group of merchants and guards.}
{252}{}{You see a vicious battle underway between several desert raiders and a group of men in Power Armor.}
{253}{}{You see several mutants exploring a patch of hostile ground.}
{254}{}{You see some strange creatures ahead...}
{256}{}{A patrol unit of Super Mutants is passing close by!}

{257}{}{You spot the ruins of a tiny village.}

# UNUSED ENTRY:
{255}{}{You find some items.}

{279}{}{Ahead you can see junk strewn about the sands.}
{280}{}{You stumble upon a Super Mutant war party.}
{281}{}{You stumble upon a pack of bizarre creatures.}
{282}{}{You stumble across a pack of hungry radscorpions.}
{283}{}{You feel nauseous, and the air seems to waver with heat. A mutated creature suddenly approaches!}
{284}{}{You have stumbled across a few bizarre mutant creatures.}
{285}{}{You encounter something out of an old Sci-Fi movie.}
{286}{}{The Deathclaw!!}
{287}{}{You stumble into a migrating pack of radscorpions. They seem to be fleeing from...}
{288}{}{You encounter a mutated creature of the desert.}
#
{299}{}{You see several radscorpions some distance away.}
{300}{}{You run across a ragged peasant.}
{301}{}{You encounter a mole rat.}

# was: "The Deathclaw!!"
{302}{}{A young Deathclaw seems to think you are lunch.}

{303}{}{You stumble into a migrating pack of radscorpions.}
#
{306}{}{A patrol unit of mutants is passing close by. Along with them are some strange creatures!}
{307}{}{You are ambushed by a small Super Mutant war party.}
{308}{}{Looks like you've stumbled into a vicious gang war!}
{309}{}{A group of hostile gangers bursts forth!}
{311}{}{A small group of gangers attack!}
{313}{}{You are suddenly attacked by a swarm of mutated manti!}

# UNUSED ENTRY:
{312}{}{You are suddenly attacked by rats!}

# SPECIAL ENCOUNTERS TEXT:
{314}{}{Hey! They're really out there.}
{315}{}{You see an overturned truck in the distance.}
{316}{}{You stumble across some wrecked cars in the middle of the wasteland.}
{317}{}{To the northeast you spot a police box.}
{318}{}{You come across a heard of wild brahmin. You feel there is something wrong...}
#
# Fo1in2:
{400}{}{You have stumbled upon a group of geckos.}
{401}{}{You have stumbled upon a group of golden geckos.}
{402}{}{Bounty hunters!}
{403}{}{You see hunters in the distance.}
{404}{}{A tribal war party looking for revenge!}
