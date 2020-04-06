>>> ARRAYS CONCEPT <<<

Sfall introduces new method of storing variables - arrays.

Array is basically a container which can store variable number of values (elements). Each element in array can be of any type.
Arrays can be extremely useful for some more advanced scripting, in conjunction with loops.

Array elements are accessed by index or key. For example:

    // this code puts some string in array "list" at index 5:
    list[5] := "Value";


There are 2 different types of arrays currently available:
1) Lists - a set of values with specific size (number of elements), where all elements have numeric indexes starting from zero (0) up to array length minus one.
For example:

    // this creates list with 3 elements. Element "A" has index 0, element "B" has index 1, element "C" - 2
    list := ["A", "B", "C"];

Limitations:
- all indexes are numeric, starting from 0;
- to assign value to a specific index, you must first resize array to contain this index
(for example, if list is of size 3 (indexes from 0 to 2), you can't assign value to index 4 unless you change list size to 5 first).


2) Maps (or associative arrays) - a set of key=>value pairs, where all elements (values) are accessed by corresponding keys.
Differences from list:
- maps don't have specific size (to assign values, you don't need to resize array first);
- keys, just like values, can be of any type (but avoid using -1 as array keys or you won't be able to use some functions reliably).

Both array types have their pros and cons and are suited for different tasks.


>>> ARRAYS SYNTAX <<<

Basically arrays are implemented using number of new operators (scripting functions). But for ease of use, there are some new syntax elements:

1) Accessing elements. Use square brackets:

    display_msg(arr[5]);
    mymap["price"] := 515.23;

2) Alternative accessing for maps. Use dot:

    display_msg(mymap.name);
    mymap.price := 232.23;

3) Array expressions. Create and fill arrays with just one expression:

    // create list with 5 values
    [5, 777, 0, 3.14, "Cool Value"]

    // create map:
    {5: "Five", "health": 50, "speed": 0.252}

NOTES:
- make sure to call "fix_array" if you want new array to be available in the next frame or "save_array" if you want to use it for a longer period
(see next section for details)


4) Iterating in loop. Use "foreach" key word like this:

    foreach (item in myarray) begin
        // this block is executed for each array element, where "item" contains current value on each step
    end

    // alternative syntax:
    foreach (key: item in myarray) begin
        // "key" will contain current key (or numeric index, for lists)
    end

See "Script editor\docs\sslc readme.txt" file for full information on new SSL syntax features.

>>> STORING ARRAYS <<<

Apart from lists/maps arrays are divided by how they are stored.
There a 3 types of arrays:

1) Temporary. They are created using temp_array function or when using array expressions.
Arrays of this type are auto-deleted at the end of the frame. So, for example, if you have a global script which runs at regular intervals,
where you create temp_array, it will not be available next time your global script is executed.

2) Permanent. They are created using "create_array" function or "fix_array" (from pre-existing temporary array).
This type of arrays are always available (by their ID) until you start a new game or load a saved game (at which point they are deleted).

3) Saved. If you want your array to really stay for a while, use function "save_array" to make any array "saved". However, they are, like permanent arrays,
"deleted" from memory when loading game. In order to use them properly, you must load them from the savegame using "load_array" whenever you want to use them.
Example:

    variable savedArray;
    procedure start begin
        if game_loaded then begin
            savedArray := load_array("traps");
        end else begin
            foreach trap in traps begin
                ....
            end
        end
    end



>>> PRACTICAL EXAMPLES <<<

> Use arrays to implement variable-argument procedures:

    // define it
    procedure give_item(variable critter, variable pidList) begin
        foreach (pid: qty in pidList) begin
            give_pid_qty(critter, pid, qty);
        end
    end

    // call it:
    call give_item(dude_obj, {PID_SHOTGUN: 1, PID_SHOTGUN_SHELLS: 4, PID_STIMPAK: 3});


> Create arrays of objects (maps) for advanced scripting:

    variable traps;
    procedure init_traps begin
        // just a quick example, there is a better way of doing it...
        traps := load_array("traps");
        if (traps == 0) then begin
            traps := [];
            save_array("traps", traps);
        end
        foreach k: v in traps begin
            traps[k] := load_array("trap_"+k); // each object is stored separately
        end
    end

    procedure add_trap(variable trapArray) begin
        variable index;
        index := len_array(traps);
        save_array("trap_"+k, trapArray);
        array_push(traps, trapArray);
    end

    // use them:
    foreach trap in traps begin
        if (self_elevation == trap["elev"] and tile_distance(self_tile, trap["tile"]) < trap["radius"]) then
            // kaboom!!!
        end
    end



