include Makefile.conf

targets=all library app qtrenderer rancheck PwMoviePlayer proputil pmvutil qt_clust

.PHONY: ${targets} clean

all: ${targets}

library:
	+ make -C src/library/

qtrenderer: library
	+ make -C src/qtrenderer/

app: library qtrenderer
	+ make -C src/app/

rancheck:
	+ make -C src/tools/rancheck

PwMoviePlayer: library qtrenderer
	+ make -C src/tools/PwMoviePlayer

proputil: library qtrenderer #todo: nullrenderer instead of qtrenderer
	+ make -C src/tools/proputil

pmvutil: library qtrenderer #todo: nullrenderer instead of qtrenderer
	+ make -C src/tools/pmvutil

qt_clust:
	+ make -C src/tools/clustering

clean:
	rm -rf ${PWBLD}