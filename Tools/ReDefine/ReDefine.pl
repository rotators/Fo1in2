#!/usr/bin/perl
#
### ReDefine
#
# Updates .ssl scripts, replacing raw values with defines for specific functions
#
# Wipe/Rotators
#

use strict;
use warnings;

use Data::Dumper;
use File::Find;

my %summary;
my %defines;
my %functions;
my %variables;
my $scripts_path = "../../Fallout2/Fallout1Port/Mapper/source/scripts";
my @files;
my $readOnly = 0;

unlink( "ReDefine.WARNING.log" ) if( -e "ReDefine.WARNING.log" );
sub WARNING
{
	my( $text, @args ) = @_;

	$text = sprintf( $text, @args ) if( scalar( @args ));

	return if( !length( $text ));

	$text = sprintf( "WARNING %s\n", $text );

	print( $text );
	if( open( my $file, ">>", "ReDefine.WARNING.log" ))
	{
		print( $file $text );
		close( $file );
	}
}

sub AddVariable
{
	my( $name, $type ) = @_;

	$name = lc( $name );
	$variables{names}{$name} = $type;
}

sub AddVariableGuess
{
	my( @types ) = @_;

	$variables{guess} = [ @types ];
}

sub AddFunction
{
	my( $name, @args ) = @_;

	my $argnum = 0;
	foreach my $arg ( @args )
	{
		$argnum++;
		$functions{$name}{args}{$argnum} = $arg;
	}
}

