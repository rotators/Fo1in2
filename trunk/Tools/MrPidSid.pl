#!/usr/bin/perl

use strict;
use warnings;

use File::Find;

sub ReadMacros
{
	my( $filename, $prefix ) = @_;
	my $content = undef;
	my %result;

	if( open( my $file, "<", $filename ))
	{
		local $/;
		$content = <$file>;
		close( $file );
	}
	else
	{
		die( "Cannot open '$filename'" );
	}
	
	die( "'$filename' is empty(?)" ) if( !length( $content ));

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
	
	return %result;
}

my @files;
sub FindFiles
{
	my $file = $File::Find::name;
	
	if( lc(substr( $file, -4 )) eq '.ssl' )
	{
		push( @files, $file );
	}
}

my %def_critter_pid = ReadMacros( "../Fallout2/Fallout1Port/Mapper/source/scripts/HEADERS/CRITRPID.H", 'PID' );
my %def_scenery_pid = ReadMacros( "../Fallout2/Fallout1Port/Mapper/source/scripts/HEADERS/SCENEPID.H", 'PID' );
my %def_item_pid = ReadMacros( "../Fallout2/Fallout1Port/Mapper/source/scripts/HEADERS/ITEMPID.H", 'PID' );
my %def_sid = ReadMacros( "../Fallout2/Fallout1Port/Mapper/source/scripts/HEADERS/scripts.h",  'SCRIPT' );
find({ wanted => \&FindFiles, no_chdir => 1 }, '../Fallout2/Fallout1Port/Mapper/source/scripts/' );

foreach my $filename( @files )
{
	#printf( "Processing %s...\n", $filename );

	my $content;
	if( open( my $file, "<", $filename ))
	{
		local $/;
		$content = <$file>;
		close( $file );
	}
	else
	{
		next;
	}

	my( $changed_file, $linenum ) = ( 0, 0 );
	my @lines = split( /\n/, $content );

	# reused for updates
	$content = "";

	foreach my $line( @lines )
	{
		$linenum++;

		# meh
		$line =~ s!\n!!g;
		$line =~ s!\r!!g;

		my $newline = $line;

		# feel my amazing regex! go on, touch it!
		if( $line =~ /^(.*create_object_sid\([\t\ ]*)([A-Z0-9_]+)([\t\ ]*\,[\t\ ]*)([A-Z0-9_]+)([\t\ ]*\,[\t\ ]*)([A-Z0-9_]+)([\t\ ]*\,[\t\ ]*)([0-9]+)([\t\ ]*\).*)$/ )
		{
			my $begin = $1;
			my $pid = int($2);
			my $comma1 = $3;
			my $arg2 = $4;
			my $comma2 = $5;
			my $arg3 = $6;
			my $comma3 = $7;
			my $sid = int($8);
			my $end = $9;

			# skip comments
			if( $line =~ /^[\t\ ]*\/\// )
			{
				$content .= sprintf( "%s\r\n", $line );
				next;
			}

			my $changed_line = 0;

			# check for proto id define - critter, scenery, item
			if( exists( $def_critter_pid{$pid} ))
			{
				$pid = $def_critter_pid{$pid};
				$changed_line = 1;
			}
			elsif( exists( $def_scenery_pid{$pid} ))
			{
				$pid = $def_scenery_pid{$pid};
				$changed_line = 1;
			}
			elsif( exists( $def_item_pid{$pid} ))
			{
				$pid = $def_item_pid{$pid};
				$changed_line = 1;
			}
			else
			{
				printf( "WARNING unknown pid<%d>, filename<%s> line<%d>\n", $pid, $filename, $linenum );
			}

			# check for script id define
			if( exists( $def_sid{$sid} ))
			{
				$sid = $def_sid{$sid};
				$changed_line = 1;
			}
			else
			{
				printf( "WARNING unknown sid<%d>, filename<%s> line<%d>\n", $sid, $filename, $linenum );
			}

			# update line
			if( $changed_line )
			{
				$changed_file = 1;

				$newline = sprintf( "%s%s%s%s%s%s%s%s%s", $begin, $pid, $comma1, $arg2, $comma2, $arg3, $comma3, $sid, $end );

				# debug :>
				printf( "@@ %s : %d\n", $filename, $linenum );
				printf( "<- %s\n", $line );
				printf( "-> %s\n", $newline );
			}
		}

		# we did it, rotators!
		$content .= sprintf( "%s\r\n", $newline );

	}

	# update file
	if( $changed_file && open( my $file, ">", $filename ))
	{
		print( $file $content );
		close( $file );
	}
}
