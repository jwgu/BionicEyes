# - Find ZMQ
# Find the native zmq includes and library
#
#  ZEROMQ_INCLUDE_DIRS - where to find zmq.h, etc.
#  ZEROMQ_LIBRARIES   - List of libraries when using zmq.
#  ZEROMQ_FOUND       - True if zmq found.

set(ZEROMQ_INCLUDE_DIR "${DEPENDENCIES_PATH}/zeromq-4.3.2/include")

if(WIN32)
	set(ZEROMQ_LIBRARY ${DEPENDENCIES_PATH}/zeromq-4.3.2/lib/libzmq.so)
elseif(UNIX)
	set(ZEROMQ_LIBRARY ${DEPENDENCIES_PATH}/zeromq-4.3.2/lib/libzmq.so)
endif(WIN32)

MESSAGE(STATUS "    Find zeromq libraries: ${ZEROMQ_LIBRARY}")
MESSAGE(STATUS "    Find zeromq include path: ${ZEROMQ_INCLUDE_DIR}")
