# Space Shooter
A game made with C++ & SDL2. The game should work without installation. Just run the
.exe file.

The game is designed to be played with a controller. I've only tested
it with an Xbox-controller. Testing with other controllers would be appreciated.
You can also play with your keyboard.

Controller inputs:
- Left analog stick moves the player
- Right analog stick shoots to the direction it's held 
- A-button selects a new game or quits in the main menu and returns you back to main menu when dead
- Start-button pauses when in game.

Keyboard inputs:
- WASD-keys move the player
- Arrow-keys shoot to a direction 
- Enter selects a new game or quits when in main menu and returns you to main menu when dead
- You can't pause with keyboard yet.

Known issues:
- Textures are fixed size, which is why the font of highscore changes depending on
how many digits it has.
- Player might keep shooting when releasing the right analog stick.
- The "enemy" might be misinterpreted as a power-up (which are not in the game yet).
- There are no options/highscores/instructions yet, even though they are shown in
the main menu.
- Pause messes up some things like player's rotation.
- Some memory leaks exist (thanks to my excellent C++ skills), most notably when
starting a new game or going back to main menu when dead.
- If player keeps moving to a direction when touching a side, the stars keep moving.
- The game loop should always tick 60 times per second, but sometimes it ticks 61
times per second.