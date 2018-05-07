print-%: ; @echo $*=$($*)

RM       = rm -f
CXX      = g++
ifeq ($(PLATFORM), Linux)
  OCLFLAGS = -lOpenCL
else
  OCLFLAGS = -framework OpenCL
endif
CXXFLAGS = -g -MMD -std=c++0x  -U__STRICT_ANSI__ -O2 $(OCLFLAGS)
LDFLAGS  = -g -O2

SRC_DIR=src
OBJ_DIR=bin

SRCS = $(shell find src -type f -name *.cpp)

OBJS_SINGLE = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRCS)))
EXEC_SINGLE = $(OBJ_DIR)/simu_single

OBJS_OPENCL = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRCS)))
EXEC_OPENCL = $(OBJ_DIR)/simu_ocl

all: $(OBJ_DIR) $(EXEC_SINGLE) $(EXEC_OPENCL)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC_SINGLE): $(OBJS_SINGLE)
	$(CXX) $(LDFLAGS) -o $@ $^

$(EXEC_OPENCL): $(OBJS_OPENCL)
	$(CXX) $(LDFLAGS) -o $@ $^ $(OCLFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJ_DIR)/ocl_%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(OBJ_DIR)/*.d

clean:
	$(RM) $(EXEC_SINGLE)
	$(RM) $(EXEC_OPENCL)
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/*.d
	$(RM) $(OBJ_DIR)/*.cl
