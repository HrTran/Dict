# Dict
         Từ điển Anh - Việt. 
	Helpful Dictionary Program
                Phiên bản 1.6 release

Yêu cầu cài đặt bộ gtk 3.0

Tạo file binary CSDL cho btree bằng trương trình taobtree.c
-----------------------------------------
Cách compile file taobtree.c
gcc -o tree taobtree.c libbt.a 
-----------------------------------------

CÁch sử dụng từ điển HDP:

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
design, code tổng hợp
Vũ Tuấn Đạt
code - xử lý xâu chuỗi, tối ưu hóa thuật toán xây dựng CSDL
Trần Tất Huy
code console app - cải tiến, nâng cấp thuật toán tìm kiếm, sao chép file
Mai Minh Phụng
tìm kiếm tài liệu, công cụ, vẽ, debug, code linh tinh.