sub ReadDefines
{
	my( $filename, $prefix ) = @_;
	my $content = undef;
	my %result;

	if( open( my $file, "<", sprintf( "%s/%s", $scripts_path, $filename )))
	{
		local $/;
		$content = <$file>;
		close( $file );
	}
	else
	{
		die( "Cannot open '[$scripts_path]/$filename'" );
	}
	
	die( "'[$scripts_path]/$filename' is empty(?)" ) if( !length( $content ));

	my $line_number = 0;
	my @lines = split( /\n/, $content );
	foreach my $line( @lines )
	{
		$line_number++;

		# meh
		$line =~ s!\n!!g;
		$line =~ s!\r!!g;

		# skip empty lines
		next if( !length( $line ));

		# skip comments
		next if( $line =~ /^\[\t\ ]*\/\// );

		# find macros with given prefix
		if( $line =~ /^[\t\ ]*\#define[\t\ ]+(${prefix}_[A-Z0-9_]+)[\t\ ]+\(([0-9]+)\)/ )
		{
			my $name  = $1;
			my $value = int($2);

			# human detection
			if( exists($result{$value}) )
			{
				WARNING( "value<%d> already used by macro<%s>, current macro<%s> ignored : file<%s:%d>", $value, $result{$value}, $name, $filename, $line_number );
				next;
			}

			$result{$value} = $name;
		}
	}
	
	return \%result;
}

sub FindFiles
{
	my $file = $File::Find::name;
	
	if( lc(substr( $file, -4 )) eq '.ssl' )
	{
		push( @files, $file );
	}
}

# check arguments
if( scalar( @ARGV ))
{
	$readOnly = lc(shift( @ARGV ));
	$readOnly = $readOnly eq 'ro' || $readOnly eq 'read' || $readOnly eq 'readonly' || $readOnly eq 'read-only';
}

# configure variables to change
AddVariable( 'critter_script', 'SID' );
AddVariable( 'critter_type', 'CRITTER_PID' );
AddVariableGuess( 'CRITTER_PID', 'SCENERY_PID' );

# configure functions to change
AddFunction( 'create_object_sid', 'ANY_PID', '?', '?', 'SID' );
AddFunction( 'message_str', 'SID', '?' );
AddFunction( 'obj_carrying_pid_obj', '?', 'ITEM_PID' );

# read defines from headers
print( "Reading defines...\n" );
$defines{pid}{critter} = ReadDefines( "HEADERS/CRITRPID.H", 'PID' );
$defines{pid}{scenery} = ReadDefines( "HEADERS/SCENEPID.H", 'PID' );
$defines{pid}{item} = ReadDefines( "HEADERS/ITEMPID.H", 'PID' );
$defines{sid} = ReadDefines( "HEADERS/scripts.h",  'SCRIPT' );

# seach for script files
print( "Finding scripts...\n" );
find({ wanted => \&FindFiles, no_chdir => 1 }, $scripts_path );

printf( "Processing scripts%s...\n", $readOnly ? " (read only)" : "" );
foreach my $filename_long( sort{lc($a) cmp lc($b)} @files )
{
	$summary{files}++;

	my $filename = $filename_long;
	$filename =~ s!^${scripts_path}/!!;
	my $content;
	if( open( my $file, "<", $filename_long ))
	{
		local $/;
		$content = <$file>;
		close( $file );
	}
	else
	{
		WARNING( "cannot open '%s'", $filename_long );
		next;
	}

	my( $update_file, $line_number ) = ( 0, 0 );
	my @lines = split( /\n/, $content );

	# reused for updates
	$content = "";

	foreach my $line( @lines )
	{
		$summary{lines}++;
		$line_number++;

		my $line_info = sprintf( "file<%s:%s>", $filename, $line_number );

		# meh
		$line =~ s!\n!!g;
		$line =~ s!\r!!g;

		# skip fully commented
		if( $line =~ /^[\t\ ]*\/\// )
		{
			$content .= sprintf( "%s\r\n", $line );
			next;
		}

		# save original line; 
		my $line_old = $line;

		# search for variables
		my @variable_matches = $line =~ /[A-Za-z0-9_]+[\t\ ]*\:\=[\t\ ]*[0-9]+\;/g;
		foreach my $variable_match( @variable_matches )
		{
			my( $variable_name, $variable_value ) = $variable_match =~ /([A-Za-z0-9_]+)[\t\ ]*\:\=[\t\ ]*([0-9]+)/;
			#printf( "DEBUG VAR [%s] -> [%s]=[%s]: %s\n", $variable_match, $variable_name, $variable_value, $line_info );

			my $var = lc( $variable_name );

			if( exists( $variables{names}{$var} ))
			{
				my $val = int( $variable_value );
				my $val_type = $variables{names}{$var};

				# prepare warning messages
				my $line_short = $line;
				$line_short =~ s!^[\t\ ]*!!;
				$line_short =~ s![\t\ ]*$!!;
				my $warning_unknown = sprintf( "unknown %s<%d> : %s =LINE= %s", $val_type, $val, $line_info, $line_short );

				# replace value with connected defines
				# duplicated in functions check
				if( $val_type eq 'CRITTER_PID' )
				{
					if( exists( $defines{pid}{critter}{$val} ))
					{
						$val = $defines{pid}{critter}{$val};
					}
					else
					{
						WARNING( $warning_unknown );
						$summary{unknown}{$val_type}{$val}++;
					}
				}
				elsif( $val_type eq 'SCENERY_PID' )
				{
					if( exists( $defines{pid}{scenery}{$val} ))
					{
						$val = $defines{pid}{scenery}{$val};
					}
					else
					{
						WARNING( $warning_unknown );
						$summary{unknown}{$val_type}{$val}++;
					}
				}
				elsif( $val_type eq 'ITEM_PID' )
				{
					if( exists( $defines{pid}{item}{$val} ))
					{
						$val = $defines{pid}{item}{$val};
					}
					else
					{
						WARNING( $warning_unknown );
						$summary{unknown}{$val_type}{$val}++;
					}
				}
				elsif( $val_type eq 'ANY_PID' )
				{
					if( exists( $defines{pid}{critter}{$val} ))
					{
						$val = $defines{pid}{critter}{$val};
					}
					elsif( exists( $defines{pid}{scenery}{$val} ))
					{
						$val = $defines{pid}{scenery}{$val};
					}
					elsif( exists( $defines{pid}{item}{$val} ))
					{
						$val = $defines{pid}{item}{$val};
					}
					else
					{
						WARNING( $warning_unknown );
						$summary{unknown}{$val_type}{$val}++;
					}
				}
				elsif( $val_type eq 'SID' )
				{
					if( $val < 1 )
					{
						# ignore
					}
					elsif( exists( $defines{sid}{$val} ))
					{
						$val = $defines{sid}{$val};
					}
					else
					{
						WARNING( $warning_unknown );
						$summary{unknown}{$val_type}{$val}++;
					}
				}
				else
				{
					WARNING( "unknown value type<%s>", $val_type );
				}

				if( $variable_value ne $val )
				{
					my $update = sprintf( "%s := %s;", $variable_name, $val );
					$line =~ s!$variable_match!$update!g;
				}
				
			}
			elsif( exists( $variables{guess} ))
			{
				foreach my $val_type( @{ $variables{guess} } )
				{
					my $val = int( $variable_value );

					if( $val_type eq 'CRITTER_PID' && exists( $defines{pid}{critter}{$val} ))
					{
						$val = $defines{pid}{critter}{$val};
					}
					elsif( $val_type eq 'SCENERY_PID' && exists( $defines{pid}{scenery}{$val} ))
					{
						$val = $defines{pid}{scenery}{$val};
					}

					if( $variable_value ne $val )
					{
						my $update = sprintf( "%s := %s;", $variable_name, $val );
						$line =~ s!$variable_match!$update!g;
					}
				}
			}
		}

		# search for functions
		foreach my $function_name ( sort{$a cmp $b} keys( %functions ))
		{
			my $re = qr{
				(
					${function_name}
					(
						\(
							(
							(?:
								(?> [^()]+ )
							|
								(?2)
							)*
							)
						\)
					)
				)
			}x;

			my @function_matches = $line =~ /${re}/g;
			next if( !scalar( @function_matches ));

			foreach my $function_match( @function_matches )
			{
				next if( $function_match !~ /^$function_name\(/ );
				next if( $function_match !~ /\)$/ );

				if( $function_match !~ /\)$/ )
				{
					WARNING( "invalid match<%s> : %s", $function_match, $line_info );
					WARNING( "matches: [%s]", join( "],[", @function_matches ));
					WARNING( "CONTENT %s", $line );
					next;
				}

				my( undef, $function_open, $function_arguments, $function_close ) = $function_match =~ m/^([A-Za-z0-9_]+)(\([\t ]*)(.+)([\t\ ]*\)[\t\ ]*)$/;

				# old sanity check
				if( !$function_name || !$function_open || !$function_arguments || !$function_close )
				{
					printf( "?? [%s] -> [%s]+[%s]+[%s]+[%s]\n",
						$function_match || 'undef',
						$function_name || 'undef',
						$function_open || 'undef',
						$function_arguments || 'undef',
						$function_close || 'undef' );
					printf( "?> %s\n", $line_info );
					printf( "?> %s\n", $line_old );
					printf( "?> %s\n", $line );
					exit;
				}

				# extract arguments
				my @args;
				push( @args, $1 ) while $function_arguments =~ /
				(
					(?:
						[^(),]+ |
						(
							\(
								(?: [^()]+ | (?2) )*
							\)
						)
					)*
				)
				(?: ,\s* | $)
				/xg;
				pop( @args ); # last element is always empty for some reason

				my @args_old = @args;
				# printf( "DEBUG args [%s] -> [%s] -> [%s]\n", $function_match, $function_arguments, join( "],[", @args ));

				# process arguments
				my( $arg_count, $idx ) = ( scalar( @args ), 0 );
				for( $idx = 0; $idx < $arg_count; $idx++ )
				{
					my $arg = $args[$idx];
					my $arg_old = $arg;
					my $arg_type;

					# detect incorrect splitting of argmuents
					if( !exists( $functions{$function_name}{args}{$idx+1} ))
					{
							WARNING( "invalid number of arguments? : %s argument<%d>", $line_info, $idx + 1 );
							WARNING( "ORIGINAL : function<%s> arguments<[%s]>", $function_name, join( "] [", @args_old ));
							WARNING( "GUESSED  : function<%s> arguments<[%s]>", $function_name, join( "] [", @args ));
							WARNING( "CONTENT  : %s", $line_old );
							WARNING( "END" );
							next;
					}
					
					$arg_type = $functions{$function_name}{args}{$idx+1};

					# skip unknown arguments
					next if( $arg_type eq '?' );

					# skip non-numeric arguments
					if( $arg !~ /^[0-9]+$/ )
					{
						#printf( "DEBUG skipped argument<%d> value<%s>\n", $idx + 1, $arg );
						next;
					}
					$arg = int($arg);

					# prepare warning message
					my $line_short = $line;
					$line_short =~ s!^[\t\ ]*!!;
					$line_short =~ s![\t\ ]*$!!;
					my $warning_unknown = sprintf( "unknown %s<%d> : %s argument<%d> =LINE= %s", $arg_type, $arg, $line_info, $idx + 1, $line_short );

					# replace argument with connected defines
					# duplicated in variables check
					if( $arg_type eq 'CRITTER_PID' )
					{
						if( exists( $defines{pid}{critter}{$arg} ))
						{
							$arg = $defines{pid}{critter}{$arg};
						}
						else
						{
							WARNING( $warning_unknown );
							$summary{unknown}{$arg_type}{$arg}++;
						}
					}
					elsif( $arg_type eq 'SCENERY_PID' )
					{
						if( exists( $defines{pid}{scenery}{$arg} ))
						{
							$arg = $defines{pid}{scenery}{$arg};
						}
						else
						{
							WARNING( $warning_unknown );
							$summary{unknown}{$arg_type}{$arg}++;
						}
					}
					elsif( $arg_type eq 'ITEM_PID' )
					{
						if( exists( $defines{pid}{item}{$arg} ))
						{
							$arg = $defines{pid}{item}{$arg};
						}
						else
						{
							WARNING( $warning_unknown );
							$summary{unknown}{$arg_type}{$arg}++;
						}
					}
					elsif( $arg_type eq 'ANY_PID' )
					{
						if( exists( $defines{pid}{critter}{$arg} ))
						{
							$arg = $defines{pid}{critter}{$arg};
						}
						elsif( exists( $defines{pid}{scenery}{$arg} ))
						{
							$arg = $defines{pid}{scenery}{$arg};
						}
						elsif( exists( $defines{pid}{item}{$arg} ))
						{
							$arg = $defines{pid}{item}{$arg};
						}
						else
						{
							WARNING( $warning_unknown );
							$summary{unknown}{$arg_type}{$arg}++;
						}
					}
					elsif( $arg_type eq 'SID' )
					{
						if( $arg < 1 )
						{
							# ignore
						}
						elsif( exists( $defines{sid}{$arg} ))
						{
							$arg = $defines{sid}{$arg};
						}
						else
						{
							WARNING( $warning_unknown );
							$summary{unknown}{$arg_type}{$arg}++;
						}
					}
					else
					{
						WARNING( "unknown argument type<%s>", $arg_type );
					}

					#printf( "DEBUG argument<%d> = %s\n", $idx + 1, $arg );
					$args[$idx] = $arg;
				}

				# rebuild line
				my $update = sprintf( "%s%s", $function_name, $function_open );
				for( $idx = 0; $idx < $arg_count; $idx++ )
				{
					$update .= $args[$idx];
					if( $idx != $arg_count - 1 )
					{
						$update .= ", ";
					}
				}
				$update .= $function_close;

				my $original = $function_match;
				if( $original ne $update )
				{
					# printf( "DEBUG update [%s] -> [%s]\n", $original, $update );

					# primitive sanitization, most likely needs updates still
					$original =~ s!\(!\\\(!g;
					$original =~ s!\)!\\\)!g;
					$original =~ s!\+!\\\+!g;
					$original =~ s!\*!\\\*!g;

					$line =~ s/${original}/${update}/g;
				}
			}
		}

		# detect line change, ignore meaningless changes
		if( $line ne $line_old )
		{
			my( $line_pre, $line_post ) = ( $line_old, $line );
			$line_pre  =~ s![\t\ ]+!!g;
			$line_post =~ s![\t\ ]+!!g;

			if( $line_pre ne $line_post )
			{
				printf( "@@ %s:%d\n", $filename, $line_number );
				printf( "<- %s\n", $line_old );
				printf( "-> %s\n", $line );
				$update_file = 1;
			}
			else
			{
				# restore original version
				$line = $line_old;
			}
		}

		# we did it, rotators!
		$content .= sprintf( "%s\r\n", $line );
	}

	$update_file = 0 if( $readOnly );

	if( $update_file && open( my $file, ">", $filename_long ))
	{
		print( $file $content );
		close( $file );
	}
}

printf( "Processed %d line%s in %d files\n", $summary{lines} || 0, $summary{lines} || 0 != 1 ? "s" : "" , $summary{files} || 0 );

foreach my $type( sort{$a cmp $b} keys( %{ $summary{unknown} } ))
{
	WARNING( " " );
	WARNING( "UNKNOWN %s:", $type );
	foreach my $value( sort{int($a) <=> int($b)} keys( %{ $summary{unknown}{$type} } ))
	{
		WARNING( "  %s (%d hit%s)", $value, $summary{unknown}{$type}{$value}, $summary{unknown}{$type}{$value} != 1 ? "s" : "" );
	}
}
