add_library(source_plugin INTERFACE)

target_sources(source_plugin INTERFACE
    PluginEditor.h
    PluginEditor.cpp
    PluginProcessor.h
    PluginProcessor.cpp
    )
