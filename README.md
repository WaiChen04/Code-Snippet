# Introduction
Here is some code I have written for class or personal use



## C

To compile the code make a Makefile in the same folder as the code that contains the following:
```
all: filename

filename: filename.c
	gcc -Wall -Werror -fsanitize=address undefined -g filename.c -o filename
	
clean:
	rm -rf filename
```
Then in the terminal run:

```
make
```




## Java

All the Java files I edited are in the "src" folder. All of the code can be run through VSCode.

To run through the terminal:

    first navigate to filename directory/folder
        to compile:  javac -d bin src/foldername/*.java
        to execute: java -cp bin foldername.Driver



**MusicPlaylist:** An ArrayList to hold all the playlists in a library and a Circular Linked List to hold all the songs in a playlist.

**RisingTides:** Uses a Weighted UnionFind algorithm to simulate floods on a terrain.

**HungerGames:**  Implements a Binary Search Tree to simulate picking people for the Hunger Games and duels that occur during the Hunger Games.

**RUHungry:** Uses hashtables to keep tracks of the menu, stock, transactions of a restaurant.

