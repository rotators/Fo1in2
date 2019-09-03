#!/usr/bin/perl

use strict;
use warnings;

use Config::IniFiles;

if( scalar( @ARGV ) != 1 )
{
	print( "Usage: ai.txt2h.pl [ai.txt]" );
	exit;
}

my $file = shift;

my $ai = Config::IniFiles->new( -file => $file, -handle_trailing_comment => 1 );
printf( "%s\n", join( "\n", @Config::IniFiles::errors ));

my $header = "#ifndef __AI__\n#define __AI__\n\n";

foreach my $section ( $ai->Sections )
{
	if( !$ai->exists( $section, "packet_num" ))
	{
		printf( "WTH: missing [%s]->packet_num\n", $section );
		next;
	}

	my $define = uc( $section );

	$define =~ s![-]!_!g;
	$define =~ s![,\.]!!g;
	$define =~ s! !_!g;

	$header .= sprintf( "#define AI_%s (%s)\n", $define, $ai->val( $section, "packet_num" ));
}

$header .= "\n#endif // __AI__ //\n";

print $header;

1;
