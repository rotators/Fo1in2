# For lines 177 and 180 and 181, spaces are intentional.
# Line 177 is prepended to encounter type. (they begin at 183 below)
{177}{}{Du begegnest }
{178}{}{Ja.}
{179}{}{Nein.}
{180}{}{Du erh�ltst }
{181}{}{ Erfahrungspunkte f�r erfolgreiche Anwendung der F�higkeit Naturbursche.}
# Line 182 is appended after 177 and the encounter type. Period and space is intentional.
{182}{}{. Begegnen?}
# These are apended to line 177.
{183}{}{Floater}
{184}{}{Gottesanbeterinnen}
{185}{}{Ratten}
{186}{}{Bauern die von Raider angegriffen werden}

{289}{}{Du ger�tst in eine Schar hungriger Geckos.}
{290}{}{Du wirst von Feuer Geckos angegriffen!}
{291}{}{Eine Schar b�sartiger Feuer Geckos schl�gt zu!}

#
# 100 to 103 are NOT USED, looks like it was old code for finding the Radscorpion Cave from the worldmap.
#
{100}{}{So wie die Dinge liegen, k�nnen sie nicht weit gereist sein. Sie m�ssen hier irgendwo einen Unterschlupf haben.}
{101}{}{Sie scheinen aus einem nahegelegenen Ort zu kommen.}
{102}{}{Sieht so aus, als w�ren sie aus dem fernen Norden hier her gereist.}
{103}{}{Anscheinend sind sie einfach durch das �dland gewandert.}

{106}{}{Du bist in eine gro�e Schar Radscorpions geraten!}
{107}{}{Du bist in eine Schar Radscorpions geraten.}
{108}{}{Du bist in eine Familie Maulwurfratten geraten.}

# DEHYDRATION ENCOUNTERS
{109}{}{Du musst nach Wasser suchen, um eine schlimme Austrocknung zu vermeiden. Die Suche nimmt eine zus�tzliche Stunde in Anspruch.}
{110}{}{ Du musst nach Wasser suchen, um eine schlimme Austrocknung zu vermeiden. Die Suche nimmt zus�tzliche }
{111}{}{ Stunden in Anspruch.}
{112}{}{Dein Wasservorrat geht zur Neige, und deine Suche nach einer Wasserquelle bleibt erfolglos. Du beginnst unter schwerer Austrocknung zu leiden, die dich }
{113}{}{ Trefferpunkte kostet.}
{114}{}{ Dein Wasservorrat geht zur Neige und deine }
{115}{}{ Stunden dauernde Suche nach einer Wasserquelle bleibt erfolglos. Du beginnst, unter schwerer Austrocknung zu leiden, die dich }
{116}{}{ Trefferpunkte kostet.}
{117}{}{Du suchst eine Stunde lang in der Landschaft der Hochw�ste nach Wasser, aber du findest nicht genug, um deinen Durst vollst�ndig stillen zu k�nnen. Du b��t einen Gesundheitspunkt ein.}
{118}{}{Du suchst eine Stunde lang in der Landschaft der Hochw�ste nach Wasser, aber du findest nicht genug, um deinen Durst vollst�ndig stillen zu k�nnen. Du b��t }
{119}{}{ Trefferpunkte ein.}
{120}{}{Du suchst }
{121}{}{ Stunden lang in der Landschaft der Hochw�ste nach Wasser, aber du findest nicht genug, um deinen Durst vollst�ndig stillen zu k�nnen. Du er einen Trefferpunkt.}
{122}{}{ Du suchst }
{123}{}{ Stunden lang in der Landschaft der Hochw�ste nach Wasser, aber du findest nicht genug, um deinen Durst vollst�ndig stillen zu k�nnen. Du b��t }
{124}{}{ Trefferpunkte.}

{125}{}{Du entgehst mit Hilfe deines Wasservorrats einer Austrocknung.}

{1250}{}{Mit Hilfe deines Vorrates an }
{1251}{}{ entgehst du einer Austrocknung.}
{1160}{}{ einen Trefferpunkt ein.}

