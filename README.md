I²C kicker slave
================

This is meant to be a I²C slave for a digital soccer table.

     +--------------+---+---+---- VCC
     |              |   |   |
     |              |S1 |S2 |          R1: 10k
     |               /   /  |          R2: 10k
     |              /   /   |          C1: 100n
     |              |   |   |          C2: 20n
     |              |R1 |R2 |          C3: 20n
     |             +++ +++  |
     |             | | | |  |
     |             | | | |  |
     |             +++ +++  |
     |              |   |   |
     |   +----------+   |   |
     |   |          |   |   |
     |   |   +------|---+   |
     |   |   |      |2  |3  |8
     |C1 |C2 |C3 +--+---+---+--+
    --- --- ---  |             |
    --- --- ---  |ATTiny25     |
     |   |   |   +--+---+---+--+
     |   |   |      |4  |7  |5
     |   |   |      |   |   +---- SDA
     |   |   |      |   |
     |   |   |      |   +-------- SCL
     |   |   |      |
     +---+---+------+------------ GND


The controller stores the absolute number of goals that have been achieved.
A connected I²C master can repeatingly query for the current status and
receive the information that a goal was achieved.  
There's no communication invoked by the slave. The master should query every
second (or perhaps quarter second) the current counters. As there usually won't
be more than 1 goal per second (at least not more than 50), also a overflow can
easily be detected and accordingly have the number of goals be calculated.

Notes
-----
 - Switch to detect goal: https://www.reichelt.de/index.html?ARTICLE=32740
