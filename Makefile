# This is for C but can easily be modified to work for other languages as well
CC = gcc

# Object files go into $(OBJDIR), executables go into $DISTDIR
OBJDIR = build
DISTDIR = dist

# Uncomment next line to overwrite standard malloc library
# WRAP = -Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=malloc_usable_size

# Compiler and linker flags
CFLAGS := $(SCM) -Wall -fPIC -g
LFLAGS := $(CFLAGS) -lpthread

# Gathers all header and C files located in the root directory
# in $(HFILES) and $(CFILES), respectively
HFILES := $(wildcard *.h)
CFILES := memtrack.c
APP_CFILES := app.c
# Produces in $(OFILES) the names of .o object files for all C files
OFILES := $(patsubst %.c,$(OBJDIR)/%.o,$(CFILES))
APP_OFILES := $(OBJDIR)/app.o

# This a rule that defines how to compile all C files that have changed
# (or their header files) since they were compiled last
$(OBJDIR)/%.o : %.c $(HFILES) $(CFILES) $(APP_CFILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Consider these targets as targets, not files
.PHONY : all libx clean
all: libx app
# Build everything: compile all C (changed) files and
# link the object files into an executable (app)
app: $(APP_OFILES)
	mkdir -p $(DISTDIR)
	$(CC) $(LFLAGS) $(APP_OFILES) -L dist -lx -o $(DISTDIR)/app

# $(OBJDIR) is an order-only prerequisite:
# only compile if $(OBJDIR) does not exist yet and
# not just because $(OBJDIR) has a new time stamp
$(OFILES): | $(OBJDIR)

# Create directory for $(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

# Build shared library, copy library header file to $(DISTDIR)
libx: $(OFILES)
	mkdir -p $(DISTDIR)
	$(CC) $(LFLAGS) $(WRAP) $(OFILES) -shared -o $(DISTDIR)/libx.so

# Clean up by removing the $(OBJDIR) and $(DISTDIR) directories
clean:
	rm -rf $(OBJDIR)
	rm -rf $(DISTDIR)