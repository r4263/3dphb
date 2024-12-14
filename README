# phb-ctrl

## Stack

**Embedded:** C and C++;

**Web:** React.js and Typescript;


    Hardware specifications:
        Board: ESP32-S3 N16R8@240MHz - 2C, 16MB Flash, 8MB PSRAM;
        LCD: ILI9488 3.5" TFT;
    Objectives:
        -Implement a heated bed controller to a 3DCloner simple printer;
        -Use FreeRTOS as the operating system and thread orchestrator;
    Functionalities:
        -Control a heating element using a closed loop;
        -Develop a HMI;
        -Develop a control panel in React.js hosted on the board to control it's state;
        -Store data to a SQLite3 internal database to persist it's variable states;

## Deploy instructions
### Control panel:
- Install and build the react application contained in "control panel" folder with:
```
  npm install
  npm run build
```

- Take the builded files from inside the *build* folder and place into(crete if not exists):
```
embedded/data/web/panel/
```

- Open the *embedded* folder in VSCode with PlatformIO and C++ extensions;
- Wait until PlatformIO sync its libraries;

### Uploading the compiled project to the board
- In the project tasks, select *Platform>Build Filesystem Image* and *Platform>Upload Filesystem Image* to upload the control panel to the board's Flash;

### Uploading the code
- In the project tasks, select *General>Upload* to upload the code to the board;
