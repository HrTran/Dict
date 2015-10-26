# Dict
         Từ điển Anh - Việt. 

                Phiên bản 1.7 release

Cách compile file taobtree.c
gcc -o tree taobtree.c libbt.a 
File taobtree.c này có tác dụng tạo ra file dữ liệu từ điển (file.dat) từ 2 file từ điển và file từ điển index.

CÁch sử dụng từ điển:
-----------------------------------------
Tạo file libbt.a trong btree 5.0 (make file)
copy file libbt.a vào thư mục gốc (dict)
------------------------------------------
compile:
gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a -rdynamic

run:
./main

----------------------------------------------------------------------------------------

Nhóm 2
Nguyễn Quang Hiển
làm gui, code tong hop
Vũ Tuấn Đạt
xu ly xau, chuoi, toi uu hoa thuat toan
Trần Tất Huy
code console app
Mai Minh Phụng
làm slide, doc, tài liệu, hỗ trợ code
