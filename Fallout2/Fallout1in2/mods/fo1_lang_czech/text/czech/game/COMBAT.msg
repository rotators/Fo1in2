#
# This is all of the combat messages used by combat.c
# Note: all %d values will be filled with a number greater than 1
#
# Truly Generic strings (no need for gender/number issues)
#
{100}{}{Potøebuješ %d akèních bodù.}
{101}{}{Došla ti munice.}
{102}{}{Cíl je mimo dosah.}
{103}{}{Nemùeš ukonèit boj, kdy jsou poblí nepøátelští tvorové.}
{104}{}{Nìco ti stojí v cestì.}
{105}{}{Nemùeš pouít zbraò, máš-li obì ruce zmrzaèeny.}
{106}{}{Nemùeš pouít dvouruèní zbraò s jednou rukou zmrzaèenou.}
{107}{}{Pro správné pouití této zbranì nemáš dost síly.}
{108}{}{ a }
#
# Combat Flag Strings (all of these happen to you, the MALE player)
#
{200}{}{byl jsi knokautován}
{201}{}{byl jsi sraen k zemi}
{202}{}{tvá levá noha byla ochromena}
{203}{}{tvá pravá noha byla ochromena}
{204}{}{tvá levá ruka byla ochromena}
{205}{}{tvá pravá ruka byla ochromena}
{206}{}{byl jsi oslepen}
{207}{}{byl jsi zabit}
{208}{}{byl jsi zasaen}
{209}{}{kriticky}
{210}{}{v plamenech}
{211}{}{byl jsi zasaen do nechránìného místa}
{212}{}{zbraò ti vybuchla v rukou}
{213}{}{tvá zbraò byla znièena}
{214}{}{zbraò ti upadla na zem}
{215}{}{ztratil jsi svùj další tah}
{216}{}{zasáhl jsi sám sebe}
{217}{}{ztratil jsi zbytek munice}
{218}{}{nezasáhl jsi nic}
{219}{}{zranil jsi sám sebe}
{220}{}{náhodnì jsi zasáhl}
{221}{}{byl jsi zasaen a jedna z tvıch konèetin byla ochromena}
{222}{}{byl jsi zasypán støepinami}
#
# Combat Flag Strings (all of these happen to you, the FEMALE player)
#
{250}{}{byla jsi knokautována}
{251}{}{byla jsi sraena k zemi}
{252}{}{tvá levá noha byla ochromena}
{253}{}{tvá pravá noha byla ochromena}
{254}{}{tvá levá ruka byla ochromena}
{255}{}{tvá pravá ruka byla ochromena}
{256}{}{byla jsi oslepena}
{257}{}{byla jsi zabita}
{258}{}{byla jsi zasaena}
{259}{}{kriticky}
{260}{}{v plamenech}
{261}{}{byla jsi zasaena do nechránìného místa}
{262}{}{zbraò ti vybuchla v rukou}
{263}{}{tvá zbraò byla znièena}
{264}{}{zbraò ti upadla na zem}
{265}{}{ztratila jsi svùj další tah}
{266}{}{zasáhla jsi sama sebe}
{267}{}{ztratila jsi zbytek munice}
{268}{}{nezasáhla jsi nic}
{269}{}{zranila jsi sama sebe}
{270}{}{náhodnì jsi zasáhla}
{271}{}{byla jsi zasaena a jedna z tvıch konèetin byla ochromena}
{272}{}{byla jsi zasypána støepinami}
#
# Combat Flag Strings (all of these happen to a male)
#
{300}{}{byl knokautován}
{301}{}{byl sraen k zemi}
{302}{}{jeho levá noha byla ochromena}
{303}{}{jeho pravá noha byla ochromena}
{304}{}{jeho levá ruka byla ochromena}
{305}{}{jeho pravá ruka byla ochromena}
{306}{}{byl oslepen}
{307}{}{byl zabit}
{308}{}{byl zasaen}
{309}{}{kriticky}
{310}{}{v plamenech}
{311}{}{byl zasaen do nechránìného místa}
{312}{}{jeho zbraò vybuchla}
{313}{}{jeho zbraò byla znièena}
{314}{}{jeho zbraò mu upadla}
{315}{}{ztratil svùj další tah}
{316}{}{trefil sám sebe}
{317}{}{ztratil zbytek munice}
{318}{}{nezasáhl nic}
{319}{}{zranil sám sebe}
{320}{}{náhodnì zasáhl}
{321}{}{byl zasaen a jedna z jeho konèetin byla ochromena}
{322}{}{byl zasypán støepinami}
#
# Combat Flag Strings (all of these happen to a female)
#
{400}{}{byla knokautována}
{401}{}{byla sraena k zemi}
{402}{}{její levá noha byla ochromena}
{403}{}{její pravá noha byla ochromena}
{404}{}{její levá ruka byla ochromena}
{405}{}{její pravá ruka byla ochromena}
{406}{}{byla oslepena}
{407}{}{byla zabita}
{408}{}{byla zasaena}
{409}{}{kriticky}
{410}{}{v plamenech}
{411}{}{byla zasaena do nechránìného místa}
{412}{}{její zbraò explodovala}
{413}{}{její zbraò byla znièena}
{414}{}{upustila svou zbraò}
{415}{}{ztratila svùj další tah}
{416}{}{zasáhla sama sebe}
{417}{}{ztratila zbytek munice}
{418}{}{promarnila vıstøel}
{419}{}{zranila sebe samotnou}
{420}{}{náhodnì zasáhla}
{421}{}{byla zasaena a jedna z jejích konèetin byla ochromena}
{422}{}{byla zasypána støepinami}
#
# Miscellaneous combat messages (all of these happen to you, the male player)
# Note: the first %s will be replaced by the value of line 506, which
#          should be the language's equivalent to 2nd person male singular,
#          which is "You" in English. The first letter of line 506 should
#          be capitalized, since it will start a sentence.
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1000's in this file, with the exception of line 509
#          where the second %s is the name of another creature
{506}{}{}
{509}{}{Jejda! %s byl jsi zasaen namísto cíle: %s!}
{511}{}{%s Byl jsi kriticky zasaen a ztratil jsi %d hit bodù. Místo zásahu: %s.}
{512}{}{%s Byl jsi zasaen a ztratil jsi %d hit bodù. Místo zásahu: %s.}
{513}{}{%s Byl jsi zasaen a ztratil jsi %d hit bodù}
{514}{}{%s Kriticky jsi minul}
{515}{}{%s Minul jsi}
{520}{}{%s Byl jsi kriticky zasaen a ztratil jsi %d hit bodù}
{521}{}{%s Byl jsi kriticky zasaen a ztratil jsi 1 hit bod. Místo zásahu: %s.}
{522}{}{%s Byl jsi zasaen a ztratil jsi 1 hit bod. Místo zásahu: %s.}
{523}{}{%s Byl jsi zasaen a ztratil jsi 1 hit bod}
{524}{}{%s Byl jsi kriticky zasaen a ztratil jsi 1 hit bod}
{525}{}{%s Byl jsi kriticky, ale bez poškození, zasaen. Místo zásahu: %s.}
{526}{}{%s Byl jsi zasaen, ale útok ti nezpùsobil ádné zranìní. Místo zásahu: %s.}
{527}{}{%s Byl jsi zasaen, ale útok ti nezpùsobil ádné zranìní}
{528}{}{%s Byl jsi kriticky zasaen, ale útok ti nezpùsobil ádné zranìní}
{533}{}{%s Kriticky jsi minul a ještì ses zranil za 1 hit bod}
{534}{}{%s Kriticky jsi minul a ještì ses zranil za %d hit bodù}
#
# Miscellaneous combat messages (all of these happen to you, the female player)
# Note: the first %s will be replaced by the value of line 556, which
#          should be the language's equivalent to 2nd person female singular,
#          which is "You" in English. The first letter of line 556 should
#          be capitalized, since it will start a sentence.
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1000's in this file, with the exception of line 559
#          where the second %s is the name of another creature
{556}{}{}
{559}{}{Jejda! %s Byla jsi zasaena namísto cíle: %s!}
{561}{}{%s Byla jsi kriticky zasaena a ztratila jsi %d hit bodù. Místo zásahu: %s.}
{562}{}{%s Byla jsi zasaena a ztratila jsi %d hit bodù. Místo zásahu: %s.}
{563}{}{%s Byla jsi zasaena a ztratila jsi %d hit bodù}
{564}{}{%s Kriticky jsi minula}
{565}{}{%s Minula jsi}
{570}{}{%s Byla jsi kriticky zasaena a ztratila jsi %d hit bodù}
{571}{}{%s Byla jsi kriticky zasaena a ztratila jsi 1 hit bod. Místo zásahu: %s.}
{572}{}{%s Byla jsi zasaena a ztratila jsi 1 hit bod. Místo zásahu: %s.}
{573}{}{%s Byla jsi zasaena a ztratila jsi 1 hit bod}
{574}{}{%s Byla jsi kriticky zasaena a ztratila jsi 1 hit bod}
{575}{}{%s Byla jsi kriticky, ale bez zranìní zasaena. Místo zásahu: %s.}
{576}{}{%s Byla jsi zasaena, ale útok ti nezpùsobil ádné zranìní. Místo zásahu: %s.}
{577}{}{%s Byla jsi zasaena, ale útok ti nezpùsobil ádné zranìní}
{578}{}{%s Byla jsi kriticky zasaena, ale útok ti nezpùsobil ádné zranìní}
{583}{}{%s Kriticky jsi minula a ještì ses zranila za 1 hit bod}
{584}{}{%s Kriticky jsi minula a ještì ses zranila za %d hit bodù}
#
# Miscellaneous combat messages (all of these happen to a male)
# Note: the first %s is the name of the male creature
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1000's in this file, with the exception of line 609
#          where the second %s is the name of another creature
#
{608}{}{Jejda! %s byl zasaen namísto tebe!}
{609}{}{Jejda! %s byl zasaen namísto cíle: %s}
{611}{}{%s byl kriticky zasaen. Místo zásahu: %s. Ztratil %d hit bodù}
{612}{}{%s byl zasaen. Místo zásahu: %s. Ztratil %d hit bodù}
{613}{}{%s byl zasaen, ztratil %d hit bodù}
{614}{}{%s kriticky minul}
{615}{}{%s minul}
{620}{}{%s byl kriticky zasaen, ztratil %d hit bodù}
{621}{}{%s byl kriticky zasaen a ztratil 1 hit bod. Místo zásahu: %s}
{622}{}{%s byl zasaen a ztratil 1 hit bod. Místo zásahu: %s}
{623}{}{%s byl zasaen a ztratil 1 hit bod}
{624}{}{%s byl kriticky zasaen a ztratil 1 hit bod}
{625}{}{%s byl kriticky zasaen, ale útok mu nezpùsobil ádné zranìní. Místo zásahu: %s}
{626}{}{%s byl zasaen, ale útok mu nezpùsobil ádné zranìní. Místo zásahu: %s}
{627}{}{%s byl zasaen, ale útok mu nezpùsobil ádné zranìní}
{628}{}{%s byl kriticky zasaen, ale útok mu nezpùsobil ádné zranìní}
{633}{}{%s kriticky minul a navíc se zranil za 1 hit bod}
{634}{}{%s kriticky minul a navíc se zranil za %d hit bodù}
#
# Miscellaneous combat messages (all of these happen to a female)
# Note: the first %s is the name of the female creature
#       the second %s (if there is one) is the hit location, which
#          will be a string from the section Hit Locations starting
#          in the 1000's in this file, with the exception of line 709
#          where the second %s is the name of another creature
#
{708}{}{Jejda! %s byla zasaena namísto tebe!}
{709}{}{Jejda! %s byla zasaena namísto cíle: %s!}
{711}{}{%s byla kriticky zasaena. Místo zásahu: %s. Ztratila %d hit bodù}
{712}{}{%s byla zasaena. Místo zásahu: %s. Ztratila %d hit bodù}
{713}{}{%s byla zasaena, ztratila %d hit bodù}
{714}{}{%s kriticky minula}
{715}{}{%s minula}
{720}{}{%s byla kriticky zasaena, ztratila %d hit bodù}
{721}{}{%s byla kriticky zasaena a ztratila 1 hit bod. Místo zásahu: %s.}
{722}{}{%s byla zasaena a ztratila 1 hit bod. Místo zásahu: %s.}
{723}{}{%s byla zasaena a ztratila 1 hit bod}
{724}{}{%s byla kriticky zasaena a ztratila 1 hit bod}
{725}{}{%s byla kriticky zasaena, ale útok jí nezpùsobil ádné zranìní. Místo zásahu %s.}
{726}{}{%s byla zasaena, ale útok jí nezpùsobil ádné zranìní. Místo zásahu %s.}
{727}{}{%s byla zasaena, ale útok jí nezpùsobil ádné zranìní}
{728}{}{%s byla kriticky zasaena, ale útok jí nezpùsobil ádné zranìní}
{733}{}{%s kriticky minula a navíc se zranila za 1 hit bod}
{734}{}{%s kriticky minula a navíc se zranila za %d hit bodù}
#
# Hit Locations (by art_num alias)
#
# regular humans
#
{1110}{}{hlava}
{1111}{}{levá ruka}
{1112}{}{pravá ruka}
{1113}{}{hrudník}
{1114}{}{pravá noha}
{1115}{}{levá noha}
{1116}{}{oèi}
{1117}{}{genitálie}
{1118}{}{necílenı zásah}
#
# Brahmin (Mutant 2-Headed Cows)
#
{1150}{}{hlava}
{1151}{}{levá kıta}
{1152}{}{pravá kıta}
{1153}{}{trup}
{1154}{}{pravá pøední noha}
{1155}{}{levá pøední noha}
{1156}{}{oèi}
{1157}{}{vemeno}
{1158}{}{necílenı zásah}
#
# dogs
#
{1160}{}{hlava}
{1161}{}{zadní noha}
{1162}{}{zadní noha}
{1163}{}{trup}
{1164}{}{pøední noha}
{1165}{}{pøední noha}
{1166}{}{oèi}
{1167}{}{genitálie}
{1168}{}{necílenı zásah}
#
# Mr. Handy
#
{1170}{}{CPU}
{1171}{}{manipulátor}
{1172}{}{manipulátor}
{1173}{}{konstrukce}
{1174}{}{servo}
{1175}{}{servo}
{1176}{}{senzory}
{1177}{}{regulátor}
{1178}{}{vibrátor pro domácí pouití}
#
# Super Mutants             # Fallout 2: Reserved?
#
{1180}{}{hlava}
{1181}{}{levá ruka}
{1182}{}{pravá ruka}
{1183}{}{hrudník}
{1184}{}{pravá noha}
{1185}{}{levá noha}
{1186}{}{oèi}
{1187}{}{genitálie}
{1188}{}{necílenı zásah}
#
# Mole-Rat
#
{1190}{}{hlava}
{1191}{}{levá tlapa}
{1192}{}{pravá tlapa}
{1193}{}{trup}
{1194}{}{pravá noha}
{1195}{}{levá noha}
{1196}{}{oèi}
{1197}{}{genitálie}
{1198}{}{necílenı zásah}
#
# big humans and mutants
#
{1210}{}{hlava}
{1211}{}{levá ruka}
{1212}{}{pravá ruka}
{1213}{}{hrudník}
{1214}{}{pravá noha}
{1215}{}{levá noha}
{1216}{}{oèi}
{1217}{}{genitálie}
{1218}{}{necílenı zásah}
#
# Radscorpion
#
{1220}{}{hlava}
{1221}{}{ocas}
{1222}{}{klepeta}
{1223}{}{krunıø}
{1224}{}{pøední nohy}
{1225}{}{zadní nohy}
{1226}{}{oèi}
{1227}{}{mozek}
{1228}{}{mozek}
#
# Floater
#
{1230}{}{hlava}
{1231}{}{tlama}
{1232}{}{pøední tlama}
{1233}{}{tìlo}
{1234}{}{zásobní vak}
{1235}{}{ocas}
{1236}{}{uzlina}
{1237}{}{kladélko}
{1238}{}{necílenı zásah}
#
# masrat? a rat perhaps?
#
{1240}{}{hlava}
{1241}{}{levá tlapa}
{1242}{}{pravá tlapa}
{1243}{}{tìlo}
{1244}{}{pravá noha}
{1245}{}{levá noha}
{1246}{}{oèi}
{1247}{}{genitálie}
{1248}{}{necílenı zásah}
#
# Centaur
#
{1250}{}{hlava}
{1251}{}{levá ruka}
{1252}{}{pravá ruka}
{1253}{}{tìlo}
{1254}{}{pravá noha}
{1255}{}{levá noha}
{1256}{}{oèi}
{1257}{}{genitálie}
{1258}{}{necílenı zásah}
#
# human midgets and children
#
{1270}{}{hlava}
{1271}{}{levá ruka}
{1272}{}{pravá ruka}
{1273}{}{hrudník}
{1274}{}{pravá noha}
{1275}{}{levá noha}
{1276}{}{oèi}
{1277}{}{genitálie}
{1278}{}{necílenı zásah}
#
# Overseer                  # Fallout 2: Reserved?
#
{1460}{}{hlava}
{1461}{}{levá ruka}
{1462}{}{pravá ruka}
{1463}{}{hrudník}
{1464}{}{pravá noha}
{1465}{}{levá noha}
{1466}{}{oèi}
{1467}{}{genitálie}
{1468}{}{necílenı zásah}
#
# Gizmo                     # Fallout 2: Reserved?
#
{1490}{}{hlava}
{1491}{}{levá ruka}
{1492}{}{pravá ruka}
{1493}{}{hrudník}
{1494}{}{pravá noha}
{1495}{}{levá noha}
{1496}{}{oèi}
{1497}{}{pupek}
{1498}{}{necílenı zásah}
#
# The Master!               # Fallout 2: Reserved?
#
{1500}{}{hlava}
{1501}{}{???}
{1502}{}{???}
{1503}{}{konstrukce}
{1504}{}{???}
{1505}{}{???}
{1506}{}{oèi}
{1507}{}{CPU}
{1508}{}{necílenı zásah}
#
# Death Claw
#
{1510}{}{hlava}
{1511}{}{levá pracka}
{1512}{}{pravá pracka}
{1513}{}{hrudník}
{1514}{}{pravá noha}
{1515}{}{levá noha}
{1516}{}{oèi}
{1517}{}{genitálie}
{1518}{}{necílenı zásah}
#
# Mantis
#
{1520}{}{hlavièka}
{1521}{}{pøední noha}
{1522}{}{pøední noha}
{1523}{}{zadeèek}
{1524}{}{zadní nohy}
{1525}{}{køídla}
{1526}{}{oèi}
{1527}{}{zadohruï}
{1528}{}{necílenı zásah}
#
# Robobrain
#
{1530}{}{CPU}
{1531}{}{manipulátor}
{1532}{}{manipulátor}
{1533}{}{konstrukce}
{1534}{}{servo}
{1535}{}{servo}
{1536}{}{senzory}
{1537}{}{regulátor}
{1538}{}{vibrátor}
#
# Eyeball (Robot)
#
{1540}{}{CPU}
{1541}{}{manipulátor}
{1542}{}{manipulátor}
{1543}{}{konstrukce}
{1544}{}{servo}
{1545}{}{servo}
{1546}{}{senzory}
{1547}{}{regulátor}
{1548}{}{vibrátor pro domácí pouití}
#
# Mutant Pig Rat (small Mole-Rat)
#
{1550}{}{hlava}
{1551}{}{levá tlapa}
{1552}{}{pravá tlapa}
{1553}{}{tìlo}
{1554}{}{pravá noha}
{1555}{}{levá noha}
{1556}{}{oèi}
{1557}{}{genitálie}
{1558}{}{necílenı zásah}
#
# Deathclaw Egg
#
{1580}{}{skoøápka}
{1581}{}{skoøápka}
{1582}{}{skoøápka}
{1583}{}{skoøápka}
{1584}{}{skoøápka}
{1585}{}{skoøápka}
{1586}{}{skoøápka}
{1587}{}{skoøápka}
{1588}{}{necílenı zásah}
#
# Lesser Radscorpion
#
{1590}{}{hlava}
{1591}{}{ocas}
{1592}{}{klepeta}
{1593}{}{krunıø}
{1594}{}{pøední nohy}
{1595}{}{zadní nohy}
{1596}{}{oèi}
{1597}{}{mozek}
{1598}{}{uncalled}
#
# Lesser Death Claw
#
{1600}{}{hlava}
{1601}{}{levı paøát}
{1602}{}{pravı paøát}
{1603}{}{hrudník}
{1604}{}{pravá noha}
{1605}{}{levá noha}
{1606}{}{oèi}
{1607}{}{genitálie}
{1608}{}{uncalled}
#
# Giant Plant
#
{1650}{}{tlama}
{1651}{}{stonek}
{1652}{}{stonek}
{1653}{}{hlavní stonek}
{1654}{}{koøeny}
{1655}{}{koøeny}
{1656}{}{smyslové úponky}
{1657}{}{podstava}
{1658}{}{uncalled}
#
# Security Robot
#
{1660}{}{hlava}
{1661}{}{raketomet}
{1662}{}{gatling}
{1663}{}{trup}
{1664}{}{pravá noha}
{1665}{}{levá noha}
{1666}{}{senzory}
{1667}{}{kloub}
{1668}{}{uncalled}
#
# Gecko 2
#
{1670}{}{hlava}
{1671}{}{levá pracka}
{1672}{}{pravá pracka}
{1673}{}{hrudník}
{1674}{}{pravá noha}
{1675}{}{levá noha}
{1676}{}{oèi}
{1677}{}{genitálie}
{1678}{}{uncalled}
#
# Gecko
#
{1680}{}{hlava}
{1681}{}{levá pracka}
{1682}{}{pravá pracka}
{1683}{}{hrudník}
{1684}{}{pravá noha}
{1685}{}{levá noha}
{1686}{}{oèi}
{1687}{}{genitálie}
{1688}{}{uncalled}
#
# Alien Thing
#
{1800}{}{hlava}
{1801}{}{levé tykadlo}
{1802}{}{pravé tykadlo}
{1803}{}{trup}
{1804}{}{pravá noha}
{1805}{}{levá noha}
{1806}{}{oèi?}
{1807}{}{pohlavní orgány}
{1808}{}{uncalled}
#
# End Boss
#
{1850}{}{hlava}
{1851}{}{levá ruka}
{1852}{}{pravá ruka}
{1853}{}{hrudník}
{1854}{}{pravá noha}
{1855}{}{levá noha}
{1856}{}{oèi}
{1857}{}{genitálie}
{1858}{}{uncalled}
#
# Alien Queen
#
{1860}{}{hlava}
{1861}{}{levé tykadlo}
{1862}{}{pravé tykadlo}
{1863}{}{trup}
{1864}{}{pravá noha}
{1865}{}{levá noha}
{1866}{}{oèi?}
{1867}{}{pohlavní orgány}
{1868}{}{uncalled}
#
# Gun Turret 2
#
{1900}{}{CPU}
{1901}{}{zbraò}
{1902}{}{zbraò}
{1903}{}{konstrukce}
{1904}{}{servomotor}
{1905}{}{servomotor}
{1906}{}{senzory}
{1907}{}{regulátor}
{1908}{}{uncalled}
#
# Giant Ant
#
{1970}{}{hlava}
{1971}{}{levá pøední noha}
{1972}{}{pravá pøední noha}
{1973}{}{zadeèek}
{1974}{}{pravá zadní noha}
{1975}{}{levá zadní noha}
{1976}{}{tykadla}
{1977}{}{zadohruï}
{1978}{}{uncalled}
#
# Goris Robed
#
{1990}{}{hlava}
{1991}{}{levá ruka}
{1992}{}{pravá ruka}
{1993}{}{hrudník}
{1994}{}{pravá noha}
{1995}{}{levá noha}
{1996}{}{oèi}
{1997}{}{genitálie}
{1998}{}{uncalled}
#
# Goris UnRobed
#
{2000}{}{hlava}
{2001}{}{levı paøát}
{2002}{}{pravı paøát}
{2003}{}{hrudník}
{2004}{}{pravá noha}
{2005}{}{levá noha}
{2006}{}{oèi}
{2007}{}{genitálie}
{2008}{}{uncalled}
#
# Gun Turret 2
#
{2010}{}{CPU}
{2011}{}{zbraò}
{2012}{}{zbraò}
{2013}{}{konstrukce}
{2014}{}{servomotor}
{2015}{}{servomotor}
{2016}{}{senzory}
{2017}{}{regulátor}
{2018}{}{uncalled}


