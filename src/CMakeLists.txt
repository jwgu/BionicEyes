if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_ImageProcess_Core/CMakeLists.txt")
    add_subdirectory(BionicEyes_ImageProcess_Core)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_ImageProcess_Core/CMakeLists.txt")

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_Base/CMakeLists.txt")
    add_subdirectory(BionicEyes_Base)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_Base/CMakeLists.txt")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_SDK/CMakeLists.txt")
    add_subdirectory(BionicEyes_SDK)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_SDK/CMakeLists.txt")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_APP/CMakeLists.txt")
    add_subdirectory(BionicEyes_APP)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_APP/CMakeLists.txt")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_Samples/CMakeLists.txt")
    add_subdirectory(BionicEyes_Samples)
endif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/BionicEyes_Samples/CMakeLists.txt")