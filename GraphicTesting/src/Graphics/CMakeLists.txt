#######################DO NOT TOUCH##############################
set(EX_DEPEND "${CMAKE_SOURCE_DIR}/../ExternalDependencies")
#######################DO NOT TOUCH##############################




#Properties->C/C++->General->Additional Include Directories
SET(INCLUDE_DIR "" "")
# Add Libs not inside ExternalDependencies e.g. opengl32.lib
# Properties->Linker->Input->Additional Dependencies
SET(DEFAULT_LIBS "opengl32.lib" "winmm.lib")
# Properties->Linker->General->Additional Library Directories
SET(LIB_DIRECTORIES "" "")
SET(COMPILER_FLAGS "-std=c++11 -Wextra -Wall -pedantic")
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(PREPROCESSOR_DEF "GLEW_STATIC" "SFML_STATIC" )
SET(MAKE_EXECUTABLE TRUE)
SET(MAKE_STATIC_LIB FALSE)
SET(MAKE_SHARED_LIB FALSE)


# Have this project grab external dependecies outside from source
SET(INCLUDE_EX_DEPEND FALSE)




function(assign_source_group)
    FOREACH(_source IN ITEMS ${ARGN})
        IF (IS_ABSOLUTE "${_source}")
            FILE(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        ELSE()
            SET(source_rel "${_source}")
        ENDIF()
        GET_FILENAME_COMPONENT(_source_path "${_source_rel}" PATH)
        STRING(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        SOURCE_GROUP("${_source_path_msvc}" FILES "${_source}")
    ENDFOREACH()
endfunction(assign_source_group)

#Checking to see if compiled in 32/64
IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    MESSAGE( "64 bits compiler detected" )
    SET( EX_PLATFORM 64 )
    SET( EX_PLATFORM_NAME "x64" )
ELSE( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
    MESSAGE( "32 bits compiler detected" )
    SET( EX_PLATFORM 32 )
    SET( EX_PLATFORM_NAME "x86" )
ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 8 )



IF( EX_PLATFORM EQUAL 64 )
MESSAGE( "Outputting to lib64 and bin64" )

# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/lib64
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin64
   CACHE PATH
   "Single Directory for all Executables."
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/lib64
   CACHE PATH
   "Single Directory for all static libraries."
   )
ELSE( EX_PLATFORM EQUAL 64 )
# ---------- Setup output Directories -------------------------
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/lib
   CACHE PATH
   "Single Directory for all Libraries"
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Executables."
   )

# --------- Setup the Executable output Directory -------------
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/lib
   CACHE PATH
   "Single Directory for all static libraries."
   )
ENDIF( EX_PLATFORM EQUAL 64 )

