OBJDIR = .obj

ZMAC_FLAGS = \
	--zmac \
	-j -m \
	-I.obj

OBJS = \
	$(OBJDIR)/src/main.rel \
	$(OBJDIR)/src/display.rel \
	$(OBJDIR)/src/interface.rel \
	$(OBJDIR)/src/keyboard.rel \
	$(OBJDIR)/src/vt102.rel \
	$(OBJDIR)/src/print.rel \

all: bterm.img

bterm.img: $(OBJDIR)/fs.cim
	cp $(OBJDIR)/fs.cim bterm.img

$(OBJDIR)/%.cim: src/%.z80 Makefile
	@mkdir -p $(dir $@)
	zmac $(ZMAC_FLAGS) -o $@ -o $(patsubst %.cim,%.lst,$@) $<

$(OBJDIR)/bterm.img: $(OBJS) Makefile
	@mkdir -p $(dir $@)
	ld80 -m -O bin -o $@.all -P7000 $(OBJS)
	tail -c+28673 $@.all > $@

$(OBJDIR)/%.rel: %.z80 Makefile src/constants.lib src/jif.lib
	@mkdir -p $(dir $@)
	zmac $(ZMAC_FLAGS) --rel7 -o $@ -o $(patsubst %.rel,%.lst,$@) $<
	
$(OBJDIR)/mkkeytab: src/mkkeytab.c Makefile
	@mkdir -p $(dir $@)
	gcc -o $@ $<

$(OBJDIR)/keymap.inc: $(OBJDIR)/mkkeytab
	@mkdir -p $(dir $@)
	$< > $@

clean:
	rm -rf $(OBJDIR)

$(OBJDIR)/fs.cim: $(OBJDIR)/boot.cim $(OBJDIR)/bterm.img
src/keyboard.z80: $(OBJDIR)/keymap.inc

