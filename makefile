DAY ?= 1

.PHONY: clean
clean:
	@rm -rf ./.build

.PHONY: build
build:
	@mkdir -p ./.build
	g++ -Isrc src/solutions/day$(DAY).cpp -o .build/day$(DAY)
