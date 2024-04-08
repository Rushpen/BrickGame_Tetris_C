CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SF = -fsanitize=leak,address
DIST_DIR :=archive

all: install run gcov_report

lib:
	sudo apt install libncursesw5-dev

tetris: brick_game/tetris/tetris_game.c brick_game/tetris/fsm.c ./gui/cli/tetris_interface.c
	$(CC) $(CFLAGS) brick_game/tetris/tetris_game.c brick_game/tetris/fsm.c ./gui/cli/tetris_interface.c -lncurses -o tetris.out

test: brick_game/tetris/tetris_game.c brick_game/tetris/fsm.c ./gui/cli/tetris_interface.c
	$(CC) -g $(CFLAGS) -fprofile-arcs -ftest-coverage brick_game/tetris/tetris_game.c brick_game/tetris/fsm.c ./gui/cli/tetris_interface.c -lncurses -o tetris.out

gcov_report: test
	chmod +x ./tetris.out
	mkdir -p gcov-report
	cp tetris.out-tetris_game.gcno brick_game/tetris/tetris_game.gcno
	cp tetris.out-tetris_interface.gcno ./gui/cli/tetris_interface.gcno
	./tetris.out
	gcov -r brick_game/tetris/tetris_game.c brick_game/tetris/fsm.c ./gui/cli/tetris_interface.c
	gcovr -r . --html --html-details -o gcov-report/index.html
	open ./gcov-report/index.html

clean:
	@rm -rf *.gcno *.gcda *.gcov brick_game/tetris/*.gcno gui/cli/*.gcno brick_game/tetris/*.gcda gui/cli/*.gcda
	@rm -rf gcov-report
	@echo "All new created files deleted"

run:
	./tetris.out

install: tetris

uninstall: clean
	@rm -rf tetris.out
	@echo "Uninstallation is finished"

dvi:
	open ../dvi/dvi.md

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz