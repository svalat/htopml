add_library(web_nodes DirectoryWebNode.cpp LinuxGetRusage.cpp)
SET_TARGET_PROPERTIES(web_nodes PROPERTIES COMPILE_FLAGS -fPIC)