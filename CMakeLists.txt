cmake_minimum_required(VERSION 3.14)
project(algorithms 
    VERSION 1.0.0
    DESCRIPTION "Algorithm library for C++"
    LANGUAGES CXX
)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

# ALGORITHMS_SHARED_LIBS option (undefined by default) can be used to force shared/static build
option(ALGORITHMS_BUILD_TESTS "Build algorithms tests" ${is_top_level})
option(ALGORITHMS_BUILD_EXAMPLES "Build algorithms examples" ${is_top_level})
option(ALGORITHMS_BUILD_DOCS "Build algorithms documentation" OFF)
option(ALGORITHMS_INSTALL "Generate target for installing algorithms" ${is_top_level})
set_if_undefined(ALGORITHMS_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/algorithms" CACHE STRING
    "Install path for algorithms package-related CMake files")

if(DEFINED ALGORITHMS_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${ALGORITHMS_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(algorithms) # initialized below
add_library(algorithms::algorithms ALIAS algorithms)

#----------------------------------------------------------------------------------------------------------------------
# algorithms dependencies
#----------------------------------------------------------------------------------------------------------------------

# Search for your dependencies here

#----------------------------------------------------------------------------------------------------------------------
# algorithms sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "algorithms_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "algorithms_shared.h")
endif()

generate_export_header(algorithms EXPORT_FILE_NAME include/algorithms/${export_file_name})

set(public_headers
    include/algorithms/export.h
    include/algorithms/DataStructures/DSU/DSU.h)
set(sources
    ${public_headers}
    src/DataStructures/DSU/DSU.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# algorithms target
#----------------------------------------------------------------------------------------------------------------------

include(CMakePackageConfigHelpers)

target_sources(algorithms PRIVATE ${sources})
target_compile_definitions(algorithms PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:ALGORITHMS_STATIC_DEFINE>")

target_include_directories(algorithms
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(algorithms PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

if(ALGORITHMS_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/algorithms-config.cmake.in algorithms-config.cmake
        INSTALL_DESTINATION "${ALGORITHMS_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(algorithms-config-version.cmake
        COMPATIBILITY SameMajorVersion)

    install(TARGETS algorithms EXPORT algorithms_export
        RUNTIME COMPONENT algorithms
        LIBRARY COMPONENT algorithms NAMELINK_COMPONENT algorithms-dev
        ARCHIVE COMPONENT algorithms-dev
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
        TYPE INCLUDE
        COMPONENT algorithms-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/algorithms/${export_file_name}"
        COMPONENT algorithms-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/algorithms")

    set(targets_file "algorithms-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "algorithms-static-targets.cmake")
    endif()

    install(EXPORT algorithms_export
        COMPONENT algorithms-dev
        FILE "${targets_file}"
        DESTINATION "${ALGORITHMS_INSTALL_CMAKEDIR}"
        NAMESPACE algorithms::)

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/algorithms-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/algorithms-config-version.cmake"
        COMPONENT algorithms-dev
        DESTINATION "${ALGORITHMS_INSTALL_CMAKEDIR}")

    if(MSVC)
        set(pdb_file "")
        set(pdb_file_destination "")

        if(BUILD_SHARED_LIBS)
            set(pdb_file "$<TARGET_PDB_FILE:algorithms>")
            set(pdb_file_destination "${CMAKE_INSTALL_BINDIR}")
        else()
            # TARGET_PDB_FILE does not work for pdb file generated for static library build, determining it manually
            set(pdb_file "$<TARGET_FILE_DIR:algorithms>/$<TARGET_FILE_PREFIX:algorithms>$<TARGET_FILE_BASE_NAME:algorithms>.pdb")
            set(pdb_file_destination "${CMAKE_INSTALL_LIBDIR}")
        endif()

        install(FILES "${pdb_file}"
            COMPONENT algorithms-dev
            CONFIGURATIONS Debug RelWithDebInfo
            DESTINATION "${pdb_file_destination}"
            OPTIONAL)
    endif()
endif()

#----------------------------------------------------------------------------------------------------------------------
# other targets
#----------------------------------------------------------------------------------------------------------------------

if(ALGORITHMS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(ALGORITHMS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(ALGORITHMS_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    doxygen_add_docs(docs include)
endif()