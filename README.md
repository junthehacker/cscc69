# cscc69

All code were compiled on macOS High Sierra with Xcode 10 tools. I can't guarantee they will work on other operating systems, especially Windows.

Simply `cd` into the directory you wish to checkout, and run `make` to compile the binary.

### locks

* `without_locks.c` - Illustrates how race condition can happen if locks are not being used. 
* `locks.c` - Spinlock solution to `without_locks.c`.