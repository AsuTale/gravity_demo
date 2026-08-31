Welcome to a small gravity 'simulation' project I did for a mini gamejam !

Stick around to see how I try to optimize it using SIMD and miserably fail.

First, clone the repo and the submodules using `git clone --recurse-submodules https://github.com/AsuTale/gravity_demo`, then create a `build` folder at the root of the project and call `cmake ..` from inside of it.
You might want to enable compiler optimizations doing the same thing but using `cmake -DCMAKE_BUILD_TYPE=Release ..`.
now you only need to call `make` and it should work !
Have fun !

Commands:

`left click` to add a particule.
you can give it momentum by dragging before releasing !
use `space` to pause the simulation.
you can control how many particules you want to add in one click with `p` and `m`, the number is written on top of the screen.
