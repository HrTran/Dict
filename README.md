# Dict
         Từ điển Anh - Việt. 

                Phiên bản 1.02b. 
  Mới chỉ có giao diện và vài chức năng cơ bản (thêm sửa xóa restore)

   Update giao diện mới. Có thể sẽ nghiên cứu thêm tính năng giống google translate:

ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----
File data.dat vẫn chưa hoàn thiện(vì lỗi stack over flow) , vậy nên tôi đã cắt một nửa cuối của file dữ liệu nhằm hạn chế lỗi.
Cần anh em viết lại hàm tạo btree (gồm các hàm đổi cơ số, xử lý xâu) . 
Tài liệu có thể tham khảo ở đây:
http://www.quantrimang.com.vn/print/4973.aspx
ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----

CÁch sử dụng
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
làm gui, code linh tinh
Vũ Tuấn Đạt
code console app
Trần Tất Huy
code console app
Mai Minh Phụng
làm slide, doc, tài liệu, hỗ trợ code
