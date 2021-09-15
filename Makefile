EXCLUDE :=
DIRS    := $(filter-out $(EXCLUDE), $(wildcard */))

$(MY_TARGETS): $(DIRS)
$(DIRS):
	$(info inside dirs)
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(MY_TARGETS) $(DIRS)
