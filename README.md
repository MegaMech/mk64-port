# mk64 port
Run in `x64 Native Tools Command Prompt for VS 2022`
Note the `x64` part.
```
cl /I"C:\SDL2\include" draw_square.c /link /LIBPATH:"C:\SDL2\lib\x64" SDL2.lib SDL2main.lib
```

# Dep
https://libsdl.org/download-2.0.php
Place `SDL2-devel-2.x.x-VC.zip` in `C:\` as `SDL`

Place `SDL2.dll` (a second download) beside out.
