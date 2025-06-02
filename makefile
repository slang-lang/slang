no_target:

clean:
	find .. -maxdepth 1 -type f -name 'slang_*' -delete

package:
	dpkg-buildpackage -us -uc -nc

.PHONY: clean package
