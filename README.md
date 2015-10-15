# Dict
Từ điển Anh - Việt. 

Phiên bản 1.02. Mới chỉ có giao diện và vài chức năng cơ bản
CÁch sử dụng
Tạo file libbt.a trong btree 5.0
copy file libbt.a vào thư mục gốc

compile:
gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a -rdynamic
run
./main
