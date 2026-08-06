Notable changes since last release ([v1.16.3771](https://github.com/rotators/Fo1in2/releases/tag/v1.16.3771))

- **Added**: Fast Shot trait implementation compatible with Fo2 CE.
- **Fixed**: Auto push function for party members could make them fail to move in certain orientations.
- **Fixed**: Because of a stray night-condition macro, many scripts were checking the beginning of the night wrong (18:00 instead of 19:00).
- **Fixed**: EXP exploit when using lockpicks on the armory door at the BoS bunker.
- **Fixed**: Logic issue in TMA script when pressing enter / numpad enter on an empty input box.
- **Fixed**: Missing or wrongly assigned strings in various script files. Mostly door related.
- **Fixed**: Possible crash related to Jack, the Khan prisoner (cut-content)
- **Fixed**: Script issue in caravan leader script.
- **Fixed**: Show Loot Weight mod is now automatically disabled if CE is detected, since CE has its own implementation.
- **Fixed**: Special radiation death screen could show up even if the player did not die from radiation
- **Fixed**: Tandi wouldn't show floating text when rescued from the Khans.
- **Fixed**: The player could survive receiving huge amounts of rads when he really shouldn't
- **Fixed**: Tthe Night Person trait effects wouldn't clean up correctly at daytime / after loading a savegame.
- **Fixed**: Unlocking the khans cell door would jam it for some reason.
- **Fixed**: Various doors could destroy the used lockpicks on successful unlocking rolls.
- **Tweaked**: Moved power armor weight change from Sfall into script.
- **Tweaked**: ShowLootWeight mini-mod now automatically disables if CE is detected, since CE has a build in feature (loot_weight_indicator=3 in fallout2.cfg)
