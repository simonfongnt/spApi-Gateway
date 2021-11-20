# spApi-Gateway
This project aims to create an individual executable for connection from other source of program. Windows and Linux version via the this gateway executable. The core C++ program are more or less the same. A python testing program is provided. Please feel free to try it out.

## What's in common?
There are some similar requirements and functions for both platforms' executables.
### Port and Login files
These files are required for the (packaged or non-packaged) executable and should be located in the same folder.

`const.txt` contains ports for connection
* 1st line is interactive port (for request and response)
* 2nd line is streaming port (for callback function like quotation, ticker)

`login.txt` contains login details
* 1st line is host name
* 2nd line is port
* 3rd line is user id
* 4th line is password
* 5th line is license id
* 6th line is app id

### Requirements
* Python `pip3 install PyQt5 PyInstaller`

### Executable and UI functions
The executable has two ports which one for request & reply and one for callback. The data will be sending via TCP protocol which will be described in detail in `Testing Tool` section. The port and login details are saved in `const.txt` and `login.txt` located in same folder of the executable. It will monitor the change of `login.txt` and decide to `change password` or terminated itself.

The UI will keep restarting the executable in case of termination. It will also be able to modify the `login.txt`.

## [Windows](Windows/README.md)
* [Requirements](Windows/README.md#Requirements)
* [File Structure](Windows/README.md#File-Structure)
* [Create and Build](Windows/README.md#Create-and-Build)
* [UI addon](Windows/README.md#UI-addon)
* [Packaging](Windows/README.md#Packaging-Optional)
## [Linux](Linux/README.md)
* [Requirements](Linux/README.md#Requirements)
* [File Structure](Linux/README.md#File-Structure)
* [Build and Run Executable](Linux/README.md#Build-and-Run-Executable)
* [UI addon](Linux/README.md#UI-addon)
## [Testing Tool](tool/README.md)
* [Requirements](Linux/README.md#Requirements)
* [Run the tool](Linux/README.md#Run-the-tool)
* [Usage](Linux/README.md#Usage)