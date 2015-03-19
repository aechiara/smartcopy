smartcopy
=========
i created this project because i needed a way to resume copies on my NAS (Network Attached Storage) from one HardDrive 
to another, but it can be also used in NFSs or even on the same machine where you see the need to stop a copy and then resume it later for any reason

-y: do not ask confirmation

-f: force flush to every write on disk


Usage: 
`./smartcopy -f -y -o original_file -d destination_file`
