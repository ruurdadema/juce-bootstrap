cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME JuceBootstrap)
set(MACOS_SDK_VERSION 10.11)

project(${PROJECT_NAME} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    # CMAKE_BUILD_TYPE has to be specified for Conan to produce valid output (ie. CONAN_INCLUDE_DIRS)
    set(CMAKE_BUILD_TYPE Debug)
    message(WARNING "CMAKE_BUILD_TYPE not specified, set it to 'Debug'")
endif ()

# Compiler settings

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILE_OPTIONS
        -fmessage-length=0
        -fstrict-overflow
        -Wall
        -Wbool-conversion
        -Wcast-align
        -Wconditional-uninitialized
        -Wconstant-conversion
        -Wconversion
        -Wenum-conversion
        -Werror=incompatible-pointer-types
        -Werror=incompatible-pointer-types-discards-qualifiers
        -Werror=macro-redefined
        -Wextra
        -Wextra-semi
        -Wfatal-errors
        -Wformat=2
        -Wignored-qualifiers
        -Winconsistent-missing-destructor-override
        -Winit-self
        -Wint-conversion
        -Wmissing-declarations
        -Wmissing-field-initializers
        -Wmissing-include-dirs
        -Wnon-virtual-dtor
        -Wnullable-to-nonnull-conversion
        -Wold-style-definition
        -Woverloaded-virtual
        -pedantic
        -Wpointer-arith
        -Wreorder
        -Wshadow
        -Wshadow-field
        -Wshadow-field-in-constructor-modified
        -Wshadow-ivar
        -Wshadow-uncaptured-local
        -Wshift-sign-overflow
        -Wshorten-64-to-32
        -Wsign-compare
        -Wsign-conversion
        -Wstrict-aliasing
        -Wstrict-overflow=5
        -Wstrict-prototypes
        -Wtype-limits
        -Wuninitialized
        -Wunreachable-code
        -Wunused-parameter
        -Wunused-private-field
        -Wwrite-strings
        -Wzero-as-null-pointer-constant)
endif ()

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
endif ()

# Conan
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()
include(${CMAKE_BINARY_DIR}/conan.cmake)

if (APPLE)
    set(CONAN_SETTINGS os.version=${MACOS_SDK_VERSION})
else ()
    set(CONAN_SETTINGS)
endif ()

conan_cmake_run(CONANFILE conanfile.py
        SETTINGS ${CONAN_SETTINGS}
        BASIC_SETUP
        CMAKE_TARGETS
        NO_OUTPUT_DIRS # Don't change output directories (so JUCE will be able to install plugins)
        BUILD missing)

# JUCE
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 6.0.4
)
FetchContent_MakeAvailable(JUCE) # Does an add_subdirectory() under the hood

# GUI App

set(GUI_NAME ${PROJECT_NAME}Gui)
juce_add_gui_app(${GUI_NAME} PRODUCT_NAME "${PROJECT_NAME}Gui")

# Plugin
set(PLUGIN_NAME ${PROJECT_NAME}Plugin)
juce_add_plugin(${PLUGIN_NAME}
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME "Owllab"                       # Specify the name of the plugin's author
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
    # NEEDS_MIDI_INPUT TRUE/FALSE               # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE              # Does the plugin need midi output?
    # IS_MIDI_EFFECT TRUE/FALSE                 # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE                # Should the plugin be installed to a default location after building?
    PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
    PLUGIN_CODE Dem0                            # A unique four-character plugin id with at least one upper-case character
    FORMATS AU VST3 Standalone                  # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "${PLUGIN_NAME}")              # The name of the final executable, which can differ from the target name

add_subdirectory(source/views)
add_subdirectory(source/plugin)
add_subdirectory(source/gui)

set(JUCE_COMMON_TARGET_DEFINITIONS
    DONT_SET_USING_JUCE_NAMESPACE
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

target_compile_definitions(${GUI_NAME} PUBLIC ${JUCE_COMMON_TARGET_DEFINITIONS})
target_compile_definitions(${PLUGIN_NAME} PUBLIC ${JUCE_COMMON_TARGET_DEFINITIONS}
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0)

juce_generate_juce_header(${GUI_NAME})
juce_generate_juce_header(${PLUGIN_NAME})

target_compile_options(${GUI_NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_options(${PLUGIN_NAME} PRIVATE ${COMPILE_OPTIONS})

if (WIN32)
    target_compile_definitions(${PLUGIN_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(${GUI_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif ()

target_link_libraries(${PLUGIN_NAME} PRIVATE
    source_plugin
    source_views
    juce::juce_gui_basics
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_audio_devices
    juce::juce_audio_plugin_client
    )

target_link_libraries(${GUI_NAME} PRIVATE
    source_gui
    source_views
    juce::juce_gui_basics
    )
