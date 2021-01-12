This is a modified copy of sslc, that has a few bugfixes from the original, that will recognise and compile the additional scripting functions provided by sfall, that can also understand some additional syntax, and that has an integrated preprocessor and optimizer.

Unlike the original script compiler, this has not been compiled as a dos program. When using this in place of the original compile.exe but still using p.bat, you need to either get rid of the dos4gw.exe reference from p.bat or replace the original dos4gw.exe with the one in this archive.

If you use fallout script editor, you can extract compile.exe and dos4gw.exe to its \binary folder, or extract them somewhere else and change your preferences in FSE to point there. FSE doesn't seem to be able to tell when errors occur when using this compiler though, so I'd recommend either using sfall's script editor instead or compiling by hand if possible.

When compiling global or hook scripts for sfall 3.4 or below, you _must_ include the line 'procedure start;' before any #includes that define procedures to avoid a few weird problems. (this is no longer required starting from 3.5)

This version of compiler was designed primarily for new sfall functions, but it can safely (and is recommended) to be used with non-sfall scripts as well, as long as you don't use any of the arrays syntax and any sfall scripting functions.

The original unmodified sslc source is over here:
http://www.teamx.ru/eng/files/srcs/index.shtml

============================
=== command line options ===
============================

-q  don't wait for input on error
-n  no warnings
-b  backward compatibility mode
-l  no logo
-p  preprocess source
-O  optimize code (see optimization.txt)
-O<N> set specific level of optimization (0 - off, 1 - basic, 2 - full, 3 - experimental)
-d  print debug messages
-D  output an abstract syntax tree of the program
-o  set output path (follows the input file name)
-s  enable short-circuit evaluation of all AND, OR operators
-m<macro[=val]> defines a macro named "macro" for conditional compilation
-I<path> specify the additional directory to search include files

The original command line option -w to turn on warnings no longer has an effect, since warnings are now on by default

===================================
=== Additional supported syntax ===
===================================

Syntax which requires sfall for compiled scripts to be interpreted, is marked by asterix (*).

> Optional arguments in user-defined procedures. You can only use constants for default values. It basically puts those constants in place of omitted arguments.

new:
    procedure test(variable x, variable y := 0, variable z := -1) begin
    ...
    end
    ...
    call test("value");

old:
    procedure test(variable x, variable y, variable z) begin
    ...
    end
    ...
    call test("value", 0, -1);


> New logical operators AndAlso, OrElse for short-circuit evaluation of logical expressions.
Using these operators allows not evaluate the result of the right of expression if the left expression result is already known, which improves performance running scripts.
Example:
    if (obj andAlso obj_pid(obj) == PID_STIMPAK) then ...

if obj is null, the second condition will not be checked and your script won't fail with "obj is null" error in debug.log

This also has an effect that a value of last computed argument is returned as a result of whole expressions, instead of always 0 (false) or 1 (true):
    obj := false;
    display_msg(obj orElse "something");  // will print "something"


You can also use the -s option the compiler this changed behavior for all the AND, OR operators in the script.
NOTE: Be aware that it may break some old scripts because operators behavior is changed slightly.


> Conditional expressions (python-inspired), also known as ternary operator:

new:
    X := value1 if condition else value2

old:
    if (condition) then
        X := value1;
    else
        X := value2;


> To assign values, you can use the alternative assignment operator from C/Java, instead of the Pascal syntax.

new:
  x = 5;
old:
  x := 5;


> Multiple variable decleration: Multiple variables can be declared on one line, seperated by commas. This is an alterative to the ugly begin/end block, or the bulky single variable per line style.

new:
  variable a, b, c;
old:
  variable begin a; b; c; end


> Variable initialization with expressions: You can now initialize local variables with complex expressions instead of constants.

new:
  variable tile := tile_num(dude_obj);

old:
  variable tile;
  tile := tile_num(dude_obj);

NOTE: if your expression starts with a constant (eg. 2+2), enclose it in parentheses, otherwise compiler will be confused and give you errors.


