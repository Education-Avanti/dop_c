VERSION=$(shell cat VERSION)
DESTDIR?=/usr
PREFIX?=/local

LDCONFIG?=ldconfig

ifneq ($V,1)
Q ?= @
endif

STATIC=libdopLibc.a
DYNAMIC=libdopLibc.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	?= gcc
INCLUDE	= -I. -I/path/to/wiringPi/includes
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC $(EXTRA_CFLAGS)

LIBS    = -lm -lpthread -lrt -lcrypt -lwiringPi 

###############################################################################


SRC	=	$(addprefix src/,\
			Accel_gyro_lib.c	\
			Arm.c				\
			Button_lib.c		\
			Color_module_lib.c	\
			Config.c			\
			DEV_Config.c		\
			Joystick_lib.c		\
			Led_lib.c			\
			Obstacle_lib.c		\
			Relay_lib.c			\
			Servo_lib.c			\
			TCS34725.c)


HEADERS =	$(shell ls include/*.h)

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

.PHONY:	static
static:	
		$Q echo "[Static libraries are deprecated]"

$(DYNAMIC):	$(OBJ)
	$Q echo "[Link (Dynamic)]"
	$Q $(CC) -shared -Wl,-soname,libdopLibc.so -o libdopLibc.so.$(VERSION) $(OBJ) $(LIBS)

.c.o:
	$Q echo [Compile] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

.PHONY:	clean
clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags Makefile.bak libdopLibc.*

.PHONY:	tags
tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

.PHONY:	install
install:	$(DYNAMIC)
	$Q echo "[Install Headers]"
	$Q install -m 0755 -d						$(DESTDIR)$(PREFIX)/include
	$Q install -m 0644 $(HEADERS)					$(DESTDIR)$(PREFIX)/include
	$Q echo "[Install Dynamic Lib]"
	$Q install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	$Q install -m 0755 libdopLibc.so.$(VERSION)	$(DESTDIR)$(PREFIX)/lib/libdopLibc.so.$(VERSION)
	$Q ln -sf $(DESTDIR)$(PREFIX)/lib/libdopLibc.so.$(VERSION)	$(DESTDIR)/lib/libdopLibc.so
	$Q $(LDCONFIG)

.PHONY: uninstall
uninstall:
	$Q echo "[Uninstall]"
	$Q cd $(DESTDIR)$(PREFIX)/include/ && rm -f $(HEADERS)
	$Q cd $(DESTDIR)$(PREFIX)/lib/ && rm -f libdopLibc.*
	$Q $(LDCONFIG)

.PHONY: depend
depend:
	makedepend -Y $(SRC)

# DO NOT DELETE THIS LINE -- make depend depends on it.