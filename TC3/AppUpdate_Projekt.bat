@echo off
cd C:\Program Files (x86)\WinSCP
echo Input the Number of Application you want to update:
echo (1): AppErrorManage
echo (2): AppNetwork
echo (3): AppMonitor
echo (4): hex file
set /p num=
if %num% equ 1 goto seg1
if %num% equ 2 goto seg2
if %num% equ 3 goto seg3
if %num% equ 4 goto seg4


:seg1
echo Update the AppErrorManage
WinSCP.exe /console /command "option batch continue" "option confirm off" "open scp://ssh_user:ssh_user@192.168.201.1:22" "option transfer binary" "put C:\Users\wsun\Dropbox\HIT_Workspace\auftrage_deutschebahn_TC3\result\ProDB_AppErrorManage /mnt/dataflash/App/" "exit"
goto end
:seg2
echo Update the AppNetwork
WinSCP.exe /console /command "option batch continue" "option confirm off" "open scp://ssh_user:ssh_user@192.168.201.1:22" "option transfer binary" "put C:\Users\wsun\Dropbox\HIT_Workspace\auftrage_deutschebahn_TC3\result\ProDB_AppNetwork /mnt/dataflash/App/" "exit"
goto end
:seg3
echo Update the AppMonitor
WinSCP.exe /console /command "option batch continue" "option confirm off" "open scp://ssh_user:ssh_user@192.168.201.1:22" "option transfer binary" "put C:\Users\wsun\Dropbox\HIT_Workspace\auftrage_deutschebahn_TC3\result\ProDB_AppMonitor /mnt/dataflash/App/" "exit"
goto end
:seg4
echo Update the hex file
WinSCP.exe /console /command "option batch continue" "option confirm off" "open scp://ssh_user:ssh_user@192.168.201.1:22" "option transfer binary" "put C:\Users\wsun\Dropbox\HIT_Workspace\auftrage_deutschebahn_STWMaster\result\Auftrage_DeuscheBahn.hex /mnt/dataflash/hex/hexfile_master/" "exit"
WinSCP.exe /console /command "option batch continue" "option confirm off" "open scp://ssh_user:ssh_user@192.168.201.1:22" "option transfer binary" "put C:\Users\wsun\Dropbox\HIT_Workspace\auftrage_deutschebahn_STWSlave\result\Auftrage_DeuscheBahn.hex /mnt/dataflash/hex/hexfile_slave/" "exit"
goto end

:end
set num=
pause
