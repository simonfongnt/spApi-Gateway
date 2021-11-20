# spApi-Gateway (Windows)

## Requirements
* Microsoft Visual Studio
* [Windows Project Example](http://sharppoint.com.hk/algo.php?lang=1&mod=api) 
* [SPAPI dll](http://sharppoint.com.hk/algo.php?lang=1&mod=api)

## File Structure
The following structure is the combination of both the example and files of this project. The necessary file are shown below and noted with their source. They will be mentioned in the following sections.
```
SPVCDLL3                            (from example)
|--SPVCDLL3_Win32_VCExa
|  |--x64
|  |  |--Debug
|  |  |--Release
|  |  |  |--dist                    (Optional, create by pyinstaller)
|  |  |  |  |--const.txt            (from here)
|  |  |  |  |--login.txt            (from user)
|  |  |  |  |--spGatewayWin64.exe   (created by pyinstaller)
|  |  |  |--py                      (from here)
|  |  |  |--spapidllm64.dll         (from download)
|  |  |  |--app.py                  (from here)
|  |  |  |--const.txt               (from here)
|  |  |  |--login.txt               (from user)
|  |  |  |--spGateway.exe           (built by Visual Studio)
|  |  |  |--...
|  |--Win32
|  |--spGateway.h                   (from here)
|  |--spGateway.cpp                 (from here)
|  |--SPVCDLL3_VCExa.cpp            (from here)
|  |--...
|--x64      (Shortcut folder of SPVCDLL3_Win32_VCExa x64)
|--Win32    (Shortcut folder of SPVCDLL3_Win32_VCExa Win32)
|--SPVCDLL3.sln                     (from example)
|--SPVCDLL3.suo                     (from example)
```
## Create and Build
In order to create and build the project successfully, these procedures should be followed:
1. download the [Windows Project Example](http://sharppoint.com.hk/algo.php?lang=1&mod=api) 
2. download the [SPAPI dll](http://sharppoint.com.hk/algo.php?lang=1&mod=api) to `x64` `Release` folder
3. launch the project (SPVCDLL3.sln)
4. `Retarget Solution / Project` matched with available SDK in Visual Studio
5. rename `Target Name` in `Solution`'s `General Properties` to `spGateway`
6. copy this `spGateway.h` as header file
7. copy this `spGateway.cpp` as source file
8. replace this `SPVCDLL3_VCExa.cpp`
9. configure to `x64` `Release` build 
10. build the executable named `spGateway.exe` in `x64\Release`

This executable `spGateway.exe` should be able to run once per login.

## UI addon
With pyQt, the executable can be interact with user. the steps are as follows:
1. copy `py` folder to `x64/Release`
2. copy `app.py` and `const.txt` to `x64/Release`
3. create your `login.txt` to `x64/Release`
4. run `python3 app.py` in `x64/Release`

## Packaging (Optional)
Further packaging can be done with pyinstaller by running this command in `x64/Release`: 
```
pyinstaller --name "spGatewayWin64" ^
--noconsole --onefile^
--add-data="spapidllm64.lib;." ^
--add-data="spapidllm64.dll;." ^
--add-data="spGateway.exe;." ^
app.py
```

This would pack the pyQt UI, dll and Visual Studio built executable as one named `spGatewayWin64.exe` in `x64/Release/dist`. At last, the folder must contain the `login.txt` and `const.txt` before it is deliverable like this.
```
dist                    
|--const.txt
|--login.txt
|--spGatewayWin64.exe
```