#
#   Messages from skill.c
#
#
#   SKILL NAMES
#
{100}{}{Armes l�g�res}
{101}{}{Armes lourdes}
{102}{}{Armes � �nergie}
{103}{}{Corps � Corps}
{104}{}{Armes de M�l�e}
{105}{}{Projectiles}
{106}{}{Secourisme}
{107}{}{M�decine}
{108}{}{Esquive}
{109}{}{Crochetage}
{110}{}{Voleur}
{111}{}{Pi�ges}
{112}{}{Science}
{113}{}{R�paration}
{114}{}{Discours}
{115}{}{Troc}
{116}{}{Jeu}
{117}{}{Vie en plein air}
#
#   SKILL DESCRIPTIONS
#
{200}{}{Maniement, entretien et connaissance g�n�rale des petites armes � feu. - Pistolets, mitraillettes et carabines.}
{201}{}{Fonctionnement et entretien de l'armement lourd. - Mini-canons, lance-roquettes, lance-flammes et autres.}
{202}{}{Entretien et chargement des armes � �nergie. Comment armer et manier des armes utilisant des techniques au laser ou au plasma.}
{203}{}{Divers arts martiaux, combats de boxe et Corps � Corps. Coups de pieds et coups de poings. Cela inclut les poings am�ricains et les gants.}
{204}{}{Capacit� � combattre avec des armes blanches. Couteaux, massues, lances, matraques, etc.}
{205}{}{Capacit� � lancer des armes � la main, telles que des couteaux, des lances et des grenades.}
{206}{}{Capacit� � pratiquer les premiers soins. Traitement des coupures l�g�res, �corchures et autres maux b�nins. La comp�tence Secourisme permet de gu�rir des points d'impact plus facilement que par un simple repos.}
{207}{}{Capacit� � traiter les l�sions importantes et � soigner les membres estropi�s.  Sans cette comp�tence, la dur�e d'attente avant de pouvoir retrouver l'usage des membres estropi�s est beaucoup plus importante.}
{208}{}{Mouvement furtif permettant de passer inaper�u. En cas de succ�s, il devient plus difficile de te localiser. Il est impossible de courir et de se d�placer furtivement en m�me temps.}
{209}{}{Capacit� � ouvrir les serrures sans la bonne cl�. L'utilisation de passe-partout classiques ou �lectroniques am�liore nettement cette comp�tence.}
{210}{}{Facult� de s'approprier ce qui appartient � autrui. S'applique aux personnes et aux lieux.}
{211}{}{Capacit� � rep�rer et retirer les pi�ges pos�s. Permet �galement de poser des explosifs.}
{212}{}{Recouvre diverses comp�tences scientifiques, notamment en informatique, biologie, physique et g�ologie.}
{213}{}{Mise en application de la comp�tence Science. R�paration des �quipements, m�canismes et appareils �lectroniques endommag�s.}
{214}{}{Capacit� � communiquer de mani�re pratique et efficace. Capacit� � se montrer persuasif, � mentir et � ne pas se faire prendre.}
{215}{}{Sens du commerce. Capacit� � tout marchander, � la vente comme � l'achat.}
{216}{}{L'art et la mani�re de parier. Talent aux jeux de cartes, de d�s et autres.}
{217}{}{Connaissance pratique de la vie en plein air et capacit� � survivre en milieu hostile. Connaissance de la flore et de la faune.}
#
#   SKILL ATTRIBUTES
#
#   Updated: 6/5/97 KSW
#   Updated to New Skill System: 9/16/98 rwh2
#
{300}{}{+ AG}
{301}{}{+ AG}
{302}{}{+ AG}
{303}{}{+ (AG + FO)/2}
{304}{}{+ (AG + FO)/2}
{305}{}{+ AG}
{306}{}{+ (PE + IN)/2}
{307}{}{+ (PE + IN)/2}
{308}{}{+ AG}
{309}{}{+ (PE + AG)/2}
{310}{}{+ AG}
{311}{}{+ (PE + AG)/2}
{312}{}{+ (2 x IN)}
{313}{}{+ IN}
{314}{}{+ (2 x CR)}
{315}{}{+ (2 x CR)}
{316}{}{+ (3 x CH)}
{317}{}{+ (EN + IN)/2}
#
#   Skill Use Text
#
{500}{}{Tu gu�ris %d points d'impact.}
{501}{}{Tu n'as pas besoin de soins.}
{502}{}{%s n'a pas besoin de soins.}
{503}{}{Tes soins restent sans effets.}
{505}{}{Tu m�rites %d PE pour avoir su affiner tes comp�tences.}
{510}{}{\nskill_use: comp�tence utilis�e incorrecte.}
{512}{}{On ne peut plus rien pour les morts.}
{513}{}{Les morts ont droit au repos �ternel.}
{514}{}{Dieu ait son �me ! Il faut se faire une raison.}
{520}{}{Tu soignes : %s.}
{521}{}{Tu soignes : %s.}
{525}{}{Tu n'as pas r�ussi � soigner : %s.}
{526}{}{Tu n'as pas r�ussi � soigner : %s.}
{530}{}{Oeil crev�}    # Lines 530-534 are the endings to lines 525 & 526.
{531}{}{bras gauche estropi�}
{532}{}{bras droit estropi�}
{533}{}{jambe droite estropi�e}
{534}{}{jambe gauche estropi�e}
{550}{}{Tu n'as pas r�ussi � forcer la serrure.}
{551}{}{Tu n'as r�ussi � rep�rer aucun pi�ge.}
{552}{}{Tu n'as rien appris.}
{553}{}{R�paration impossible.}
{570}{}{Tu t'es fait surprendre en train de voler : %s.}
{571}{}{Tu as vol� : %s.}
{572}{}{Tu t'es fait surprendre en train de d�poser : %s.}
{573}{}{Tu as d�pos� : %s.}
{590}{}{Tu as �puis� tes comp�tences en la mati�re. Attends un moment.}
{591}{}{Tu es � bout de forces.}
{592}{}{Le surmenage, c'est mauvais pour le coeur.}

# Fallout 2!
{600}{}{Tu ne disposes pas du niveau de comp�tence permettant de gu�rir les membres estropi�s.}
{601}{}{L'unit� robotique n'est pas r�parable.}



#
# Fallout 2: Party Member skill use generic responses
#

#   I'll try
{1000}{}{Laisse-moi t'aider.}
{1001}{}{Je peux faire �a.}
{1002}{}{Je m'en occupe.}
{1003}{}{Ca m'a fait plaisir d'�tre utile.}
{1004}{}{Ok.}
{1005}{}{Laisse-moi essayer.}

#   Player wants to do it
{1100}{}{En cas de probl�me, appelle-moi.}
{1101}{}{Tu t'en charges ?}
{1102}{}{Bon, si tu veux.}
{1103}{}{Vas-y, essaie.}
{1104}{}{Non, toi, vas-y.}
