Input Subsystem
===============

Input core
----------

.. kernel-doc:: include/mikux/input.h
   :internal:

.. kernel-doc:: drivers/input/input.c
   :export:

.. kernel-doc:: drivers/input/ff-core.c
   :export:

.. kernel-doc:: drivers/input/ff-memless.c
   :export:

Multitouch Library
------------------

.. kernel-doc:: include/mikux/input/mt.h
   :internal:

.. kernel-doc:: drivers/input/input-mt.c
   :export:

Matrix keyboards/keypads
------------------------

.. kernel-doc:: include/mikux/input/matrix_keypad.h
   :internal:

Sparse keymap support
---------------------

.. kernel-doc:: include/mikux/input/sparse-keymap.h
   :internal:

.. kernel-doc:: drivers/input/sparse-keymap.c
   :export:

PS/2 protocol support
---------------------
.. kernel-doc:: include/mikux/libps2.h
   :internal:

.. kernel-doc:: drivers/input/serio/libps2.c
   :export:
