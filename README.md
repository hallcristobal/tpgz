<!-- # <img src="./res/icons/icon.jpg" height="42" width="42" align="top"/> tpgz -->

# <img src="./res/icons/icon.jpg" height="36" width="36" align="top" style="padding-top:3px;"/> tpgz

Twilight Princess ROM hack to practice speedrunning.

- [Creating an ISO](#creating-an-iso) - How to create a practice iso.
- [Get Started](#creating-an-iso) - How to create an iso.

⚠️ tpgz is still in early development.<br>
If you have questions or need help, please check the [FAQ](#faq) or ask the TP Speedrunning Discord.

## Quick Overview

tpgz takes a Twilight Princess ISO and generates a new ISO with features that help you practice.
Play the new ISO on [Dolphin](https://dolphin-emu.org/) or a homebrewed Wii.

```
 <TP iso>   +   <patch file>   =>   <TPGZ iso>
     ^               ^                   ^
You provide       Provided            Created
```

## Features

Use L+R+dpadDown to open the main menu which contains the following options:

```
cheats menu:
- infinite air                  // Gives Link infinite air underwater
- infinite arrows               // Gives Link 99 arrows
- infinite bombs                // Gives Link 99 bombs in all bags
- infinite hearts               // Link will always have full hearts
- infinite oil                  // Gives Link infinite lantern oil
- infinite rupees               // Link will always have 1000 rupees
- infinite slingshot            // Gives Link 99 slingshot pellets
- invincible                    // Makes Link invincible (no hurtbox, but can still take fall damage and drown)
- invincible enemies*           // Makes some enemies invincible (infinite health)
- moon jump                     // Hold R+A to moon jump
- super clawshot (TBD)          // Clawshot is long and can grab most things (not implemented yet)
- super spinner (TBD)           // Spinner is very fast and can hover (not implemented yet)

flags menu:
- boss flag                     // Set the boss flag value. Press A to lock the value
- epona stolen                  // Toggle flag for Epona being stolen
- epona tamed                   // Toggle flag for Epona being tamed
- map warping                   // Toggle flag for having map warping
- midna charge                  // Toggle flag for Midna charge
- midna healthy                 // Toggle flag for Midna being healthy/sick
- midna on back                 // Toggle flag for Midna appearing on Wolf Link's back
- midna on z                    // Toggle flag for being able to use Midna
- transform/warp                // Toggle flag for transforming/warping
- wolf sense                    // Toggle flag for having wolf sense

inventory menu:
- item wheel                    // Can set the 24 item wheel slots to any item
- pause menu (TBD)              // Can modify the pause menu collection (not implemented yet)

memory menu:
- Add memory watches to the screen (not implemented yet)

practice menu:
- Load practice files* (supports popular Any% and 100% locations)

scene menu:
- disable bg music*             // Disables background and enemy music
- disable sfx                   // Disables sound effects (item, weather, etc.)
- freeze actors                 // Freezes actors
- freeze camera                 // Locks the camera in place
- hide actors                   // Hides actors
- hide hud                      // Hides the heads-up display
- time (hrs)                    // The current in-game hour
- time (mins)                   // The current in-game minutes

settings menu:
- log level                     // Changes log level for debugging
- drop shadows                  // Adds shadows to all font letters
- save card                     // Save settings to memory card
- load card                     // Load settings from memory card
- area reload behavior          // load area = Reload last area; load file = Reload last file

tools menu:
- area reload                   // Use L+R+Start+A to reload current area
- fast bonk recovery            // Reduces bonk animation significantly
- fast movement                 // Link's movement is much faster
- gorge checker                 // Use L+Z to warp to Kakariko Gorge
- input viewer                  // Show current inputs (buttons only for now)
- link debug info               // Show Link's position, angle, and speed
- no sinking in sand            // Link won't sink in sand
- roll checker                  // Frame counter for chaining rolls
- teleport                      // dpadUp to set, dpadDown to load
- timer                         // Frame timer: Z+A to start/stop, Z+B to reset
- link tunic color:             // Changes Link's tunic color (green, blue, red, orange, yellow, white, or cycle)

warping menu:
- warp to dungeons, towns, grottos, etc. (not implemented yet)
```

## Known Issues

```
- invicible enemies cheat can't be turned off once turned on
- disabled bg music tool may not always disable bg music
- loading practice files can crash in certain situations
```

## Planned Features

```
- free cam
- actor spawner
- frame advance
- collision viewer
- menu font selector
- lag counter & loading counter
```

## Creating an ISO

_These instructions are for Windows.
Mac and Linux please see [BUILDING](./BUILDING.md)._

Your new practice ISO is minutes away.<br>
_Don't worry!_
These instructions are intentionally detailed to prevent confusion.
Anyone with basic computer experience will have no problem.

**You will need a Twilight Princess ISO.**
_(Only supports US Gamecube version for now.)_

1. Download the latest release [here](https://github.com/hallcristobal/tpgz/releases).
   _(Feel free to follow the release page instructions instead of these.)_

2. Unzip the downloaded file to create a new folder, then open that folder.<br>
   You should see something _similar_ to the following:

   - romhack.exe
   - tpgz.patch

3. Put a copy of your Twilight Princess ISO (NTSC-U) in this folder.
   The ISO's filename is not important.<br>
   _Example:_

   - romhack.exe
   - tpgz.patch
   - Legend of Zelda, The - Twilight Princess (USA).iso

4. Copy the folder's path.
   _(Example: `C:\example\path`)_

5. Open cmd.

   - Press `<WindowsKey>+r` then type "cmd" into the popup and hit `<Enter>`.

6. Navigate to the above folder within cmd.

   - In cmd, enter the following and hit enter:<br>
     `cd <paste folder's path here>`

     _Example output:_

     ```
     C:\Users\Name>cd C:\Users\Name\Downloads\tpgz-folder

     C:\Users\Name\Downloads\tpgz-folder>
     ```

7. Run the following to create the tpgz ISO:<br>
   `romhack.exe apply <The-tpgz-patch>.patch <Your-ISO-name>.iso tpgz-patched.iso`

   - It is recommended that you type this out rather than copy-paste to avoid some common mistakes.
   - Type 'romhack.exe apply'.
     - _Note that you can use `<Tab>` to auto-complete files in the current folder.
       Typing "rom" then hitting `<Tab>` should change "rom" to "romhack.exe".
       You can hit `<Tab>` multiple times to cycle through available options.
       "apply" is not a filename so you will have to type it out._
   - Add the patch file's name.
     - _Type "tpgz", then hit `<Tab>.`
       This will auto-complete to the patch's filename._
   - Add your ISO's name.

     - _It is strongly recommended that you use `<Tab>` to auto-complete the ISO's filename.
       This will add necessary quotes if your filename has spaces.<br>
       Correct: "My TP ISO.iso"<br>
       Incorrect: My TP ISO.iso_

   - Add a filename for the new ISO.
     - Use "tpgz-patched.iso" or any other name ending in ".iso".
   - Press `<Enter>` after you have finished entering the command.
     - This will generate the new ISO.
       It may take a few minutes to complete.

8. Load the new ISO in
   [Dolphin emulator](https://dolphin-emu.org/) or a Wii using a homebrew loader such as [Nintendont](https://github.com/FIX94/Nintendont).

9. Use L+R+dpadDown to open the features menu in game.

Having trouble? See the FAQ.

Want the latest features but tired of waiting on releases? See

## Building

See [BUILDING](./BUILDING.md).

## Contributing

See [CONTRIBUTING](./CONTRIBUTING.md).
