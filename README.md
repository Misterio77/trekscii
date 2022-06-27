# trekscii

An ASCII Star Trek scene generator!
![demo](demo.png)

## Compilation

In the root project directory:

```
$ make
# make install
```

## Usage

```bash
trekscii [height] [width]
```
e.g.

```bash
trekscii 25 85
trekscii 35 $(tput cols)               # terminal width, fixed height
trekscii $(tput lines) $(tput cols)    # full-terminal
```
