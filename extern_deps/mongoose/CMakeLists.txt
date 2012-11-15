add_library(mongoose mongoose.c)
SET_TARGET_PROPERTIES(mongoose PROPERTIES COMPILE_FLAGS -fPIC)