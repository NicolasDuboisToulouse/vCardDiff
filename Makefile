SUBDIRS=src

# Define default target
all:

# Run each target in each ${SUBDIRS}
%:
	@for DIR in ${SUBDIRS}; do \
		$(MAKE) -C $$DIR $@;   \
	done

# Extend clean target
clean: clean-am
clean-am:
	rm -rf *~

