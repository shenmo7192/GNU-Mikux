#! /usr/bin/env perl
# SPDX-License-Identifier: GPL-2.0
#
# checkversion finds uses of all macros in <mikux/version.h>
# where the source files do not #include <mikux/version.h>; or cases
# of including <mikux/version.h> where it is not needed.
# Copyright (C) 2003, Randy Dunlap <rdunlap@infradead.org>

use strict;

$| = 1;

my $debugging;

foreach my $file (@ARGV) {
    next if $file =~ "include/generated/uapi/mikux/version\.h";
    next if $file =~ "usr/include/mikux/version\.h";
    # Open this file.
    open( my $f, '<', $file )
      or die "Can't open $file: $!\n";

    # Initialize variables.
    my ($fInComment, $fInString, $fUseVersion);
    my $iMikuxVersion = 0;

    while (<$f>) {
	# Strip comments.
	$fInComment && (s+^.*?\*/+ +o ? ($fInComment = 0) : next);
	m+/\*+o && (s+/\*.*?\*/+ +go, (s+/\*.*$+ +o && ($fInComment = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iMikuxVersion      = $. if m/^\s*#\s*include\s*"mikux\/version\.h"/o;
	}

	# Strip strings.
	$fInString && (s+^.*?"+ +o ? ($fInString = 0) : next);
	m+"+o && (s+".*?"+ +go, (s+".*$+ +o && ($fInString = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iMikuxVersion      = $. if m/^\s*#\s*include\s*<mikux\/version\.h>/o;
	}

	# Look for uses: MIKUX_VERSION_CODE, KERNEL_VERSION,
	# MIKUX_VERSION_MAJOR, MIKUX_VERSION_PATCHLEVEL, MIKUX_VERSION_SUBLEVEL
	if (($_ =~ /MIKUX_VERSION_CODE/) || ($_ =~ /\WKERNEL_VERSION/) ||
	    ($_ =~ /MIKUX_VERSION_MAJOR/) || ($_ =~ /MIKUX_VERSION_PATCHLEVEL/) ||
	    ($_ =~ /MIKUX_VERSION_SUBLEVEL/)) {
	    $fUseVersion = 1;
            last if $iMikuxVersion;
        }
    }

    # Report used version IDs without include?
    if ($fUseVersion && ! $iMikuxVersion) {
	print "$file: $.: need mikux/version.h\n";
    }

    # Report superfluous includes.
    if ($iMikuxVersion && ! $fUseVersion) {
	print "$file: $iMikuxVersion mikux/version.h not needed.\n";
    }

    # debug: report OK results:
    if ($debugging) {
        if ($iMikuxVersion && $fUseVersion) {
	    print "$file: version use is OK ($iMikuxVersion)\n";
        }
        if (! $iMikuxVersion && ! $fUseVersion) {
	    print "$file: version use is OK (none)\n";
        }
    }

    close($f);
}