#Checking compiler version to set flags
IF (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  # using Clang
  #set ( CMAKE_CXX_FLAGS "/GLOBAL_FLAGS_GO_HERE")
  #set ( CMAKE_CXX_FLAGS_DEBUG "/DEBUG_FLAGSS_GO_HERE")
  #set ( CMAKE_CXX_FLAGS_RELEASE  "/RELEASE_FLAGS_GO_HERE" )
ELSEIF (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using GCC
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}")
ELSEIF (${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
  # using Intel C++
ELSEIF (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  # WarningLevel: /W<level 0 to 4> or /Wall
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")  
ENDIF()



# Instruct CMake to run moc automatically when needed.
#SET(CMAKE_AUTOMOC ON)
#SET(CMAKE_AUTOUIC ON)

#SET(CMAKE_INCLUDE_CURRENT_DIR ON)

####################CUSTOM STUFF HERE#########################

####################CUSTOM STUFF HERE#########################

FOREACH(predef ${PREPROCESSOR_DEF})
  ADD_DEFINITIONS(-D"${predef}")
ENDFOREACH()

IF(INCLUDE_EX_DEPEND STREQUAL TRUE)
  ######################ExternalDependencies Include 32/64#####################
  IF(EX_PLATFORM EQUAL 64 ) #64 bit
    #Properties->C/C++->General->Additional Include Directories
    INCLUDE_DIRECTORIES("${EX_DEPEND}/include")
    INCLUDE_DIRECTORIES("${EX_DEPEND}/SFML_include/64")
    LINK_DIRECTORIES("${EX_DEPEND}/lib/De/64/" )
    LINK_DIRECTORIES("${EX_DEPEND}/lib/Re/64/" )

    ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
  ELSE( EX_PLATFORM EQUAL 64 ) #32 bit
    INCLUDE_DIRECTORIES("${EX_DEPEND}/include")
    INCLUDE_DIRECTORIES("${EX_DEPEND}/SFML_include/86")
    INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
    LINK_DIRECTORIES("${EX_DEPEND}/lib/De/86/" )
    LINK_DIRECTORIES("${EX_DEPEND}/lib/Re/86/" )
    FOREACH(predef ${PREPROCESSOR_DEF})
      ADD_DEFINITIONS(-D"${predef}")
    ENDFOREACH()
    ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
  ENDIF( EX_PLATFORM EQUAL 64 )
  ######################ExternalDependencies Include 32/64#####################
ENDIF(INCLUDE_EX_DEPEND STREQUAL TRUE)


INCLUDE_DIRECTORIES("${EX_DEPEND}/include")
INCLUDE_DIRECTORIES("${EX_DEPEND}/SFML_include/64")
#LINK_DIRECTORIES("${EX_DEPEND}/lib/De/64/" )

#Get the folder name
GET_FILENAME_COMPONENT(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
#Replacing space with _ from the above directory
STRING(REPLACE " " "_" ProjectId ${ProjectId})

# Getting every file and putting it in the variable SRCS
FILE(GLOB SRCS *.h *.hpp *.c *.cpp)

#GLOBAL variable listVar that will be used to combine everything inside this project
LIST(APPEND listVar ${SRCS})

SUBDIRLIST( SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

GET_FILENAME_COMPONENT(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)

#Add sub-directories and check if the sub-directories is not a empty string
IF(SUBDIRS STREQUAL "")
ELSE(NOT SUBDIRS STREQUAL "")
  FOREACH(subdir ${SUBDIRS})
    ADD_SUBDIRECTORY(${subdir})
  ENDFOREACH()
ENDIF()

#Grab the list of every file in here and make
#a visual studio filter out of it
assign_source_group(${listVar})

add_library(sfmlW STATIC IMPORTED)
set_property(TARGET sfmlW PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/libsfml-window-s-d.a)

add_library(sfmlS STATIC IMPORTED)
set_property(TARGET sfmlS PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/libsfml-system-s-d.a)

add_library(sfmlG STATIC IMPORTED)
set_property(TARGET sfmlG PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/libsfml-graphics-s-d.a)

add_library(glewS STATIC IMPORTED)
set_property(TARGET glewS PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/glew32sd.lib)

add_library(sfJPEG STATIC IMPORTED)
set_property(TARGET sfJPEG PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/libjpeg.a)

add_library(sfFREE STATIC IMPORTED)
set_property(TARGET sfFREE PROPERTY IMPORTED_LOCATION_DEBUG ${EX_DEPEND}/lib/GCC/De/64/libfreetype.a)

IF(MAKE_EXECUTABLE STREQUAL TRUE)
  #Make the folder name the same name as the solution
  ADD_EXECUTABLE(${ProjectId} ${listVar})
ELSEIF(MAKE_STATIC_LIB EQUAL TRUE)
  ADD_LIBRARY(${ProjectId} STATIC ${listVar})
ELSEIF(MAKE_SHARED_LIB EQUAL TRUE)
  ADD_LIBRARY(${ProjectId} SHARED ${listVar})
ENDIF()
#"opengl32.lib" "winmm.lib"gdi32
TARGET_LINK_LIBRARIES(${ProjectId} gdi32.lib)
TARGET_LINK_LIBRARIES(${ProjectId} winmm.lib)
TARGET_LINK_LIBRARIES(${ProjectId} opengl32.lib)
TARGET_LINK_LIBRARIES(${ProjectId} sfmlS)

TARGET_LINK_LIBRARIES(${ProjectId} sfmlW)
TARGET_LINK_LIBRARIES(${ProjectId} glewS)



TARGET_LINK_LIBRARIES(${ProjectId} sfJPEG)

TARGET_LINK_LIBRARIES(${ProjectId} sfFREE)




IF(INCLUDE_EX_DEPEND STREQUAL TRUE)
  IF(EX_PLATFORM EQUAL 64 ) #64 bit
  FILE(GLOB FULL_DLIBS "${EX_DEPEND}/lib/De/64/*.lib")
  FILE(GLOB FULL_RLIBS "${EX_DEPEND}/lib/Re/64/*.lib")
  FOREACH(FULL_DLIBS ${FULL_DLIBS})
    GET_FILENAME_COMPONENT(DLIB "${FULL_DLIBS}" NAME)
    #Properties->Linker->Input->Additional Dependencies
    TARGET_LINK_LIBRARIES(${ProjectId} debug ${DLIB})
  ENDFOREACH(FULL_DLIBS)
  
  FOREACH(FULL_RLIBS ${FULL_RLIBS})
    GET_FILENAME_COMPONENT(RLIB "${FULL_RLIBS}" NAME)
    #Properties->Linker->Input->Additional Dependencies
    TARGET_LINK_LIBRARIES(${ProjectId} optimized ${RLIB})
  ENDFOREACH(FULL_RLIBS)
  
  ELSE( EX_PLATFORM EQUAL 64 ) #32 bit
  FILE(GLOB FULL_DLIBS "${EX_DEPEND}/lib/De/86/*.lib")
  FILE(GLOB FULL_RLIBS "${EX_DEPEND}/lib/Re/86/*.lib")
  FOREACH(FULL_DLIBS ${FULL_DLIBS})
    GET_FILENAME_COMPONENT(DLIB "${FULL_DLIBS}" NAME)
    # Properties->Linker->Input->Additional Dependencies
    TARGET_LINK_LIBRARIES(${ProjectId} debug ${DLIB})
  ENDFOREACH(FULL_DLIBS)
  
  FOREACH(FULL_RLIBS ${FULL_RLIBS})
    GET_FILENAME_COMPONENT(RLIB "${FULL_RLIBS}" NAME)
    # Properties->Linker->Input->Additional Dependencies
    TARGET_LINK_LIBRARIES(${ProjectId} optimized ${RLIB})
  ENDFOREACH(FULL_RLIBS)
  ENDIF( EX_PLATFORM EQUAL 64 )
ENDIF(INCLUDE_EX_DEPEND STREQUAL TRUE)



###############MORE CUSTOME THINGS HERE######################

###############MORE CUSTOME THINGS HERE######################

#install(TARGETS ${ProjectId} RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin64)