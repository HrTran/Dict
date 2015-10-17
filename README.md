# Dict
		Từ điển Anh - Việt. 
	Helpful Dictionary Program

		Phiên bản 1.5 

Còn thiếu chức năng tự động tìm từ đã tra.

Cách compile file taobtree.c
gcc -o tree taobtree.c libbt.a 
File taobtree.c này có tác dụng tạo ra file dữ liệu từ điển (file.dat) từ 2 file từ điển và file từ điển index.

CÁch sử dụng từ điển:
-----------------------------------------
compile file libbt.a trong btree 5.0 (make file)
copy file libbt.a vào thư mục gốc (dict)
------------------------------------------
compile:
gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0` -w libbt.a -rdynamic

run:
./main

----------------------------------------------------------------------------------------

Nhóm 2
Nguyễn Quang Hiển
làm gui, code tổng hợp
Vũ Tuấn Đạt
code console 
xử lý xâu chuỗi, tối ưu hóa thuật toán mã hóa file nhị phân
Trần Tất Huy
code console
tối ưu hóa thuật toán copy, xử lý dữ liệu
Mai Minh Phụng
làm slide, doc, tài liệu,thiết kế logo, giao diện , hỗ trợ code
