#
#	 Messages from stat.c
#
#
#	 STAT NAMES
#
{100}{}{Síla}
{101}{}{Vnímavost}
{102}{}{Odolnost}
{103}{}{Charisma}
{104}{}{Inteligence}
{105}{}{Hbitost}
{106}{}{Štìstí}
{107}{}{Hit body}
{108}{}{Akèní body}
{109}{}{Tøída zbroje}
{110}{}{Boj beze zbranì}
{111}{}{Boj na blízko}
{112}{}{Nosnost}
{113}{}{Postøeh}
{114}{}{Uzdravování}
{115}{}{Šance na kritickı zásah}
{116}{}{Lepší kritickı zásah}
{117}{}{Práh odolnosti}
{118}{}{Práh odolnosti vùèi laseru}
{119}{}{Práh odolnosti vùèi ohni}
{120}{}{Práh odolnosti vùèi plazmì}
{121}{}{Práh odolnosti vùèi elektøinì}
{122}{}{Práh odolnosti vùèi EMP}
{123}{}{Práh odolnosti vùèi explozi}
{124}{}{Odolnost vùèi zranìní}
{125}{}{Odolnost vùèi laseru}
{126}{}{Odolnost vùèi ohni}
{127}{}{Odolnost vùèi plazmì}
{128}{}{Odolnost vùèi elektøinì}
{129}{}{Odolnost vùèi EMP}
{130}{}{Odolnost vùèi explozi}
{131}{}{Odolnost vùèi radiaci}
{132}{}{Odolnost vùèi jedùm}
{133}{}{Vìk}
{134}{}{Pohlaví}
{135}{}{momentální Hit body}
{136}{}{momentální stupeò otravy}
{137}{}{momentální stupeò ozáøení}
#
#	 STAT DESCRIPTIONS
#
# @ Basic stats @
#
# Strength
{200}{}{Vlastní fyzická síla. Vysoká hodnota SÍLY je vhodná pro postavy specializující se na boj zblízka. Ovlivòuje: mnoství Hit bodù, úèinnost pøi boji holıma rukama a váhu uneseného nákladu.}
# Perception
{201}{}{Schopnost vidìt, slyšet, cítit a zaznamenat neznámé a neobvyklé vìci. Vysoká hodnota VNÍMAVOSTI je dùleitá zejména pro postavy milující boj na delší vzdálenost. Ovlivòuje: Postøeh a šanci uspìt ve støelbì.}
# Endurance
{202}{}{Fyzická odolnost a ivotní síla. Postava s vysokou hodnotou ODOLNOSTI pøeije i tam, kde jiní umírají. Ovlivòuje: poèet Hit bodù, odolnost vùèi radiaci a jedùm, schopnost uzdravit se, mnoství pøidávanıch Hit bodù.}
# Charisma
{203}{}{Kombinace fyzického vzhledu a osobního kouzla. Vysoká hodnota CHARISMATU je dùleitá pro postavy, které chtìjí ovlivòovat své okolí nenásilnì, tj. prostøednictvím øeèi. Ovlivòuje: reakce NPC a ceny v obchodech.}
# Intelligence
{204}{}{Znalosti, schopnost bystrého uvaování. Vysoká hodnota INTELIGENCE je dùleitá pro všechny postavy. Ovlivòuje: poèet novì pøidìlenıch bodù dovedností za úroveò, bohatost volby dialogu s NPC a spoustu dalších vìcí.}
# Agility
{205}{}{Svalová koordinace a schopnost rychlého pohybu. Vysoká hodnota HBITOSTI je dùleitá pro všechny aktivní postavy. Ovlivòuje: poèet Akèních bodù, Tøídu zbroje, Postøeh a mnoho dalšího.}
# Luck
{206}{}{Osud. Karma. Extrémnì vysoká nebo nízká hodnota ŠTÌSTÍ postavu urèitım zpùsobem ovlivní. Události a jejich následky se zmìní podle toho, jakou má postava kliku nebo smùlu.}
#
# Derived/Non Derived stats
#
# Maximum Hit Points
{207}{}{Urèuje, kolik zásahù vydrí tvá postava, ne zemøe. Pokud dosáhneš 0 a ménì HB, je po tobì.}
# Maximum Action Points
{208}{}{Poèet akcí, které mùe tvá postava uèinit bìhem souboje. Kadá akce samozøejmì spotøebuje jiné mnoství AB.}
# Armor Class
{209}{}{Ovlivòuje šanci, e tvá postava bude bìhem boje zasaena.}
# Unarmed Damage
{210}{}{Mnoství poškození, které tvá postava zpùsobí soupeøi pøi souboji holıma rukama.}
{211}{}{Mnoství poškození, které tvá postava zpùsobí soupeøi pøi souboji zbranìmi na blízko.}
# Carry Weight
{212}{}{Maximální mnoství pøedmìtù a vybavení, které je tvá postava schopna unést (v librách).}
# Sequence
{213}{}{Urèuje, jak rychle je tvá postava schopna v boji reagovat.}
# Healing Rate
{214}{}{Na konci kadého dne se tvá postava uzdraví o 1 HB za kadı bod schopnosti UZDRAVOVÁNÍ SE. Kdy odpoèíváš, dìje se to kadé 3 hodiny.}
# Critical Chance
{215}{}{Šance zpùsobit soupeøi v souboji kritickı zásah se tímto parametrem navyšuje.}
{216}{}{Lepší kritické zásahy}
{217}{}{Práh odolnosti}
{218}{}{Práh odolnosti vùèi laseru}
{219}{}{Práh odolnosti vùèi ohni}
{220}{}{Práh odolnosti vùèi plazmì}
{221}{}{Práh odolnosti vùèi elektøinì}
{222}{}{Práh odolnosti vùèi EMP}
{223}{}{Práh odolnosti vùèi explozi}
# Damage Resistance
{224}{}{Jakıkoliv zásah, kterı utrpí tvá postava se tímto parametrem redukuje. Odolnost vùèi poškození lze zvıšit typem obleèeného brnìní.}
{225}{}{Odolnost vùèi laseru}
{226}{}{Odolnost vùèi ohni}
{227}{}{Odolnost vùèi plazmì}
{228}{}{Odolnost vùèi elektøinì}
{229}{}{Odolnost vùèi EMP}
{230}{}{Odolnost vùèi explozi}
# Radiation Resistance
{231}{}{Mnoství radiace, které jsi vystaven, je redukováno tímto procentem. Odolnost vùèi radiaci mùe bıt zvıšena podle typu obleèeného brnìní a pouitím anti-radiaèních chemikálií.}
# Poison Resistance
{232}{}{Tímto parametrem jsou redukována zranìní zpùsobená jedy.}
{233}{}{Vìk}
{234}{}{Pohlaví}
{235}{}{Aktuální hit body}
{236}{}{Momentální stupeò otravy}
{237}{}{Momentální stupeò ozáøení}
#
# STAT LEVEL DESCRIPTIONS
#
{301}{}{Chudáèek}
{302}{}{Ubohé}
{303}{}{Mizerné}
{304}{}{Obstojné}
{305}{}{Prùmìr}
{306}{}{Dobré}
{307}{}{Vıborné}         # Abbreviated for character editor
{308}{}{Skvìlé}
{309}{}{Úasné}
{310}{}{Super}
#
#	 PC STAT NAMES
#
{400}{}{Nespotøebované dovednostní body}
{401}{}{Level}
{402}{}{Zkušenost}
{403}{}{Reputace}
{404}{}{Karma}
#
#	 PC STAT DESCRIPTIONS
#
# Unspent Skill Points
{500}{}{Mnoství bodù obdrenıch po postupu na další úroveò. Bìné schopnosti lze zvıšit o 1% za kadı bod. U „talentu“ se tyto zvyšují o 2% za bod.}
# Level
{501}{}{Obecná zpùsobilost tvé postavy. Míra tvıch zkušeností a schopností.}
# Experience
{502}{}{Odmìna za dokonèení speciálních úkolù nebo za poráku nepøátel v boji. Nasbírání dostateèné zkušenosti je podmínkou pro dosaení další úrovnì.}
# Reputation
{503}{}{To, co okolní svìt ví o tvıch skutcích. Tento parametr rovnì mìní reakce NPC ve høe.}
# Karma
{504}{}{Následky tvıch èinù ve høe. Zvláš dùleité informace budou speciálnì zobrazeny.}

#
#  Experience-gain messages
#
{600}{}{Postoupil jsi o další úroveò.}