#
# DRANK BUT STILL THIRSTY
#
{161}{}{Dein Wasservorrat geht zur Neige und deine }
{162}{}{und deine Suche von }
{148}{}{ Trefferpunkte.}
{163}{}{aber du vermeidest Austrocknung indem du nach Wasser suchst. Die Suche dauert }
{164}{}{1 Stunde.}
#
# CRITICAL SUCCESS ON OUTDOORSMAN CHECK
{147}{}{Du vermeidest Austrocknung indem du nach Wasser suchst. Die Suche dauert 1 hour.}
{138}{}{ Du f�llst }
{159}{}{Flaschen}
{160}{}{ mit trinkbarem Wasser.}
{165}{}{Du erh�ltst }
{166}{}{ Erfahrungspunkte f�r erfolgreiche Anwendung der F�higkeit Naturbursche.}

# NORTH_TABLE ENCOUNTERS
#
#
# North1
#
# if pass Perception check or have Awareness:
#   197 Uh-oh... a raiding party!
# else is:
{105}{}{HINTERHALT!!!}
#
# North2
#
{104}{}{Du bist in einen wilden Kampf zwischen Radscorpions und Maulwurfratten geraten.}
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
{132}{}{Du ger�tst in eine gro�e Schar of Radscorpions!}
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
{144}{}{Du ger�tst in eine gro�e Ansammlung von Maulwurfratten.}
#
# South6
#
{145}{}{Du begegnest einer Schar Radscorpions.}
#
#
# SHADY ENCOUNTERS
#
#
# Shady1
#
{146}{}{Du begegnest einigen Bauern, die gerade angegriffen werden.}
#
# Shady2
#
# -Dehydration-
#
# Shady3
#
{169}{}{Du ger�tst in eine Familie Radscorpions.}
#
# Shady4
#
{170}{}{Du triffst einen reisenden H�ndler mit Wachen.}
#
# unless he's dead, then you get
#
{305}{}{Du kommst zu den �berresten der feindlichen Wachen des H�ndlers Duc.}
#
# once that has been seen, call Shady3
#
# Shady5
#
{175}{}{Du triffst einen Reisenden.}
# or if killed,
{171}{}{Du siehst einen toten Reisenden.}
#
# else call Shady2
#
# Shady
#
{126}{}{Du bist in eine Gruppe Radscorpions geraten, die gerade Maulwurfratten jagt.}
{127}{}{Feindliche, magere, menschliche Wesen mit gr�nlicher Hautfarbe kommen n�her.}
{128}{}{�berall ist M�ll und Ger�ll verstreut. Du fragst dich ob etwas Wertvolles darunter ist...}
#
# UNUSED ENTRY:
{129}{}{Ein einsamer Radscorpion greift dich aus dem Hinterhalt an!}
#
{130}{}{Du bemerkst eine bereits angeknabberte Leiche.}
{134}{}{Eine Schar b�sartiger Radscorpions schlagen aus der W�ste zu!}
{135}{}{Du begegnest einer Gruppe Wachm�nner auf Patrouille.}
{136}{}{Du triffst einen H�ndler mit mehreren Wachen.}
{174}{}{Du entdeckst die �berreste eines von Raidern gepl�nderten Caravans.}
{137}{}{Du siehst einen Bauern, der ein paar Brahmin h�tet.}
{139}{}{Du siehst Radscorpions die Maulwurfsratten in Stadtruinen jagen.} # Sduibek, Fallout ''Fixt''
{172}{}{Du bist �ber einige Sachen gestolpert, die am Boden lagen.}
{176}{}{Du bist an einem kleinen Ort gelandet, der voller Ruinen und verlassener Geb�ude ist.}
#
#
# RAIDER_TABLE ENCOUNTERS
#
#
# Raider1
#
{133}{}{Raider �berfallen dich aus dem Hinterhalt!}
#
# Raider2 - half chance of either msg displayed, but encounter the same
#
{143}{}{Raiders!!!}
{197}{}{Oh, oh... eine Raiderbande!}
#
# Raider3
#
{173}{}{Du entdeckst die �berreste eines von Raidern gepl�nderten Caravans.}
#
# Raider4
#
{310}{}{Eine kleine Raidergruppe greift an!}
#
# Raider5 - 198 always, plus 196 half the time
#
{198}{}{In der Ferne siehst du einen einsamen Raider.}
{196}{}{Radscorpions kommen n�her!}
#
# Raider6 - displays and runs both (because bodies are empty)
#
{199}{}{Du kommst an ein altes Schlachtfeld, auf dem noch einige Leichen herumliegen.}
#plus 196
#
#
{223}{}{Du sichtest eine wandernde Gruppe wilder Kojoten.}
{200}{}{Radscorpions kommen n�her!}
{224}{}{Du bemerkst einige einzelne Personen, die sich hier umsehen.}
{225}{}{Du triffst eine kleine Gruppe von H�ndlern und Wachen.}
{226}{}{Du siehst ein Gefecht zwischen M�nnern und Mutanten!}
{227}{}{Eine riesige Horde Radscorpions kommt n�her!}
#
{250}{}{Einige M�nner in Powerr�stungen n�hern sich dir.}
{251}{}{Du siehst eine Gruppe H�ndler und Wachen.}
{252}{}{Du siehst eine wilde Schlacht zwischen mehreren W�stenraidern und einer Gruppe M�nner in Powerr�stungen.}
{253}{}{Du siehst mehrere Mutanten, die feindliches Gebiet erkunden.}
{254}{}{Du siehst einige merkw�rdige Kreaturen vor dir . . .}
{256}{}{Eine Patrouille von Supermutanten zieht ganz dicht vorbei!}

