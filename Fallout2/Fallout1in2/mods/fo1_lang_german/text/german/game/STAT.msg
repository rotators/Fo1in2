#
#    Messages from stat.c
#
#
#    STAT NAMES
#
{100}{}{St�rke}
{101}{}{Wahrnehmung}
{102}{}{Ausdauer}
{103}{}{Charisma}
{104}{}{Intelligenz}
{105}{}{Beweglichkeit}
{106}{}{Gl�ck}
{107}{}{Trefferpunkte}
{108}{}{Aktionspunkte}
{109}{}{R�stung}
{110}{}{Schaden ohne Bewaffnung}
{111}{}{Schaden im Nahkampf}
{112}{}{Tragekapazit�t}
{113}{}{Reaktion}
{114}{}{Heilung}
{115}{}{Kritische Treffer}
{116}{}{Bessere kritische Treffer}
{117}{}{Verletzungsschwelle}
{118}{}{Verletzungsschwelle - Laser}
{119}{}{Verletzungsschwelle - Feuer}
{120}{}{Verletzungsschwelle - Plasma}
{121}{}{Verletzungsschwelle - Elektrisch}
{122}{}{Verletzungsschwelle - EMP}
{123}{}{Verletzungsschwelle - Explosion}
{124}{}{Verletzungsresistenz}
{125}{}{Verletzungsresistenz - Laser}
{126}{}{Verletzungsresistenz - Feuer}
{127}{}{Verletzungsresistenz - Plasma}
{128}{}{Verletzungsresistenz - Elektrisch}
{129}{}{Verletzungsresistenz - EMP}
{130}{}{Verletzungsresistenz - Explosion}
{131}{}{Strahlungsresistenz}
{132}{}{Giftresistenz}
{133}{}{Alter}
{134}{}{Geschlecht}
{135}{}{Aktuelle Trefferpunkte}
{136}{}{Aktueller Vergiftungsgrad}
{137}{}{Aktueller Verstrahlungsgrad}
#
#    STAT DESCRIPTIONS
#
# @ Basic stats @
#
# Strength
{200}{}{Rohe k�rperliche Gewalt. Gro�e St�rke ist f�r k�rperbetonte Figuren wichtig. Beeinflusst: Trefferpunkte, Schaden im Nahkampf und Tragekapazit�t.}
# Perception
{201}{}{F�higkeit, ungew�hnliche Dinge zu sehen, zu h�ren, zu schmecken und wahrzunehmen. Eine gute Wahrnehmung ist z.B. f�r Scharfsch�tzen wichtig. Beeinflusst: Reaktions- und Distanzkampffaktoren.}
# Endurance
{202}{}{Kondition und Belastbarkeit. Eine Figur mit hoher Ausdauer �berlebt, wo andere l�ngst sterben. Beeinflusst: Trefferpunkte, Resistenz gegen Gift u. Strahlung, Heilung, Zusatztrefferpunkte pro Level.}
# Charisma
{203}{}{Kombination aus �u�erer Erscheinung und Charme. Ein ausgepr�gtes Charisma ist f�r Figuren wichtig, die Menschen mit Worten beeinflussen wollen. Beeinflusst: Reaktionen von inaktiven Figuren und Preise beim Handeln.}
# Intelligenz
{204}{}{Wissen, Weisheit und schnelles Denkverm�gen. Eine hohe Intelligenz ist f�r jede Figur wichtig. Beeinflusst: Anzahl der neuen F�higkeitspunkte pro Level, Dialogoptionen und viele F�higkeiten.}
# Agility
{205}{}{Koordination und geschickte Bewegung. Eine hohe Beweglichkeit ist f�r jede aktive Figur wichtig. Beeinflusst: Aktionspunkte, R�stung, Reaktion und viele F�higkeiten.}
# Luck
{206}{}{Schicksal oder Karma. Ein extrem hoher oder niedriger Gl�ckswert wirkt sich auf irgendeine Art auf die Figur aus. Ereignisse und Situationen �ndern sich in Abh�ngigkeit davon, wie viel oder wenig Gl�ck eine Figur hat.}
#
# Derived/Non Derived stats
#
# Maximum Hit Points
{207}{}{Die Verletzungen, die deine Figur verkraften kann, bevor sie stirbt. Wenn du null oder weniger Trefferpunkte erreichst, bist du tot.}
# Maximum Action Points
{208}{}{Die Anzahl der Aktionen, die eine Figur durchf�hren kann, wenn sie am Zug ist.}
# Armor Class
{209}{}{Beeinflusst die Wahrscheinlichkeit, dass diese Figur getroffen wird.}
# Unarmed Damage
{210}{}{Der zus�tzliche Schaden, den deine Figur im Nahkampf anrichten kann.}
{211}{}{Der zus�tzliche Schaden, den deine Figur im Nahkampf anrichten kann.}
# Carry Weight
{212}{}{Das H�chstgewicht der Ausr�stung, die deine Figur tragen kann, angegeben in Pfund.}
# Sequence
{213}{}{Legt fest, wie schnell deine Figur im Kampf reagieren kann.}
# Healing Rate
{214}{}{Am Ende eines jeden Tages heilt deine Figur einen Trefferpunkt mit einem Heilungspunkt. Wenn du dich ausruhst, erfolgt die Heilung alle drei Stunden.}
# Critical Chance
{215}{}{Die Wahrscheinlichkeit, im Kampf einen kritischen Treffer zu landen, wird um diesen Prozentsatz erh�ht.}
{216}{}{Bessere kritische Treffer}
{217}{}{Verletzungsschwelle}
{218}{}{Verletzungsschwelle - Laser}
{219}{}{Verletzungsschwelle - Feuer}
{220}{}{Verletzungsschwelle - Plasma}
{221}{}{Verletzungsschwelle - Elektrisch}
{222}{}{Verletzungsschwelle - EMP}
{223}{}{Verletzungsschwelle - Explosion}
# Damage Resistance
{224}{}{Jede Verletzung wird um diesen Prozentsatz verringert. Die Verletzungsresistenz kann durch das Tragen einer R�stung erh�ht werden.}
{225}{}{Verletzungsresistenz - Laser}
{226}{}{Verletzungsresistenz - Feuer}
{227}{}{Verletzungsresistenz - Plasma}
{228}{}{Verletzungsresistenz - Elektrisch}
{229}{}{Verletzungsresistenz - EMP}
{230}{}{Verletzungsresistenz - Explosion}
# Radiation Resistance
{231}{}{Die Strahlung, der du ausgesetzt bist, wird um diesen Prozentsatz verringert. Die Strahlungsresistenz l�sst sich durch die Art der getragenen R�stung und Antistrahlenmittel beeinflussen.}
# Poison Resistance
{232}{}{Jede Vergiftung wird um diesen Prozentsatz verringert.}
{233}{}{Alter}
{234}{}{Geschlecht}
{235}{}{Aktuelle Trefferpunkte}
{236}{}{Aktueller Vergiftungsgrad}
{237}{}{Aktueller Verstrahlungsgrad}
#
# STAT LEVEL DESCRIPTIONS
#
{301}{}{�bel}
{302}{}{Mies}
{303}{}{D�rftig}
{304}{}{Leidlich}
{305}{}{Mittel}
{306}{}{Gut}
{307}{}{Toll}         # Abbreviated for character editor
{308}{}{Klasse}
{309}{}{Super}
{310}{}{Spitze}
#
#    PC STAT NAMES
#
{400}{}{�brige F�higkeitspunkte}
{401}{}{Level}
{402}{}{Erfahrung}
{403}{}{Ansehen}
{404}{}{Karma}
#
#    PC STAT DESCRIPTIONS
#
# Unspent Skill Points
{500}{}{Punkte, die durch das Erreichen eines neuen Levels verdient wurden. Mit einem Punkt l�sst sich eine F�higkeit um 1 % oder eine Spezialkenntnis um 2 % erh�hen.}
# Level
{501}{}{Die allgemeine Kompetenz einer Spielerfigur. Ein Ma� f�r deine Erfahrung und F�higkeiten.}
# Experience
{502}{}{Eine Belohnung f�r die Durchf�hrung bestimmter Aufgaben oder das Besiegen des Feindes im Kampf. Um h�here Level zu erreichen, sind mehr Erfahrungspunkte erforderlich.}
# Reputation
{503}{}{Was die Welt von deinen Handlungen und Taten wei�. Beeinflusst die Reaktionen von inaktiven Figuren.}
# Karma
{504}{}{Die Auswirkungen deiner Handlungen. Wichtige Informationen werden angezeigt.}

#
#  Experience-gain messages
#
{600}{}{Du hast ein neues Level erreicht.}
