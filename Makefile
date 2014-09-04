# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.


# The package path prefix, if you want to install to another root, set DESTDIR to that root
PREFIX ?= /usr
# The library path excluding prefix
LIB ?= /lib
# The resource path excluding prefix
DATA ?= /share
# The library path including prefix
LIBDIR ?= $(PREFIX)$(LIB)
# The resource path including prefix
DATADIR ?= $(PREFIX)$(DATA)
# The generic documentation path including prefix
DOCDIR ?= $(DATADIR)/doc
# The info manual documentation path including prefix
INFODIR ?= $(DATADIR)/info
# The license base path including prefix
LICENSEDIR ?= $(DATADIR)/licenses

# The name of the package as it should be installed
PKGNAME = jlibgamma


# The Java compiler
JAVAC = javac
# The Java archive creator
JAR = jar
# The JNI header generator
JAVAH = javah


# The version of the library.
LIB_MAJOR = 1
LIB_MINOR = 0
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)

# The so in libgammamm.so as the library file is named on Linux
ifeq ($(PLATFORM),w32)
SO = dll
else
ifeq ($(PLATFORM),osx)
SO = dylib
else
SO = so
endif
endif

# Platform dependent flags
ifeq ($(PLATFORM),w32)
SHARED = -mdll
LDSO = -Wl,-soname,jlibgamma.$(SO).$(LIB_MAJOR)
PIC =
else
ifeq ($(PLATFORM),osx)
SHARED = -dynamiclib
LDSO =
PIC = -fPIC
else
SHARED = -shared
LDSO = -Wl,-soname,jlibgamma.$(SO).$(LIB_MAJOR)
PIC = -fPIC
endif
endif

# The C standard for C code compilation
STD = c99
# Optimisation settings for C code compilation
C_OPTIMISE ?= -Og -g
# Optimisation settings for Java code compilation
JAVA_OPTIMISE ?= -O

# Warning flags for C code, set to empty if you are not using GCC
C_WARN = -Wall -Wextra -pedantic
## TODO add more warnings

# Warning flags for Java code.
JAVA_WARN = -Xlint:all



# Flags to use when compiling C code
CC_FLAGS = -std=$(STD) $(C_OPTIMISE) $(CFLAGS) $(PIC) $(CPPFLAGS) $(WARN)

# Flags to use when linking native objects
LD_FLAGS = -lgamma -std=$(STD) $(C_OPTIMISE) $(LDFLAGS) $(WARN)

# Flags to use when compiling Java code
JAVAC_FLAGS = $(JAVACFLAGS) $(JAVA_OPTIMISE) $(JAVA_WARN)


# Java classes
JAVA_OBJ = AdjustmentMethod CRTC CRTCInformation GammaRamps Libgamma Partition Site         \
           AdjustmentMethodCapabilities ConnectorType LibgammaException Ramp SubpixelOrder  \
           Ramp16 Ramp32 Ramp64 Ramp8 Rampd Rampf



.PHONY: all
all: lib

.PHONY: lib
lib: jar

.PHONY: jar
jar: bin/jlibgamma.jar

.PHONY: class
class: $(foreach O,$(JAVA_OBJ),obj/libgamma/$(O).class)


bin/jlibgamma.jar: class
	@mkdir -p bin
	cd obj; $(JAR) cf jlibgamma.jar $(foreach O,$(JAVA_OBJ),libgamma/$(O).class)
	mv obj/jlibgamma.jar $@

obj/libgamma/%.class: src/libgamma/%.java
	@mkdir -p obj/libgamma
	$(JAVAC) $(JAVAC_FLAGS) -cp src -s src -d obj $<


.PHONY: clean
clean:
	-rm -r obj bin

