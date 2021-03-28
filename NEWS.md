Notable changes since last release ([v1.5.2288](https://github.com/rotators/Fo1in2/releases/tag/v1.5.2288))

- **Added**: All Fo2 lockpick items are now supported in scripts (Lockpicks, Expanded Lockpick set, Electronic Lockpick, Electronic Lockpick MK2).
- **Fixed**: A potential procedure loop in the (generic) super mutant sergeant script when talking to them in disguise.
- **Fixed**: Cathedral technicians would blast the disguise-check code on every game tick, no matter if they see thep player or not. This can cause the game to crash on certain hardware.
- **Fixed**: Gizmo's dead remains (with flies animation) can now be looted correctly.
- **Fixed**: Mines / Traps spatial scripts had no range assigned to them.
- **Fixed**: Mines in the thief circle map didn't want to explode.
- **Fixed**: Player can enter V13 already after waiting 1 day and not 2.
- **Fixed**: Player can't get the Champion reputation state anymore if he is a childkiller.
- **Tweaked**: Reverted the MFC -> SEC item change in super mutant encounters, because they seem to drop SECs on purpose and not by bug. 
- **Tweaked**: Rewrote the interaction between Killian and his shopdoor. Also, the inside shopguard will react to the player now if he is found inside the building at night time.
