# For lines 177 and 180 and 181, spaces are intentional.
# Line 177 is prepended to encounter type. (they begin at 183 below)
{177}{}{Te encuentras con }
{178}{}{Sí.}
{179}{}{No.}
{180}{}{Ganas }
{181}{}{ puntos de experiencia por utilizar tu habilidad de Supervivencia con éxito.}
# Line 182 is appended after 177 and the encounter type. Period and space is intentional.
{182}{}{. ¿Quieres acercarte?}
# These are apended to line 177.
{183}{}{unos flotadores}
{184}{}{unas mantis}
{185}{}{unas ratas}
{186}{}{unos campesinos siendo atacados por saqueadores}

{289}{}{Te topas con una manada de gecos hambrientos.}
{290}{}{¡Te atacan gecos de fuego!}
{291}{}{Te topas con unos feroces gecos de fuego.}

#
# 100 to 103 are NOT USED, looks like it was old code for finding the Radscorpion Cave from the worldmap.
#
{100}{}{Tal y como están las cosas, no pueden haber ido muy lejos. Deben tener una guarida por aquí cerca.}
{101}{}{Parece que han viajado hasta aquí desde un lugar cercano.}
{102}{}{Por lo visto, venían de un lugar muy al norte de aquí.}
{103}{}{Aparentemente, solo estaban merodeando por el yermo.}

{106}{}{¡Te topas con una gran manada de escorpiones rad!}
{107}{}{Te topas con una manada de escorpiones rad.}
{108}{}{Te topas con una familia de ratas topo.}

# DEHYDRATION ENCOUNTERS
{109}{}{Has evitado un gravísimo caso de deshidratación al buscar agua. La búsqueda te lleva una hora más.}
{110}{}{Has evitado un gravísimo caso de deshidratación al buscar agua. La búsqueda te lleva }
{111}{}{ horas.}
{112}{}{Tus reservas de agua están bajas. Buscas durante una hora pero no consigues encontrar más agua. Sufres una grave deshidratación y pierdes }
{113}{}{ puntos de salud.}
{114}{}{Tus reservas de agua están bajas. Buscas durante }
{115}{}{ horas pero no consigues encontrar más agua. Sufres una grave deshidratación y pierdes }
{116}{}{ puntos de salud.}
{117}{}{Buscas agua por el alto desierto durante una hora, pero no encuentras bastante para satisfacer tu sed. Pierdes un punto de salud.}
{118}{}{Buscas agua por el alto desierto durante una hora, pero no encuentras bastante para satisfacer tu sed. Pierdes }
{119}{}{ puntos de salud.}
{120}{}{Buscas agua por el alto desierto durante }
{121}{}{ horas, pero no encuentras bastante para satisfacer tu sed. Pierdes un punto salud.}
{122}{}{Buscas agua por el alto desierto durante }
{123}{}{ horas, pero no encuentras bastante para satisfacer tu sed. Pierdes }
{124}{}{ puntos de salud.}

{125}{}{Consigues evitar la deshidratación gracias a tus reservas de agua.}

{1250}{}{Consigues evitar la deshidratación gracias a tus reservas de }
{1251}{}{.}
{1160}{}{un punto de salud.}

# CRITICAL SUCCESS ON OUTDOORSMAN CHECK
{147}{}{Consigues evitar la deshidratación por haber buscado agua. La búsqueda  te lleva 1 hora.}
{138}{}{ Llenas }
{159}{}{tus petacas}
{160}{}{ con agua potable.}
{165}{}{Ganas }
{166}{}{ puntos de experiencia por utilizar tu habilidad de Supervivencia con éxito.}

