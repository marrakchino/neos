# Hello World

This is the most basic example to come up with when developing a kernel.
I spent a long time trying to grasp as many mecanisms as possible (the 
compilation process, linking, inspecting object files, ... ) in order to have 
a decent understanding of the process, and I learned many things, some of which 
still need more investigation though.

This directory is included only as an example:

* The system prints ""Hello, world!" on a black screen and does nothing special.

* The only noteworthy module is `screen` which drives the VGA output and prints
to the screen.

* This example is so rudimentary that there is no notion of process/task, 
scheduler, interrupts, time, keyboard/mouse driver whatsoever.


## Comments

I recycled these files from a 2015 school lab. This is the reason why 
several files (which were given as a skeleton) are used 'as is', their
license/copyright headers are consequently kept intact. 

Also, some code is outdated, some parts are undocumented, and some
functions/variables are still in their original state (not clean at all). 

The code will be revisited gradually to only keep the strict minimum.

## Further reading

* http://wiki.osdev.org/Bare_Bones

* http://dbp-consulting.com/tutorials/debugging/linuxProgramStartup.html

## License

Unless a used file contains its own copyright/license, these files are licensed
under the MIT license.

