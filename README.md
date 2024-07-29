# WordleV2
Version 2 of my previous Wordle Game with Object-Oriented Programming and dynamic memory!

Windows Users:
1. Download the .exe file called "WordleGame" and .txt file "wordleWords.txt"
2. Make sure they are in the same folder
3. Open "WordleGame" and play

Mac Users:
1. This method is a lot less accessible because MacOS requires absolute path of .txt file to open, so I created a program that gets the pathname but it will need to be compiled in terminal
2. Download both cpp files "wordle.cpp" and "words.cpp" and the .txt file "wordleWords.txt"
3. Go to your terminal, navigate to the folder with these (make sure they're in the same folder) and perform the following commands
4. g++ -c words.cpp wordle.cpp
5. g++ words.o wordle.o -o wordle
6. ./wordle
7. If these don't work, you will need to download the gcc compiler or Xcode (yes this is way less accessible)
