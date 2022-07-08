bterm
=====

What?
-----

This is a set of firmware and hardware to turn a Brother WP-1 into a serial
terminal for a Raspberry Pi.

It consists of:

  - software to make a Brother bootable floppy containing a VT102-subset serial
	terminal

  - firmware for a PSoC5 CY8CKIT-049 based interface

  - a PCB which connects the Brother, CY8CKIT-049 and Raspberry Pi together

  - a 3D printable fascia which fits into the Brother's expansion slot

It also provides a MDA/Hercules/CGA-compatible video out connector which
reproduces what's on the Brother's screen.


Why?
----

Why not?


How?
----

So this is all so bespoke to my purposes that it's probably not going to be
very useful to anyone else. What documentation there is comes from the Youtube
series of videos I made while I developed this:

https://www.youtube.com/playlist?list=PLuQ2s_IbSWv5NDpc9Ew3BYDSF7siX9mNj

But here are some quick notes:

  - build the client software are write it to a floppy (you'll need zmac, ld80
	and fluxengine)

  - build the CY8CKIT-049 firmware and flash it with the Cypress development
	tools

  - get the PCB made and solder the connectors onto it

  - solder a 44-pin connector onto the unpopulated expansion breakout pads on
	the Brother motherboard

  - install Linux (or another OS of your choice) onto a Raspberry Pi, and
	configure out to use hardware handshaking on the main UART

  - plug everything together and attach the flyleads to the Brother CPU's /RD,
	/WR and /IOEN lines

  - ensure that there's a reset button and power switch connected to the
	interface board

  - switch everything on with Code+Q pressed on the Brother

...and then, if you're lucky, it might work.

If you are actually interested in trying this, best thing is to [file an
issue](https://github.com/davidgiven/bterm/issues/new/choose) and I'll see what
I can do to help. Or just send me an email (see below).


Who?  ----

I am David Given, a.k.a. hjalfi in various places. Feel free to send me email
at [dg@cowlark.com](mailto:dg@cowlark.com). You may also [like to visit my
website](http://cowlark.com); there may or may not be something interesting
there.


License?  --------

Everything I wrote, which is nearly everything, is freely redistributable under
the terms of the simplified 2-clause BSD license. tl;dr: go nuts, just don't
claim you wrote it. See the `LICENSE` file for more details.

The one exception are the Raspberry Pi and CYC8KIT-049 footprints in the
`kicad-pcb` directory, which are by SnapEDA and licensed under a Creative
Commons Attribution-ShareAlike 4.0 International License (CC BY-SA) with Design
Exception 1.0. This exception essentially means that the CC BY-SA limitations
don't apply as they're being distributed as part of an aggregate design. [See
SnapEDA's page for
details.](https://support.snapeda.com/en/articles/2957815-what-is-the-design-exception-1-0)

