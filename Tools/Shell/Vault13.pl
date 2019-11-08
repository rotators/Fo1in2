#!/usr/bin/perl

use strict;
use warnings;

my $content;

if( open( my $file, '<', "Vault13.gam" ))
{
	local $/;
	$content = <$file>;
	close( $file );
	$content =~ s!\r!!g;
}
else
{
	die( "Cannot open Vault13.gam" );
}

my( $name_length, $value_length, $gvar_length ) = ( 0, 0, 0 );
my( $line_number, $gvar_number ) = ( 0, -1 );
my @lines = split( /\n/, $content );
foreach my $line( @lines )
{
	if( $line =~ /^[\t\ ]*([A-Za-z0-9_]+)[\t\ ]*:=[\t\ ]*([0-9\-]+[\t\ ]*\;)/ )
	{
		my( $name, $value ) = ( $1, $2 . '' );
		$value =~ s!\t!!g;
		$value =~ s! !!g;
		$name_length = length( $name ) if( length( $name ) > $name_length );
		$value_length = length( $value ) if( length( $value ) > $value_length );

		$gvar_number++;
		$gvar_length = length( $gvar_number ) if( length( $gvar_number ) > $gvar_length );
	}
}

my $name_format = sprintf( "%%-%us", $name_length );
my $value_format = sprintf( "%%-%us", $value_length );
my $gvar_format = sprintf( "%%-%us", $gvar_length + 2 );
$gvar_number = -1;
foreach my $line( @lines )
{
	my $newline = $line;
	$line_number++;

	if( $line =~ /^[\t\ ]*([A-Za-z0-9_]+)[\t\ ]*:=[\t\ ]*([0-9\-]+[\t\ ]*\;)(.*)/ )
	{
		$gvar_number++;
		my( $name, $value, $gvar, $comment ) = ( sprintf( $name_format, $1 ), $2, sprintf( $gvar_format, "($gvar_number)" ), $3 );
		$value =~ s!\t!!g;
		$value =~ s! !!g;
		$value = sprintf( $value_format, $value );

		$comment =~ s!^[\t\ ]+!!;
		$comment =~ s!^\/\/!!;
		$comment =~ s!^[\t\ ]+!!;
		$comment =~ s!^\([0-9]+\)!!;
		$comment =~ s!^[\t\ ]+!!;
		$comment =~ s!^\/\/!!;
		$comment =~ s!^[\t\ ]+!!;

		$newline = sprintf( "%s := %s // %s %s", $name, $value, $gvar, $comment );
		$newline =~ s![\t\ ]+$!!;
	}

	printf( "%s\r\n", $newline );
}
