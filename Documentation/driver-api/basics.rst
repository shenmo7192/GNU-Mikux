Driver Basics
=============

Driver Entry and Exit points
----------------------------

.. kernel-doc:: include/mikux/module.h
   :internal:

Driver device table
-------------------

.. kernel-doc:: include/mikux/mod_devicetable.h
   :internal:
   :no-identifiers: pci_device_id


Delaying and scheduling routines
--------------------------------

.. kernel-doc:: include/mikux/sched.h
   :internal:

.. kernel-doc:: kernel/sched/core.c
   :export:

.. kernel-doc:: kernel/sched/cpupri.c
   :internal:

.. kernel-doc:: kernel/sched/fair.c
   :internal:

.. kernel-doc:: include/mikux/completion.h
   :internal:

Time and timer routines
-----------------------

.. kernel-doc:: include/mikux/jiffies.h
   :internal:

.. kernel-doc:: kernel/time/time.c
   :export:

.. kernel-doc:: kernel/time/timer.c
   :export:

High-resolution timers
----------------------

.. kernel-doc:: include/mikux/ktime.h
   :internal:

.. kernel-doc:: include/mikux/hrtimer.h
   :internal:

.. kernel-doc:: kernel/time/hrtimer.c
   :export:

Wait queues and Wake events
---------------------------

.. kernel-doc:: include/mikux/wait.h
   :internal:

.. kernel-doc:: kernel/sched/wait.c
   :export:

Internal Functions
------------------

.. kernel-doc:: kernel/exit.c
   :internal:

.. kernel-doc:: kernel/signal.c
   :internal:

.. kernel-doc:: include/mikux/kthread.h
   :internal:

.. kernel-doc:: kernel/kthread.c
   :export:

Reference counting
------------------

.. kernel-doc:: include/mikux/refcount.h
   :internal:

.. kernel-doc:: lib/refcount.c
   :export:

Atomics
-------

.. kernel-doc:: include/mikux/atomic/atomic-instrumented.h
   :internal:

.. kernel-doc:: include/mikux/atomic/atomic-arch-fallback.h
   :internal:

.. kernel-doc:: include/mikux/atomic/atomic-long.h
   :internal:

Kernel objects manipulation
---------------------------

.. kernel-doc:: lib/kobject.c
   :export:

Kernel utility functions
------------------------

.. kernel-doc:: include/mikux/kernel.h
   :internal:
   :no-identifiers: kstrtol kstrtoul

.. kernel-doc:: kernel/printk/printk.c
   :export:
   :no-identifiers: printk

.. kernel-doc:: kernel/panic.c
   :export:

Device Resource Management
--------------------------

.. kernel-doc:: drivers/base/devres.c
   :export:

