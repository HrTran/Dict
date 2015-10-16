# Dict
         Từ điển Anh - Việt. 

                Phiên bản 1.1 beta

  update chức năng gợi ý từ

   Update giao diện mới. 

   /////////////BUG  BUG  BUG  BUG  BUG  BUG  BUG  ///
   BUG mới, chức năng restore hoạt động nhưng trương trình bị out ngay lập tức
   Cần fix
   -------------------------------------------------------

Cách compile file taobtree.c
gcc -o taotree taobtree.c libbt.a 
File taobtree.c này có tác dụng tạo ra file dữ liệu từ điển (file.dat) từ 2 file từ điển và file từ điển index.

ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----
File .dat vẫn chưa hoàn thiện(vì taobtree.c bị lỗi stack over flow) , vậy nên tôi đã cắt một nửa cuối của file dữ liệu nhằm hạn chế lỗi.
Cần anh em viết lại hàm taobtree.c (gồm các hàm đổi cơ số, xử lý xâu) . 
Tài liệu có thể tham khảo ở đây:
http://www.quantrimang.com.vn/print/4973.aspx
ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----ERROR----

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
làm gui, code linh tinh
Vũ Tuấn Đạt
code console app
Trần Tất Huy
code console app
Mai Minh Phụng
làm slide, doc, tài liệu, hỗ trợ code
