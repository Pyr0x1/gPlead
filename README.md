gPlead
======

A card game inspired by FF8 Triple Triad written in C and GTK+.

<a href="http://it.tinypic.com?ref=2nki6hx" target="_blank"><img src="http://i61.tinypic.com/2nki6hx.png" border="0" alt="gPlead"></a>


How to Play
======

Each player has 5 cards in his deck and the game field is 3x3 wide.   
For each turn, a card has to be played from the deck to the game field. If there is an opponent card whose adjacent value is lower than the played card, the weaker card is conquered.     
Each Game field space has four runes. Also cards have a rune, used to improve the values when one card is played on the field. If the card rune is equal to the rune on the field where it's placed, the card get a bonus of +1 on the value corresponding the field rune.    
The game ends when the game field is full, so no more cards can be played.

Compilation / Installation (Linux)
======

In order to play you'll need to compile the source code hosted on github (binaries will be available in future).    
You'll need GTK+ 3 development packages to succesfully compile the program. This can be easily installed on Ubuntu and derivatives (tested on version 14.04) by running
```bash
sudo apt-get install libgtk-3-dev 
```
Apt should handle all required dependencies.   
Once you have GTK+ libraries correctly installed, you can compile the program by simply running
```bash
make  
```
from a terminal window.    
The game can then be started by running
```bash
./gPlead  
```