#
# Critical Hit Messages
#
# 5000 series - men (including generics)
#
{5000}{}{ a opravdu ho to zabolelo}
{5001}{}{. Zásah mu zpùsobil váné zranìní}
{5002}{}{, protoe rána pronikla brnìním}
{5003}{}{. Drtivá rána ho dokonale omráèila}
{5004}{}{. Rána ho srazila k zemi}
{5005}{}{. Silná rána do hlavy ho úplnì knokautovala}
{5006}{}{. Rána mu rozdrtila spánek. Tak dobrou noc, princezno}
{5007}{}{, smrt nastala okamitì}
{5008}{}{, rána mu zpùsobila velice bolestivı tenisovı loket}
{5009}{}{, rána mu urvala ruku}
{5010}{}{, rána zanechala velkou podlitinu}
{5011}{}{, rána zanechala jeho levou ruku zcela ochromenou}
{5012}{}{, rána zanechala jeho levou ruku houpající se na kusu kùe}
{5013}{}{. Z ruky mu zbyl jen krvavı pahıl}
{5014}{}{, zanechávajíc pravou ruku zcela ochromenou}
{5015}{}{. Jeho pravá ruka byla touto strašlivou ranou rozdrcena na kaši}
{5016}{}{ pøi tomto rychlém a brutálním útoku}
{5017}{}{, protoe rána pronikla skrz jeho brnìní}
{5018}{}{, útok byl velice devastující.}
{5019}{}{, rána ho zasáhla tìsnì vedle brnìní a srazila ho k zemi}
{5020}{}{, rána mu vyrazila dech a on upadl na zem, definitivnì tímto vyøazen z boje}
{5021}{}{. Skrz cáry vnitøností a krvácejícího svalstva se bíle leskne jeho páteø}
{5022}{}{ a rána mu vyrvala na stehnì díru velikosti muské pìsti}
{5023}{}{, zásah ho srazil k zemi lehce jako kuelku}
{5024}{}{, pøièem mu rána pøerazila a ochromila nohu}
{5025}{}{, jeho koleno bylo rozdrceno na krvavou kaši. V šoku upadl na zem}
{5026}{}{. Strašlivá bolest z utrené nohy zpùsobila, e zpanikaøil a chce odbelhat pryè}
{5027}{}{ a vytrpìl šílenou bolest }
{5028}{}{ a ke vší té smùle je navíc nadobro oslepen}
{5029}{}{, a protoe útok nebyl blokován brnìním, zpùsobil mu pøíšernou bolest}
{5030}{}{, a ta hrozná rána ho témìø oslepila}
{5031}{}{. Ztratit oko, to u bylo trochu moc i na nìj. Upadl na zem}
{5032}{}{, bohuel je ale právì teï pøíliš zaujatı umíráním, ne aby vnímal vlahı dotek vìtru na svém mozku}
{5033}{}{. Au! To teda muselo bolet}
{5034}{}{, a poprvé v ivotì mìl pøíleitost zahlédnout na kratièkı okamik své vnitønosti}
{5035}{}{, zlomil se v pase, upadl na zem a v agónii zaèal chroptìt}
{5036}{}{. Bolest ze zranìní byla tak hrozná, e se zhroutil jako panák z hadrù}
{5037}{}{. Skoro neslyšnì zamumlal „Mami!“ a jeho oèi se pomalu obrátily v sloup}
#
# series 5100 - women
#
{5100}{}{ a poøádnì jí to zabolelo}
{5101}{}{. Zásah jí zpùsobil váné zranìní}
{5102}{}{ protoe rána pronikla brnìním}
{5103}{}{. Drtivá rána jí srazila do bezvìdomí}
{5104}{}{. Rána jí srazila k zemi}
{5105}{}{. Silná rána do hlavy jí úplnì knokautovala}
{5106}{}{. Rána jí rozdrtila spánek. Sbohem a díky za všechny orgasmy}
{5107}{}{, smrt následovala okamitì}
{5108}{}{, rána jí zpùsobila velice ošklivı tenisovı loket}
{5109}{}{, rána jí urvala ruku}
{5110}{}{, rána zanechala velkou podlitinu}
{5111}{}{, rána zanechala její levou ruku zcela ochromenou}
{5112}{}{. Rána zanechala její levou ruku houpající se na kusu kùe}
{5113}{}{. Z ruky jí zbyl jen krvavı pahıl}
{5114}{}{, zanechávajíce pravou ruku zcela ochromenou}
{5115}{}{. Její pravá ruka teï pøipomíná krvavı karbanátek}
{5116}{}{ pøi tomto rychlém a brutálním útoku}
{5117}{}{ protoe rána pronikla skrz její brnìní}
{5118}{}{, útok byl velice devastující}
{5119}{}{ rána ji zasáhla tìsnì vedle brnìní a srazila k zemi}
{5120}{}{ rána jí vyrazila dech a ona upadla na zem, definitivnì vyøazena z boje}
{5121}{}{. Její nejintimnìjší orgán si teï mùou prohlídnout všichni. A dokonce zevnitø}
{5122}{}{ a rána jí vyrvala na stehnì díru velikosti muské pìsti}
{5123}{}{, rána jí zasáhla hùø ne soulo bez orgasmu}
{5124}{}{, pøièem jí rána pøerazila a zmrzaèila nohu}
{5125}{}{, její koleno bylo rozdrceno na krvavou kaši. Skácela se na zem}
{5126}{}{. Køièí bolestí a tiskne si pøeraenou nohu}
{5127}{}{ a zaila pøíšernou bolest, která ji málem pøipravila o rozum. Tedy o tu špetku co má}
{5128}{}{ rána jí èásteènì oslepila. Dìlá hroznì legraèní grimasy}
{5129}{}{, a protoe útok nebyl blokován brnìním, zpùsobil jí pøíšernou bolest}
{5130}{}{. Zranìní ji témìø oslepilo}
{5131}{}{. Šlehla sebou o zem jak románová naivka}
{5132}{}{, bohuel se nestihla pomodlit ke svım bohùm, aèkoliv se s nimi u brzy potká}
{5133}{}{. Pøijala to stateènì jako mu. Feministky by na ni mohly bıt hrdé}
{5134}{}{, útok ji srazil k zemi}
{5135}{}{. Bìhem nìkolika vteøin absolvovala svou poslední a nejvìtší menstruaci}
#
# series 5200 - children
#
{5200}{}{. Dítì se rozplakalo}
{5201}{}{. Dítì bylo omráèeno a upadlo na zem}
{5202}{}{. Auvej!}
{5203}{}{. Zásah dítì omráèil}
{5204}{}{, zásah zmìnil dítì na krvavı hadøík}
{5205}{}{. Levá ruka dítìte visí na kousku šlachy}
{5206}{}{, rána zbavila dítì rovnováhy}
{5207}{}{, ruka se s hlasitım rupnutím zlomila. Teï u zaèínají téct opravdové slzy}
{5208}{}{, ruka se zlomila lehce jako kousek cukrkandlu}
{5209}{}{. Jeho pravá ruka otekla jako meloun}
{5210}{}{, a zaèalo plakat}
{5211}{}{ do citlivého místa}
{5212}{}{. Zásah do ivotnì dùleitıch orgánù srazil dítì k zemi}
{5213}{}{, rána odkopla dítì lehce jako plyšovou hraèku}
{5214}{}{. Tohle dítì u ádnou další ivotní zkušenost neudìlá}
{5215}{}{, zásah zpùsobil hlubokou trnou ránu}
{5216}{}{. Rána dítì porazila a zlomila mu nohu}
{5217}{}{, rána ho tìce poranila}
{5218}{}{. To malé dítì se na tebe podívalo a zaèalo plakat. Nestydíš se aspoò trochu?}
{5219}{}{, zásah dítì oslepil}
{5220}{}{, rána ho zasáhla do nosu}
{5221}{}{. Z èela mu zaèala vytékat krev}
{5222}{}{, rána ho zasáhla do udivenıch oèí. Dítì vypadá dezorientovanì}
{5223}{}{ zásah ho oslepil. Dítì upadlo na zem. Baví tì to støílet do dìtí, ty jeden uboáku?}
{5224}{}{, rána ho zasáhla do mozku}
{5225}{}{. Dítì se tøese a vypadá zmatenì}
{5226}{}{, rána srazila tvùj malı cíl k zemi}
#
# series 5300 - Super Mutants
#
{5300}{}{, útok mohutného mutanta bolestivì poranil}
{5301}{}{, rána zasáhla ivotnì dùleitou oblast. Mutant zaèal zvracet krev}
{5302}{}{, útok zasáhl ivotnì dùleitou oblast a srazil obra k zemi}
{5303}{}{. Obrovitı mutant se na tebe udivenì podíval a pak se pomalu sesunul k zemi}
{5304}{}{. Jeho hlava vybuchla jako velkı krvavı meloun}
{5305}{}{, rána zpùsobila obrovitému mutantovi vánì poranìní}
{5306}{}{, co dalo tomu obrovi èas, aby stihl proklít okamik kdy se narodil}
{5307}{}{, rána zasáhla nerv a zpùsobila obrovi pøíšernou bolest}
{5308}{}{. Rána mu zlomila loket. Vypadá to, e ho to muselo bolet}
{5309}{}{, rána mu zlomila ruku. Mutantova krev vychrstla na zem všude okolo}
{5310}{}{, obr se na chvíli zapotácel a pak padl jak podatı strom}
{5311}{}{, a jeho vnitønosti s hlasitım šplouchnutím dopadly na zem}
{5312}{}{, rána ho odhodila lehce jako pírko}
{5313}{}{. Mutant se zapotácel a upadl. Jeho noha mu u nebude k nièemu}
{5314}{}{, rána mu zpùsobila tìké zranìní. Mutant zakolísal, jeho noha je pøeraená vejpùl}
{5315}{}{. Bolest ze zlomené nohy obra natolik pøemohla, e skuèí jako malé dítì}
{5316}{}{, zásah supermutanta oslepil}
{5317}{}{, rána mutanta oslepila. A taky ho ovšem rozzuøila k nepøíèetnosti}
{5318}{}{, rána supermutanta oslepila a zbavila ho veškeré rovnováhy}
{5319}{}{. Oslepenı mutant zakolísal, nepøipraven na další útok}
{5320}{}{, rána mutanta omráèila a oslepila}
{5321}{}{. Mutantovy oèi na chvíli zazáøily a potom jejich svit pohasl - navdy}
#
# series 5400 - Ghouls
#
{5400}{}{. Ghúl byl naprosto zaskoèen a nezmohl se na sebemenší pokus o obranu}
{5401}{}{. Tato šlupka ghúla definitivnì pohøbila}
{5402}{}{. Ghúlova ruka efektnì odplachtila vzduchem}
{5403}{}{, rána pronikla skrz brnìní a zpùsobila mu rozsáhlá poranìní}
{5404}{}{, rána pronikla skrz brnìní a odtrhla mu témìø celé rameno}
{5405}{}{. Ten ghúl se v nepravou chvíli pohnul špatnım smìrem a pøišel o oko}
{5406}{}{. Tento ghúl nemìl obleèeno ádné brnìní}
{5407}{}{ a bez brnìní ghúl oslepl}
{5408}{}{, co zpùsobilo, e ghúl vypadá dost zmatenì ve vrcholném okamiku jeho ivota}
#
# series 5500 - Brahmin
#
{5500}{}{, rána to veliké zvíøe srazila na zem}
{5501}{}{, útok zasáhl oba mozky a srazil zvíøe na zem}
{5502}{}{. Kráva ze sebe vyrazila hlasité, pøekvapené zabuèení}
{5503}{}{, rána mu pøerazila jednu z nohou}
{5504}{}{, útok zmutovanou krávu vánì poranil}
{5505}{}{, rána lehouèce pronikla tlustou kùí obrovského zvíøete}
{5506}{}{, rána pronikla pøímo skrz obì srdce zmutované krávy}
{5507}{}{, jedinou ranou byly oslepeny všechny ètyøi oèi mohutného zvíøete}
{5508}{}{, rána oslepila obì hlavy zvíøete. To se zapotácelo a kleslo k zemi}
{5509}{}{, rána zvíøe úplnì oslepila a odhodila ho stranou}
{5510}{}{, zvíøe na chvíli strnulo bez pohnutí}
{5511}{}{. Obrovské zvíøe se tøese vztekem}
{5512}{}{. Kráva zafunìla bolestí}
{5513}{}{. Útok rozdrtil zvíøeti vemeno. Tváøí se víc ne pøekvapenì}
#
# series 5600 - Radscorpions
#
{5600}{}{, radškorpión proletìl vzduchem a dopadl na záda}
{5601}{}{, útok oddìlil jeho hlavu od krunıøe}
{5602}{}{, rána tìce poškodila jeho ocas}
{5603}{}{, rána mu urazila obì klepeta}
{5604}{}{. Radškorpiónùv krunıø s hlasitım lupnutím praskl}
{5605}{}{, zásah prorazil jeho chitinové brnìní}
{5606}{}{, rána prošla jeho pøirozenım brnìním a odhodila ho dozadu}
{5607}{}{. Radškorpiónovi se skuteènost, e mu teï schází nìkteré dùleité vnitøní orgány, evidentnì vùbec nezamlouvá}
{5608}{}{, jedna z radškorpiónovıch nohou proletìla vzduchem}
{5609}{}{. Rána ho zasáhla do kloubu a pøesekla mu nohu}
{5610}{}{, zmutovaná bestie byla tìce poranìna a oslepena}
{5611}{}{, rána témìø pronikla k jeho mozku}
{5612}{}{, útok pronikl témìø a k mozku a navdy ho oslepil}
{5613}{}{. Útok byl ïábelsky sofistikovanı na tak jednoduché zvíøe}
{5614}{}{. Kdyby to byl èlovìk, byl bys pøísahal, e je pìknì naštvanı}
{5615}{}{, rána zbavila ubohé zvíøe smyslù}
{5616}{}{, zvíøe si teï mùe zblízka prohlédnout svùj mozek. Leí toti pøed jeho oèima}
#
# series 5700 - Rats
#
{5700}{}{. Hlodavec ze sebe vyrazil pár skøekù}
{5701}{}{, hlodavcova lebka vybuchla jako papírovı sáèek}
{5702}{}{, hlodavcova levá pracka je jak krvavá placka. To se to krásnì rımuje, co?}
{5703}{}{. Levá noha hlodavce byla utrena}
{5704}{}{. Pravá noha hlodavce byla rozmaèkána na kaši}
{5705}{}{, hlodavcova pravá noha byla urvána}
{5706}{}{. Hlodavec byl tímto útokem tìce poranìn}
{5707}{}{, rána hlodavce odhodila nazpìt a tìce ho poranila}
{5708}{}{, rána hlodavce rozmázla po podlaze}
{5709}{}{, rána zmrzaèila hlodavcovu pravou nohu}
{5710}{}{, rána hlodavci vyhloubila na levé noze velikou díru}
{5711}{}{, útok zasáhl hlodavce do citlivé oblasti a zpùsobil mu váné poranìní}
{5712}{}{, rána hlodavce poslala k velkému potkanímu bohu na nebesích}
#
# series 5800 - Floaters
#
{5800}{}{, Slizoun spadl na zem}
{5801}{}{, Slizoun spadl na zem, zdánlivì mrtvı}
{5802}{}{, jeho existence byla ukonèena}
{5803}{}{, bestie byla omráèena}
{5804}{}{, rána zasáhla jeho citlivé místo a omráèila ho}
{5805}{}{. Po této ránì se Slizoun zmìnil v krvavı vodotrysk}
{5806}{}{, rána bestii rozzuøila}
{5807}{}{. Slizoun náhle vzplanul prudkım plamenem}
{5808}{}{ potom sebou prudce zaškubal a roztøásl se jako rosol}
{5809}{}{, rána zasáhla kritické místo}
{5810}{}{. Bestie tím pochopitelnì znervóznìla}
#
# series 5900 - Centaurs
#
{5900}{}{, kentaur upadl a byl omráèen}
{5901}{}{ jak rána zasáhla jeho citlivé místo}
{5902}{}{, rána zpùsobila masivní selhání všech mozkovıch funkcí}
{5903}{}{, tvùj brutální útok ho zcela omráèil}
{5904}{}{, rána mu ochromila ruku}
{5905}{}{ rána zasáhla citlivé místo a ochromila mu ruku}
{5906}{}{, rána ho odhodila stranou a ochromila mu nohu}
{5907}{}{, kentaur se zakymácel na bezvládné noze a pak se svalil na zem}
{5908}{}{, rána ho oslepila}
{5909}{}{, rána ho zaskoèila nepøipraveného. Chvíli se slepì potácel}
{5910}{}{, rána ho zaskoèila. Zhroutil se na hromadu}
{5911}{}{, rána kentaura pøekvapila. Zhroutil se a zùstal leet}
{5912}{}{. Útok nebyl tak efektivní jak by mohl bıt}
#
# series 6000 - Robots
#
{6000}{}{, útok poškodil jeho konstrukci}
{6001}{}{, z robota se zajiskøilo a na chvíli strnul bez pohybu}
{6002}{}{, rána zasáhla energetickı zdroj a vyøadila robota z chodu}
{6003}{}{, rána zasáhla øídící procesor a zpùsobila masivní selhání obvodù}
{6004}{}{. Robot se pokouší pøemostit poškozené okruhy}
{6005}{}{. Robot provádí kontrolu poškození a pokouší se pøemostit vyøazené okruhy}
{6006}{}{, rána zasáhla nìkolik klíèovıch obvodù a zpùsobila robotovi tìké poškození}
{6007}{}{, rána tìce narušila konstrukci}
{6008}{}{, rána zasáhla hlavní souèástku a tìce ji poškodila}
{6009}{}{. Robot se zapotácel}
{6010}{}{, rána zasáhla pohonnou jednotku a definitivnì poslala robota mezi šrot}
{6011}{}{. Robot nìkolik vteøin zkoušel pøemostit vadné okruhy, ale selhal a s tøeskem se zhroutil na zem}
{6012}{}{. Robot vybuchl v oblaku jisker}
{6013}{}{, rána mu roztøíštila èelní panel a vyøadila z provozu všechny senzory}
#
# series 6100 - Dogs
#
{6100}{}{, rána ho srazila k zemi}
{6101}{}{, rána ho zasáhla do èumáku}
{6102}{}{. Pes upadl na zem, ale stále dıchá}
{6103}{}{, pes vykašlává krvavé hleny}
{6104}{}{, rána mu zmrzaèila nohu}
{6105}{}{, rána mu zmrzaèila nohu. Pes se zkouší postavit, ale nepodaøilo se mu to}
{6106}{}{. Oslepené zvíøe vyje bolestí}
{6107}{}{, rána to ubohé zvíøe vykastrovala}
#
# series 6200 - Manti
#
{6200}{}{, rána srazila hmyz k zemi}
{6201}{}{, hmyz se zhroutil}
{6202}{}{. Zásah byl tak strašnı, e hmyz uvauje, zda má ještì vùbec cenu ít}
{6203}{}{, rána mu urvala nohy}
{6204}{}{, hmyz si olizuje zranìní. V pøedních nohách drí utrené zadní nohy}
{6205}{}{, rána prorazila jeho chitinovı krunıø}
{6206}{}{. Hmyz se tøese a nelidsky vøíská}
{6207}{}{, rána ho pøevrátila na záda. Jeho noha visí na kousku chrupavky}
{6208}{}{, zásah mu odtrhl køídla}
{6209}{}{, rána prorazila jeho chitinovı krunıø a odhodila ho stranou}
{6210}{}{, pøesnı zásah zmutovanı hmyz dokonale oslepil}
#
# series 6300 - Deathclaw
#
{6300}{}{. I tato bestie byla tímto omraèujícím útokem dokonale zaskoèena}
{6301}{}{, rána ho tìce ochromila. Páraè rozevøel své obrovské èelisti, zachvìl se a divoce zavrèel}
{6302}{}{. Vısledkem je masivní poškození páraèovıch oèí}
#
# series 6400 - Spore Plant
#
{6400}{}{. Rána prorazila chabı pokus plevele zakrıt se listy}
{6401}{}{. Rána odtrhla nìkolik listù}
{6402}{}{. Rána mu pøelomila stonek}
{6403}{}{. Útok mu poškodil nìkolik koøenù}
{6404}{}{. Rána rozprášila pyl do okolí}
{6405}{}{. Rána ho témìø odhodila dozadu}
{6406}{}{. Rána poškodila nìkolik vìtvièek}
#
# series 6500 - The Player
#
{6500}{}{. Pokud se doiješ zítøka, bude tì poøádnì bolet hlava}
{6501}{}{. Proti tomuto skvìle míøenému zásahu ti tvoje brnìní nebylo nic platné}
{6502}{}{. Na kratièkou chvíli jsi pocítil pøíšernou bolest a potom tì pohltila tma...}
{6503}{}{, rána prorazila tvoji ochranu. Odletìl jsi dozadu jako míè}
{6504}{}{, ten šok uvrhl všechno kolem na okamik do tmy. Po chvíli jsi uvidìl, e nevidíš}
{6505}{}{. Mìl jsi pøíleitost zahlédnout svoje tìlo a poprvé v ivotì jsi vidìl i svoje záda, kdy tvá hlava plachtila vzduchem}
{6506}{}{. Kupodivu tohle zranìní nevypadá hùø ne obvykle}
{6507}{}{, rána tì na chvíli omráèila}
{6508}{}{. Cítíš bolest}
{6509}{}{. Útok zanechal tvoji ruku nepouitelnou}
{6510}{}{, zásah prorazil tvojí zbroj. Z ruky ti trèí zlomená kost}
{6511}{}{, zásah prorazil tvoje brnìní. Tvoje ruka zùstala bezvládnì viset}
{6512}{}{. Podlitina bude vypadat krásnì a s tìmi jizvami se budeš moci pochlubit na mejdanu}
{6513}{}{, rána zasáhla vnitøní orgány. Tvoje krev zurèivì dopadá na zem}
{6514}{}{, tvoje hlava se protoèila kolem dokola}
{6515}{}{, rána ti zlomila nohu a poslala tì efektním obloukem k zemi}
{6516}{}{, rána prorazila tvoje brnìní. Byl jsi sraen k zemi a tvoje koleno je na kaši}
{6517}{}{. Bolest zlomené nohy pøerušilo a milosrdné bezvìdomí}
{6518}{}{. Bolestivı zásah tì pøinutil o kus ustoupit}
{6519}{}{. Naneštìstí pro tebe zpùsobil zásah okamitou ztrátu zraku}
{6520}{}{. Chvíli bude trvat ne si z oèí vytøeš krev}
{6521}{}{, zásah prorazil tvoje brnìní. Kdy jsi zjistil, e nevidíš, omdlel jsi}
{6522}{}{. Máš podivnı pocit. Zøejmì to bude tím, e umíráš}
{6523}{}{, zásah tì donutil shrbit se}
{6524}{}{. Popadl ses za podbøišek a v bolestech ses skácel k zemi}
{6525}{}{. Bolest je tak hrozná, e tì srazila k zemi. Ajajaj}
{6526}{}{. Ve vesmíru neexistují slova, která by popsala bolest, kterou teï proíváš}


