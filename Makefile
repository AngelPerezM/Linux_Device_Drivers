EXCLUDE :=
DIRS    := $(filter-out $(EXCLUDE), $(wildcard */))

all clean check: $(DIRS)
$(DIRS):
	$(info inside dirs)
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all check $(DIRS)
