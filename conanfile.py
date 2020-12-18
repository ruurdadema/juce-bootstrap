from conans import ConanFile, CMake


class AudioStreamerPlugin(ConanFile):
    name = "AudioStreamerPlugin"
    settings = "os", "compiler", "build_type", "arch"
    requires = ("spdlog/1.8.2")
    # generators = "deploy"
    build_policy = "always" # "missing"
