# Project settings
HID_OBJNAME :=		hid
PHYS_OBJNAME :=		physical
HID_SRC :=			$(wildcard $(HID_OBJNAME)/src/*.c)
PHYS_SRC :=			$(wildcard $(PHYS_OBJNAME)/src/*.c)
HID_HEADERS :=		$(wildcard $(HID_OBJNAME)/include/*.h)
PHYS_HEADERS :=		$(wildcard $(PHYS_OBJNAME)/include/*.h)

# Helper targets
.PHONY : all
all : /tmp/pico-sdk $(HID_OBJNAME).uf2 $(PHYS_OBJNAME).uf2

.PHONY : install-deps
	@if ! [ "$(shell id -u)" = 0 ];then
		@echo "You are not root, run this target as root please"
		exit 1
	fi
	apt install -y \
		git cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential

/tmp/pico-sdk :
	cd /tmp; git clone -b master https://github.com/raspberrypi/pico-sdk.git
	cd /tmp/pico-sdk; git submodule update --init

.PHONY : clean
clean :
	rm -rf /tmp/pico-sdk
	rm -rf $(HID_OBJNAME)/build
	rm -rf $(PHYS_OBJNAME)/build
	rm -rf $(HID_OBJNAME).uf2
	rm -rf $(PHYS_OBJNAME).uf2

# Main targets
$(HID_OBJNAME).uf2 : $(HID_SRC) $(HID_HEADERS)
	mkdir -p $(HID_OBJNAME)/build
	cd $(HID_OBJNAME)/build; PICO_SDK_PATH=/tmp/pico-sdk cmake ..
	cd $(HID_OBJNAME)/build; make
	cp $(HID_OBJNAME)/build/$(HID_OBJNAME).uf2 .
	
$(PHYS_OBJNAME).uf2 : $(PHYS_SRC) $(PHYS_HEADERS)
	mkdir -p $(PHYS_OBJNAME)/build
	cd $(PHYS_OBJNAME)/build; PICO_SDK_PATH=/tmp/pico-sdk cmake ..
	cd $(PHYS_OBJNAME)/build; make
	cp $(PHYS_OBJNAME)/build/$(PHYS_OBJNAME).uf2 .
