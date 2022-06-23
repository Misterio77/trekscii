# trekscii

An ASCII Star Trek scene generator! Ex:
![demo](demo.png)

## Compilation

If this project becomes any more complicated, I'll add a proper build system. For now:

```
g++ trekscii.cpp -o trekscii
```
If you'd like, install the resulting binary to a location in your `$PATH`.

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
