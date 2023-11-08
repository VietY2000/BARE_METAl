                                    BARE-METAL
    Bare-Metal Embedded là quá trình xây dựng một ứng dụng cho vi điều khiển từ những 
    "nguyên liệu thô sơ nhất". Có nghĩa là ta sẽ tự viết Linker Script File, Startup Code,
    Makefile.

    Đây là dự án bare-metal chớp tắt led cơ bản sử dụng dòng MCU STM32F4xx. Tiếp theo ta sẽ 
    bước các bước để xây dựng một dự án bare-metal.

    Đầu tiên ta sẽ viết Startup code cho vi điều khiển. Start up code là một file dùng để 
    khởi tạo cấp thấp cho vi điều khiển và thao tác bộ nhớ cho chương trình chính chạy. 
    Trong startup code sẽ chứa một bảng vector chứa con trỏ SP, hàm Reset_Hander, các hàm 
    ngoại lệ hệ thống và các hàm ngắt của chương trình.

    /* chèn hình vector table */

    Bảng vector table sẽ được tìm thấy trong Reference manual của MCU. Bấm Ctrl + F và gõ
    vào nội dung vector table để tìm kiếm. Đây là hình ảnh vector table của MCU STM32F4xx. 
    
    /* chèn hình vector table trong RM*/

    Lưu ý là phải để đúng vị trí của các hàm giống như trong vector table của RM. Ở đây chúng
    ta chỉ làm một dự án chớp tắt led cơ bản nên chúng ta sẽ để tất cả các ngoại lệ hệ thống 
    và các trình sử lý ngắt thành default_handler. Trong default_handler chúng ta sẽ để một 
    vòng lặp vô hạn (điều này là không nên đối với các dự án thực tế). 
   
    Hàm reset_handler có nhiệm vụ là hàm đầu tiên được chạy để sao chép các dữ liệu của vùng 
    .data trong bộ nhớ Flash lên Sram và chuyển các giá trị trong vùng .bss về 0 sau đó là 
    gọi hàm main chính của chương trình chạy. 
    
    /* chèn hình reset_handler */

    Và làm sao để biết vùng .data và .bss bắt đầu từ đâu và kích thước như thế nào ta sẽ bước
    tiếp đến phần viết file Linker Script File để phân vùng địa chỉ trên VĐK và gộp các file 
    object lại với nhau và phân bổ bộ nhớ như người dùng mong muốn.

    Command ENTRY dùng để set entry point ở đầu file elf. Debugger sẽ dùng entry point này để
    biết hàm nào được chạy đầu tiên (có thể có hoặc không có lệnh này). Ví dụ hay được dùng nhất
    là reset_handler.

    /* chèn hình lệnh ENTRY */

    Command MEMORY dùng để set các phân vùng bộ nhớ, bao gồm các thông tin như là địa chỉ bắt
    đầu, kích thước bao nhiêu và đặt tính là gì (đọc/ghi/thực thi,...). Các thông tin về các
    vùng nhớ này có trong RM với từ khóa "memory map".


    /* chèn hình command MEMORY */


    Command SECTIONS để chia các thành phần trong bộ nhớ thành các sections là .text, .data .bss. 
    
    /* chèn hình command SECTIONS 

    Các lệnh sẽ được lưu vào vùng .text, các biến global được khởi tạo và có giá trị và các biến 
    static sẽ được lưu vào vùng .data, các biến global được khởi tạo mà không có giá trị hoặc được
    gán giá trị bằng 0 sẽ được lưu vào vùng .bss

    Tiếp theo ta sẽ viết code hàm main để chạy ứng dụng. Trên VĐK STM32F4xx nhà sản xuất đã trang
    bị cho chúng ta 4 con led để có thể lập trình. Ở đây chúng ta sẽ dùng led màu xanh trên VĐK 
    được điều khiển bằng PORTD15. Để sử dụng PORTD ta phải enable clock cho PORTD và ở đây thanh 
    ghi. Thanh ghi để điều khiển PORTD là thanh ghi RCC_AHB1 và 2 thanh ghi để điều khiển led là
    GPIODModeReg dùng để cấu hình mode cho PORTD15 và thanh ghi GPIODDataReg để set đầu ra là mức
    thấp hay mức cao cho PORTD15.

    /* chèn hình các thanh ghi */

    Việc cuối cùng là viết một Makefile để build toàn bộ source code. Việc dùng Makefile để build và
    nạp code sẽ dễ dàng build và nạp code cho các bài khác vì chúng ta chỉ cần đổi các đường dẫn của các 
    file source trong Makefile phù hợp với đự án là chúng ta có thể sử dụng lại Makefile để build và nạp
    code cho dự án mới.

    Các tool sử dụng trong bài: 
      - GNU Arm Embedded Toolchain
      - GNU Make
      - Git bash
      - STM32CubeProg
    
    Tài liệu tham khảo:
      - STM32F407 Reference Manual

    Để build thử source và nạp chương trình vào mạch các bạn hãy clone source về máy sửa các đường dẫn của
    COMPILER_DIR và FLASH_DIR. Lưu ý là sử dụng git pash hoặc có thể tải cywin về để gõ command line để có 
    thể chạy một số lệnh chỉ thực hiện được ở môi trường linux. Trước khi sử dụng lệnh make hãy đưa đường dẫn
    chưa file make vào trong system path để có thể gõ make mà không cần kèm theo đường dẫn. Gõ lệnh "make clean" 
    để xóa folder bin (folder chứa file object và file thực thi). Sau đó gõ lệnh "make build" để build chương trình.
    Sau khi build thấy có dòng chữ "-----build OK-----" hiện ra có nghĩa là đã build thành công.

    /* chèn ảnh build */

    Sau đó hãy  gõ lệnh "make flash" để nạp chương trình vào board. Thấy dòng chữ "-----flash OK-----" là đã nạp thành
    công.

    /* chèn ảnh flash */

    Nhấn nút reset trên board để chương trình thực hiện.

    /* chèn ảnh kết quả chương trình */
