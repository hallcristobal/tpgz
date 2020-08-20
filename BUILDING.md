# Building

## Compiling

1.  Clone the repo with `git clone https://github.com/hallcristobal/tpgz.git`

2.  Run `git submodule update --init --recursive` in the root `tpgz` folder.<br>

3.  Copy your NTSC-U Twilight Princess ISO to the root `tpgz` folder, and rename it to `gz2e01.iso`.

        - You can choose not copy or rename it if you would prefer, just make sure that the lines in
        Romhack.toml match the iso path.
        ```Toml
        # ...
        [src]
        iso = "<iso-path/file-name>"
        # ...
        ```

4.  Install devkitpro.

    - Windows: Download [here](https://github.com/devkitPro/installer/releases)
    - MacOS/Linux: Read [this guide](https://devkitpro.org/wiki/Getting_Started)

5.  Download [Romhack-Compiler](https://github.com/hallcristobal/romhack-compiler/releases).<br>
    This is used to add the compiled code into the ISO.

6.  Run `make` in the root `tpgz` folder.

7.  After the build succeeds, run:

    ```
    romhack build --raw
    ```

8.  The built ISO will now be in a build/ folder in the same directory as the source code.

## Creating Patches

If you'd like to create a patch file for sharing you can with:

```
romhack build --raw --patch
```

---

If you want to compile alternative fonts:

1. Place your font in external/fonts/fonts/

2. Replace the following command in the Makefile

```rust
cargo run -I fonts/your_font.ttf -S 18.0 -N Your_Font_Name -O build
```

3. Run

```
make font
```
