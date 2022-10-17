# Animal-Guessing-Game

This is an Animal Guessing Game created in C++. 

It uses a binary tree to store and build a database of questions and responses which are intended to lead the user to the animal they are currently thinking of. This program takes input from a .txt file in the same folder and creates a binary tree from it. The game will be based on the contents of this binary tree. If the program can't find your guess from the binary tree then you are able to add it by creating a new question and node. After you are done with the program, if you added any animals, you have the option to save the new binary tree into a designated output file.

There are several .txt files attached to this project. These are the two that the code is already set to utilize.
- animalGuessingOutputTree.txt  -   should always be blank before running the program
- animalGuessingInputTree.txt   -   this input file has a very large database of animals and guesses

I have attached one other optional input file. In order to use this file, you will have to change one line of code. There are instructions in the code header and the line you need to change is clearly marked.
- animalGuessingShortTree.txt   -   this input file has a very small database of animals. Use this file if you want to build your own grand database

Next steps I wish to take with this code:
    I want to eventually create a React application using this code. I also want to create a single database that covers almost every animal you could think of. I would love to turn this program into a game, and perhaps put it on a personal website. 
