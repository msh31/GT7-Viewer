from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMakeDeps

class GT7Viewer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def requirements(self):
        self.requires("glad/2.0.8")
        self.requires("glfw/3.4")
        self.requires("opengl/system")
        self.requires("imgui/1.92.6")
        self.requires("nlohmann_json/3.12.0")
        self.requires("spdlog/1.17.0")
        # self.test_requires("gtest/1.17.0")

    def layout(self):
        cmake_layout(self)
