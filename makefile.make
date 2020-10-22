CCC = g++
CXX = g++
INCLUDE_DIR = src/shared
BASICOPTS = -std=c++11 -I$(INCLUDE_DIR)
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN =


TARGETDIR_master=build/master
TARGETDIR_child=build/child
TARGETDIR_shared=build/shared
TARGETDIR=.



all: $(TARGETDIR)/oss $(TARGETDIR)/child


OBJS_master = \
        $(TARGETDIR_master)/ArgumentHandler.o \
        $(TARGETDIR_master)/ChildProcessHandler.o \
        $(TARGETDIR_master)/HelpDisplay.o \
        $(TARGETDIR_shared)/SharedMem.o \
        $(TARGETDIR_shared)/TimeType.o \
        $(TARGETDIR_shared)/MessageHandler.o \
        $(TARGETDIR_master)/main.o
USERLIBS_master = $(SYSLIBS_master)
DEPLIBS_master =
LDLIBS_master = $(USERLIBS_master)



$(TARGETDIR)/oss: $(TARGETDIR_master) $(OBJS_master) $(DEPLIBS_master)
        $(LINK.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ $(OBJS_master) $(LDLIBS_master)


$(TARGETDIR_master)/ArgumentHandler.o: $(TARGETDIR_master) src/master/ArgumentHandler.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/master/ArgumentHandler.cpp

$(TARGETDIR_master)/ChildProcessHandler.o: $(TARGETDIR_master) src/master/ChildProcessHandler.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/master/ChildProcessHandler.cpp

$(TARGETDIR_master)/HelpDisplay.o: $(TARGETDIR_master) src/master/HelpDisplay.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/master/HelpDisplay.cpp

$(TARGETDIR_shared)/SharedMem.o: $(TARGETDIR_shared) src/shared/SharedMem.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/shared/SharedMem.cpp

$(TARGETDIR_shared)/TimeType.o: $(TARGETDIR_shared) src/shared/TimeType.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/shared/TimeType.cpp

$(TARGETDIR_shared)/MessageHandler.o: $(TARGETDIR_shared) src/shared/MessageHandler.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/shared/MessageHandler.cpp

$(TARGETDIR_master)/main.o: $(TARGETDIR_master) src/master/main.cpp
        $(COMPILE.cc) $(CCFLAGS_master) $(CPPFLAGS_master) -o $@ src/master/main.cpp




OBJS_child = \
        $(TARGETDIR_shared)/SharedMem.o \
        $(TARGETDIR_shared)/TimeType.o \
        $(TARGETDIR_shared)/MessageHandler.o \
        $(TARGETDIR_child)/main.o
USERLIBS_child = $(SYSLIBS_child)
DEPLIBS =
LDLLIBS_child = $(USERLIBS_child)

$(TARGETDIR)/child: $(TARGETDIR_child) $(OBJS_child) $(DEPLIBS_child)
        $(LINK.cc) $(CCFLAGS_child) $(CPPFLAGS_child) -o $@ $(OBJS_child) $(LDLIBS_child)



$(TARGETDIR_child)/main.o: $(TARGETDIR_child) src/child/main.cpp
        $(COMPILE.cc) $(CCFLAGS_child) $(CPPFLAGS_child) -o $@ src/child/main.cpp




clean:
        rm -f \
                $(TARGETDIR)/oss \
                $(TARGETDIR_master)/* \
                $(TARGETDIR)/child \
                $(TARGETDIR_child)/* \
                $(TARGETDIR_shared)/*
        $(CCADMIN)
        rm -f -r $(TARGETDIR_child)
        rm -f -r $(TARGETDIR_master)
        rm -f -r $(TARGETDIR_shared)



$(TARGETDIR_child):
        mkdir -p $(TARGETDIR_child)
$(TARGETDIR_master):
        mkdir -p $(TARGETDIR_master)
$(TARGETDIR_shared):
        mkdir -p $(TARGETDIR_shared)