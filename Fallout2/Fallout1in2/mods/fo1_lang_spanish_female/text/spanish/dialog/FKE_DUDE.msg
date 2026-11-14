# This file's lines are used when performing First Aid or Doctor skill on self, if feature enabled.
#
# 1 Antidote takes away 75 Poison Level
# 1 RadAway takes away 150 Irradiation Level
#
{100}{}{Eres incapaz de determinar si estás envenenada o irradiada.}

{101}{}{Estás irradiada y envenenada, pero no sabes en qué medida.}
{102}{}{Estás irradiada, pero no sabes en qué medida.}
{103}{}{Estás envenenada, pero no sabes en qué medida.}

{104}{}{Estás }  # 104 will be completed with lines below.

{105}{}{mínimamente}
{106}{}{ligeramente}
{107}{}{levemente}
{108}{}{moderadamente}
{109}{}{muy}
{110}{}{extremadamente}
{111}{}{peligrosamente}
{112}{}{mortalmente}

{113}{}{ irradiada}
{114}{}{.}  # Used after line X if player isn't also poisoned...
{115}{}{ y }  # ...but if also poisoned, this is used.

{116}{}{Nivel de radiación: }
{117}{}{ rads.}
{118}{}{ Estás envenenada a un nivel }

{119}{}{No estás irradiada o envenenada.}

{200}{}{}

##
##
# for displaying radiation and poison level of dude's body
# code by Cubik2k and Wasteland Ghost
#
# FALLOUT RADIATION EFFECTS TABLE:
# 	Rads 	        Message 		healper  hp 	ST 	PE 	EN 	CH 	IN 	AG
#   1 49		insignificant
#   50 100		slight
#   101 149		mild
# 	0-149 		very nauseous 								
# 	150-299 	slightly fatigued 			-1 					
# 	300-449 	vomiting does not stop 	-3 		-1 					-1
# 	450-599 	hair is falling out 	-5 	-5 	-2 		-1 			-2
# 	600-999 	skin is falling off 	-10 	-15 	-4 	-3 	-3 	-3 	-1 	-5
# 	1000+ 		intense agony 		-10 	-20 	-6 	-5 	-5 	-5 	-3 	-6 
#
#RADIATION:
#
#150 to 299 - next level to name!
#
#   300 400		moderate
#   400 500		heavily
#   500 600
#   600 700
#   700 800		extreme
#   800 900		dangerous
#   900 1000	excessive
#   1000+		fatal
#
