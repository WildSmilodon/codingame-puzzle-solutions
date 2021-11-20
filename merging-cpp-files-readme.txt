To merge a normal cpp project to a single file, which is accepted by codingame platform do:

Installation:

  sudo apt update
  sudo apt install nodejs
  nodejs -v
  sudo apt install npm
  sudo npm i -g codingame-cpp-merge

Usage (assuming your main file is main.cpp):

codingame-merge -o cg.cpp -w /path/to/cppfiles -m main.cpp

Sync cg.cpp in your browser with condigame website.
