DIRS = ./Hello_World_Module
MY_TARGETS =all clean check

$(MY_TARGETS): $(DIRS)
$(DIRS):
	$(info inside dirs)
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(MY_TARGETS) $(DIRS)
