Performance testing EnTT.

```bash
$ clang-cl main.cpp /std:c++17 -m64
# main.exe (500 kb)
$ clang-cl main.cpp /std:c++17 -m64 -ftime-trace
# main.cpp.json (1,889 kb)
```

Drag'n'drop JSON file at https://www.speedscope.app/
