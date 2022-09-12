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


VS Code example tasks file:


{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "cd /mnt/c/jure/Programiranje/codingame/merge && codingame-merge -o cg.cpp -w /mnt/c/jure/repos/codingame-puzzle-solutions/bots/cultist-wars/ -m main.cpp",
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}