{257}{}{Du machst die Ruinen eines kleinen Dorfes aus.}

# UNUSED ENTRY:
{255}{}{Du findest einige Sachen.}

{279}{}{Vor dir siehst du im Sand verstreuten M�ll.}
{280}{}{Du ger�tst in eine kriegerische Gruppe von Supermutanten.}
{281}{}{Du ger�tst in eine Gruppe bizarrer Kreaturen.}
{282}{}{Du ger�tst in eine Schar hungriger Radscorpions.}
{283}{}{Du f�hlst dich ekelhaft, und die Luft scheint vor Hitze zu flimmern.}
{284}{}{Du bist �ber eine bizarre, schwimmende Kreatur gestolpert.}
{285}{}{Du begegnest etwas aus einem alten Science Fiction-Film.}
{286}{}{Die Deathclaw!!}
{287}{}{Du ger�tst in eine herumziehende Schar Radscorpions.}
{288}{}{Du begegnest einer mutierten Kreatur aus der W�ste.}
#
{299}{}{In einiger Entfernung siehst du mehrere Radscorpions.}
{300}{}{Du triffst einen zerlumpten Bauern.}
{301}{}{Du begegnest einer Maulwurfratte.}

# was: "The Deathclaw!!"
{302}{}{Eine junge Deathclaw glaubt du w�rst Mittag.}

{303}{}{Du ger�tst in eine Schar wandernder Radscorpions.}
#
{306}{}{Eine Patrouille von Mutanten zieht zusammen mit einigen merkw�rdigen Kreaturen ganz dicht vorbei!}
{307}{}{Du ger�tst in den Hinterhalt einer kleinen, kriegerischen Gruppe Supermutanten.}
{308}{}{Sieht so als, als w�rst du in einen teuflischen Bandenkrieg hineingeraten!}
{309}{}{Eine Gruppe feindlicher Gangmitglieder brechen hervor!}
{311}{}{Eine kleine Gruppe von Gangmitgliedern greift an!}
{313}{}{Du wirst v�llig unvermittelt von einem Schwarm Gottesanbeterinnen angegriffen!}

# UNUSED ENTRY:
{312}{}{Du wirst v�llig unvermittelt von Ratten angegriffen!}

# SPECIAL ENCOUNTERS TEXT:
{314}{}{Hey! Sie sind wirklich da drau�en.}
{315}{}{In der Ferne siehst du einen umgest�rzten Lastwagen.}
{316}{}{Du findest einige Autowracks, die mitten im �dland liegen.}
{317}{}{Im Nordosten sichtest du ein Polizeih�uschen.}
{318}{}{Du kommst an einer Herde wilder Brahmin vorbei. Du sp�rst, dass irgendetwas nicht stimmt...}
#
# Fo1in2:
{400}{}{Du bist in eine Gruppe Geckos geraten.}
{401}{}{Du bist in eine Gruppe Goldener Geckos geraten.}
{402}{}{Kopfgeldj�ger!}
{403}{}{Weit entfernt siehst du einige J�ger.}
{404}{}{Du begegnest Stammeskriegern auf der Suche nach Rache!}
