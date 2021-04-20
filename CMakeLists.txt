cmake_minimum_required(VERSION 3.14)

PROJECT(BionicEyes3)

set(${CMAKE_PROJECT_NAME}_SUMMARY              "SDK for Eyevolution Bionic Eye Products")
set(${CMAKE_PROJECT_NAME}_VENDOR_NAME          "Shanghai Eyevolution Technology Co.,Ltd")
set(${CMAKE_PROJECT_NAME}_VENDOR_SHORTNAME     "Eyevolution")
set(${CMAKE_PROJECT_NAME}_VENDOR_CONTACT       "wang.kaifang@ilooktech.com")
set(${CMAKE_PROJECT_NAME}_VENDOR_DOMAIN        "http://www.ilooktech.com/")
set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR        1)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR        0)
set(${CMAKE_PROJECT_NAME}_VERSION_PATCH        0)
set(PROJECT_VERSION
  "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")

set(PROJECT_PATH                               "${CMAKE_CURRENT_SOURCE_DIR}")
set(BE_SYSTEM_PATH                             "/usr/Evo_BionicEyes")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}     "${PROJECT_PATH}/cmake/Modules")
set(INCLUDE_PATH                               "${PROJECT_PATH}/include")
set(INCLUDE_PATH_BACKUP                        "${BE_SYSTEM_PATH}/include")
set(LIB_PATH                                   "${PROJECT_PATH}/lib")
set(LIB_PATH_BACKUP                            "${BE_SYSTEM_PATH}/lib")
set(INTERNAL_INCLUDE_PATH                      "${PROJECT_PATH}/include/internal")
set(INTERNAL_LIB_PATH                          "${PROJECT_PATH}/lib/internal")
set(INTERNAL_LIB_PATH_BACKUP                   "${BE_SYSTEM_PATH}/lib/internal")
set(DEPENDENCIES_PATH                          "${BE_SYSTEM_PATH}/dependencies")
set(PATCH_PATH                          	   "${PROJECT_PATH}/patch")
set(BIN_PATH                                   "${PROJECT_PATH}/bin")
set(SRC_PATH                                   "${PROJECT_PATH}/src")

execute_process(
        COMMAND cat "/etc/lsb-release"
        COMMAND grep -E "18.04"
        OUTPUT_VARIABLE UBUNTU_STR)

if(UBUNTU_STR MATCHES "18.04")
    message(STATUS "SYSTEM DISTRIB_RELEASE is 18.04")
    set(UBUNTU_DISTRIB_RELEASE "1804")
else()
    message(STATUS "SYSTEM DISTRIB_RELEASE is 16.04")
    set(UBUNTU_DISTRIB_RELEASE "1604")
endif()

message(STATUS "Compiling on ARM " ${CMAKE_BUILD_TYPE})

#if(NOT EXTERNAL_PATH)
#	set(EXTERNAL_PATH                          "${PROJECT_PATH}/external")
#endif(NOT EXTERNAL_PATH)
#if(NOT DOXYGEN_PATH)
#	set(DOXYGEN_PATH                           "${PROJECT_BINARY_DIR}/docs")
#endif(NOT DOXYGEN_PATH)
#if(NOT DOCS_PATH)
#	set(DOCS_PATH                              "${PROJECT_PATH}/docs")
#endif(NOT DOCS_PATH)
#set(LICENSE_PATH                               "${PROJECT_PATH}/license")
#set(RESOURCE_PATH                              "${PROJECT_PATH}/resource")

#.exe .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BIN_PATH})
#.so
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH_BACKUP})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${LIB_PATH_BACKUP})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${LIB_PATH_BACKUP})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${LIB_PATH_BACKUP})
#.a
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH_BACKUP})

option(BE_DEP_UPDATE                            "Update project dependencies"  OFF)
option(BE_LIB_UPDATE                            "Update project libs"  ON)
option(BE_INCLUDE_UPDATE                        "Update project include folder"  ON)
option(BE_COMPILE_V3                            "Compile BionicEyes device hardware version 3"  ON)
option(BE_COMPILE_V5                            "Compile BionicEyes device hardware version 5"  ON)
#option(BUILD_APPS                              "Build apps"                     OFF)
#option(BUILD_DUMMY                             "Build dummy"                    OFF)
#option(BUILD_DEMOS                             "Build demos"                    ON)
#option(BUILD_DOXYGEN_DOCS                      "Build docs"                     OFF)
#option(BUILD_TESTS                             "Build tests"                    ON)
#option(BUILD_TOOLS                             "Build tools"                    ON)
option(BUILD_SAMPLES                           "Build samples"                  ON)
#option(BUILD_DEV                               "Build modules under develop"    OFF)
#option(WITH_OPENCL               	       "With OpenCL"                    OFF)
#option(BUILD_SLAMBASE                          "Build Slam Base Module(Under Test)"    OFF)
#option(USE_OPENMP                              "Set to ON to build use OpenMP"  ON)
#option(USE_SSE                                 "Set to ON to build use SSE"  ON)
#option(USE_PCH                                 "Set to ON to build use PCH"  OFF)
#option(USE_CPACK                               "Set to ON to enable CPACK tool"  OFF)
#option(INSTALL_DEMOS                           "Export demo applications to installer"  OFF)
#option(INSTALL_TESTS                           "Export test applications to installer"  OFF)
#option(INSTALL_TOOLS                           "Export tool applications to installer"  OFF)
#option(EVO_OFFICAL_RELEASE                     "Obfuscation (protect the code)"                  OFF)
#option(EVO_BINO_SDK_WITH_CUDA                  "Build SDK with CUDA"                  ON)

