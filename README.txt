----------------------
   gPlead Card Game   
----------------------


A card game inspired by FF8 Triple Triad written in C and GTK+.


=== How to Play ===


Each player has 5 cards on his hand and the game field is 3x3 wide, with a
total of nine space. In each turn the player has to move a card from his hand
into a void field space. If there is an opponent card near, the cards values are
compared and if the opponent one is weaker, then it is conquered. There is a
value on each side of the cards, only adjacent numbers are compared to choose
which card is stronger.
Each field space has four runes. Also cards have a rune, used to increase or
decrease the values when one card is played on the field. If the card rune is
equal to the rune on the field where it's placed, the card gets a bonus of +1 on
the corresponding value. Otherwise, if the runes are of opposite types, a -1 is
applied to the value.
The winner is the player that conquered more cards when the game ends (when the
game field is full, and no more cards can be played).

=== Credits ===

Loris "Pyrox" Gabriele
	www.pyrox.it
Davide "Unwlelt" Benotto
	unwlelt.altervista.org

