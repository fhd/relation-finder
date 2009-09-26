all:
	$(MAKE) -C src

unit-tests:
	$(MAKE) test -C test

clean:
	$(MAKE) clean -C src
	$(MAKE) clean -C test
