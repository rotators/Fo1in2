# This is all of the combat messages used by combat.c
#################################################################################
# TRANSLATION NOTE: all %d values will be filled with a number greater than 1
#################################################################################
#
# NOTE: EACH LINE IN THE STATUS BOX AT 640x480 ONLY DISPLAYS TWENTY SIX
# (26) CHARACTERS. Anything over that will wrap.  --Sduibek, Fallout Fixt
#
#
# Truly Generic strings (no need for gender/number issues)
#
#
{100}{}{Il te faut %d points d'action.}
{101}{}{Plus de munitions. Recharge.}
{102}{}{Cible hors de port�e.}
#
# TRANSLATION 103: "Combat cannot be terminated at this time via End Combat button. If no hostile critters or hostile NPCs are present, click End Turn button instead."
#
{103}{}{Impossible de terminer le combat. Essayez le bouton Fin du Tour.}
{104}{}{Ton viseur est bloqu�.}
#
# 105 106 107 have been shortened to fit into 2 lines in the message window
#
{105}{}{Impossible d'utiliser des armes avec deux bras estropi�s.}
{106}{}{Impossible d'utiliser une arme � deux mains avec un bras estropi�.}
{107}{}{Tu n'as pas assez de force pour utiliser correctement cette arme.}
#
# spaces in 108 are intentional, don't remove !
#
{108}{}{ et }
#
#
# Combat Flag Strings (all of these happen to you, the MALE player)
#
#
{200}{}{K.O}
{201}{}{sonn�}
{202}{}{a estropi� ta jambe gauche}
{203}{}{a estropi� ta jambe droite}
{204}{}{a estropi� ton bras gauche}
{205}{}{a estropi� ton bras droit}
{206}{}{aveugl�}
{207}{}{a �t� tu�}
{208}{}{touch�}
{209}{}{critique}
{210}{}{en feu}
{211}{}{ton armure a �t� transperc�e}
{212}{}{ton arme a explos�}
{213}{}{ton arme a �t� d�truite}
{214}{}{ton arme est tomb�e � terre}
{215}{}{as laiss� passer ton tour}
{216}{}{t'es touch�}
{217}{}{as perdu le reste de tes munitions}
{218}{}{as tir� un coup foireux}
{219}{}{t'es bless�}
{220}{}{as �t� touch� au hasard}
{221}{}{as estropi� un membre au hasard}
{222}{}{as �t� cribl� de plombs}
#
#
# Combat Flag Strings (all of these happen to you, the FEMALE player)
#
#
{250}{}{K.O}
{251}{}{sonn�e}
{252}{}{a estropi� ta jambe gauche}
{253}{}{a estropi� ta jambe droite}
{254}{}{a estropi� ton bras gauche}
{255}{}{a estropi� ton bras droit}
{256}{}{aveugl�e}
{257}{}{as �t� tu�e}
{258}{}{touch�e}
{259}{}{critique}
{260}{}{en feu}
{261}{}{ton armure a �t� transperc�e}
{262}{}{ton arme a explos�}
{263}{}{ton arme a �t� d�truite}
{264}{}{ton arme est tomb�e � terre}
{265}{}{as laiss� passer ton tour}
{266}{}{t'es touch�e}
{267}{}{as perdu le reste de tes munitions}
{268}{}{as tir� un coup foireux}
{269}{}{t'es bless�e}
{270}{}{as �t� touch�e au hasard}
{271}{}{as estropi� un membre au hasard}
{272}{}{as �t� cribl�e de plombs}
#
# Combat Flag Strings (all of these happen to a male)
#
{300}{}{sonn�}
{301}{}{assomm�}
{302}{}{a estropi� sa jambe gauche}
{303}{}{a estropi� sa jambe droite}
{304}{}{a estropi� son bras gauche}
{305}{}{a estropi� son bras droit}
{306}{}{aveugl�}
{307}{}{a �t� tu�}
{308}{}{touch�}
{309}{}{critique}
{310}{}{en feu}
{311}{}{son armure a �t� transperc�e}
{312}{}{son arme a explos�}
{313}{}{son arme a �t� d�truite}
{314}{}{son arme est tomb�e � terre}
{315}{}{a laiss� passer son tour}
{316}{}{s'est touch�}
{317}{}{a perdu le reste de ses munitions}
{318}{}{a tir� un coup foireux}
{319}{}{s'est bless�}
{320}{}{a �t� touch� au hasard}
{321}{}{a estropi� un membre au hasard}
{322}{}{a �t� cribl� de plombs}
#
# Combat Flag Strings (all of these happen to a female)
#
{400}{}{sonn�e}
{401}{}{assomm�e}
{402}{}{a estropi� sa jambe gauche}
{403}{}{a estropi� sa jambe droite}
{404}{}{a estropi� son bras gauche}
{405}{}{a estropi� son bras droit}
{406}{}{aveugl�e}
{407}{}{a �t� tu�e}
{408}{}{touch�e}
{409}{}{critique}
{410}{}{en feu}
{411}{}{son armure a �t� transperc�e}
{412}{}{son arme a explos�}
{413}{}{son arme a �t� d�truite}
{414}{}{son arme est tomb�e � terre}
{415}{}{a laiss� passer son tour}
{416}{}{s'est touch�e}
{417}{}{a perdu le reste de ses munitions}
{418}{}{a tir� un coup foireux}
{419}{}{s'est bless�e}
{420}{}{a �t� touch�e au hasard}
{421}{}{a estropi� un membre au hasard}
{422}{}{a �t� cribl�e de plombs}
#
# Miscellaneous combat messages (all of these happen to you, the MALE player)
# Note: the first %s will be replaced by the value of line 506, which
#          should be the language's equivalent to 2nd person male singular,
#          which is "You" in English. The first letter of line 506 should
#          be capitalized, since it will start a sentence.
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1010's in this file, with the exception of line 509
#          where the second %s is the name of another creature
#
{506}{}{Tu}
{509}{}{Oh ! %s as �t� touch� � la place de %s !}
{511}{}{%s as �t� touch� (coup critique) (%s) pour %d points d'impact}
{512}{}{%s as �t� touch� (%s) pour %d points d'impact}
{513}{}{%s as �t� touch� pour %d points d'impact}
{514}{}{%s as compl�tement rat�}
{515}{}{%s as rat�}
{520}{}{%s as �t� touch� (coup critique) pour %d points d'impact}
{521}{}{%s as �t� touch� (coup critique) (%s) pour 1 point d'impact}
{522}{}{%s as �t� touch� (%s) pour 1 point d'impact}
{523}{}{%s as �t� touch� pour 1 point d'impact}
{524}{}{%s as �t� touch� (coup critique) pour 1 point d'impact}
{525}{}{%s as �t� touch� (coup critique) (%s) mais sans aucun d�g�t}
{526}{}{%s as �t� touch� (%s) sans aucun d�g�t}
{527}{}{%s as �t� touch� sans aucun d�g�t}
{528}{}{%s as �t� touch� (coup critique) mais sans aucun d�g�t}
{533}{}{%s as compl�tement rat� ta cible et as pris 1 point d'impact}
{534}{}{%s as compl�tement rat� ta cible et as pris %d points d'impact}
#
# Miscellaneous combat messages (all of these happen to you, the FEMALE player)
# Note: the first %s will be replaced by the value of line 556, which
#          should be the language's equivalent to 2nd person female singular,
#          which is "You" in English. The first letter of line 556 should
#          be capitalized, since it will start a sentence.
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1010's in this file, with the exception of line 559
#          where the second %s is the name of another creature
{556}{}{Tu}
{559}{}{Oh ! %s as �t� touch�e � la place de %s !}
{561}{}{%s as �t� touch�e (coup critique) (%s) pour %d points d'impact}
{562}{}{%s as �t� touch�e (%s) pour %d points d'impact}
{563}{}{%s as �t� touch�e pour %d points d'impact}
{564}{}{%s as compl�tement rat�}
{565}{}{%s as rat�}
{570}{}{%s as �t� touch�e (coup critique) pour %d points d'impact}
{571}{}{%s as �t� touch�e (coup critique) (%s) pour 1 point d'impact}
{572}{}{%s as �t� touch�e (%s) pour 1 point d'impact}
{573}{}{%s as �t� touch�e pour 1 point d'impact}
{574}{}{%s as �t� touch�e (coup critique) pour 1 point d'impact}
{575}{}{%s as �t� touch�e (coup critique) (%s) mais sans aucun d�g�t}
{576}{}{%s as �t� touch�e (%s) sans aucun d�g�t}
{577}{}{%s as �t� touch�e sans aucun d�g�t}
{578}{}{%s as �t� touch�e (coup critique) mais sans aucun d�g�t}
{583}{}{%s as compl�tement rat� ta cible et as pris 1 point d'impact}
{584}{}{%s as compl�tement rat� ta cible et as pris %d points d'impact}
#
# Miscellaneous combat messages (all of these happen to a MALE)
# Note: the first %s is the name of the male creature
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1010's in this file, with the exception of line 609
#          where the second %s is the name of another creature
#
{608}{}{Oh ! %s a �t� touch� � ta place !}
{609}{}{Oh ! %s a �t� touch� � la place de %s !}
{611}{}{%s a �t� touch� (coup critique) (%s) pour %d points d'impact}
{612}{}{%s a �t� touch� (%s) pour %d points d'impact}
{613}{}{%s a �t� touch� pour %d points d'impact}
{614}{}{%s a compl�tement rat�}
{615}{}{%s a rat�}
{620}{}{%s a �t� touch� (coup critique) pour %d points d'impact}
{621}{}{%s a �t� touch� (coup critique) (%s) pour 1 point d'impact}
{622}{}{%s a �t� touch� (%s) pour 1 point d'impact}
{623}{}{%s a �t� touch� pour 1 point d'impact}
{624}{}{%s a �t� touch� (coup critique) pour 1 point d'impact}
{625}{}{%s a �t� touch� (coup critique) (%s) mais sans aucun d�g�t}
{626}{}{%s a �t� touch� (%s) sans aucun d�g�t}
{627}{}{%s a �t� touch� sans aucun d�g�t}
{628}{}{%s a �t� touch� (coup critique) mais sans aucun d�g�t}
{633}{}{%s a compl�tement rat� sa cible et a pris 1 point d'impact}
{634}{}{%s a rat� sa cible et a pris %d points d'impact}
#
# Miscellaneous combat messages (all of these happen to a FEMALE)
# Note: the first %s is the name of the female creature
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1000's in this file, with the exception of line 709
#          where the second %s is the name of another creature
#
{708}{}{Oh ! %s a �t� touch�e � ta place !}
{709}{}{Oh ! %s a �t� touch�e � la place de %s !}
{711}{}{%s a �t� touch�e (coup critique) (%s) pour %d points d'impact}
{712}{}{%s a �t� touch�e (%s) pour %d points d'impact}
{713}{}{%s a �t� touch�e pour %d points d'impact}
{714}{}{%s a compl�tement rat�}
{715}{}{%s a rat�}
{720}{}{%s a �t� touch�e (coup critique) pour %d points d'impact}
{721}{}{%s a �t� touch�e (coup critique) (%s) pour 1 point d'impact}
{722}{}{%s a �t� touch�e (%s) pour 1 point d'impact}
{723}{}{%s a �t� touch�e pour 1 point d'impact}
{724}{}{%s a �t� touch�e (coup critique) pour 1 point d'impact}
{725}{}{%s a �t� touch�e (coup critique) (%s) mais sans aucun d�g�t}
{726}{}{%s a �t� touch�e (%s) sans aucun d�g�t}
{727}{}{%s a �t� touch�e sans aucun d�g�t}
{728}{}{%s a �t� touch�e (coup critique) mais sans aucun d�g�t}
{733}{}{%s a compl�tement rat� sa cible et a pris 1 point d'impact}
{734}{}{%s a rat� sa cible et a pris %d points d'impact}
#
# Hit Locations (by art_num alias)
#
#
# To get the beginning line number below, take number after comma from CRITTERS.LST in ART/CRITTERS and multiply by 10 and then add 1000.
#
# Humans in Power Armor (1) - hapowr,1 napowr,1 - death graphics: HAPOWRxx
#
{1010}{}{t�te}
{1011}{}{bras gauche}
{1012}{}{bras droit}
{1013}{}{torse}
{1014}{}{jambe droite}
{1015}{}{jambe gauche}
{1016}{}{yeux}
{1017}{}{aine}
{1018}{}{pas de nom}
#
{1110}{}{t�te}
{1111}{}{bras gauche}
{1112}{}{bras droit}
{1113}{}{torse}
{1114}{}{jambe droite}
{1115}{}{jambe gauche}
{1116}{}{yeux}
{1117}{}{aine}
{1118}{}{pas de nom}
#
# Brahmin (Mutant 2-Headed Cows)
#
{1150}{}{t�tes}
{1151}{}{patte arri�re gauche}
{1152}{}{patte arri�re droite}
{1153}{}{corps}
{1154}{}{patte avant droite}
{1155}{}{patte avant gauche}
{1156}{}{yeux}
{1157}{}{mamelles}
{1158}{}{pas de nom}
#
# dogs
#
{1160}{}{t�te}
{1161}{}{patte avant}
{1162}{}{patte avant}
{1163}{}{corps}
{1164}{}{patte arri�re}
{1165}{}{patte arri�re}
{1166}{}{yeux}
{1167}{}{aine}
{1168}{}{pas de nom}
#
# Mr. Handy
#
{1170}{}{unit� centrale}
{1171}{}{bras gauche}
{1172}{}{bras droit}
{1173}{}{bo�tier}
{1174}{}{moteur}
{1175}{}{motivateur}
{1176}{}{capteurs}
{1177}{}{r�gulateur}
{1178}{}{pas de nom}
#
# The Lieutenant
#
{1180}{}{t�te}
{1181}{}{bras gauche}
{1182}{}{bras droit}
{1183}{}{torse}
{1184}{}{jambe droite}
{1185}{}{jambe gauche}
{1186}{}{monocle}
{1187}{}{aine}
{1188}{}{pas de nom}
#
# Mole Rat (molerat)
#
{1190}{}{t�te}
{1191}{}{patte avant gauche}
{1192}{}{patte avant droite}
{1193}{}{corps}
{1194}{}{patte arri�re droite}
{1195}{}{patte arri�re gauche}
{1196}{}{yeux}
{1197}{}{aine}
{1198}{}{pas de nom}
#
# Super Mutants
#
{1210}{}{t�te}
{1211}{}{bras gauche}
{1212}{}{bras droit}
{1213}{}{torse}
{1214}{}{jambe droite}
{1215}{}{jambe gauche}
{1216}{}{yeux}
{1217}{}{aine}
{1218}{}{pas de nom}
#
# Radscorpion
#
{1220}{}{t�te}
{1221}{}{queue}
{1222}{}{pinces}
{1223}{}{carapace}
{1224}{}{pattes avant}
{1225}{}{pattes arri�re}
{1226}{}{yeux}
{1227}{}{cerveau}
{1228}{}{pas de nom}
#
# Floater
#
{1230}{}{t�te}
{1231}{}{gueule}
{1232}{}{avant-gueule}
{1233}{}{corps}
{1234}{}{sacs flotteurs}
{1235}{}{queue}
{1236}{}{ganglions}
{1237}{}{organe de ponte}
{1238}{}{pas de nom}
#
# Rats
#
{1240}{}{t�te}
{1241}{}{patte avant gauche}
{1242}{}{patte avant droite}
{1243}{}{corps}
{1244}{}{patte arri�re droite}
{1245}{}{patte arri�re gauche}
{1246}{}{yeux}
{1247}{}{aine}
{1248}{}{pas de nom}
#
# Centaur
#
{1250}{}{t�te}
{1251}{}{queue}
{1252}{}{bras}
{1253}{}{corps}
{1254}{}{patte droite}
{1255}{}{patte gauche}
{1256}{}{yeux}
{1257}{}{aine}
{1258}{}{pas de nom}
#
# human midgets and children
#
{1270}{}{t�te}
{1271}{}{bras gauche}
{1272}{}{bras droit}
{1273}{}{torse}
{1274}{}{jambe droite}
{1275}{}{jambe gauche}
{1276}{}{yeux}
{1277}{}{aine}
{1278}{}{pas de nom}
#
# Overseer
#
{1460}{}{t�te}
{1461}{}{bras gauche}
{1462}{}{bras droit}
{1463}{}{torse}
{1464}{}{jambe droite}
{1465}{}{jambe gauche}
{1466}{}{yeux}
{1467}{}{aine}
{1468}{}{pas de nom}
#
# Gizmo
#
{1490}{}{t�te}
{1491}{}{bras gauche}
{1492}{}{bras droit}
{1493}{}{torse}
{1494}{}{jambe droite}
{1495}{}{jambe gauche}
{1496}{}{yeux}
{1497}{}{ventre}
{1498}{}{pas de nom}
#
# The Master !
#
{1500}{}{t�te}
{1501}{}{???}
{1502}{}{???}
{1503}{}{processeur}
{1504}{}{patte}
{1505}{}{colonne vert�brale}
{1506}{}{yeux}
{1507}{}{�cran}
{1508}{}{pas de nom}
#
# Deathclaw
#
{1510}{}{t�te}
{1511}{}{bras gauche}
{1512}{}{bras droit}
{1513}{}{torse}
{1514}{}{jambe droite}
{1515}{}{jambe gauche}
{1516}{}{yeux}
{1517}{}{aine}
{1518}{}{pas de nom}
#
# Mantis
#
{1520}{}{t�te}
{1521}{}{patte gauche}
{1522}{}{patte droite}
{1523}{}{abdomen}
{1524}{}{pattes}
{1525}{}{ailes}
{1526}{}{yeux}
{1527}{}{thorax}
{1528}{}{pas de nom}
#
# Robobrain
#
{1530}{}{unit� centrale}
{1531}{}{bras gauche}
{1532}{}{bras droit}
{1533}{}{bo�tier}
{1534}{}{pneus}
{1535}{}{motivateur}
{1536}{}{capteurs}
{1537}{}{r�gulateur}
{1538}{}{pas de nom}
#
# Eyebot
#
{1540}{}{unit� centrale}
{1541}{}{manipulateur}
{1542}{}{arme}
{1543}{}{bo�tier}
{1544}{}{motivateur}
{1545}{}{motivateur}
{1546}{}{capteurs}
{1547}{}{r�gulateur}
{1548}{}{pas de nom}
#
# Pig Rat (pigrat)
#
{1550}{}{t�te}
{1551}{}{patte avant gauche}
{1552}{}{patte avant droite}
{1553}{}{corps}
{1554}{}{patte arri�re droite}
{1555}{}{patte arri�re gauche}
{1556}{}{yeux}
{1557}{}{aine}
{1558}{}{pas de nom}
#
# Deathclaw Egg
#
{1580}{}{coquille}
{1581}{}{coquille}
{1582}{}{coquille}
{1583}{}{coquille}
{1584}{}{coquille}
{1585}{}{coquille}
{1586}{}{coquille}
{1587}{}{coquille}
{1588}{}{pas de nom}
#
# Lesser radscorpion
#
{1590}{}{la t�te}
{1591}{}{la queue}
{1592}{}{la griffe}
{1593}{}{la carapace}
{1594}{}{les pattes avant}
{1595}{}{les pattes arri�res}
{1596}{}{les yeux}
{1597}{}{le cerveau}
{1598}{}{pas de nom}
#
# Lesser Death Claw
#
{1600}{}{la t�te}
{1601}{}{le bras gauche}
{1602}{}{le bras droit}
{1603}{}{le torse}
{1604}{}{la jambe droite}
{1605}{}{la jambe gauche}
{1606}{}{les yeux}
{1607}{}{entrejambe}
{1608}{}{pas de nom}
#
# Giant Plant
#
{1650}{}{la bouche}
{1651}{}{le p�doncule}
{1652}{}{le p�doncule}
{1653}{}{le p�doncule central}
{1654}{}{les racines}
{1655}{}{les racines}
{1656}{}{les vrilles sensorielles}
{1657}{}{la base}
{1658}{}{pas de nom}
#
# Security Robot
#
{1660}{}{la t�te}
{1661}{}{la main lance missiles}
{1662}{}{la main porte canon}
{1663}{}{le corps}
{1664}{}{la jambe droite}
{1665}{}{la jambe gauche}
{1666}{}{les d�tecteurs}
{1667}{}{le torse inf�rieur}
{1668}{}{pas de nom}
#
# Gecko 2
#
{1670}{}{la t�te}
{1671}{}{la griffe gauche}
{1672}{}{la griffe droite}
{1673}{}{le corps}
{1674}{}{la jambe droite}
{1675}{}{la jambe gauche}
{1676}{}{les yeux}
{1677}{}{entrejambe}
{1678}{}{pas de nom}
#
# Gecko
#
{1680}{}{la t�te}
{1681}{}{la griffe gauche}
{1682}{}{la griffe droite}
{1683}{}{le corps}
{1684}{}{la jambe droite}
{1685}{}{la jambe gauche}
{1686}{}{les yeux}
{1687}{}{entrejambe}
{1688}{}{pas de nom}
#
# Alien Thing
#
{1800}{}{la t�te}
{1801}{}{la tentacule gauche}
{1802}{}{la tentacule droite}
{1803}{}{le corps}
{1804}{}{le pied droit}
{1805}{}{le pied gauche}
{1806}{}{les yeux ?}
{1807}{}{la jointure de l'entrejambe}
{1808}{}{pas de nom}
#
# End Boss
#
{1850}{}{la t�te}
{1851}{}{le bras gauche}
{1852}{}{le bras droit}
{1853}{}{le torse}
{1854}{}{la jambe droite}
{1855}{}{la jambe gauche}
{1856}{}{les yeux}
{1857}{}{l'entrejambe}
{1858}{}{pas de nom}
#
# Alien Queen
#
{1860}{}{la t�te}
{1861}{}{la tentacule gauche}
{1862}{}{la tentacule droite}
{1863}{}{le corps}
{1864}{}{le pied droit}
{1865}{}{le pied gauche}
{1866}{}{les yeux ?}
{1867}{}{la jointure de l'entrejambe}
{1868}{}{pas de nom}
#
# Gun Turret 2
#
{1900}{}{le processeur}
{1901}{}{le servo du canon}
{1902}{}{le servo du canon}
{1903}{}{la structure}
{1904}{}{le servo de base}
{1905}{}{le servo de base}
{1906}{}{les d�tecteurs}
{1907}{}{le r�gulateur}
{1908}{}{pas de nom}
#
# Giant Ant
#
{1970}{}{la t�te}
{1971}{}{la patte avant gauche}
{1972}{}{la patte avant droite}
{1973}{}{l'abdomen}
{1974}{}{la patte arri�re droite}
{1975}{}{la patte arri�re gauche}
{1976}{}{les antennes}
{1977}{}{le m�tathorax}
{1978}{}{pas de nom}
#
# Goris Robed
#
{1990}{}{la t�te}
{1991}{}{le bras gauche}
{1992}{}{le bras droit}
{1993}{}{le torse}
{1994}{}{la jambe droite}
{1995}{}{la jambe gauche}
{1996}{}{les yeux}
{1997}{}{l'entrejambe}
{1998}{}{pas de nom}
#
# Goris UnRobed
#
{2000}{}{la t�te}
{2001}{}{le bras gauche}
{2002}{}{le bras droit}
{2003}{}{le torse}
{2004}{}{la jambe droite}
{2005}{}{la jambe gauche}
{2006}{}{les yeux}
{2007}{}{l'entrejambe}
{2008}{}{pas de nom}
#
# Gun Turret 2
#
{2010}{}{le processeur}
{2011}{}{le servo du canon}
{2012}{}{le servo du canon}
{2013}{}{la structure}
{2014}{}{le servo de base}
{2015}{}{le servo de base}
{2016}{}{les d�tecteurs}
{2017}{}{le r�gulateur}
{2018}{}{pas de nom}


#
#
# Critical Hit Messages
#
#
# 5000 series - MEN (including generics)
#
{5000}{}{. Ca fait vraiment mal}
{5001}{}{. Ca doit piquer}
{5002}{}{ sans la protection d'une armure}
{5003}{}{. Cette attaque perverse le met K.O}
{5004}{}{. Le coup le met � terre}
{5005}{}{. Ce solide coup port� � la t�te lui fait perdre connaissance}
{5006}{}{. L'attaque explose sa tempe. Bonne nuit, Gracie}
{5007}{}{, la mort est instantan�e}
{5008}{}{, provoquant une s�rieuse blessure au coude}
{5009}{}{, arrachant le bras}
{5010}{}{, ce qui lui laisse un gros h�matome}
{5011}{}{, lui mutilant le bras gauche}
{5012}{}{, laissant le bras gauche pendouiller}
{5013}{}{. Il ne reste plus de son bras qu'un moignon}
{5014}{}{, lui mutilant le bras droit}
{5015}{}{. Ce violent coup pulv�rise son bras droit}
{5016}{}{ sous un coup d'une force inou�e}
{5017}{}{ passant sous l'armure}
{5018}{}{, infligeant ainsi une autre dose de d�g�ts}
{5019}{}{ sans protection, flanquant le combattant � terre}
{5020}{}{ compl�tement sonn�, il s'effondre et est hors de combat}
{5021}{}{. Maintenant, m�me de face, on voit tr�s clairement sa colonne vert�brale}
{5022}{}{ blessant gravement sa jambe}
{5023}{}{, le renversant comme une quille dans une partie de bowling}
{5024}{}{, provoquant sa chute et mutilant sa jambe}
{5025}{}{, envoyant valser son genou sur une autre plan�te. Il tombe}
{5026}{}{. La douleur intense li�e � l'amputation de sa jambe le pousse � abandonner la partie}
{5027}{}{ lui infligeant une douleur suppl�mentaire}
{5028}{}{ provoquant son aveuglement, le malheureux}
{5029}{}{, et sans aucune protection, provoquant une douleur atroce}
{5030}{}{, et l'aveuglant sous l'effet d'un coup violent}
{5031}{}{. La perte d'un oeil est plus qu'il ne peut supporter, et il s'effondre au sol}
{5032}{}{, malheureusement, il est tellement occup� par cette soudaine sensation de fra�cheur qui le traverse qu'il ne se rend pas compte que l'heure de sa mort a sonn�}
{5033}{}{. Ouille ! Ca a d� faire mal}
{5034}{}{, et il n'a rien pour se couvrir, non plus}
{5035}{}{ et, sans protection, il s'�croule, hurlant de douleur}
{5036}{}{. La douleur est trop grande pour lui et il s'�croule telle une loque}
{5037}{}{. L'ennemi, les yeux r�vuls�s, laisse �chapper le mot 'Maman'}
#
# series 5100 - WOMEN
#
{5100}{}{. Ca fait vraiment mal}
{5101}{}{. Ca doit piquer}
{5102}{}{ sans protection}
{5103}{}{. Cette agression violente lui fait perdre conscience}
{5104}{}{. Le coup la fait tomber � terre}
{5105}{}{. Le violent coup port� � la t�te l'assomme compl�tement}
{5106}{}{. L'attaque explose sa tempe dans une gerbe de sang. Bonne nuit, Gracie}
{5107}{}{, la mort est imm�diate}
{5108}{}{, provoquant une s�rieuse blessure au coude}
{5109}{}{, arrachant le bras}
{5110}{}{, ce qui laisse un gros h�matome}
{5111}{}{, estropiant le bras gauche}
{5112}{}{. Le bras gauche pendouille � son �paule}
{5113}{}{. Ce bras est tel un moignon sanguinolent}
{5114}{}{, ne laissant qu'un bras droit estropi�}
{5115}{}{. Suite � ce coup, son bras droit ressemble � un steak saignant}
{5116}{}{ d'un coup d'une force inou�e}
{5117}{}{ traversant ses d�fenses}
{5118}{}{, provoquant de nouveaux d�g�ts}
{5119}{}{ sans armure, renversant la combattante au sol}
{5120}{}{ �touffant, elle s'effondre sur le sol}
{5121}{}{. Malheureusement, ses organes vitaux sont �tal�s en plein jour}
{5122}{}{ lui provoquant une douleur aigu� dans la jambe}
{5123}{}{, la vidant de ses derni�res forces comme une rencontre amoureuse qui tourne au vinaigre}
{5124}{}{, la renversant et la mutilant de la jambe}
{5125}{}{, envoyant valser son genou sur une autre plan�te. Elle s'affale par terre}
{5126}{}{. Sa jambe cass�e la fait hurler de douleur}
{5127}{}{ infligeant une douleur suppl�mentaire}
{5128}{}{ provoquant son aveuglement. Elle fait une grimace}
{5129}{}{, et en l'absence de protection, provoquant une douleur immense}
{5130}{}{. La blessure provoque une c�cit� des plus graves (comme si cela pouvait ne pas �tre grave !)}
{5131}{}{. L'attaque qui est � l'origine de son aveuglement la fait s'�vanouir}
{5132}{}{, malheureusement pour elle, elle n'a pas le temps de prier ses dieux avant de s'en aller les rejoindre}
{5133}{}{. Elle r�agit comme un homme. Enfin, �a fait mal}
{5134}{}{, la terrassant}
{5135}{}{. Elle s'�croule comme une masse molle. On se demande si, apr�s une telle chute, elle pourra jamais enfanter}
#
# series 5200 - children
#
{5200}{}{. Le petit gamin se met � pleurer}
{5201}{}{. Inconscient, l'enfant tombe dans les pommes}
{5202}{}{. Ouille !}
{5203}{}{. Le coup est bien r�el, et l'enfant est assomm�}
{5204}{}{, projetant le petit enfant dans tout les sens comme un chiffon mou}
{5205}{}{. Le bras gauche de cet enfant laisse appara�tre un joli bleu}
{5206}{}{, d�s�quilibrant l'enfant}
{5207}{}{, cassant ce bras dans un craquement sourd. De grosses larmes se mettent � jaillir}
{5208}{}{, en cassant facilement ce bras comme une petite sucrerie}
{5209}{}{. Le bras droit se met � gonfler comme un ballon}
{5210}{}{, et se met � pleurer}
{5211}{}{ dans un endroit sensible}
{5212}{}{. L'attaque d'un organe vital assomme l'enfant}
{5213}{}{, frappant l'enfant qui se d�sarticule comme un jouet cass�}
{5214}{}{. Maintenant cet enfant n'exp�rimentera jamais vraiment la vie}
{5215}{}{, infligeant une profonde entaille}
{5216}{}{. L'attaque fait rouler l'enfant et lui casse une jambe}
{5217}{}{, infligeant un grand mal au petit enfant}
{5218}{}{. L'enfant regarde en l'air et se met � pleurer}
{5219}{}{, qui aveugle l'enfant}
{5220}{}{, frappant le jeune nez de l'enfant}
{5221}{}{. Une coupure appara�t au-dessus de l'oeil et le sang coule � flots}
{5222}{}{, qui lui ouvre l'oeil comme un raisin qui explose. L'enfant semble atterr�}
{5223}{}{ provoquant l'aveuglement. L'enfant tombe au sol}
{5224}{}{, le coup atteint le jeune cerveau et le transforme en bouillie}
{5225}{}{. L'enfant semble confus et secou�}
{5226}{}{, projetant la jeune cible au sol}
#
# series 5300 - Super Mutants
#
{5300}{}{, blessant le puissant mutant}
{5301}{}{, frappant un endroit vital}
{5302}{}{, frappant un endroit vital et faisant tomber le g�ant � terre}
{5303}{}{. Le mutant g�ant regarde autour de lui pendant un instant puis s'effondre}
{5304}{}{. Sa t�te explose comme une past�que g�ante et sanguinolente}
{5305}{}{, blessant gravement le puissant mutant}
{5306}{}{, provoquant le g�ant qui se met � maudire l'univers entier}
{5307}{}{, touchant un nerf et for�ant le g�ant � saisir son bras de douleur}
{5308}{}{. Le coup brise le coude et �a doit faire bien mal}
{5309}{}{, brisant le bras muscl� et faisant jaillir le sang du mutant sur le sol}
{5310}{}{, faisant vaciller le g�ant pendant un moment puis le faisant s'effondrer comme un arbre que l'on abat}
{5311}{}{, et des litres de visc�res sont d�vers�s sur le sol}
{5312}{}{, envoyant le g�ant valser sur le sol}
{5313}{}{. Le mutant tr�buche et tombe, sa jambe ayant du mal � le retenir}
{5314}{}{, frappant un endroit vital. Le mutant s'affaisse sur une jambe cass�e}
{5315}{}{. La douleur d'une jambe cass�e assomme le puissant g�ant}
{5316}{}{, aveuglant presque le mutant}
{5317}{}{, aveuglant le mutant fou de col�re}
{5318}{}{, aveuglant presque le mutant tout en lui faisant perdre l'�quilibre}
{5319}{}{. Le mutant aveugl� perd de l'assurance, pris au d�pourvu par la prochaine attaque}
{5320}{}{, aveuglant le mutant sans connaissance}
{5321}{}{. Pendant un instant, les yeux du mutant brillent ; puis la lumi�re s'�teint, pour toujours}
#
# series 5400 - Ghouls
#
{5400}{}{. Le Goule est pris au d�pourvu et n'a pas le temps de se d�fendre contre cette attaque}
{5401}{}{. Ce coup ensevelit le Goule}
{5402}{}{. La main du Goule stup�fait s'ouvre brusquement}
{5403}{}{, s'infiltrant sous son armure et touchant un endroit vital}
{5404}{}{, s'infiltrant sous son armure et sectionnant le bras}
{5405}{}{. Le Goule part dans la mauvaise direction et au mauvais moment, il perd un oeil}
{5406}{}{. Le Goule ne porte pas d'armure � cet endroit-l�}
{5407}{}{, et sans armure, le Goule perd la vue}
{5408}{}{, provoquant la stup�faction du Goule au moment de son tr�pas}
#
# series 5500 - Brahmin (brahma)
#
{5500}{}{, faisant s'�crouler la grosse b�te au sol}
{5501}{}{, assommant les deux t�tes et abattant l'animal g�ant}
{5502}{}{. La vache mutante pousse un cri fort et alarmant}
{5503}{}{, brisant l'une des pattes de la Brahmine}
{5504}{}{, blessant gravement la vache mutante}
{5505}{}{, p�n�trant ais�ment le cuir �pais de la b�te g�ante}
{5506}{}{, traversant directement les deux coeurs de la vache mutante}
{5507}{}{, crevant les deux paires d'yeux d'un seul coup d'un seul}
{5508}{}{, aveuglant les deux t�tes et assommant la vache mutante}
{5509}{}{, aveuglant compl�tement la Brahmine et la mettant K.O}
{5510}{}{, la grosse vache mutante vacille pendant un moment}
{5511}{}{. La Brahmine tremble de col�re}
{5512}{}{. La Brahmine pousse des grognements de douleur}
{5513}{}{. La Brahmine est extr�mement �nerv�e face � cette attaque des plus d�vastatrices}
#
# series 5600 - Radscorpions
#
{5600}{}{, envoyant le radscorpion valser sur le dos}
{5601}{}{, s�parant la t�te de la carapace}
{5602}{}{, ab�mant gravement la queue}
{5603}{}{, blessant gravement ses griffes}
{5604}{}{. Le coup passe entre les fentes de l'�paisse carapace du radscorpion}
{5605}{}{, frappant sans arr�t l'�paisse carapace}
{5606}{}{, passant au travers de l'armure naturelle et mettant K.O le radscorpion}
{5607}{}{. Le radscorpion expire de mort 'naturelle', il lui manque quelques organes internes}
{5608}{}{, envoyant le radscorpion valser et estropiant quelques-unes de ses pattes}
{5609}{}{. L'attaque atteint une articulation non prot�g�e de la patte pour la sectionner}
{5610}{}{, blessant gravement et aveuglant la cr�ature mutante}
{5611}{}{, atteignant presque le cerveau. Tu parles d'�craser une bestiole..}
{5612}{}{, atteignant presque le cerveau mais aveuglant plut�t la cr�ature}
{5613}{}{. L'attaque est agressive et bien trop compliqu�e pour cette cr�ature toute simple}
{5614}{}{. S'il s'agissait d'un humain, vous jureriez qu'elle est furieuse}
{5615}{}{, laissant la cr�ature au sol sans connaissance}
{5616}{}{, transper�ant le cerveau au sol}
#
# series 5700 - Rats
#
{5700}{}{. Le cr�ne du rongeur fait des bruits bizarres}
{5701}{}{, �crasant le cr�ne du rongeur comme un sac en papier mouill�}
{5702}{}{, et la patte gauche semble maintenant un peu aplatie}
{5703}{}{. La patte gauche du rat est arrach�e}
{5704}{}{. La patte droite est gravement ab�m�e}
{5705}{}{, arrachant la patte droite}
{5706}{}{. Le rat est gravement bless� au cours de cette attaque}
{5707}{}{, blessant gravement le rat et le malmenant}
{5708}{}{, faisant gicler le rat sur le sol}
{5709}{}{, estropiant la patte droite}
{5710}{}{, trouant largement la patte gauche}
{5711}{}{, provoquant des d�g�ts suppl�mentaires en raison de sa localisation sensible}
{5712}{}{, faisant para�tre cette cr�ature devant le grand chasseur de rats des cieux}
#
# series 5800 - Floaters
#
{5800}{}{, le Flotteur tombe � terre}
{5801}{}{, le Flotteur tombe � terre, apparemment inanim�}
{5802}{}{, ayant de graves cons�quences sur l'avenir de cette cr�ature}
{5803}{}{, assommant la cr�ature immonde}
{5804}{}{, touchant un point sensible et assommant le Flotteur}
{5805}{}{. Le coup provoque des vibrations violentes du Flotteur qui d�gage un nuage de pluie rouge sang}
{5806}{}{. Le coup provoque des r�actions violentes de la part de la cr�ature}
{5807}{}{. Le Flotteur prend soudainement feu}
{5808}{}{ puis il se crispe intens�ment et se met � trembler comme une feuille}
{5809}{}{, le coup atteignant une partie sensible}
{5810}{}{. La cr�ature est �videmment dans tous ses �tats}
#
# series 5900 - Centaurs
#
{5900}{}{, rejet� comme une mauvaise habitude, le Centaure tombe et s'assomme}
{5901}{}{ tandis que le coup frappe un point sensible}
{5902}{}{, engendrant de graves probl�mes neurologiques}
{5903}{}{, l'assommant avec ton attaque violente}
{5904}{}{, estropiant le bras}
{5905}{}{ frappant un point sensible et mutilant le bras}
{5906}{}{, faisant tomber la cr�ature et en estropiant la jambe}
{5907}{}{, �tourdissant le Centaure alors qu'il est renvers� avec une jambe mutil�e}
{5908}{}{, aveuglant une t�te}
{5909}{}{, surprenant le Centaure. Il avance � l'aveuglette en tr�buchant pendant un moment}
{5910}{}{, surprenant le Centaure. Il s'�croule sur un tas}
{5911}{}{, surprenant le Centaure. Il s'�croule dans une substance visqueuse}
{5912}{}{. Cette attaque aurait pu �tre bien plus efficace}
#
# series 6000 - Robots
#
{6000}{}{, infligeant quelques d�g�ts structurels}
{6001}{}{, des �tincelles jaillissent et le robot est momentan�ment incontr�lable}
{6002}{}{, atteignant un composant important qui rend le robot incontr�lable}
{6003}{}{, atteignant un composant important et provoquant un dysfonctionnement global}
{6004}{}{. Le robot tente de compenser}
{6005}{}{. Le robot s'efforce de compenser}
{6006}{}{, touchant des pi�ces ma�tresses et provoquant de s�rieux d�g�ts}
{6007}{}{, infligeant de graves d�g�ts structurels}
{6008}{}{, touchant un composant important et provoquant de s�rieux d�g�ts}
{6009}{}{. Le robot tr�pide sous cette attaque intense}
{6010}{}{, d�mantelant le robot}
{6011}{}{. Le robot essaie de compenser mais �choue et s'�croule}
{6012}{}{. Le robot s'�puise sous la pression et tombe au sol}
{6013}{}{, brisant les lentilles des capteurs}
#
# series 6100 - Dogs
#
{6100}{}{, mettant le cabot � terre}
{6101}{}{, en plein sur le museau}
{6102}{}{. Le chien tombe mais respire toujours}
{6103}{}{, l'animal crache un caillot de sang}
{6104}{}{, estropiant la patte}
{6105}{}{, estropiant la patte. L'animal tente de rester debout mais n'y arrive pas}
{6106}{}{. L'animal rendu aveugle hurle de douleur}
{6107}{}{, ch�trant la pauvre b�te}
#
# series 6200 - Manti
#
{6200}{}{, mettant K.O cet insecte mutant}
{6201}{}{, qui s'effondre}
{6202}{}{. La mante se demande si elle doit mettre un terme � sa vie}
{6203}{}{, estropiant le membre}
{6204}{}{, entra�nant la mante � l�cher ses blessures. Elle tient le membre d'une fa�on insolite}
{6205}{}{, venant � bout de l'armure chitineuse}
{6206}{}{. La mante hurle et tremble de fa�on presque humaine}
{6207}{}{, ce qui provoque la chute de la mante. Un membre se plie et prend une forme insolite}
{6208}{}{, d�chiquetant les ailes}
{6209}{}{, venant � bout de l'armure chitineuse et d�sint�grant la mante}
{6210}{}{, aveuglant l'insecte d'un coup pr�cis}
#
# series 6300 - Deathclaw
#
{6300}{}{. Cette b�te elle-m�me est d�concert�e par cette attaque surprise}
{6301}{}{, passant au travers des �normes griffes pour frapper le monstre. Le Griffemort tremble et grogne}
{6302}{}{. Les yeux du Griffemort sont tr�s s�rieusement touch�s}
#
# series 6400 - Spore Plant  # Was The Master
#
{6400}{}{, passant au travers des d�fenses de la plante }
{6401}{}{, arrachant une partie de ses feuilles}
{6402}{}{, fracassant une partie de ses frondes}
{6403}{}{, endommageant son arriv�e de chlorophylle}
{6404}{}{, la vidant de son pollen}
{6405}{}{. la renversant presque}
{6406}{}{, endommageant une partie de ses branches}
#
# series 6500 - The Player
#
{6500}{}{. Tu auras un mal de t�te terrible demain, si tu vis assez longtemps pour �a}
{6501}{}{. Ton armure ne te prot�ge pas contre ce coup bien pr�cis}
{6502}{}{. Tu sens la douleur pendant un court moment puis tu sombres dans les t�n�bres.}
{6503}{}{, venant � bout de ton armure. Le coup te fait te casser la figure}
{6504}{}{, le choc te fait perdre provisoirement la vue. Apr�s un instant, tu te rends compte que c'est bien d�finitif}
{6505}{}{. T'as une belle vue de ton corps alors que ta t�te vole dans les airs}
{6506}{}{. Chose �trange, tu ne sens rien de plus que d'habitude}
{6507}{}{, t'assommant pour un moment}
{6508}{}{. Tu sens la douleur}
{6509}{}{. L'attaque te laisse avec un bras en moins}
{6510}{}{, passant au travers de ton armure. Le coup broie les os de ton bras comme si ce n'�tait que du bois mort}
{6511}{}{, venant � bout de ton armure. Ton bras pendouille maintenant mollement sur le c�t�}
{6512}{}{. L'h�matome sera beau et les cicatrices feront parler d'elles}
{6513}{}{, broyant tes organes internes. Il ne te reste plus qu'� te vider de ton sang}
{6514}{}{, t'envoyant les quatre fers en l'air}
{6515}{}{, t'envoyant valser et te brisant la jambe}
{6516}{}{, fondant � travers ton armure. Le coup t'envoie valser et blesse gravement ton genou}
{6517}{}{. Ta jambe cass�e te fait tellement mal que tu tombes dans les pommes}
{6518}{}{. Le coup douloureux te fait vaciller mais sans plus}
{6519}{}{. Malheureusement pour toi, tu vas vite perdre la vue}
{6520}{}{. Il te faut un moment pour essuyer le sang qui coule de tes yeux}
{6521}{}{, passant au travers de ton armure. Tu t'�bahis quand tu te rends compte que tu ne vois plus rien}
{6522}{}{. Tu ressens une dr�le de sensation � la t�te. Tu te rends compte que la mort c�r�brale est imminente}
{6523}{}{, te for�ant � reculer}
{6524}{}{. Tu soutiens ton ventre et tombe � terre en te tordant de douleur}
{6525}{}{. La douleur suffit � te mettre K.O. Ouille}
{6526}{}{. Aucun mot dans tout l'univers n'est assez fort pour d�crire la douleur que tu ressens � ce moment-l�}


# Fallout 2:
#
# series 6700 - Gecko
#
{6700}{}{, passant au travers des d�fenses du l�zard}
{6701}{}{, arrachant un peu de sa peau visqueuse}
{6702}{}{, brisant quelques-uns de ses doigts}
{6703}{}{, mettant � mal son syst�me respiratoire}
{6704}{}{, l'amochant gravement}
{6705}{}{, le renversant presque}
{6706}{}{, endommageant plusieurs de ses membres}
#
# series 6800 - Alien
#
{6800}{}{, passant au travers des d�fenses de la cr�ature}
{6801}{}{, le d�barrassant d'un peu du liquide gluant qui le recouvre}
{6802}{}{, �crasant plusieurs de ses ventouses}
{6803}{}{, mettant � mal sa prise d'air (?)}
{6804}{}{, l'amochant salement}
{6805}{}{, le renversant presque}
{6806}{}{, endommageant plusieurs de ses tentacules}
#
# series 6900 - Giant Ant
#
{6900}{}{, passant au travers des d�fenses de la fourmi}
{6901}{}{, arrachant une partie de ses antennes}
{6902}{}{, brisant plusieurs de ses antennes}
{6903}{}{, le mettant dans un sale �tat}
{6904}{}{, le ballottant un peu}
{6905}{}{, le renversant presque}
{6906}{}{, endommageant une partie de son exosquelette}
#
# series 7000 - Gun Turret  -- WIP! Won't Work!
#
{7000}{}{, passant au travers des d�fenses de la fourmi}
{7001}{}{, arrachant une partie de ses antennes}
{7002}{}{, brisant plusieurs de ses antennes}
{7003}{}{, le mettant dans un sale �tat}
{7004}{}{, le ballottant un peu}
{7005}{}{, le renversant presque}
{7006}{}{, endommageant une partie de son exosquelette}
#
# Series 7100 - End Boss
#
{7100}{}{, passant au travers de l'armure du Garde du corps}
{7101}{}{, mettant le Garde du corps � genoux}
{7102}{}{, d�truisant le m�canisme de son bras}
{7103}{}{, d�truisant le m�canisme de rotation de sa jambe}
{7104}{}{, fracassant son oeil bionique}
{7105}{}{, l'obligeant � s'immobiliser pour r�cup�rer de ton attaque d�vastatrice}
{7106}{}{, compactant sa plaque pectorale}

#
# ENTRIES FROM WASTELAND, FOR SDUIBEK'S REFERENCE:
#
#  A. Exploding it    3. like a blood sausage
#  B. Reducing it     2. into a thin red paste
#  B. Reducing it     2. into a fine red mist
#  B. Reducing it     7. into an undertaker's nightmare
#  C. Spinning him    4. into a dance of death
#  D. Blasting it     1. into ground round
#  E. Sending him     6. to meet his maker
#  F. Ripping it      5. into a scarlet side of meat
#  G. Killing it      [no ending]
#
#  heap of unrecognizable gore
#  reducing it to platinum shards
#
