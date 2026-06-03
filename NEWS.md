Notable changes since last release ([v1.15.3735](https://github.com/rotators/Fo1in2/releases/tag/v1.15.3735))

- **Added**: Czech localization
- **Added**: Updated Sfall to version 4.5
- **Fixed**: A few text corrections / style improvements.
- **Fixed**: Added a combat fail-safe to Neal, since there was a possibility of him attacking the player in the Skum Pitt raid, if the player got caught stealing the Urn before.
- **Fixed**: Aradesh dialog reaction to Tandi's death (if kidnapped and not returned) would never show up due to logic issues with variables.
- **Fixed**: Changed "Nothing, bye." exit dialog text to generic "goodbye" strings in Iguana Bob dialog, since it never matched with the current dialog.
- **Fixed**: Explosive traps would show wrong text when looking at them.
- **Fixed**: If the V13 water thief gets killed by anyone but the player, he would not get any experience points.
- **Fixed**: If the player destroyed Mariposa and then joins the Unity while talking to the Master, the dipping-in-Vats cutscene won't play anymore.
- **Fixed**: Looking at Vance in the Hub after knowing his name would print an error message in the log window.
- **Fixed**: Typos in audio references in dialog files
- **Fixed**: Various TMA strings couldn't be accessed due to mismatching line numbers.
- **Tweaked**: Rebalanced the amount of bonus hitpoints for critters when using the Tougher Humans and Mutants settings.
- **Tweaked**: Replaced merchant restocking condition with unsigned int comparison, so the timer won't break after many (ingame) years have passed.