> Hexadecimal numerical constants: Simply prefix a number with 0x to create a hexadecimal. The numbers 0 to 9 and a-f are allowed in the number. The number may not have a decimal point.

new:
  a := 0x1000;
old:
  a := 4096;


> increment/decrement operators: ++ and -- can be used as shorthand for +=1 and -=1 respectively. They are mearly a syntactic shorthand to improve readability, and so their use is only allowed where +=1 would normally be allowed.

new:
  a++;
old:
  a += 1;


> "break" & "continue" statements: they work just like in most high-level languages. "break" jumps out of the loop. "continue" jumps right to the beginning of the next iteration (see "for" and "foreach" sections for additional details).

new:
  while (i < N) begin
    // ...
    if (/* some condition */) then break;
    // ...
  end

old:
  while (i < N and not(breakFlag)) begin
    // ...
    if (/* condition */) then breakFlag := true;
    // ...
  end

new:
  for (i := 0; i < N; i++) begin
    // ...
    if (/* condition */) then begin
      // action
      continue;
    end
    // else actions
  end

old:
  for (i := 0; i < N; i++) begin
    // ...
    if (/* condition */) then begin
      // action
    end else begin
      // else actions
    end
  end


> "for" loops: Another piece of syntactic shorthand, to shorten while loops in many cases. Parentheses around the loop statements are recommended but not required (when not using parentheses, a semicolon is required after the 3rd loop statement).
new:
  for (i := 0; i < 5; i++) begin
    display_msg("i = "+i);
  end
old
  i := 0;
  while i < 5 do begin
    display_msg("i = "+i);
    i++;
  end

NOTE: "continue" statement in a "for" loop will recognize increment statement (third statement in parentheses) and will execute it before jumping back to the beginning of loop. This way you will not get an endless loop.


> switch statements: A shorthand way of writing big 'if then else if...' blocks
new:
  switch get_attack_type begin
  case ATKTYPE_PUNCH: display_msg("punch");
  case ATKTYPE_KICK: display_msg("kick");
  default: display_msg("something else");
  end
old:
  variable tmp;
  tmp := get_attack_type;
  if tmp == ATKTYPE_PUNCH then begin
    display_msg("punch");
  end else if tmp == ATKTYPE_KICK then begin
    display_msg("kick");
  end else begin
    display_msg("something else");
  end


> empty statements in blocks are allowed: This is just a convenience to save scripters a bit of memory. Some of the macros in the fallout headers include their own semicolons while others do not. With the original compiler you had to remember which was which, and if you got it wrong the script would not compile. Now it's always safe to include your own semicolon, even if the macro already had its own. For example, this would not compile with the original sslc, but will with the sfall edition:

#define my_macro diplay_msg("foo");

procedure start begin
  my_macro;
end


> Procedure stringify operator "@": designed to make callback-procedures a better option and allow for basic functional programming. Basically it replaces procedure names preceeded by "@" by a string constant.
Not many people know that since vanilla Fallout you can call procedures by "calling a variable" containing it's name as a string value. There was a couple of problems using this:
- optimizer wasn't aware that you are referencing a procedure, and could remove it, if you don't call it explicitly (can be solved by adding making procedure "critical")
- you couldn't see all references of a procedure from a Script Editor
- it was completely not obvious that you could do such a thing, it was a confusing syntax

old:
    callbackVar := "Node000";
    callbackVar();

new:
    callbackVar := @Node000;
    callbackVar();



> *arrays: In vanilla fallout arrays had to be constructed by reserving a block of global/map variables. Since sfall 2.7, specific array targeted functions have been available, but they are fairly messy and long winded to use. The compiler provides additional syntactic shorthand for accessing and setting array variables, as well as for array creation. When declaring an array variable, put a constant integer in []'s to give the number of elements in the array. (before sfall 3.4 you had to specify size in bytes for array elements, now it's not required, see "arrays.txt" for more information)

