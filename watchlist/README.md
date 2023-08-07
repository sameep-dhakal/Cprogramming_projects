# watchlist

A watchlist manager, specifically for managing a watchlist for movies
and series. Allows for adding items to the list, removing them, and
modifying their properties like their watch status (unwatched, watched,
plan to watch etc). All data is stored in a binary file, so that it
can persist across runs of the program.

## authors

- Sadbhav Adhikari, BCT-B1 (ACE079BCT054)
- Shekhar Gyawali,  BCT-B1 (ACE079BCT061)

## building

Prerequesites:

- A C compiler (preferably `gcc`, but MSVC and `clang` will also work)
- `make` (not compulsory but useful)

Clone the repository, change directory to the root folder and simply 
run `make`:

```bash
make
```

This will produce a `wl.exe` in the current folder.

If you don't have `make` installed, you can compile `main.c` and `term.c`
yourself:

```bash
# for MSVC:
cl main.c term.c

# for gcc or clang:
gcc main.c term.c -o wl.exe
```
