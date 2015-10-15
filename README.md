# Dict
Từ điển Anh - Việt. 

Cách dùng:
Tạo file libbt.a trong bt-5.0.0
compile:
gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a -rdynamic
run: 
./main