#!/usr/bin/perl
#
### ReDefine
#
# Updates .ssl scripts, replacing raw values with defines for specific variables and functions
#
# Wipe/Rotators
#
###

use strict;
use warnings;

use Data::Dumper;
use File::Find;

my %summary;
my %defines;

my @files;
my %variables;
my %functions;
my %raw;

my $scripts_dir;
my $readOnly = 0;

# 0 - do nothing
# 1 - save to file
# 2 - save to file and print to screen
my $debug = 2;
unlink( "ReDefine.DEBUG.log" ) if( -e "ReDefine.DEBUG.log" );
sub DEBUG
{
	my( $text, @args ) = @_;

	return if( !$debug );
	$text = sprintf( $text, @args ) if( scalar( @args ));

	return if( !length( $text ));

	$text = sprintf( "DEBUG %s\n", $text );

	print( $text ) if( $debug >= 2 );

	if( open( my $file, ">>", "ReDefine.DEBUG.log" ))
	{
		print( $file $text );
		close( $file );
	}
}

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

unlink( "ReDefine.log" ) if( -e "ReDefine.log" );
sub LOG
{
	my( $text, @args ) = @_;

	$text = sprintf( $text, @args ) if( scalar( @args ));

	return if( !length( $text ));

	$text = sprintf( "%s\n", $text );

	print( $text );
	if( open( my $file, ">>", "ReDefine.log" ))
	{
		print( $file $text );
		close( $file );
	}
}

#

