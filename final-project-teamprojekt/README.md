# Chess Game

Chess Game is a C++ implementation for the famous game loved by all made for single and multi-player usage.

## Installation

Use the SFML library [sfml](https://www.sfml-dev.org/download/sfml/2.5.1/) to install sfml ro successfully run the program on your local machine.

Once SFML library is installed you should be good to go. The code below should make and help you run the game.

```bash
make gui
./bin/gui
```

## Functionality
Chess Game functions as a virtual game which either one or more people can play chess on.
It validates and runs according to all up-to-date chess rules and invalidates all illegal moves for the user and declares the game over when either of the King is dead.
Chess Game also implements the usage of an undo feature which helps the user undo any move or revert back to any situation during the playthrough, even multiple moves ago.

## Testing
The Game has been throughly tested on a mac. GUI compatibility on windows was not tested and may not work as expected on windows as WSL re-routing was required.
