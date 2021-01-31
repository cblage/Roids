###########
#CONFIG
######################
CG_CPP = $(wildcard cg/*.cpp)
CG_OBJS = $(CG_CPP:%.cpp=%.o)
AST_CPP  = $(wildcard asteroids/*.cpp)
AST_OBJS = $(AST_CPP:%.cpp=%.o)
GAME = roids
CXXFLAGS  = -ggdb -I. -I./cg
LDFLAGS = -lglut -lGL -lGLU
OUT_DIR = build
CONFIG_FILE = ../platfrom-independent/resources/config.ini

###############
#TARGETS
################
all: $(GAME)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cg: $(CG_OBJS)

asteroids: $(AST_OBJS)

$(GAME) : cg asteroids $(CONFIG_FILE)
	mkdir -p $(OUT_DIR)
	$(CXX) -o $(OUT_DIR)/$@ $(CG_OBJS) $(AST_OBJS) $(LDFLAGS)
	cp $(CONFIG_FILE) $(OUT_DIR)
clean:
	$(RM)  $(CG_OBJS) $(AST_OBJS)
