# SamITOS
SamITOS_SIM - SamITOS_SIM is an OS simulator written in C.
## Peculiarities:
- Works in CLI, without a graphical interface.
- Simple shell with basic commands for interacting with the simulator.
- This OS simulator depends on Linux.
- Also, the simulator already has a prepared profile for the user. Name: UnixUser, Password: unix@2011.
- After entering the simulator, the ls command will display the WELCOME.txt file, which contains a description of the project components.
## Installation and use:
1. Copy the project to your PC:
   ```bash
    git clone https://github.com/Mrprogrammer201/SamITOS.git
    ```
2. Next, go to the directory with the project:
   ```bash
    cd SamITOS
   ```
3. Installing dependencies:
   ```bash
   ./scripts/dependencies.sh
   ```

4. Assemble the project:
    ```bash
    ./scripts/build.sh
    ```
5. Project launch:
   ```bash
   ./bin/SamITOS_SIM
   ```
