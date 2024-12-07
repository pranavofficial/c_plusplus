all:
	@g++ main.cpp -o app -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto

.PHONY: run
run:
	@g++ main.cpp -o app -lfltk_images -lpng -lz -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lhttp -lssl -lcrypto
	@./app

.PHONY: test
test:
	@echo There is nothing to test in this project

.PHONY: visual_test
visual_test:
	@echo There is nothing to test in this project

.PHONY: pull
pull:
	@echo There is nothing to pull in this project

.PHONY: clean
clean:
	@rm -f app
	@rm -f test