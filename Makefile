CC = g++12
CFLAGS += -w -O2 -g -std=c++20 -pipe -Wl,-rpath=/usr/local/lib/gcc12
BINDIR = .
TARGET = $(BINDIR)/vrunner

# ############# libfoxnet libs and includes
# INCDIR += -I../../../extern/tinyxml2/src
# LIBDIR += -L../../../extern/tinyxml2/lib
# LIBS   += -ltinyxml2

# ############# libfoxnet libs and includes
# INCDIR += -I../../../extern/FoxNet/src
# LIBDIR += -L../../../extern/FoxNet/lib
# LIBS   += -lfoxnet

# ############# libthecore libs and includes
# INCDIR += -I/../../libthecore/src
# LIBDIR += -L../../libthecore
# LIBS   += -lthecore

# ############# mysql libs and includes
# INCDIR += -I../../../extern/mysql
# LIBDIR += -L../../../extern/mysql/lib
# LIBS   += -lmysqlclient -lz -pthread

# ############# boost libs and includes
# INCDIR += -I../../../extern/boost
# LIBDIR += -L../../../extern/boost/lib
# LIBS   += -lboost_system -lboost_thread

# INCDIR += -I../../../extern/spdlog
# INCDIR += -I../../../extern/amy

############# source files
CPP = \
    main.cpp \
    runner.cpp \
    utils.cpp

############################################################################
OBJDIR = .obj

$(shell if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi)
OBJS = $(CPP:%.cpp=$(OBJDIR)/%.o)

default: $(TARGET)

clean:
	@echo Clean done!
	@find . -type f | xargs -n 5 touch
	@rm -rf $(OBJDIR)
	@rm -rf $(TARGET)

$(TARGET): $(OBJS)
	@echo linking ...
	@$(CC) $(CFLAGS) $(LIBDIR) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@echo compile $<
	@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@