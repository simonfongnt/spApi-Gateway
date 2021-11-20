# spApi-Gateway (Linux)

## Requirements
- [Linux Project Example](http://sharppoint.com.hk/algo.php?lang=1&mod=api) 
- [Shared Library](http://sharppoint.com.hk/algo.php?lang=1&mod=api)

## File Structure
The following structure is final. It may be worth visiting [Sharp Point](http://sharppoint.com.hk/algo.php?lang=1&mod=api) and see if the shared library (`include` and `lib`) is up-to-date. The file shown below would be referred in the following sections.
```
project
|--include
|  |--ApiProxyWrapper.h
|  |--ApiProxyWrapperReply.h
|  |--CCTypes.h
|  |--SPApiProxyDataType.h
|--lib
|  |--libapiwrapper.so
|--py
|--app.py
|--spGateway.sh
|--spGateway.h
|--spGateway.cpp
|--main.cpp
|--makefile
```

## Build and Run Executable
With the files in this project, just simply use these commands:
- `make` to create the executable
- `./spGateway.sh` to run the executable

## UI addon
With pyQt, the executable can be interact with user. just simply type:
- `python3 app.py` to run the UI executable