DIRS = ./Hello_World_Module

all clean check: $(DIRS)
$(DIRS):
	$(info inside dirs)
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: all check $(DIRS)