>>> ARRAY OPERATORS REFERENCE <<<

*mixed means any type

> int create_array(int size, int flags):
- creates permanent array (but not "saved")
- if size is >= 0, creates list with given size
- if size == -1, creates map (associative array)
- if size == -1 and flags == 2, creates a "lookup" map (associative array) in which the values of existing keys are read-only and can't be updated.
This type of array allows you to store a zero (0) key value
- NOTE: in earlier versions (up to 4.1.3/3.8.13) the second argument is not used, just use 0
- returns arrayID (valid until array is deleted)

> int temp_array(int size, int flags):
- works exactly like "create_array", only created array becomes "temporary"

> void fix_array(int arrayID):
- changes "temporary" array into "permanent" ("permanent" arrays are not automatically saved into savegames)

> void set_array(int arrayID, mixed key, mixed value):
- sets array value
- if used on list, "key" must be numeric and within valid index range (0..size-1)
- if used on map, key can be of any type
- to "unset" a value from map, just set it to zero (0)
- NOTE: to add a value of 0 for the key, use the float value of 0.0
- this works exactly like statement:
    arrayID[key] := value;

> mixed get_array(int arrayID, mixed key):
- returns array value by key or index
- if key doesn't exist or index is not in valid range, returns 0
- works exactly like expression:
    (arrayID[key])

> void resize_array(int arrayID, int size):
- changes array size
- applicable to maps too, but only to reduce elements
- there are number of special negative values of "size" which perform various operations on the array,
use macros sort_array, sort_array_reverse, reverse_array, shuffle_array from sfall.h header

> void free_array(int arrayID):
- deletes any array
- if array was "saved", it will be removed from a savegame

> mixed scan_array(int arrayID, mixed value):
- searches for a first occurence of given value inside given array
- if value is found, returns it's index (for lists) or key (for maps)
- if value is not found, returns -1 (be careful, as -1 can be a valid key for a map)

> int len_array(int arrayID):
- returns number of elements or key=>value pairs in a given array
- if array is not found, returns -1  (can be used to check if given array exist)

> mixed array_key(int arrayID, int index):
- don't use it directly; it is generated by the compiler in foreach loops
- for lists, returns index back (no change)
- for maps, returns a key at the specified numeric index (don't rely on the order in which keys are stored though)
- can be checked if given array is associative or not, by using index (-1): 0 - array is list, 1 - array is map

> int arrayexpr(mixed key, mixed value):
- don't use it directly; it is used by compiler to create array expressions
- assigns value to a given key in an array, created by last "create_array" or "temp_array" call
- always returns 0

> void save_array(mixed key, int arrayID):
- makes the array saveable; it will be saved in sfallgv.sav file when saving the game
- arrayID is associated with given "key"
- array becomes permanent (if it was temporary) and "saved"
- key can be of any type (int, float or string)
- if you specify 0 as the key for the array ID, it will make the array "unsaved"

> int load_array(mixed key):
- load array from savegame data by the same key provided in "save_array"
- arrayID is returned or zero (0) if none found



>>> BACKWARD COMPATIBILITY NOTES <<<

For those who used arrays in their mods before sfall 3.4:
1) There is an INI parameter "arraysBehavior" in "Misc" section of ddraw.ini. If set to 0, all scripts which used sfall arrays before should work. This basically changes that "create_array" will create permanent arrays which are "saved" by default and their ID is also permanent. It is 1 by default.
2) How savegame compatibility is handled?
Saved arrays are stored in sfallgv.sav file (in savegame) in new (more flexible) format, just after the old arrays. So basically, when you load older savegame, sfall will load arrays from old format and save them to new format on next game save. If you load savegame made with sfall 3.4 using sfall 3.3 (for example), game shouldn't crash, but all arrays will be lost.
3) Previously you had to specify size in bytes for array elements. This parameter is now ignored and you can store strings of arbitrary length in arrays.

