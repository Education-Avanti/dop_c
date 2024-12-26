
VERSION=$(shell cat ../VERSION)
DESTDIR?=/usr
PREFIX?=/local

LDCONFIG?=ldconfig

ifneq ($V,1)
Q ?= @
endif

STATIC=dop_lib_c.a
DYNAMIC=dop_lib_c.so.$(VERSION)

#DEBUG	= -g -O0
DEBUG	= -O2
CC	?= gcc
INCLUDE	= -I.
DEFS	= -D_GNU_SOURCE
CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Winline $(INCLUDE) -pipe -fPIC $(EXTRA_CFLAGS)
#CFLAGS	= $(DEBUG) $(DEFS) -Wformat=2 -Wall -Wextra -Wconversion -Winline $(INCLUDE) -pipe -fPIC

LIBS    = -lwiringPi -lm -lpthread

###############################################################################

SRC	=	src/Accel_gyro_lyb.c	\
		src/Arm.c				\
		src/Button_lib.c		\
		src/Color_module_lib.c	\
		src/Config.c			\
		src/DEV_Config.c		\
		src/Joystick_lib.c		\
		src/Led_lib.c			\
		src/Obstacle_lib.c		\
		src/Relay_lib.c			\
		src/Servo_lib.c			\
		src/TCS34725.c			\

HEADERS =	$(shell ls include/*.h)

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

.PHONY:	static
static:	
		$Q cat noMoreStatic

$(DYNAMIC):	$(OBJ)
	$Q echo "[Link (Dynamic)]"
	$Q $(CC) -shared -Wl,-soname,dop_lib_c.so$(WIRINGPI_SONAME_SUFFIX) -o dop_lib_c.so.$(VERSION) $(OBJ) $(LIBS)

.c.o:
	$Q echo [Compile] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@


.PHONY:	clean
clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) $(OBJ_I2C) *~ core tags Makefile.bak dop_lib_c.*

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
	$Q install -m 0755 dop_lib_c.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/dop_lib_c.so.$(VERSION)
	$Q ln -sf $(DESTDIR)$(PREFIX)/lib/dop_lib_c.so.$(VERSION)	$(DESTDIR)/lib/dop_lib_c.so
	$Q $(LDCONFIG)

.PHONY: check-deb-destdir
check-deb-destdir:
ifndef DEB_DESTDIR
	$(error DEB_DESTDIR is undefined)
endif

.PHONY:	install-deb
install-deb:	$(DYNAMIC) check-deb-destdir
	$Q echo "[Install Headers: deb]"
	$Q install -m 0755 -d							$(DEB_DESTDIR)/usr/include
	$Q install -m 0644 $(HEADERS)						$(DEB_DESTDIR)/usr/include
	$Q echo "[Install Dynamic Lib: deb]"
	install -m 0755 -d							$(DEB_DESTDIR)/usr/lib
	install -m 0755 dop_lib_c.so.$(VERSION)				$(DEB_DESTDIR)/usr/lib/dop_lib_c.so.$(VERSION)
	ln -sf $(DEB_DESTDIR)/usr/lib/dop_lib_c.so.$(VERSION)	$(DEB_DESTDIR)/usr/lib/dop_lib_c.so

.PHONY:	uninstall
uninstall:
	$Q echo "[UnInstall]"
	$Q cd $(DESTDIR)$(PREFIX)/include/ && rm -f $(HEADERS)
	$Q cd $(DESTDIR)$(PREFIX)/lib/     && rm -f dop_lib_c.*
	$Q $(LDCONFIG)


.PHONY:	depend
depend:
	makedepend -Y $(SRC) $(SRC_I2C)

# DO NOT DELETE

###################################################################################################


# #DIR_FONTS = ./Fonts
# DIR_OBJ = ./TCS34725
# DIR_BIN = ./bin

# OBJ_C = $(wildcard ${DIR_OBJ}/*.c)
# OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

# TARGET = main
# #BIN_TARGET = ${DIR_BIN}/${TARGET}

# CC = gcc

# DEBUG = -g -O0 -Wall
# CFLAGS += $(DEBUG) 

# LIB = -lwiringPi -lpthread -lm

# ${TARGET}:${OBJ_O}
# 	$(CC) $(CFLAGS) $(OBJ_O) -o $@  $(LIB)

# ${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
# 	$(CC) $(CFLAGS) -c  $< -o $@  $(LIB)


	
# clean :
# 	rm $(DIR_BIN)/*.* 
# 	rm $(TARGET) 