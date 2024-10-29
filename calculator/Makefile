all:
	@g++ main.cpp -o app -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto

.PHONY: run
run:
	@g++ main.cpp -o app -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto
	@./app

.PHONY: test
test:
	g++ -D BOBCAT_UI_TESTING=1 -o test test.cpp -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto
	clear && echo Running tests:
	@./test --output=color

.PHONY: visual_test
visual_test:
	g++ -o test test.cpp -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto
	clear && echo Running tests:
	@./test --output=color

.PHONY: pull
pull:
ifeq ($(shell git rev-parse --is-inside-work-tree 2>/dev/null),true)
	@git reset --hard
	@git clean -fdx
	@git pull --ff-only
else
	@echo "No git repository found in the current directory"
endif

.PHONY: clean
clean:
	@rm -f app
	@rm -f test