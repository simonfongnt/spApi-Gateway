# spApi-Gateway (Linux)

## Requirements
- [Linux Project Example](http://sharppoint.com.hk/algo.php?lang=1&mod=api) 
- [Shared Library](http://sharppoint.com.hk/algo.php?lang=1&mod=api)

## File Structure
The following structure is final. It may be worth visiting [Sharp Point](http://sharppoint.com.hk/algo.php?lang=1&mod=api) and see if the shared library (`include` and `lib`) is up-to-date. The file shown below would be referred in the following sections.
```
project
|--include          (from example)
|  |--ApiProxyWrapper.h
|  |--ApiProxyWrapperReply.h
|  |--CCTypes.h
|  |--SPApiProxyDataType.h
|--lib              (from example)
|  |--libapiwrapper.so
|--py               (copy from here)
|--app.py           (copy from here)
|--spGateway.sh     (copy from here)
|--spGateway.h      (copy from here)
|--spGateway.cpp    (copy from here)
|--main.cpp         (replace from here)
|--makefile         (replace from here)
|--const.txt        (copy from here)
|--login.txt        (create by user)
```

## Build and Run Executable
With the example project, put the following files into the folder before the build:
1. check if Shared Library is up-to-date
2. copy this `py` folder
3. copy this `app.py`, `spGateway.sh`, `spGateway.h` and `spGateway.cpp`
4. replace this`main.cpp` and `makefile` 
5. `make` to create the executable
6. `./spGateway.sh` to run the executable

## UI addon
With pyQt, the executable can be interact with user. just simply type:
- `python3 app.py` to run the UI executable