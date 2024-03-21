# DivineBrush

![divinebrush_logo](./doc/pic/divinebrush_logo.png)

## Origin of name

![name_gpt](./doc/pic/name_gpt.png)

ChatGPT: 

​        将“神笔马良”组合成一个英文名字有一些挑战，因为这是一个中国文化的特定名称，不太容易直译为英文。但是，你可以尝试将其意思转化为英文，并且尽量保留其音韵或意境。我建议的英文名字是 "DivineBrush Ma Liang"。这个名字试图保留“神笔”和“马良”的意义，并使用了“DivineBrush”来译“神笔”，同时保留了“Ma Liang”的姓名。



Windows:

1. install vcpkg
2. vcpkg integrate install
3. vcpkg install glad
4. vcpkg install glfw3
5. vcpkg install freeimage
6. vcpkg install glew
7. vcpkg install glm
8. vcpkg install rttr
9. vcpkg install imgui
10. vcpkg install rapidxml
11. vcpkg install freetype
12. 



Compile:

1. clion->setting->build,execution,deployment->cmake->cmake options:

```
-DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
```

2. [vcpkg-root] replace your local dir

