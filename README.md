Performance testing EnTT.

```bash
$ clang-cl main.cpp /std:c++17 -m64
# main.exe (500 kb)
$ clang-cl main.cpp /std:c++17 -m64 -ftime-trace
# main.cpp.json (1,889 kb)
```

Drag'n'drop JSON file at https://www.speedscope.app/

<br>

### Overview

The [Sequentity Example Application](https://github.com/alanjfs/sequentity) is an example built with EnTT, and takes 10-13 seconds to build on a moderate, 2 year-old machine. That's a lot, and I wasn't sure where it was spending its time.

Thanks to the new `-ftime-trace` in Clang 9, the mysteries of the universe was revealed and encapsulated into this benchmark example you see before you. The [`main.cpp`](https://github.com/alanjfs/enttbench/blob/master/main.cpp) of this repository contains the entire Sequentity Example Application, but stripped from anything but calls to EnTT. It uses the same components, the same lambdas and same calls to EnTT. Well, as close as possible given that the actual logic is excluded.

The result is 130 lines of C++, plus 300 lines of plain-old-data components, building in *9 seconds*.

<br>

### Summary

![image](https://user-images.githubusercontent.com/2152766/73074528-c3015780-3eb1-11ea-8e30-6e4f821a109e.png)
![image](https://user-images.githubusercontent.com/2152766/73075688-618eb800-3eb4-11ea-8205-47eb1a29a2a9.png)

<br>

### Tips

For developing with EnTT, here are calls to look out for.

| Function                      | Cost/call
|:------------------------------|:-----------
| `registry.view<>()`           | `~0.5-150.0 ms`
| `registry.on_construct<>()`   | `~0.500 ms`
| `registry.view<>().each()`    | `~0.8-40.0 ms`
| `registry.view<>().less()`    | `~0.5-28.0 ms`
