..\gbdk\bin\lcc.exe -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o main.c
..\gbdk\bin\lcc.exe -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o main.gb main.o
..\bgb\bgb.exe main.gb