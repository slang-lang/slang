no_target:

clean:
	rm slang_*.buildinfo
	rm slang_*.changes
	rm slang_*.deb
	rm slang_*.dsc
	rm slang_*.tar.gz
	rm slang_*.tar.xz

package:
	dpkg-buildpackage -us -uc

.PHONY: clean compile
