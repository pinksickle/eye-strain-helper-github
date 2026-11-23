mod:
	geode build

run:
	steam steam://rungameid/322170

clean:
	rm -rf .cache
	rm -rf build
	rm -rf build-win

all: mod run