# enable folders for each target
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# default built type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "set build type to Release" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

include(cmake/Utils.cmake)
include(cmake/GetArch.cmake)
get_architecture(arch)
message(STATUS "get target arch (32/64 bit):" ${arch})

# postfix, based on type
#set(CMAKE_DEBUG_POSTFIX "${arch}d" CACHE STRING "postfix applied to debug build of libraries")
#set(CMAKE_RELEASE_POSTFIX "${arch}" CACHE STRING "postfix applied to release build of libraries")
#set(CMAKE_RELWITHDEBINFO_POSTFIX "${arch}" CACHE STRING "postfix applied to relwithdebinfo build of libraries")


# work out the postfix; required where we use OUTPUT_NAME
if(CMAKE_BUILD_TYPE MATCHES Release)
    set(EXE_POSTFIX ${CMAKE_RELEASE_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set(EXE_POSTFIX ${CMAKE_RELWITHDEBINFO_POSTFIX})
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    set(EXE_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif(CMAKE_BUILD_TYPE MATCHES Release)

# Allow the developer to select if Dynamic or Static libraries are built
option (BUILD_SHARED_LIBS "Build Shared Libraries" ON)
set (LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
    set (LIB_TYPE SHARED)
    set (EVO_BE_SDK_SHARED_LIBS 1)
endif()

#set THIRDPARTY_LIB_ARCH_NAME as x64 or x86
set(DEPENDENCIES_ARCH_NAME "x64")
if(${arch} AND ${arch} STREQUAL "32")
    set(DEPENDENCIES_ARCH_NAME "x86")
endif()

if(BE_LIB_UPDATE MATCHES ON)
    message(STATUS "set to update libs")
else()
    message(STATUS "set not to update libs")
endif(BE_LIB_UPDATE MATCHES ON)

if(BE_INCLUDE_UPDATE MATCHES ON)
    message(STATUS "set to update include folder")
else()
    message(STATUS "set not to update include folder")
endif(BE_INCLUDE_UPDATE MATCHES ON)

if(BE_DEP_UPDATE MATCHES ON)
    message(STATUS "set to update dependencies")
else()
    message(STATUS "set not to update dependencies")
endif(BE_DEP_UPDATE MATCHES ON)

# Set platform-specific compiler flags.
# Check Embedded Platform
is_archarm(ARM)
if(WIN32)
    set(EVO_BE_ENV "EVO_BE_ENV_WINDOWS")
    set(PLATFORM_FOLDER "win/${DEPENDENCIES_ARCH_NAME}")
    set(PLATFORM_NAME "win-${DEPENDENCIES_ARCH_NAME}")
    message(STATUS "Compiling on Windows " ${CMAKE_BUILD_TYPE})


elseif(ARM)
    set(EVO_BE_ENV "EVO_BE_ENV_ARM")
    set(PLATFORM_FOLDER "tegra/arm${arch}")
    set(PLATFORM_NAME "tegra-arm${arch}")
    message(STATUS "Compiling on ARM " ${CMAKE_BUILD_TYPE})


elseif(UNIX)
    set(EVO_BE_ENV "EVO_BE_ENV_LINUX")
    set(PLATFORM_FOLDER "linux/${DEPENDENCIES_ARCH_NAME}")
    set(PLATFORM_NAME "linux-${DEPENDENCIES_ARCH_NAME}")
    message(STATUS "Compiling on Unix " ${CMAKE_BUILD_TYPE})
    if(EXISTS "${BE_SYSTEM_PATH}/dependencies/")
        execute_process(COMMAND rm -r "${BE_SYSTEM_PATH}/resource/")
        execute_process(COMMAND cmake -E copy_directory "${PROJECT_PATH}/resource/" "${BE_SYSTEM_PATH}/resource/")
    else()
        execute_process(COMMAND cmake -E copy_directory "${PROJECT_PATH}/resource/" "${BE_SYSTEM_PATH}/resource/")
    endif(EXISTS "${BE_SYSTEM_PATH}/dependencies/")
    # renew Dependencies folder
    if(EXISTS "${BE_SYSTEM_PATH}/dependencies/")
        if(BE_DEP_UPDATE MATCHES ON)
            message(STATUS "Dependencies folder exists, updating...")
            execute_process(COMMAND rm -r "${BE_SYSTEM_PATH}/dependencies/")
            execute_process(COMMAND cmake -E copy_directory "${PROJECT_PATH}/dependencies/" "${BE_SYSTEM_PATH}/dependencies/")
        else()
            message(STATUS "Dependencies folder exists, don't excute copy.")
        endif(BE_DEP_UPDATE MATCHES ON)
    else()
        message(STATUS "Dependencies folder don't exists, copying......")
        execute_process(COMMAND cmake -E
            copy_directory "${PROJECT_PATH}/dependencies/" "${BE_SYSTEM_PATH}/dependencies/")
    endif(EXISTS "${BE_SYSTEM_PATH}/dependencies/")

    # renew lib folder
    if(EXISTS "${BE_SYSTEM_PATH}/lib/")
        if(BE_LIB_UPDATE MATCHES ON)
            message(STATUS "Bionic library folder exists, updating...")
            execute_process(COMMAND rm -r "${BE_SYSTEM_PATH}/lib/")
            execute_process(COMMAND cmake -E copy_directory "${PROJECT_PATH}/lib/" "${BE_SYSTEM_PATH}/lib/")
        else()
            message(STATUS "Bionic library folder exists, don't excute copy.")
        endif(BE_LIB_UPDATE MATCHES ON)
    else()
        message(STATUS "Bionic library folder don't exists, copying......")
        execute_process(COMMAND cmake -E
                copy_directory "${PROJECT_PATH}/lib/" "${BE_SYSTEM_PATH}/lib/")
    endif(EXISTS "${BE_SYSTEM_PATH}/lib/")

    # renew include folder
    if(EXISTS "${BE_SYSTEM_PATH}/include/")
        if(BE_INCLUDE_UPDATE MATCHES ON)
            message(STATUS "Bionic include folder exists, updating...")
            execute_process(COMMAND rm -r "${BE_SYSTEM_PATH}/include/")
            execute_process(COMMAND cmake -E copy_directory "${PROJECT_PATH}/include/" "${BE_SYSTEM_PATH}/include/")
        else()
            message(STATUS "Bionic include folder exists, don't excute copy.")
        endif(BE_INCLUDE_UPDATE MATCHES ON)
    else()
        message(STATUS "Bionic include folder don't exists, copying......")
        execute_process(COMMAND cmake -E
                copy_directory "${PROJECT_PATH}/include/" "${BE_SYSTEM_PATH}/include/")
    endif(EXISTS "${BE_SYSTEM_PATH}/include/")

endif(WIN32)

if(NOT EXISTS "${BE_SYSTEM_PATH}/io_path/")
    message(STATUS "Bionic IO folder don't exists, creating......")
    execute_process(COMMAND cmake -E
            make_directory "${BE_SYSTEM_PATH}/io_path/")
endif(NOT EXISTS "${BE_SYSTEM_PATH}/io_path/")

if(NOT EXISTS "${BE_SYSTEM_PATH}/log_path/")
    message(STATUS "Bionic LOG folder don't exists, creating......")
    execute_process(COMMAND cmake -E
            make_directory "${BE_SYSTEM_PATH}/log_path/")
endif(NOT EXISTS "${BE_SYSTEM_PATH}/log_path/")

if(NOT EXISTS "${BE_SYSTEM_PATH}/tmp_path")
    message(STATUS "Bionic TMP folder don't exists, creating......")
    execute_process(COMMAND cmake -E
            make_directory "${BE_SYSTEM_PATH}/tmp_path")
endif(NOT EXISTS "${BE_SYSTEM_PATH}/tmp_path")

include_directories(${INCLUDE_PATH} ${INTERNAL_INCLUDE_PATH})
link_directories(${LIB_PATH_BACKUP} ${INTERNAL_LIB_PATH_BACKUP} ${BIN_PATH})

set(CMAKE_CXX_STANDARD 11) #C++ 11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #..without compiler extensions like gnu++11

include(macros.cmake)

##OpenCV static
#set(OPENCV_STATIC_INCLUDE_DIRS ${DEPENDENCIES_PATH}/opencv-static-3.4.6/${PLATFORM_FOLDER}/../include)
#if(WIN32)
#    set(OPENCV_STATIC_LIBRARIES ${DLIB_LIBRARIES} ${DEPENDENCIES_PATH}/opencv-static-3.4.6/${PLATFORM_FOLDER}/opencv_world341.lib ${DEPENDENCIES_PATH}/opencv-static-3.4.1/${PLATFORM_FOLDER}/zlib.lib ${DEPENDENCIES_PATH}/dlib-static-19.13/${PLATFORM_FOLDER}/lib/dlib19.13.0_release_64bit_msvc1914.lib)
#elseif(UNIX)
#    find_package(ZLIB REQUIRED)
#    set(OPENCV_STATIC_LIBRARIES ${DEPENDENCIES_PATH}/opencv-static-3.4.6/${PLATFORM_FOLDER}/libopencv_world.a ${DLIB_LIBRARIES} z pthread ${DEPENDENCIES_PATH}/dlib-static-19.13/${PLATFORM_FOLDER}/lib/libdlib.a)
#endif(WIN32)
#
#if(WIN32)
#    set(CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/opencv-3.4.6/${PLATFORM_FOLDER}")
#elseif(UNIX)
#    set(CMAKE_PREFIX_PATH "${DEPENDENCIES_PATH}/opencv-3.4.6/${PLATFORM_FOLDER}/share/OpenCV")
#endif(WIN32)
#
##Opencv_shared_withoutCUDA
#set(OPENCV_WITHOUT_CUDA_INCLUDE_DIRS ${DEPENDENCIES_PATH}/opencv-3.4.6/${PLATFORM_FOLDER}/WithoutCUDA/include)
#if(WIN32)
#    set(OPENCV_STATIC_LIBRARIES ${DLIB_LIBRARIES} ${DEPENDENCIES_PATH}/opencv-static-3.4.6/${PLATFORM_FOLDER}/opencv_world341.lib ${DEPENDENCIES_PATH}/opencv-static-3.4.1/${PLATFORM_FOLDER}/zlib.lib ${DEPENDENCIES_PATH}/dlib-static-19.13/${PLATFORM_FOLDER}/lib/dlib19.13.0_release_64bit_msvc1914.lib)
#elseif(UNIX)
#    find_package(ZLIB REQUIRED)
#    set(OPENCV_STATIC_LIBRARIES ${DEPENDENCIES_PATH}/opencv-static-3.4.6/${PLATFORM_FOLDER}/libopencv_world.a ${DLIB_LIBRARIES} z pthread ${DEPENDENCIES_PATH}/dlib-static-19.13/${PLATFORM_FOLDER}/lib/libdlib.a)
#endif(WIN32)


#if(EVO_BE_SDK_WITH_CUDA)
#    include(macros_cuda.cmake)
#
#    string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\1" CUDA_VERSION_MAJOR "${CUDA_VERSION}")
#    string(REGEX REPLACE "([0-9]+)\\.([0-9]+).*" "\\2" CUDA_VERSION_MINOR "${CUDA_VERSION}")
#    message(STATUS "CUDA VERSION : " ${CUDA_VERSION})
#
#    if (CMAKE_VERSION VERSION_LESS "3.9.0")
#        # Set only because there are old target_link_libraries() statements in the
#        # FindCUDA.cmake file that comes with CMake that error out if the new behavior
#        # is used.  In newer versions of CMake we can instead set CUDA_LINK_LIBRARIES_KEYWORD which fixes this issue.
#        cmake_policy(SET CMP0023 OLD)
#    else()
#        set(CUDA_LINK_LIBRARIES_KEYWORD PRIVATE)
#    endif()
#
#    #add C++11 for CUDA (windows is no need)
#    if(WIN32)
#    else(WIN32)
#        set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-std=c++11)
#    endif(WIN32)
#
#    #add fast math for CUDA
#    set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-prec-div=false;-use_fast_math)
#
#    #CUDA Settings
#    #http://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/index.html#gpu-compilation
#    #https://developer.nvidia.com/cuda-gpus
#    #http://docs.nvidia.com/cuda/pascal-compatibility-guide/index.html#building-pascal-compatible-apps-using-cuda-8-0
#    set(GENCODE_SM30 -gencode=arch=compute_30,code=sm_30)
#    set(GENCODE_SM32 -gencode=arch=compute_32,code=sm_32)
#    set(GENCODE_SM35 -gencode=arch=compute_35,code=sm_35)
#    set(GENCODE_SM50 -gencode=arch=compute_50,code=sm_50)
#    set(GENCODE_SM52 -gencode=arch=compute_52,code=sm_52)
#    set(GENCODE_SM53 -gencode=arch=compute_53,code=sm_53)
#    set(GENCODE_SM60 -gencode=arch=compute_60,code=sm_60)
#    set(GENCODE_SM61 -gencode=arch=compute_61,code=sm_61)
#    set(GENCODE_SM62 -gencode=arch=compute_62,code=sm_62)
#    set(GENCODE_SM70 -gencode=arch=compute_70,code=sm_70)
#
#    option(CUDA_GENCODE_SM30 	  "ON to generate code for Compute Capability 3.0 devices (e.g. Tesla K10)" 	OFF)
#    option(CUDA_GENCODE_SM32 	  "ON to generate code for Compute Capability 3.2 devices (e.g. Teegra TK1)" 	OFF)
#    option(CUDA_GENCODE_SM35 	  "ON to generate code for Compute Capability 3.5 devices (e.g. Tesla K20)"		OFF)
#    option(CUDA_GENCODE_SM50	  "ON to generate code for Compute Capability 5.0 devices (e.g. GeForce GTX 750)"	OFF)
#    option(CUDA_GENCODE_SM52 	  "ON to generate code for Compute Capability 5.2 devices (e.g. GeForce GTX 965M)"	OFF)
#    option(CUDA_GENCODE_SM53 	  "ON to generate code for Compute Capability 5.3 devices (e.g. Tegra TX1)"	ON)
#    option(CUDA_GENCODE_SM60 	  "ON to generate code for Compute Capability 6.0 devices (e.g. Quadro GP100)" 	OFF)
#    option(CUDA_GENCODE_SM61 	  "ON to generate code for Compute Capability 6.1 devices (e.g. GeForce GTX 1050)" 	OFF)
#    option(CUDA_GENCODE_SM62 	  "ON to generate code for Compute Capability 6.2 devices (e.g. Tegra TX2)" 	OFF)
#    if (CUDA_VERSION VERSION_LESS 9.0)
#        message(WARNING "SM70 need CUDA 9.0!")
#    else()
#        option(CUDA_GENCODE_SM70 	  "ON to generate code for Compute Capability 7.0 devices (e.g. Tesla V100)" 	OFF)
#    endif()
#
#    if (CUDA_GENCODE_SM30)
#        set(GENCODE ${GENCODE} ${GENCODE_SM30})
#        set(GENCODE_COMPUTE -gencode=arch=compute_30,code=compute_30)
#    endif(CUDA_GENCODE_SM30)
#    if (CUDA_GENCODE_SM32)
#        set(GENCODE ${GENCODE} ${GENCODE_SM32})
#        set(GENCODE_COMPUTE -gencode=arch=compute_32,code=compute_32)
#    endif(CUDA_GENCODE_SM32)
#    if (CUDA_GENCODE_SM35)
#        set(GENCODE ${GENCODE} ${GENCODE_SM35})
#        set(GENCODE_COMPUTE -gencode=arch=compute_35,code=compute_35)
#    endif(CUDA_GENCODE_SM35)
#    if (CUDA_GENCODE_SM50)
#        set(GENCODE ${GENCODE} ${GENCODE_SM50})
#        set(GENCODE_COMPUTE -gencode=arch=compute_50,code=compute_50)
#    endif(CUDA_GENCODE_SM50)
#    if (CUDA_GENCODE_SM52)
#        set(GENCODE ${GENCODE} ${GENCODE_SM52})
#        set(GENCODE_COMPUTE -gencode=arch=compute_52,code=compute_52)
#    endif(CUDA_GENCODE_SM52)
#    if (CUDA_GENCODE_SM53)
#        set(GENCODE ${GENCODE} ${GENCODE_SM53})
#        set(GENCODE_COMPUTE -gencode=arch=compute_53,code=compute_53)
#    endif(CUDA_GENCODE_SM53)
#    if (CUDA_GENCODE_SM60)
#        set(GENCODE ${GENCODE} ${GENCODE_SM60})
#        set(GENCODE_COMPUTE -gencode=arch=compute_60,code=compute_60)
#    endif(CUDA_GENCODE_SM60)
#    if (CUDA_GENCODE_SM61)
#        set(GENCODE ${GENCODE} ${GENCODE_SM61})
#        set(GENCODE_COMPUTE -gencode=arch=compute_61,code=compute_61)
#    endif(CUDA_GENCODE_SM61)
#    if (CUDA_GENCODE_SM62)
#        set(GENCODE ${GENCODE} ${GENCODE_SM62})
#        set(GENCODE_COMPUTE -gencode=arch=compute_62,code=compute_62)
#    endif(CUDA_GENCODE_SM62)
#    if (CUDA_GENCODE_SM70)
#        set(GENCODE ${GENCODE} ${GENCODE_SM70})
#        set(GENCODE_COMPUTE -gencode=arch=compute_70,code=compute_70)
#    endif(CUDA_GENCODE_SM70)
#
#    option(CUDA_GENCODE_PTX 	  "ON to generate code forward-compatible (risk: leak source)" 	ON)
#    if (CUDA_GENCODE_PTX)
#        message(STATUS "forward-compatible PTX: " ${GENCODE_COMPUTE})
#        set(GENCODE ${GENCODE} ${GENCODE_COMPUTE})
#    endif(CUDA_GENCODE_PTX)
#
#
#    if(WIN32) # Windows
#    else() # Linux
#        exec_program(uname ARGS -p OUTPUT_VARIABLE CMAKE_SYSTEM_NAME2)
#        #TK1 do not ask for CUDA version
#        if ( CMAKE_SYSTEM_NAME2 MATCHES "armv7l" )
#            message ("TK1")
#        endif()
#
#        ##For Jetson TX1
#        if ( CMAKE_SYSTEM_NAME2 MATCHES "aarch64")
#            unset(CUDA_USE_STATIC_CUDA_RUNTIME CACHE)
#            option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
#            message ("CUDA_USE_STATIC_CUDA_RUNTIME : ${CUDA_USE_STATIC_CUDA_RUNTIME}")
#            ##to prevent from opencv_dep_cudart dependencies error...
#            ## cmake with -DCUDA_USE_STATIC_CUDA_RUNTIME=false can also be called.
#        endif()
#        set(SPECIAL_OS_LIBS "pthread" "X11")
#    endif(WIN32)
#
#endif(EVO_BINO_SDK_WITH_CUDA)

# Doxygen docs
#if(BUILD_DOXYGEN_DOCS)
#    find_package(Doxygen)
#
#    if(NOT DOXYGEN_FOUND)
#        message(FATAL_ERROR
#                "Doxygen is needed to build the documentation. Please make sure it is installed.")
#    endif(NOT DOXYGEN_FOUND)
#
#    configure_file(${PROJECT_PATH}/Doxyfile.in
#            ${PROJECT_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)
#
#    # Add a custom target to run Doxygen whenever the project is built.
#    # If you do NOT want the documentation to be generated EVERY time you build the project
#    # then leave out the 'ALL' keyword from the command below.
#    add_custom_target(doxygen_docs ALL
#            COMMAND ${DOXYGEN_EXECUTABLE}
#            ${PROJECT_BINARY_DIR}/Doxyfile
#            SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
#    add_custom_command(TARGET doxygen_docs
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_PATH}/docs/captures ${PROJECT_BINARY_DIR}/docs/captures)
#
#    if(${PREDEFINED_TARGETS_FOLDER})
#        set(CMAKE_PROJECTS_FLODER ${PREDEFINED_TARGETS_FOLDER})
#    else(${PREDEFINED_TARGETS_FOLDER})
#        set(CMAKE_PROJECTS_FLODER "CMakePredefinedTargets")
#    endif(${PREDEFINED_TARGETS_FOLDER})
#
#    set_target_properties (doxygen_docs PROPERTIES FOLDER ${CMAKE_PROJECTS_FLODER})
#endif(BUILD_DOXYGEN_DOCS)

#configure_file (${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md  ${CMAKE_CURRENT_SOURCE_DIR}/license/LICENSE.txt)

file(RELATIVE_PATH REL_INCLUDE_DIR "${PROJECT_PATH}" "${INCLUDE_PATH}")
file(RELATIVE_PATH REL_LIB_DIR "${PROJECT_PATH}" "${LIB_PATH}")
file(RELATIVE_PATH REL_BIN_DIR "${PROJECT_PATH}" "${BIN_PATH}")
file(RELATIVE_PATH REL_BIN_DIR "${PROJECT_PATH}" "${BIN_PATH}")
file(RELATIVE_PATH REL_PATCH_DIR "${PROJECT_PATH}" "${PATCH_PATH}")
#file(RELATIVE_PATH REL_DOC_DIR "${PROJECT_BINARY_DIR}" "${DOXYGEN_PATH}")

#set(CMAKE_INSTALL_PREFIX  "${PROJECT_PATH}/lib")
#set(CMAKE_INSTALL_RPATH ${LIB_PATH_BACKUP})
#
#if(EVO_BINO_SDK_WITH_CUDA)
#    install(DIRECTORY ${INCLUDE_PATH}	DESTINATION .	PATTERN "internal" EXCLUDE PATTERN "evo_bino_config.h" EXCLUDE)
#else(EVO_BINO_SDK_WITH_CUDA)
#    install(DIRECTORY ${INCLUDE_PATH}	DESTINATION .	PATTERN "internal" EXCLUDE PATTERN "evo_bino_config.h" EXCLUDE PATTERN "evo_depthcamera.h" EXCLUDE)
#endif(EVO_BINO_SDK_WITH_CUDA)
#install(DIRECTORY ${DOXYGEN_PATH}	DESTINATION .)
#install(DIRECTORY ${LICENSE_PATH}	DESTINATION ${REL_DOC_DIR})#install license files to docs folder

#####
## Setup EvoBinoSDKConfig.cmake
#####
## ... for the install tree
#set(CONF_INCLUDE_DIRS "\${EvoBinoSDK_CMAKE_DIR}/${REL_INCLUDE_DIR}")
#
#if(WIN32)
#    set(CONF_LIB_DIR "\${EvoBinoSDK_CMAKE_DIR}/${REL_LIB_DIR}")
#elseif(UNIX)
#    set(CONF_LIB_DIR "\${EvoBinoSDK_CMAKE_DIR}/${REL_BIN_DIR}")
#endif(WIN32)
## Create the EvoBinoSDKConfig.cmake and EvoBinoSDKConfigVersion files
#configure_file(EvoBinoSDKConfig.cmake.in  "${PROJECT_BINARY_DIR}/EvoBinoSDKConfig.cmake" @ONLY)
#configure_file(EvoBinoSDKConfigVersion.cmake.in  "${PROJECT_BINARY_DIR}/EvoBinoSDKConfigVersion.cmake" @ONLY)
#
## Install the EvoBinoSDKConfig.cmake and EvoBinoSDKConfigVersion.cmake
#install(FILES
#        "${PROJECT_BINARY_DIR}/EvoBinoSDKConfig.cmake"
#        "${PROJECT_BINARY_DIR}/EvoBinoSDKConfigVersion.cmake"
#        DESTINATION .)
#
##install(EXPORT "${CMAKE_PROJECT_NAME}"  DESTINATION "share/cmake" )
#####

#if(WIN32)
#    #install qt5 runtime to bin
#    file(GLOB QT_RUNTIME_DLLS "${BIN_PATH}/Qt5*.dll")
#    file(GLOB HLSL_COMPILER_DLLS "${BIN_PATH}/D3Dcompiler_*.dll")
#    install(FILES ${QT_RUNTIME_DLLS} DESTINATION ${REL_BIN_DIR})
#    install(FILES ${HLSL_COMPILER_DLLS} DESTINATION ${REL_BIN_DIR})
#    install(FILES "${BIN_PATH}/libEGL.dll" DESTINATION ${REL_BIN_DIR})
#    install(FILES "${BIN_PATH}/libGLESV2.dll" DESTINATION ${REL_BIN_DIR})
#    install(FILES "${BIN_PATH}/opengl32sw.dll" DESTINATION ${REL_BIN_DIR})
#    install(FILES "${BIN_PATH}/platforms/qwindows.dll" DESTINATION ${REL_BIN_DIR}/platforms)
#    install(FILES "${BIN_PATH}/platforms/qminimal.dll" DESTINATION ${REL_BIN_DIR}/platforms)
#    install(FILES "${BIN_PATH}/platforms/qoffscreen.dll" DESTINATION ${REL_BIN_DIR}/platforms)
#    install(FILES "${BIN_PATH}/platforms/qdirect2d.dll" DESTINATION ${REL_BIN_DIR}/platforms)
#    install(FILES "${BIN_PATH}/styles/qwindowsvistastyle.dll" DESTINATION ${REL_BIN_DIR}/styles)
#
#    #install dependencies runtime to bin)
#    file(GLOB_RECURSE DEPENDENCE_RUNTIME_DLLS "${DEPENDENCIES_PATH}/*.dll" )
#
#    if(NOT INSTALL_TESTS)
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "opencv" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "yolo" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "g2o" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "glut" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "realsense" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#        EXCLUDE_FILES_FROM_DIR_IN_LIST("${DEPENDENCE_RUNTIME_DLLS}" "zbar" FALSE)#return result stored in FILE_LIST variable
#        set(DEPENDENCE_RUNTIME_DLLS ${FILE_LIST})
#    endif(NOT INSTALL_TESTS)
#
#    install(FILES ${DEPENDENCE_RUNTIME_DLLS} DESTINATION ${REL_BIN_DIR})
#elseif(UNIX)
#    file(GLOB_RECURSE PATCH_FILES "${PATCH_PATH}/usb.rules")
#    install(FILES ${PATCH_FILES} DESTINATION ${REL_PATCH_DIR})
#    if(INSTALL_TESTS)
#        find_package(OpenCV REQUIRED)
#        file(GLOB_RECURSE OPENCV_LIBRARY "${OpenCV_INSTALL_PATH}/lib*.so*" )
#        install(FILES ${OPENCV_LIBRARY} DESTINATION ${REL_BIN_DIR})
#    endif(INSTALL_TESTS)
#endif(WIN32)

#for Eigen, do not use LGPL part
set(EIGEN_MPL2_ONLY 1)

#for PCL, use user defined cmake file to not find Eigen again
#set(PCL_DIR "${PROJECT_PATH}/cmake/Modules")

# Use SSE
if (USE_SSE)
    message(STATUS "Use SSE")
    if(WIN32) # Windows
        add_definitions(-D__SSE__)
        add_definitions(-D__SSE2__)
        add_definitions(-D__SSE4_1__)
        add_definitions(-DPNG_INTEL_SSE)
    elseif(ARM AND ${arch} STREQUAL "32" )#TK1
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon")
        add_definitions(-DPNG_ARM_NEON_CHECK_SUPPORTED)
    elseif(ARM)#TX1
        add_definitions(-DPNG_ARM_NEON_CHECK_SUPPORTED)
    elseif(UNIX) #Other Unix
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
    endif(WIN32)
endif(USE_SSE)

##Use PCH
#if (USE_PCH)
#    include(cmake/cotire.cmake)
#    set(COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
#    set (COTIRE_PCH_MEMORY_SCALING_FACTOR "1000")
#endif(USE_PCH)

## Use OpenMP
#if (USE_OPENMP)
#    find_package(OpenMP)
#    if (OPENMP_FOUND)
#        message(STATUS "Use OpenMP")
#        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
#    endif(OPENMP_FOUND)
#endif(USE_OPENMP)

#configure_file (${CMAKE_CURRENT_SOURCE_DIR}/config-build.h.in  ${INCLUDE_PATH}/evo_bino_config.h)
#configure_file (${CMAKE_CURRENT_SOURCE_DIR}/config-install.h.in  ${CMAKE_BINARY_DIR}/config-install.h)
#install(FILES "${CMAKE_BINARY_DIR}/config-install.h" DESTINATION ${REL_INCLUDE_DIR} RENAME evo_bino_config.h) #overwirte config.h when install program

## Develop: support all kinds of LeadSense and other stereo cameras
## Retail: only support LeadSense for retail
## OEM_XX: only support OEM LeadSense XX
#if(EVO_OFFICAL_RELEASE)
#    set(EVO_OFFICAL_RELEASE_TYPE CACHE STRING "set evo official release type (available: Retail/OEM_JY)")
#    # set availabe items for officail release type
#    set_property(CACHE EVO_OFFICAL_RELEASE_TYPE PROPERTY STRINGS "Retail" "OEM_JY")
#    if(EVO_OFFICAL_RELEASE_TYPE MATCHES Retail)
#        message("evo official release type Retail")
#        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/product_list_release_retail.h.in  ${INCLUDE_PATH}/evo_product_list.h)
#    elseif(EVO_OFFICAL_RELEASE_TYPE MATCHES OEM_JY)
#        message("evo official release type OEM_JY")
#        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/product_list_release_oem_jy.h.in  ${INCLUDE_PATH}/evo_product_list.h)
#    else(EVO_OFFICAL_RELEASE_TYPE MATCHES Retail)
#        message(WARNING "evo official release type is not available, set to Retail")
#        set(EVO_OFFICAL_RELEASE_TYPE Retail)
#        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/product_list_release_retail.h.in  ${INCLUDE_PATH}/evo_product_list.h)
#    endif(EVO_OFFICAL_RELEASE_TYPE MATCHES Retail)
#else(EVO_OFFICAL_RELEASE)
#    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/product_list_develop.h.in  ${INCLUDE_PATH}/evo_product_list.h)
#endif(EVO_OFFICAL_RELEASE)


add_subdirectory(src)

#if(USE_CPACK)
#    if(WIN32)
#        #copy dependency folder to install, except the libraries not be used in sample code
#        install(DIRECTORY ${DEPENDENCIES_PATH}	DESTINATION .	PATTERN "qwt*" EXCLUDE PATTERN "opencv*" EXCLUDE PATTERN "*-static*" EXCLUDE PATTERN "yolo*" EXCLUDE PATTERN "easypr*" EXCLUDE PATTERN "realsense*" EXCLUDE PATTERN "MIPP*" EXCLUDE PATTERN "zbar*" EXCLUDE)
#    endif(WIN32)
#    # Set up packager.
#    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CMAKE_PROJECT_NAME}")
#    set(CPACK_PACKAGE_VENDOR              "${${CMAKE_PROJECT_NAME}_VENDOR_NAME}")
#    set(CPACK_PACKAGE_DESCRIPTION_FILE    "${PROJECT_PATH}/README.md")
#    set(CPACK_RESOURCE_FILE_LICENSE       "${PROJECT_PATH}/LICENSE.md")
#    set(CPACK_PACKAGE_VERSION_MAJOR       "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}")
#    set(CPACK_PACKAGE_VERSION_MINOR       "${${CMAKE_PROJECT_NAME}_VERSION_MINOR}")
#    set(CPACK_PACKAGE_VERSION_PATCH       "${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")
#
#    if(EVO_BINO_SDK_WITH_CUDA)
#        set(CPACK_PACKAGE_FILE_NAME			  "${CMAKE_PROJECT_NAME}-v${PROJECT_VERSION}-${PLATFORM_NAME}")
#    else(EVO_BINO_SDK_WITH_CUDA)
#        set(CPACK_PACKAGE_FILE_NAME			  "${CMAKE_PROJECT_NAME}-v${PROJECT_VERSION}-${PLATFORM_NAME}-nocuda")
#    endif(EVO_BINO_SDK_WITH_CUDA)
#    if(EVO_OFFICAL_RELEASE)
#        if(EVO_OFFICAL_RELEASE_TYPE MATCHES OEM_JY)
#            set(CPACK_PACKAGE_FILE_NAME			  "${CPACK_PACKAGE_FILE_NAME}-jy")
#        endif(EVO_OFFICAL_RELEASE_TYPE MATCHES OEM_JY)
#    else(EVO_OFFICAL_RELEASE)
#        set(CPACK_PACKAGE_FILE_NAME			  "${CPACK_PACKAGE_FILE_NAME}-develop")
#    endif(EVO_OFFICAL_RELEASE)
#
#    set(CPACK_PACKAGE_INSTALL_DIRECTORY   "${CMAKE_PROJECT_NAME}")
#    if(WIN32 AND NOT UNIX)
#        # There is a bug in NSI that does not handle full unix paths properly. Make
#        # sure there is at least one set of four (4) backlasshes.
#        set(CPACK_NSIS_DISPLAY_NAME         "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
#        set(CPACK_NSIS_CONTACT              "${${CMAKE_PROJECT_NAME}_VENDOR_CONTACT}")
#        set(CPACK_NSIS_MODIFY_PATH 		  OFF)	#default add bin to system path for all users
#        set(CPACK_NSIS_MUI_ICON			  "${RESOURCE_PATH}/app_icon_white.ico")
#        set(CPACK_NSIS_MUI_UNIICON		  "${RESOURCE_PATH}/app_icon_green.ico")
#        set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP	  "${RESOURCE_PATH}/side.bmp")
#        set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP	  "${RESOURCE_PATH}/side.bmp")
#        set(CPACK_NSIS_MUI_HEADERIMAGE_BITMAP 		  "${RESOURCE_PATH}/header.bmp")
#        set(CPACK_NSIS_MUI_SPLASH_BITMAP 		  "${RESOURCE_PATH}/logo.bmp")
#
#        string(REGEX REPLACE "/" "\\\\\\\\" CPACK_NSIS_MUI_HEADERIMAGE_BITMAP ${CPACK_NSIS_MUI_HEADERIMAGE_BITMAP})
#        string(REGEX REPLACE "/" "\\\\\\\\" CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP ${CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP})
#        string(REGEX REPLACE "/" "\\\\\\\\" CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP ${CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP})
#        string(REGEX REPLACE "/" "\\\\\\\\" CPACK_NSIS_MUI_SPLASH_BITMAP ${CPACK_NSIS_MUI_SPLASH_BITMAP})
#
#    else(WIN32 AND NOT UNIX)
#        set(CPACK_MY_DEFAULT_PACKAGING_INSTALL_DIR		"/usr/local/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
#        set(CPACK_GENERATOR				 	"STGZ;TZ")
#    endif(WIN32 AND NOT UNIX)
#
#    message(STATUS "APPS below are registed into start menu apps: ${CPACK_PACKAGE_EXECUTABLES}")
#    include(CPack)
#    #clear CPACK_PACKAGE_EXECUTABLES in cache
#    set(CPACK_PACKAGE_EXECUTABLES CACHE INTERNAL "CPACK_PACKAGE_EXECUTABLES")
#endif(USE_CPACK)