new:
  procedure bingle begin
    variable a[2];
    a[0]:=5;
    a[a[0]-4]:=a[0] + 4;
    display_msg("a[0]="+a[0]+", a[1]="+a[1]);
  end
old:
  procedure bingle begin
    variable a;
    a:=temp_array(2, 4);
    set_array(a, 0, 5);
    set_array(a, get_array(a, 0) - 4, get_array(a, 0) + 4);
    display_msg("a[0]="+get_array(a, 0)+", a[1]="+get_array(a, 1));
  end


> *array expressions: sometimes you need to construct an array of elements and you will probably want to do it in just one expression. This is now possible:
new:
  list := ["A", "B", "C", "D"];

old:
  list := temp_array(4, 2);
  list[0] := "A";
  list[1] := "B";
  list[2] := "C";
  list[3] := "D";


Syntax specific for associative arrays is also available. (see "arrays.txt" for full introduction to this type of arrays).

> *map array expressions:

  map := {5: "five", 10: "ten", 15: "fifteen", 20: "twelve"};


> * "dot" syntax to access elements of associative arrays. "dot" syntax allows to work with arrays like objects:
  trap.radius := 3;
  trap.tile := tile_num(dude_obj);

you can chain dot and bracket syntax to access elements of multi-dimensional arrays:
  collectionList[5].objectList[5].name += " foo";

NOTE: when using incremental operators like +=, *=, ++, -- compiler will use additional temp variable to get an array at penultimate level in order to avoid making the same chain of "get_array" calls twice.


> * "foreach" loops: A shorthand method of looping over all elements in an array. Syntax is 'foreach (<symbol> in <expression>) '
new:
  procedure bingle begin
    variable critter;
    foreach (critter in list_as_array(LIST_CRITTERS)) begin
      display_msg(""+critter);
    end
  end
old:
  procedure bingle begin
    variable begin critter; array; len; count; end
    array:=list_as_array(LIST_CRITTERS);
    len:=len_array(array);
    count:=0;
    while count < len do begin
      critter:=array[count];
      display_msg(""+critter);
    end
  end

If you want an index array element (or key for "maps") at each iteration, use syntax: 'foreach (<symbol>: <symbol> in <expression>) '
  foreach (pid: price in itemPriceMap) begin
    if (itemPid == pid) then
      itemPrice := price;
  end

If you want to add additional condition for continuing the loop, use syntax: 'foreach (<symbol> in <expression> while <expression>) '. In this case loop will iterate over elements of an array until last element or until "while" expression is true (whatever comes first).

NOTE: just like "for" loop, "continue" statement will respect increments of a hidden counter variable, so you can safely use it inside "foreach".




====================
=== int2ssl note ===
====================

int2ssl by Anchorite (TeamX) is included in sfall modderspack package. It was updated to support all additional opcodes of sfall, along with some syntax features. You can use it to decompile any sfall or non-sfall script.

=============
=== Fixes ===
=============

playmoviealpharect was using the token for playmoviealpha, breaking both functions in the process.

addbuttonflag had an entry in the token table, and could be parsed, but was missing an entry in the emit list. This resulted in the compiler accepting it as a valid function, but not outputting any code for it into the compiled script.

The function tokenize was missing an entry in the token table, and so would not be recognised by the compiler.

fixed the check for the 'call "foo"' syntax so that non-string constants will no longer be accepted.

==============================
=== Backward compatibility ===
==============================
There are several changes in this version of sslc which may result in problems for previously working scripts. A new command line option '-b' is available, which will turn off all new fixes and features which have the possibility of causing a previously compiling script to change its behaviour. (And only those features; anything which would not compile under the old sslc is not affected.) This includes the following:

- Since 'for', 'foreach', 'break', 'continue', 'in' and 'tokenize' are now hardcoded names, existing scripts that use any of them as a variable or procedure name will no longer compile.

- Missing a semicolon after a variable declaration is now a hard error. (Originally sslc would check for the semicolon, but would not complain if it was missing.)

