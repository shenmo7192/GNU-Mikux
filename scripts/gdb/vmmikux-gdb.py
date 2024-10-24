#
# gdb helper commands and functions for Mikux kernel debugging
#
#  loader module
#
# Copyright (c) Siemens AG, 2012, 2013
#
# Authors:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This work is licensed under the terms of the GNU GPL version 2.
#

import os

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)) + "/scripts/gdb")

try:
    gdb.parse_and_eval("0")
    gdb.execute("", to_string=True)
except:
    gdb.write("NOTE: gdb 7.2 or later required for Mikux helper scripts to "
              "work.\n")
else:
    import mikux.constants
    if mikux.constants.LX_CONFIG_DEBUG_INFO_REDUCED:
        raise gdb.GdbError("Reduced debug information will prevent GDB "
                           "from having complete types.\n")
    import mikux.utils
    import mikux.symbols
    import mikux.modules
    import mikux.dmesg
    import mikux.tasks
    import mikux.config
    import mikux.cpus
    import mikux.lists
    import mikux.rbtree
    import mikux.proc
    import mikux.timerlist
    import mikux.clk
    import mikux.genpd
    import mikux.device
    import mikux.vfs
    import mikux.pgtable
    import mikux.radixtree
    import mikux.interrupts
    import mikux.mm
    import mikux.stackdepot
    import mikux.page_owner
    import mikux.slab
    import mikux.vmalloc
    import mikux.kasan
