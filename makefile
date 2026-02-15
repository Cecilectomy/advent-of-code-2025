DAY ?= 1

.PHONY: clean
clean:
	@rm -rf ./.build

.PHONY: build
build:
	@mkdir -p ./.build
	g++ -std=c++20 -Isrc src/solutions/day$(DAY).cpp -o .build/day$(DAY)
