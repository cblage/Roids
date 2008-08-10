###########
#CONFIG
######################
CG_CPP = $(wildcard cg/*.cpp)
CG_OBJS = $(CG_CPP:%.cpp=%.o)
AST_CPP  = $(wildcard asteroids/*.cpp)
AST_OBJS = $(AST_CPP:%.cpp=%.o)
GAME = roids
CXXFLAGS  = -ggdb -I.
LDFLAGS = -lglut -lGL

###############
#TARGETS
################
all: $(GAME)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

cg: $(CG_OBJS)

asteroids: $(AST_OBJS)

$(GAME) : cg asteroids
	$(CXX) -o $@ $(CG_OBJS) $(AST_OBJS) $(LDFLAGS)

clean:
	$(RM)  $(CG_OBJS) $(AST_OBJS)
