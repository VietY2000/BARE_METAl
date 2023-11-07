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
    vòng lặp vô hạn( điều này là không nên đối với các dự án thực tế). 

    /* chèn hình reset_handler */

    Hàm reset_handler có nhiệm vụ là hàm đầu tiên được chạy để sao chép các dữ liệu của vùng 
    .data trong bộ nhớ Flash lên Sram và chuyển các giá trị trong vùng .bss về 0 sau đó là 
    gọi hàm main chính của chương trình chạy. 
    
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


