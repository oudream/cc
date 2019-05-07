all: libgnurx-0.dll libgnurx.dll.a libregex.a gnurx.lib

THIS = libgnurx
VERSION = 2.9

CC = gcc -mthreads -mtune=pentium3 -O3 -D__USE_GNU
CFLAGS = -I .

SOURCES = $(wildcard *.c *.h)
OBJECTS = regex.o

libgnurx-0.dll libgnurx.dll.a: $(OBJECTS) Makefile
	$(CC) -shared -o libgnurx-0.dll -Wl,--enable-auto-image-base -Wl,--out-implib,libgnurx.dll.a -Wl,--output-def,libgnurx.def $(OBJECTS)

libregex.a: libgnurx.dll.a
	cp -p libgnurx.dll.a $@

gnurx.lib: libgnurx-0.dll
	lib -def:libgnurx.def -out:gnurx.lib

dist: $(THIS)-$(VERSION).zip $(THIS)-dev-$(VERSION).zip $(THIS)-src-$(VERSION).zip

install:
	cp -p libgnurx-0.dll /usr/local/bin
	cp -p libregex.a /usr/local/lib
	cp -p regex.h /usr/local/include
	cp -p libgnurx.dll.a /usr/local/lib

$(THIS)-$(VERSION).zip: libgnurx-0.dll
	mkdir -p runtime/bin
	cp -p libgnurx-0.dll runtime/bin
	(cd runtime; zip -r ../$(THIS)-$(VERSION).zip bin)
	rm -rf runtime

$(THIS)-dev-$(VERSION).zip:  regex.h libgnurx.dll.a libregex.a gnurx.lib
	mkdir -p dev/include dev/lib
	cp -p regex.h dev/include
	cp -p libgnurx.dll.a libregex.a gnurx.lib dev/lib
	(cd dev; zip -r ../$(THIS)-dev-$(VERSION).zip .)
	rm -rf dev

$(THIS)-src-$(VERSION).zip: Makefile COPYING $(SOURCES)
	mkdir $(THIS)-$(VERSION)
	cp -p Makefile COPYING $(SOURCES) $(THIS)-$(VERSION)
	zip -r $@ $(THIS)-$(VERSION$)
	rm -rf $(THIS)-$(VERSION$)