# Fallout 2:

#
# series 6700 - Gecko
#
{6700}{}{. Útok pronikl geckonovım krunıøem}
{6701}{}{. Zásah odtrhl ještìrce nìkolik velkıch kusù slizké kùe}
{6702}{}{. Rána zlomila geckonovi nìkolik prstù}
{6703}{}{. Rána ještìrce vyrazila dech}
{6704}{}{. Rána geckona odhodila nazpìt}
{6705}{}{. Rána ho témìø odhodila nazpìt}
{6706}{}{. Rána zranila geckonovu konèetinu}
#
# series 6800 - Alien
#
{6800}{}{. Zásah prorazil alienùv chabı pokus o obranu}
{6801}{}{. Po zásahu se do okolí rozstøíkly cákance slizu}
{6802}{}{. Zásah mu rozdrtil nìkolik chapadel}
{6803}{}{. Rána poškodila jeho dıchací otvor}
{6804}{}{. Jeho mozek se rozstøíkl po okolí}
{6805}{}{. Rána ho témìø odhodila nazpìt}
{6806}{}{. Rána rozmaèkala nìkolik jeho tykadel}
#
# series 6900 - Giant Ant
#
{6900}{}{. Zásah prorazil krunıø obøího mravence}
{6901}{}{. Rána urvala mravenci nìkolik jeho antének}
{6902}{}{. Zásah mu zlomil nìkolik tykadel}
{6903}{}{. Zásah ho tìce zranil}
{6904}{}{. Rána ho odhodila dozadu}
{6905}{}{. Rána ho témìø odhodila dozadu}
{6906}{}{. Zásah mu poškodil èást exoskeletonu}
#
# series 7000 - Gun Turret  -- WIP! Won't Work!
#
{7000}{}{. Zásah prorazil krunıø obøího mravence}
{7001}{}{. Rána urvala mravenci nìkolik jeho antének}
{7002}{}{. Zásah mu zlomil nìkolik tykadel}
{7003}{}{. Zásah ho tìce zranil}
{7004}{}{. Rána ho odhodila dozadu}
{7005}{}{. Rána ho témìø odhodila dozadu}
{7006}{}{. Zásah mu poškodil èást exoskeletonu}

# Series 7100 - End Bos - The Master
{7100}{}{, útok prorazil jeho bio-organickou obranu}
{7101}{}{, zásah zpùsobil Vùdci váné problémy}
{7102}{}{, útok prorazil jeho bio-organickou obranu a vyøadil z èinnosti nìkolik vedlejších okruhù}
{7103}{}{, Vùdce se pokouší pøeskupit svoje ochranné bariéry}
{7104}{}{, zásah zpùsobil pøetíení Vùdcovıch systémù}
{7105}{}{. Útok, jak se zdá, nezpùsobil Vùdci a tolik škody}
{7106}{}{. Rána prorazila jeho bio-organické obranné systémy a oslepila ho}
