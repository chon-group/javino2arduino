#! /bin/bash
FRAMEWORK="/usr/bin/jacamo"
SIMULIDE="/opt/group.chon/simulide/simulide"
SERIALPORT="/dev/ttyEmulatedPort0"

clear
if [[ ! -f "$FRAMEWORK"  ]] || [[ ! -f "$SIMULIDE" ]] || [[ ! -e "$SERIALPORT" ]]
then
    echo "The computer hasn't JaCaMo Framework!"
    echo "Installing dependencies..."
    sleep 3
    echo "deb [trusted=yes] http://packages.chon.group/ chonos main" | sudo tee /etc/apt/sources.list.d/chonos.list
    sudo apt update
    sudo apt install jacamo-cli -y                                              # https://github.com/chon-group/dpkg-jacamo
    sudo apt install linux-headers-`uname -r` chonos-serial-port-emulator -y    # https://github.com/chon-group/dpkg-virtualport-driver
    sudo apt install chonos-simulide                                            # https://github.com/chon-group/dpkg-simulide
    
else
    echo "The computer has JaCaMo, SimulIDE and SerialPort Emulator"
fi

echo "Starting SimulIDE..."

chonos-simulide Blink.sim1 &
SIMULIDE_PID=$!

sleep 3

until read -r -t 2 -p "PLEASE, start the execution in simulIDE. After, press ENTER to continue"
do
    echo "" 
done

echo ""
echo "Starting the MAS!"
jacamo jacamo/blinkProject.jcm
kill $SIMULIDE_PID 2>/dev/null
echo "FINISH!"
