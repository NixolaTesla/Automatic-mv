# Automatic-mv
A tool I made to help me automate moving files on my jellyfin server around.

# Installation

To install this program, simply clone the repository and compile it into an executable. (You can use **gcc** for example)

gcc automove.c -o automove

# Usage

Adding directory names: ./automove <dir1> <dir2>

Clearing movedir.txt: ./automove clear

Running: ./automove


# Notes

STILL A W.I.P! Also if you wanna add something ending with /* (e.g Downloads/*) you should format it like this: ./automove "Downloads/*" /example/dir

IMPORTANT: you will need to move all the files inside of Automatic-mv/ out of it and into another directory after cloning or the tool wont work, ill probably fix it in the future, just thought id upload this here because i need to use this tool on my server + i thought maybe someone else might find this useful too