sub ReadDefines
{
	my( $type, $filename, $prefix, $group ) = @_;
	my $content;

	# validate arguments

	if( !defined( $type ) || !length( $type ))
	{
		WARNING( "ReadDefines(): missing type name" );
		return;
	}
	elsif( !defined( $filename ) || !length( $filename ))
	{
		WARNING( "ReadDefines(): missing filename : type<%s>", $type );
		return;
	}
	elsif( !defined( $prefix ) || !length( $prefix ))
	{
		WARNING( "ReadDefines(): missing prefix : type<%s> filename<%s>", $type, $filename );
		return;
	}
	elsif( defined( $group ) && !length( $group ))
	{
		WARNING( "ReadDefines(): missing group name : type<%s> filename<%s> prefix<%s>", $type, $filename, $prefix );
		return;
	}

	# validate type name

	if( exists( $defines{regular} ) && exists( $defines{regular}{$type} ))
	{
		WARNING( "ReDefines() type<%s> already in use", $type );
		return;
	}
	elsif( exists( $defines{virtual} ) && exists( $defines{virtual}{$type} ))
	{
		WARNING( "ReDefines() type<%s> already in use", $type );
		return;
	}

	# read file

	if( open( my $file, "<", sprintf( "%s/%s", $scripts_dir, $filename )))
	{
		local $/;
		$content = <$file>;
		close( $file );
		$content =~ s!\r!!g;
	}
	else
	{
		WARNING( "ReadDefines(): cannot open : [%s]/%s", $scripts_dir, $filename );
		return;
	}

	if( !length( $content ))
	{
	
		WARNING( "ReadDefines(): empty file : [%s]/%s", $scripts_dir, $filename );
		return;
	}

	# store defines

	my $line_number = 0;
	my @lines = split( /\n/, $content );
	foreach my $line( @lines )
	{
		$line_number++;

		# meh
		$line =~ s!\n!!g;

		# skip empty lines
		next if( !length( $line ));

		# skip comments
		next if( $line =~ /^\[\t\ ]*\/\// );

		# find macros with given prefix
		if( $line =~ /^[\t\ ]*\#define[\t\ ]+(${prefix}_[A-Za-z0-9_]+)[\t\ ]+\(([0-9]+)\)/ ||
			$line =~ /^[\t\ ]*\#define[\t\ ]+(${prefix}_[A-Za-z0-9_]+)[\t\ ]+([0-9]+)/ )
		{
			my $name  = $1;
			my $value = int( $2 );

			# human detection
			if( exists( $defines{regular} ) && exists( $defines{regular}{$type} ) && exists( $defines{regular}{$type}{$value} ))
			{
				WARNING( "value<%d> already used by define<%s>, current define<%s> ignored : fileline<%s:%d>", $value, $defines{regular}{$type}{$value}, $name, $filename, $line_number );
				next;
			}

			$defines{regular}{$type}{$value} = $name;

			if( defined( $group ))
			{
				push( @{ $defines{virtual}{$group} }, $type );
			}
		}
	}

	my $count = scalar( keys( %{ $defines{regular}{$type} } ));
	LOG( "Reading %s... %d %s define%s%s", $filename, $count, $prefix, $count != 1 ? "s" : "", defined( $group ) ? sprintf( " -> %s", $group ) : "" );
}

sub IsDefineType
{
	my( $type ) = @_;

	if( !defined( $type ) || !length( $type ))
	{
		WARNING( "IsDefineType(): missing type" );
		return 0;
	}

	# virtual types
	return 1 if( $type eq "?" );
	return 1 if( exists( $defines{virtual} ) && exists( $defines{virtual}{$type} ));

	# regular types
	return 1 if( exists( $defines{regular} ) && exists( $defines{regular}{$type} ));

	return 0;
}

sub IsDefine
{
	my( $type, $value ) = @_;

	return 0 if( !IsDefineType( $type ));

	if( exists( $defines{virtual} ) && exists( $defines{virtual}{$type} ))
	{
		foreach my $real_type( @{ $defines{virtual}{$type} } )
		{
			return 1 if( exists( $defines{regular} ) && exists( $defines{regular}{$real_type} ) && exists( $defines{regular}{$real_type}{$value} ));
		}
	}

	# SID < 1 ignored for readibility
	return 1 if( $type eq "SID" && $value < 1 );

	# regular defines
	return 1 if( exists( $defines{regular} ) && exists( $defines{regular}{$type} ) && exists( $defines{regular}{$type}{$value} ));

	return 0;
}

sub GetDefine
{
	my( $type, $value, $warning ) = @_;

	# used for unknown arguments for function checks
	return $value if( $type eq "?" );

	if( IsDefine( $type, $value ))
	{
		if( exists( $defines{virtual} ) && exists( $defines{virtual}{$type} ))
		{
			foreach my $regular( @{ $defines{virtual}{$type} } )
			{
				if( exists( $defines{regular} ) && exists( $defines{regular}{$regular} ) && exists( $defines{regular}{$regular}{$value} ))
				{
					return $defines{regular}{$regular}{$value};
				}
			}
		}
		elsif( $type eq "SID" && $value < 1 )
		{
			return $value;
		}

		# regular defines
		return $defines{regular}{$type}{$value};
	}

	# for quick lookup, do not emit warning if message isn't set
	if( defined( $warning ))
	{
		WARNING( $warning );
		$summary{unknown}{$type}{$value}++;
	}

	return $value;
}

sub GetOp
{
	my( $op_name ) = @_;

	$op_name = lc( $op_name );

	return ":=" if( $op_name eq "assign" );
	return "==" if( $op_name eq "equals" );
	return "!=" if( $op_name eq "notequals" );
	return "<"  if( $op_name eq "lower" );
	return "<=" if( $op_name eq "lowerequals" );
	return ">"  if( $op_name eq "greater" );
	return ">=" if( $op_name eq "greaterequals" );
	return "+"  if( $op_name eq "add" );
	return "+=" if( $op_name eq "addequals" );

	return undef;
}

sub GetOpName
{
	my( $op ) = @_;

	return "assign"        if( $op eq ":=" );
	return "equals"        if( $op eq "==" );
	return "notequals"     if( $op eq "!=" );
	return "lower"         if( $op eq "<" );
	return "lowerequals"   if( $op eq "<=" );
	return "greater"       if( $op eq ">" );
	return "greaterequals" if( $op eq ">=" );
	return "add"           if( $op eq "+" );
	return "addequals"     if( $op eq "+=" );

	return undef;
}

sub AddVariable
{
	my( $name, $op_name, $type ) = @_;
	my $op = GetOp( $op_name );

	if( !defined( $op ))
	{
		WARNING( "AddVariable(): unknown op<%s> : variable<%s>", $op_name, $name );
	}
	elsif( !IsDefineType( $type ))
	{
		WARNING( "AddVariable(): unknown type<%s> : variable<%s> op<%s>", $type, $name, $op_name );
		return;
	}

	$name = lc( $name );
	$variables{$op_name}{$name} = $type;

	LOG( "Added variable %s: %s %s %s", $op_name, $name, $op, $type );
}

sub AddVariableGuess
{
	my( @types ) = @_;

	foreach my $type( @types )
	{
		if( !IsDefineType( $type ))
		{
			WARNING( "AddVariableGuess : unknown define type<%s>", $type );
			return;
		}
	}

	$variables{guess} = [ @types ];

	LOG( "Added variable guessing: %s", join( " ", @types ));
}

sub AddFunction
{
	my( $name, @types ) = @_;

	my $arg_number = 0;
	foreach my $type( @types )
	{
		if( !IsDefineType( $type ))
		{
			WARNING( "AddFunction : unknown define type<%s> : function<%s>", $type, $name );
			return;
		}

		$arg_number++;
		$functions{$name}{args}{$arg_number} = $type;
	}

	LOG( "Added function: %s( %s )", $name, join( ", ", @types ));
}

sub AddFunctionOp
{
	my( $name, $op_name, $type ) = @_;
	my $op = GetOp( $op_name );

	if( !defined( $op ))
	{
		WARNING( "AddFuctionOp: unknown op<%s> : function<%s>", $op_name, $name );
	}
	elsif( !IsDefineType( $type ))
	{
		WARNING( "AddFuctionOp: unknown define type<%s> : function<%s> op<%s>", $type, $name, $op_name );
		return;
	}

	$name = lc( $name );
	$functions{$name}{$op_name} = $type;

	LOG( "Added function %s: %s(...) %s %s", $op_name, $name, $op, $type );
}

sub AddRaw
{
	my( $from, $to ) = @_;

	$raw{$from} = $to;

	LOG( "Added raw: %s", $from );
}

sub ReadConfig
{
	my $content;

	if( open( my $file, "<", "ReDefine.pl.cfg" ))
	{
		local $/;
		$content = <$file>;
		close( $file );
	}
	else
	{
		die( "Cannot open 'ReDefine.pl.cfg'" );
	}

	my @lines = split( /\n/, $content );
	my $section;
	foreach my $line( @lines )
	{
		# meh
		$line =~ s!\n!!g;
		$line =~ s!\r!!g;

		my $known = 1;

		# skip empty lines and comments
		if( !length( $line ) || $line =~ /^[\t\ ]*$/ || $line =~ /^[\t\ ]*[\;\#]/ )
		{
			next;
		}
		# detect section
		elsif( $line =~ /^\[([A-Za-z0-9]+)\]$/ )
		{
			$section = $1;
			next;
		}
		# detect variable = value
		elsif( defined( $section ) && length( $section ) && $line =~ /[\t\ ]*(.+?)[\t\ ]*\=[\t\ ]*(.+?)[\t\ ]*$/ )
		{
			my( $variable, $value ) = ( $1, $2 );
			my @values = split( /[\t\ ]+/, $value );
			my $count = scalar( @values );
			my $bad_count = sprintf( "[%s]->%s : invalid number of values, skipped", $section, $variable );

			if( !$count )
			{
				WARNING( $bad_count );
			}
			elsif( $section eq "ReDefine" )
			{
				if( $variable eq "ScriptsDir" && length( $variable ))
				{
					LOG( "ScriptsDir = %s", $value );
					$scripts_dir = $value;
				}
			}
			elsif( $section eq "Defines" )
			{
				if( $count < 2 || $count > 3 )
				{
					WARNING( $bad_count );
				}
				else
				{
					ReadDefines( $variable, @values );
				}
			}
			elsif( $section eq "VariableGuess" )
			{
				if( $variable eq "VariableGuess" )
				{
					AddVariableGuess( @values ) if( $count );
				}
				else
				{
					$known = 0;
				}
			}
			elsif( substr( $section, 0, 8 ) eq "Variable" )
			{
				if( $count != 1 )
				{
					WARNING( $bad_count );
				}
				else
				{
					my $op_name = lc( substr( $section, 8 ));
					if( defined( GetOp( $op_name )))
					{
						AddVariable( $variable, $op_name, $value );
					}
					else
					{
						$known = 0;
					}
				}
			}
			elsif( $section eq "Function" )
			{
				if( $count < 1 )
				{
					WARNING( $bad_count );
				}
				else
				{
					AddFunction( $variable, @values );
				}
			}
			elsif( substr( $section, 0, 8 ) eq "Function" )
			{
				if( $count != 1 )
				{
					WARNING( $bad_count );
				}
				else
				{
					my $op_name = lc( substr( $section, 8 ));
					if( defined( GetOp( $op_name )))
					{
						AddFunctionOp( $variable, $op_name, $value );
					}
					else
					{
						$known = 0;
					}
				}
			}
			elsif( $section eq "Raw" )
			{
				if( $count < 1 )
				{
					WARNING( $bad_count );
				}
				else
				{
					AddRaw( $variable, $value );
				}
			}
			else
			{
				$known = 0;
			}

			next if( $known );
		}

		WARNING( "unknown or invalid config line<%s>", $line );
	}
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

# read configuration
ReadConfig( "ReDefine.cfg" );

# seach for script files
LOG( "Finding scripts..." );
find({ wanted => \&FindFiles, no_chdir => 1 }, $scripts_dir );

LOG( "Processing scripts%s...", $readOnly ? " (read only)" : "" );
foreach my $filename_long( sort{lc($a) cmp lc($b)} @files )
{
	$summary{files}++;

	my $filename = $filename_long;
	$filename =~ s!^${scripts_dir}/!!;
	my $content;
	if( open( my $file, "<", $filename_long ))
	{
		local $/;
		$content = <$file>;
		close( $file );
		$content =~ s!\r!!g;
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

		# skip fully commented
		if( $line =~ /^[\t\ ]*\/\// )
		{
			$content .= sprintf( "%s\r\n", $line );
			next;
		}

		# save original line; 
		my $line_old = $line;

		# search for variables
		my @variable_matches = $line =~ /[A-Za-z0-9_]+[\t\ ]*[\:\=\!\<\>\+]+[\t\ ]*[0-9]+/g;
		foreach my $variable_match( @variable_matches )
		{
			my( $variable_name, $variable_op, $variable_value ) = $variable_match =~ /([A-Za-z0-9_]+)[\t\ ]*(.+?)[\t\ ]*([0-9]+)/;

			my $variable_op_name = GetOpName( $variable_op );

			if( !defined( $variable_op_name ))
			{
				if( $variable_op ne ":" && $variable_op ne "=" ) # comments
				{
					DEBUG( "op [%s] -> [%s] [%s] [%s]: %s", $variable_match, $variable_name, $variable_op, $variable_value, $line_info );
				}
				next;
			}

			my $var = lc( $variable_name );

			if( exists( $variables{$variable_op_name} ) && exists( $variables{$variable_op_name}{$var} ))
			{
				my $val = int( $variable_value );
				my $val_type = $variables{$variable_op_name}{$var};

				# prepare warning messages
				my $line_short = $line;
				$line_short =~ s!^[\t\ ]*!!;
				$line_short =~ s![\t\ ]*$!!;
				my $warning_unknown = sprintf( "unknown %s<%d> : %s =LINE= %s", $val_type, $val, $line_info, $line_short );

				# replace value with connected defines
				$val = GetDefine( $val_type, $val, $warning_unknown );

				if( $variable_value ne $val )
				{
					my $update = sprintf( "%s %s %s", $variable_name, $variable_op, $val );
					$line =~ s!$variable_match!$update!g;
				}
				
			}
			elsif( exists( $variables{guess} ))
			{
				foreach my $val_type( @{ $variables{guess} } )
				{
					my $val = int( $variable_value );

					$val = GetDefine( $val_type, $val, undef );

					if( $variable_value ne $val )
					{
						my $update = sprintf( "%s := %s", $variable_name, $val );
						$line =~ s!$variable_match!$update!g;
					}
				}
			}
		}

		# search for functions
		foreach my $function_name ( sort{$a cmp $b} keys( %functions ))
		{
			# extract functions
			# this is an unsanctioned use of magical energy
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

				my( undef, $function_open, $function_arguments, $function_close ) = $function_match =~ m/^([A-Za-z0-9_]+)(\([\t ]*)(.+)([\t\ ]*\)[\t\ ]*)$/;

				# process return value operations
				my $function_match_re = $function_match;
				$function_match_re =~ s!\(!\\\(!g;
				$function_match_re =~ s!\)!\\\)!g;
				$function_match_re =~ s!\+!\\\+!g;
				$function_match_re =~ s!\*!\\\*!g;

				# need extra caution here to not catch my_func() when looking for func()
				my @function_op_matches = $line =~ /(?:^|.)${function_match_re}[\t\ ]*[\:\=\!\<\>\+]+[\t\ ]*[0-9]+/g;
				foreach my $function_op_match( @function_op_matches )
				{
					my( $f, $function_left, $function_op, $function_right ) = $function_op_match =~/(^|.)(${function_match_re})[\t\ ]*([\:\=\!\<\>\+]+)[\t\ ]*([0-9]+)/;
					my $function_op_name = GetOpName( $function_op );

					#DEBUG( "FUNC? %s -> (%s) [%s] [%s] [%s] %s", $function_op_match, $f, $function_left, $function_op, $function_right, $line_info );

					# extra caution
					if( $f =~ /[A-Za-z0-9_]/ )
					{
						#DEBUG( "SABOTAGE!!! %s", $line );
						next;
					}

					if( !defined( $functions{$function_name}{$function_op_name} ))
					{
						next;
					}
					
					#DEBUG( "FUNC! %s -> (%s) [%s] [%s] [%s] %s", $function_op_match, $f, $function_left, $function_op, $function_right, $line_info );
					my $val_type = $functions{$function_name}{$function_op_name};
					my $val = int( $function_right );

					# prepare warning message
					my $line_short = $line;
					$line_short =~ s!^[\t\ ]*!!;
					$line_short =~ s![\t\ ]*$!!;
					my $warning_unknown = sprintf( "unknown %s<%d> : %s =LINE= %s", $val_type, $val, $line_info, $line_short );

					$val = GetDefine( $val_type, $val, $warning_unknown );
					if( $val ne $function_right )
					{
						my $original = sprintf( "%s", $function_op_match );
						$original =~ s!\(!\\\(!g;
						$original =~ s!\)!\\\)!g;
						$original =~ s!\+!\\\+!g;
						$original =~ s!\*!\\\*!g;

						my $update = sprintf( "%s%s %s %s", $f, $function_left, $function_op, $val );
						$line =~ s!${original}!${update}!g;
					}
				}

				if( exists( $functions{$function_name}{args} ))
				{
					# extract arguments
					# this is an unsanctioned use of magical energy
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
					#DEBUG( "args [%s] -> [%s] -> [%s]", $function_match, $function_arguments, join( "],[", @args ));

					# process arguments
					my( $arg_count, $idx ) = ( scalar( @args ), 0 );
					for( $idx = 0; $idx < $arg_count; $idx++ )
					{
						my $arg = $args[$idx];
						my $arg_old = $arg;
						my $arg_type;

						# detect incorrect splitting of arguments
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

						# prepare warning message
						my $line_short = $line;
						$line_short =~ s!^[\t\ ]*!!;
						$line_short =~ s![\t\ ]*$!!;

						# skip non-numeric arguments
						if( $arg !~ /^[0-9]+$/ )
						{
							# hold on! check if it's just some simple math
							if( $arg =~ /^([0-9]+)[\t\ ]*(\*|\/|\+|\-)[\t\ ]*([0-9]+)$/ )
							{
								my( $left, $op, $right ) = ( int( $1 ), $2, int( $3 ));
								#DEBUG( "oh noes math! <%s> %s <%s>", $left, $op, $right );

								my $calc = 0;

								# no, i won't eval() this

								if( $op eq "*" )
								{
									$calc = $left * $right;
								}
								elsif( $op eq "/" )
								{
									# don't get into trouble due to shitty modders
									if( $right == 0 )
									{
										WARNING( "DIVISION BY ZERO : %s =LINE= %s", $line_info, $line_short );
										next;
									}
									else
									{
										$calc = $left / $right;
									}
								}
								elsif( $op eq "+" )
								{
									$calc = $left + $right;
								}
								elsif( $op eq "-" )
								{
									$calc = $left - $right;
								}

								# check
								my $warning_unknown = sprintf( "unknown %s<%d> : %s argument<%d> =LINE= %s", $arg_type, $calc, $line_info, $idx + 1, $line_short );
								$calc = GetDefine( $arg_type, $calc, $warning_unknown );

								# math failed us
								next if( $calc =~ /^[0-9]+$/ );

								# great success!
								$args[$idx] = $calc;
								next;
							}

							#DEBUG( "skipped argument<%d> value<%s>", $idx + 1, $arg );
							next;
						}

						$arg = int( $arg );

						# replace argument with connected defines
						my $warning_unknown = sprintf( "unknown %s<%d> : %s argument<%d> =LINE= %s", $arg_type, $arg, $line_info, $idx + 1, $line_short );
						$args[$idx] = GetDefine( $arg_type, $arg, $warning_unknown );
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
						#DEBUG( "update [%s] -> [%s]", $original, $update );

						# primitive sanitization, most likely needs updates still
						$original =~ s!\(!\\\(!g;
						$original =~ s!\)!\\\)!g;
						$original =~ s!\+!\\\+!g;
						$original =~ s!\*!\\\*!g;

						$line =~ s/${original}/${update}/g;
					}
				}
			}
		}

		# search for raw text
		foreach my $from( keys( %raw ))
		{
			$line =~ s!$from!$raw{$from}!g;
		}

		# detect line change, ignore meaningless changes
		if( $line ne $line_old )
		{
			my( $line_pre, $line_post ) = ( $line_old, $line );
			$line_pre  =~ s![\t\ ]+!!g;
			$line_post =~ s![\t\ ]+!!g;

			if( $line_pre ne $line_post )
			{
				LOG( "@@ %s:%d", $filename, $line_number );
				LOG( "<- %s", $line_old );
				LOG( "-> %s", $line );
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

LOG( "Processed %d line%s in %d files\n", $summary{lines} || 0, $summary{lines} || 0 != 1 ? "s" : "" , $summary{files} || 0 );

foreach my $type( sort{$a cmp $b} keys( %{ $summary{unknown} } ))
{
	WARNING( " " );
	WARNING( "Unknown '%s' value%s:", $type, scalar( keys( %{ $summary{unknown}{$type} } )) != 1 ? "s" : "" );
	foreach my $value( sort{int($a) <=> int($b)} keys( %{ $summary{unknown}{$type} } ))
	{
		WARNING( "  %s (%d hit%s)", $value, $summary{unknown}{$type}{$value}, $summary{unknown}{$type}{$value} != 1 ? "s" : "" );
	}
}
