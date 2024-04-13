CC = g++12
CFLAGS += -w -O2 -g -std=c++20 -pipe -Wl,-rpath=/usr/local/lib/gcc12
BINDIR = .
TARGET = $(BINDIR)/vrunner
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