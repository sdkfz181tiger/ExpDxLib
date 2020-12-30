# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("mydxlib01")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../DxLib/${ANDROID_ABI}
        ${CMAKE_CURRENT_SOURCE_DIR}/main
        ${CMAKE_CURRENT_SOURCE_DIR}/utility)
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../DxLib/${ANDROID_ABI}
        ${CMAKE_CURRENT_SOURCE_DIR}/main
        ${CMAKE_CURRENT_SOURCE_DIR}/utility)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp
             main/BtnBase.cpp
             main/GameManager.cpp
             main/SceneBase.cpp
             main/SceneGame.cpp
             main/SceneResult.cpp
             main/SceneTitle.cpp
             main/SpriteBase.cpp
             main/SpriteDancer.cpp
             main/SpriteFrames.cpp
             utility/Utility.h
             utility/UtilDebug.cpp
             utility/UtilDx.cpp
             utility/UtilGraph.cpp
             utility/UtilLabel.cpp
             utility/UtilMath.cpp
             utility/UtilSound.cpp
             utility/Vec2.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       android
                       GLESv1_CM
                       EGL
                       GLESv2
                       OpenSLES
                       m
                       DxLib
                       DxUseCLib
                       jpeg
                       png
                       zlib
                       tiff
                       theora_static
                       vorbis_static
                       vorbisfile_static
                       ogg_static
                       bullet
                       opus)