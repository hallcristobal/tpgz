## FAQ

\*\*faqs here

- How do I know I have the correct ISO? (md5sum)

### I get an Unexpected Argument error when I try to generate the ISO.

```
error: Found argument 'Zelda,' which wasn't expected, or isn't valid in this context
```

Your ISO likely has spaces in the filename and you do not have quotes around it.

'romhack.exe apply' expects 3 arguments (patch file, initial ISO, output filename):<br>
`romhack.exe apply [1] [2] [3]`

Correct:

```
romhack.exe apply tpgz-v0.1a.patch "Twilight Princess (USA).iso" output.iso
                  ^                 ^                            ^
                 [1]               [2]                          [3]
```

Incorrect:

```
romhack.exe apply tpgz-v0.1a.patch Twilight Princess (USA).iso output.iso
                  ^                 ^       ^        ^         ^
                 [1]               [2]     [3]      [4]       [5]
```