# NORTH_TABLE ENCOUNTERS
#
#
# North1
#
# if pass Perception check or have Awareness:
#   197 Uh-oh... a raiding party!
# else is:
{105}{}{¡¡¡EMBOSCADA!!!}
#
# North2
#
{104}{}{Has llegado en plena batalla entre escorpiones rad y ratas topo.}
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
{131}{}{¡¡¡ESTAMPIDA!!!}
#
# South2
#
{132}{}{¡Te has topado con una gran manada de escorpiones rad!}
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
{144}{}{Te has topado con un gran grupo de ratas topo.}
#
# South6
#
{145}{}{Te encuentras con un grupo de escorpiones rad salvajes.}
#
#
# SHADY ENCOUNTERS
#
#
# Shady1
#
{146}{}{Te encuentras con unos campesinos que están siendo atacados.}
#
# Shady2
#
# -Dehydration-
#
# Shady3
#
{169}{}{Tropiezas con una familia de escorpiones rad.}
#
# Shady4
#
{170}{}{Te cruzas con un mercader que viaja con unos guardias.}
#
# unless he's dead, then you get
#
{305}{}{Te encuentras con lo que queda de los guardias hostiles del mercader Duc.}
#
# once that has been seen, call Shady3
#
# Shady5
#
{175}{}{Te encuentras un viajero.}
# or if killed,
{171}{}{Encuentras un viajero muerto.}
#
# else call Shady2
#
# Shady
#
{126}{}{Te has topado con unos escorpiones rad que cazan ratas topo.}
{127}{}{Se acercan humanoides flacos con aspecto hostil y piel verdusca.}
{128}{}{El suelo está cubierto de trastos y de rocas. Te preguntas si puede quedar algo de valor...}
#
# UNUSED ENTRY:
{129}{}{¡Un escorpión rad te ha tendido una emboscada!}
#
{130}{}{Aquí ves un cadáver medio devorado.}
{134}{}{¡Una manada de escorpiones rad peligrosos surge del desierto!}
{135}{}{Encuentras un grupo de centinelas patrullando.}
{136}{}{Te cruzas con un mercader con varios guardias.}
{174}{}{Te cruzas con los restos de un mercader y sus guardias.}
{137}{}{Ves a un campesino cuidando de varios brahmines.}
{139}{}{Escorpiones rad cazan ratas topo junto a las ruinas de una ciudad.} # Sduibek, Fallout ''Fixt''
{172}{}{Te encuentras objetos tirados por el suelo.}
{176}{}{Te has topado con un pequeño grupo de construcciones derruidas y abandonadas.}
#
#
# RAIDER_TABLE ENCOUNTERS
#
#
# Raider1
#
{133}{}{¡Unos saqueadores te tienden una emboscada!}
#
# Raider2 - half chance of either msg displayed, but encounter the same
#
{143}{}{¡¡¡Saqueadores!!!}
{197}{}{¡Uh-oh... un grupo de saqueadores!}
#
# Raider3
#
{173}{}{Divisas los restos de una caravana atacada por saqueadores.}
#
# Raider4
#
{310}{}{¡Ataque de un pequeño grupo de saqueadores!}
#
# Raider5 - 198 always, plus 196 half the time
#
{198}{}{A lo lejos ves a un saqueador solitario.}
{196}{}{¡Escorpiones rad, acercándose!}
#
# Raider6 - displays and runs both (because bodies are empty)
#
{199}{}{Has dado con los restos de un campo de batalla. El suelo está cubierto de cuerpos.}
#plus 196
#
#
{223}{}{Divisas una manada de coyotes salvajes merodeando.}
{200}{}{¡Escorpiones rad, acercándose!}
{224}{}{Ves a varios individuos explorando.}
{225}{}{Te encuentras con un grupo comerciantes y guardias.}
{226}{}{Asistes a una pequeña guerra... ¡hombres contra mutantes!}
{227}{}{¡Una horda de escorpiones rad se acerca de aquí!}
#
{250}{}{Se te acercan varios hombres con Servoarmaduras.}
{251}{}{Ves un grupo de mercaderes y guardias.}
{252}{}{Asistes a una horrible batalla entre varios saqueadores del desierto y un grupo de hombres con Servoarmaduras.}
{253}{}{Ves varios mutantes explorando una zona hostil.}
{254}{}{Divisas unas criaturas extrañas...}
{256}{}{¡Una patrulla de Supermutantes está pasando cerca!}

{257}{}{Divisas las ruinas de una aldea.}

# UNUSED ENTRY:
{255}{}{Encuentras algunos objetos.}

{279}{}{Divisas chatarra diseminada sobre la arena.}
{280}{}{Tropiezas con un grupo de Supermutantes guerreros.}
{281}{}{Tropiezas con una manada de criaturas rarísimas.}
{282}{}{Tropiezas con una manada de escorpiones rad hambrientos.}
{283}{}{Sientes náuseas y te parece que el aire quema. ¡Una criatura mutante se te acerca de repente!}
{284}{}{Te has topado con unas extraña criaturas mutantes.}
{285}{}{Has encontrado algo que parece salido de una vieja película de ciencia ficción.}
{286}{}{¡¡La Garra Mortal!!}
{287}{}{Te has topado con una manada migratoria de escorpiones rad. Parecen estar huyendo de...}
{288}{}{Te encuentras una criatura mutada del desierto.}
#
{299}{}{A cierta distancia ves varios escorpiones rad.}
{300}{}{Te cruzas con un campesino harapiento.}
{301}{}{Encuentras una rata topo.}

# was: "The Deathclaw!!"
{302}{}{Una Garra Mortal parece pensar que eres su almuerzo.}

{303}{}{Tropiezas con una manada migratoria de escorpiones rad.}
#
{306}{}{Muy cerca de aquí patrulla una unidad de mutantes. ¡Acompañada por algunas criaturas extrañas!}
{307}{}{Una pequeña partida de guerra de Supermutantes te tiende una emboscada.}
{308}{}{¡Parece que has caído en plena guerra de bandas!}
{309}{}{¡Un grupo de bandidos hostiles se acerca!}
{311}{}{¡Ataque de un pequeño grupo de bandidos!}
{313}{}{¡Un grupo de mantis te ataca de repente!}

# UNUSED ENTRY:
{312}{}{¡Unas ratas te atacan de repente!}

# SPECIAL ENCOUNTERS TEXT:
{314}{}{¡Eh! En serio, están ahí fuera.}
{315}{}{A lo lejos ves un camión volcado.}
{316}{}{Encuentras algunos coches desvencijados en medio del desierto.}
{317}{}{Divisas una cabina de policía al noreste.}
{318}{}{Te cruzas con una manada salvaje de brahmines. Sientes que algo no encaja...}
#
# Fo1in2:
{400}{}{Te topas con un grupo de gecos.}
{401}{}{Te topas con un grupo de gecos dorados.}
{402}{}{¡Cazarrecompensas!}
{403}{}{Ves a unos cazadores a lo lejos.}
{404}{}{¡Una partida de guerra tribal en busca de venganza!}
