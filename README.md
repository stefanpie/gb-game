#  15 Square Slide Puzzle Game Boy Game
Simple 15 Square Slide Puzzle Game for the Game Boy

![Game Screenshot](/bgb00001.bmp "Game Screenshot")

I did this project to refresh myself on my C programming skills as well as experiment with designing an application for an "embedded system", the Game Boy with unique hardware features and constraints. The game is implemented in C using the [Game Boy Developers Kit](http://gbdk.sourceforge.net/) which is a library and set of tools that enables development for the Game Boy using C. I also used the the [Game Boy Tile Designer tool](http://www.devrs.com/gb/hmgd/gbtd.html) to create the graphics for the game and the [BGB emulator](http://bgb.bircd.org/) for testing the game.

The actual code for the game simple, ans is composed of two parts. First, the initial state of the puzzle game is initialized randomly and the initial puzzle board graphics are drawn. Second, the event loop is executed which handles inputs from the user. If a direction input is captured, the the game will update the puzzle game state by moving the appropriate piece and redrawing the graphics.

The current state of the game is the minimal function prototype that I consider playable. Currently, there is no check or indicator for a game completed / end state. Therefore, there is method to reset the game once the puzzle is solved other than to power cycle the Game Boy. I plan to continue my exploration of software and game development for the Game Boy in C in order to polish the game and develope more advanced ideas for the Game Boy. This also lead to the possibility to experiential with the implantation of physical carts to test on real Game Boys.
