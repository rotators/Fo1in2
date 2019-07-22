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

#use Data::Dumper;
use File::Find;

my $scripts_path = "../Fallout2/Fallout1Port/Mapper/source/scripts";

my %functions;
my %defines;
my @files;
my $readOnly = 0;

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
		die( "Cannot open '$filename'" );
	}
	
	die( "'[$scripts_path]/$filename' is empty(?)" ) if( !length( $content ));

	my @lines = split( /\n/, $content );
	foreach my $line( @lines )
	{
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
				printf( "WARNING value<%d> already used by macro<%s>, current macro<%s> ignored\n", $value, $result{$value}, $name );
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
$readOnly = lc(shift( @ARGV ));
$readOnly = $readOnly eq 'ro' || $readOnly eq 'read' || $readOnly eq 'readonly' || $readOnly eq 'read-only';

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
		printf( "WARNING cannot open '$filename_long'\n" );
		next;
	}

	my( $update_file, $line_number ) = ( 0, 0 );
	my @lines = split( /\n/, $content );

	# reused for updates
	$content = "";

	foreach my $line( @lines )
	{
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
		my( $line_old, $line_prev ) = ( $line );

		$line_prev = $line;
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
					printf( "WARNING invalid match<%s> : %s\n", $function_match, $line_info );
					printf( "WARNING matches: [%s]\n", join( "],[", @function_matches ));
					printf( "WARNING CONTENT %s\n", $line );
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
							printf( "WARNING invalid number of arguments? : %s argument<%d>\n", $line_info, $idx + 1 );
							printf( "WARNING ORIGINAL : function<%s> arguments<[%s]>\n", $function_name, join( "] [", @args_old ));
							printf( "WARNING GUESSED  : function<%s> arguments<[%s]>\n", $function_name, join( "] [", @args ));
							printf( "WARNING CONTENT  : %s\n", $line_old );
							printf( "WARNING END\n" );
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

					# save short version of full line, for warnings
					my $line_short = $line;
					$line_short =~ s!^[\t\ ]*!!;
					$line_short =~ s![\t\ ]*$!!;

					# replace argument with connected defines
					if( $arg_type eq 'CRITTER_PID' )
					{
						if( exists( $defines{pid}{critter}{$arg} ))
						{
							$arg = $defines{pid}{critter}{$arg};
						}
						else
						{
							printf( "WARNING unknown CRITTER_PID<%d> : %s argument<%d> =LINE= %s\n", $arg, $line_info, $idx + 1, $line_short );
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
							printf( "WARNING unknown SCENERY_PID<%d> : %s argument<%d> =LINE= %s\n", $arg, $line_info, $idx + 1, $line_short );
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
							printf( "WARNING unknown ITEM_PID<%d> : %s line<%d> argument<%d> =LINE= %s\n", $arg, $line_info, $idx + 1, $line_short );
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
							printf( "WARNING unknown ANY_PID<%d> : %s argument<%d> =LINE= %s\n", $arg, $line_info, $idx + 1, $line_short );
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
							printf( "WARNING unknown SID<%d> : %s argument<%d> =LINE= %s\n", $arg, $line_info, $idx + 1, $line_short );
						}
					}
					else
					{
						printf( "WARNING unknown argument type<%s>\n", $arg_type );
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

		# detect line change
		if( $line ne $line_old )
		{
			printf( "@@ %s:%d\n", $filename, $line_number );
			printf( "<- %s\n", $line_old );
			printf( "-> %s\n", $line );
			$update_file = 1;
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