- The function addbuttonflag used to be recognised by the compiler, but would not emit any code into the int file.

- The function playmoviealpharect compiled as playmoviealpha


=================
=== Changelog ===
=================
> sslc v1.2.3:
- added additional opcodes sfall_func7 and sfall_func8 for sfall 4.2.9/3.8.29
- fixed a script compilation error when there is a BOM UTF-8 encoding marker

> sslc v1.2.2:
- added ability to declare a local variable procedures anywhere in the procedure body

> sslc v1.2:
- added new "div" operator for unsigned integer division for sfall 4.2.3/3.8.23
- added new logical operators "andAlso", "orElse" for short-circuit evaluation of logical expressions
- added an alternative (C/Java-style) assignment operator
- fixed compiler giving "assignment operator expected" error when a variable-like macro is not being defined properly

> sslc v1.1:
- added new opcode reg_anim_callback for sfall 4.2.2/3.8.22
- the basic optimization is now enabled by default when not specifying any optimization options
- unreferenced "critical" procedures and procedures with the names "Node998" and "Node999" are now removed by the optimizer

> sslc v1.0:
- added new opcode register_hook_proc_spec for sfall 4.2/3.8.20
- added -m<macro[=val]> option to define a macro named "macro" for conditional compilation
- added -I<path> option to specify an additional directory to search for include files
- now it is possible to run preprocess or optimization passes in backward compatibility mode

=================
> sfall 4.0:
- enabled code for "ceil" math function
- fixed missing argument for "how_much" function
- added "desc_p_proc" (from Fallout 1) to protected procedures that should not be removed by the optimizer
- fixed compiler giving "division by zero" error when using zero as the second factor in multiplication

> sfall 3.6:
- added python-style ternary operator (conditional expression)
- added -s short-circuit evalution option for AND, OR expressions
- int2ssl will detect and decompile conditional expressions and short-circuit logical operators
- added -F option to include full file paths in "#line" directives after preprocessing
- added -D option to write abstract syntax tree into .txt file
- fixed compiler crash when number of arguments in procedure declaration does not match definition
- fixed incorrect constant folding of "bwnot" operator
- fixed more invalid results in constant folding
- implemented optional arguments for user-defined procedures
- implemented stringify procedure names using @ operator, which is helpful to pass procedures around to call them from variables (it will properly handle references)
- logic for procedures passed as arguments to scripting functions was moved from code generation to parsing stage
- now it is possible to call user-defined procedures inside argument list of scripting functions, without compiler attempting to treat them as procedure references and probably fail (procedures will still be passed, but only to appropriate scripting functions at appropriate argument positions)
- int2ssl will now place empty parantheses after a call to user-defined procedure - this will distinct calls from passing procedures to some scripting functions (like giq_option)
- fixed inline procedure "calls" not working when optimization is enabled
- added column numbers to error/warning output
- added code to simplify adding sfall opcodes into compiler (need to add code in 3 places, instead of 7 places for each opcode)
- fixed bug when initializing variable with expression starting from a symbol
- added division by zero constant check

> sfall 3.5:
- completed namespace compression optimization with respect to imported/exported variables
- changed 'for' and 'foreach' syntax to allow parentheses which are easier to read IMHO
- heavy code refactoring - split "parse.c" into several files, replaced all dirty workaround code in "lex()" (some syntax features) with parser-level equivalents
- added syntax to reference elements in multi-dimensional arrays (unlimited sequence of brackets [] and dots . )
- added fully featured "break" and "continue" statements for loops
- moved some optimizations (namely constant propagation and variable reuse) to "experimental" because they were breaking my scripts
- added ability to initialize variables with expressions

> sfall 3.4:
- added "foreach .. while .." syntax
- added array expressions for lists and maps
- added "foreach (key: value in ...)" syntax for convenience
- fixed crash bug in "for" loop parsing function
- added ability to access array elements with string keys using OOP-like dot (".") syntax
