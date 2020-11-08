# IDP
This is the repository for the Independent Design Project 2020. Active developers are @barkermrl, @moonear2000 and @LukeJA.

## Guide to Contributing
Please branch off main when implementing a feature. Work on the branch locally, committing as needed. When the feature is complete, rebase off master (ensuring you fetch the latest version from origin) and submit a pull request to merge into main.

Please work in a python virtual environment (creating using anaconda or pip etc.) and install the python packages for this project, run:
```
pip install -r requirements.txt
```
If you add any python packages to the project, ensure you add them to the requirements file using pip:
```
pip freeze > requirements.txt
```

Platformio can be installed as an extension for most common IDEs such as VS Code and CLion. The supported editors can be found [here](https://platformio.org/install/integration) and the documentation can be found [here](https://docs.platformio.org/en/latest/what-is-platformio.html). Note the CLI tool is installed automatically via pip so can be used to suplement the IDE interface.


## Repository Structure
This repository contains the following directories:

`.github/workflows/`  
Contains two workflow files which run PlatformIO and Pytest tests whenever code is pushed or a pull request is submitted.

`build/`  
Contains the compiled code for an Arduino Uno WiFi Rev2 board. This is generated automatically when PlatformIO builds the code.

`docs/`  
Contains markdown files which is used to generate documentation for this software. These can be viewed on the [GitHub pages site](https://barkermrl.github.io/IDP/).

`include/`  
This directory is intended for PlatformIO project header files.

`lib/`  
This directory is intended for project specific (private) libraries. PlatformIO will compile them to static libraries and link into executable file.

`python/`  
Contains the python code used for implementing computer vision in the robot.

`src/`  
Contains the C++ source code which is compiled by PlatformIO and uploaded to the Arduino board.

`test/`
This directory is intended for PlatformIO Unit Testing and project tests.
