print-%: ; @echo $*=$($*)

RM       = rm -f
CXX      = g++
ifeq ($(PLATFORM), Linux)
  OCLFLAGS = -lOpenCL
else
  OCLFLAGS = -framework OpenCL
endif
CUDAFLAGS = -L/usr/local/cuda/lib64 -lcuda -lcudart
CXXFLAGS = -g -MMD -std=c++0x  -U__STRICT_ANSI__ -O2 $(OCLFLAGS)
LDFLAGS  = -g -O2

SRC_DIR=src
OBJ_DIR=bin

DEPS = $(shell find src -type f -name Vec*.cpp)

SRCS_SERIAL = $(DEPS) $(shell find src -type f -name *_serial.cpp)
SRCS_OPENCL = $(DEPS) $(shell find src -type f -name *_ocl.cpp)
SRCS_CUDA = $(DEPS) $(shell find src -type f -name *_cuda.cpp)

OBJS_SERIAL = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRCS_SERIAL)))
EXEC_SERIAL = $(OBJ_DIR)/simu_serial

OBJS_OPENCL = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRCS_OPENCL)))
EXEC_OPENCL = $(OBJ_DIR)/simu_ocl

OBJS_CUDA = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(subst .cpp,.o,$(SRCS_CUDA)))
EXEC_CUDA = $(OBJ_DIR)/simu_cuda

all: $(OBJ_DIR) $(EXEC_SERIAL) $(EXEC_OPENCL) $(EXEC_CUDA)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC_SERIAL): $(OBJS_SERIAL)
	$(CXX) $(LDFLAGS) -o $@ $^

$(EXEC_OPENCL): $(OBJS_OPENCL)
	$(CXX) $(LDFLAGS) -o $@ $^ $(OCLFLAGS)

$(EXEC_CUDA): $(OBJS_CUDA)
	$(CXX) $(LDFLAGS) -o $@ $^ $(CUDAFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(OBJ_DIR)/*.d

clean:
	$(RM) $(EXEC_SERIAL)
	$(RM) $(EXEC_OPENCL)
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(OBJ_DIR)/*.d
	$(RM) $(OBJ_DIR)/*.cl
