I²C kicker slave
================

This is meant to be a I²C slave for a digital soccer table.

       +---+----- (+)
       |   |
        /   /
       /   /
       |   |
    +--+---+--+
    |         |
    |         |
    +--+---+--+
       |   |
       |   +---- SDA
       |
       +-------- SCL


The controller stores the absolute number of goals that have been achieved.
A connected I²C master can repeatingly query for the current status and
receive the information that a goal was achieved.  
There's no communication invoked by the slave. The master should query every
second (or perhaps quarter second) the current counters. As there usually won't
be more than 1 goal per second (at least not more than 50), also a overflow can
easily be detected and accordingly have the number of goals be calculated.
