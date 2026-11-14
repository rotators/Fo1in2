<p align="center"><img src="fo1_spanish.png" alt="Fallout 1 Spanish"/></p>

Fallout 1 Language Pack - Spanish / Español
-------------------------------------------

Traducción al español de FALLOUT ET TU.

Desde la última versión de la traducción mejorada, se han corregido muchos errores y se han adaptado todos los gráficos.
Si encuentras cualquier problema o error, házmelo saber o, si lo prefieres, colabora directamente en este repositorio.

### Instalación

1. Cambia el idioma en `fallout2.cfg` a español: `language=spanish`.
2. Descomenta los mods de la traducción en `mods_order.txt` para que se carguen:
   - `fo1_lang_spanish_base`: siempre es necesario, contiene la interfaz y los textos comunes.
   - `fo1_lang_spanish_male` / `fo1_lang_spanish_female`: elige uno según el género de tu personaje.
3. (Opcional) Descomenta cualquiera de los otros mods que se han traducido:
   - `fo1_interface`: si quieres la interfaz original de Fallout 1 (mirar punto 4).
   - `fo1_new_premades`: si quieres nuevos personajes predefinidos.
   - `fo1_robodog`: si quieres que Albóndiga sea un roboperro.
   - `fo1_alternative_Junktown_Endings`: si quieres finales alternativos para Ciudad Vertedero.
   - `InterfaceUpscaled`: si quieres las pantallas de carga en mayor resolución.
4. (Opcional) Recomiendo usar CE (inicia el juego con `fallout2-ce.exe`), ya que tiene muchas mejoras sobre Fallout normal. Pero ahora mismo CE tiene un error para cargar la interfaz principal de otros lenguajes. Ya está arreglado para la interfaz de Et Tu (Fallout 2), pero si utilizas `fo1_interface`necesitas hacer lo siguiente:
   - Copia `HR_IFACE_800.FRM`de `fo1_interface\art\spanish\intrface\` a `fo1_interface\art\intrface\` (sobrescribe cuando te pregunte).
