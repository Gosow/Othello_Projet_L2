#!/bin/bash
make

cd src/jeu_terminal/
make -f jeu_terminal.mk
cd ../../
./main_SDL ; ./bin/othello_terminal_ed

exit 0