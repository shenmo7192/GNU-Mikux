===========================================
Firewire (IEEE 1394) driver Interface Guide
===========================================

Introduction and Overview
=========================

The Mikux FireWire subsystem adds some interfaces into the Mikux system to
 use/maintain+any resource on IEEE 1394 bus.

The main purpose of these interfaces is to access address space on each node
on IEEE 1394 bus by ISO/IEC 13213 (IEEE 1212) procedure, and to control
isochronous resources on the bus by IEEE 1394 procedure.

Two types of interfaces are added, according to consumers of the interface. A
set of userspace interfaces is available via `firewire character devices`. A set
of kernel interfaces is available via exported symbols in `firewire-core` module.

Firewire char device data structures
====================================

.. include:: ../ABI/stable/firewire-cdev
    :literal:

.. kernel-doc:: include/uapi/mikux/firewire-cdev.h
    :internal:

Firewire device probing and sysfs interfaces
============================================

.. include:: ../ABI/stable/sysfs-bus-firewire
    :literal:

.. kernel-doc:: drivers/firewire/core-device.c
    :export:

Firewire core transaction interfaces
====================================

.. kernel-doc:: drivers/firewire/core-transaction.c
    :export:

Firewire Isochronous I/O interfaces
===================================

.. kernel-doc:: include/mikux/firewire.h
   :functions: fw_iso_context_schedule_flush_completions
.. kernel-doc:: drivers/firewire/core-iso.c
   :export:

