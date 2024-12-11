<?php
// Thông tin cấu hình cơ sở dữ liệu
$host = "localhost";     // Địa chỉ máy chủ MySQL (thường là localhost)
$username = "root";      // Tên tài khoản MySQL
$password = "";          // Mật khẩu MySQL (để trống nếu chưa đặt)
$database = "ctd"; // Tên cơ sở dữ liệu

// Tạo kết nối
$conn = new mysqli($host, $username, $password, $database);

// Kiểm tra kết nối
if ($conn->connect_error) {
    die("Kết nối thất bại: " . $conn->connect_error);
} else {
    echo "Kết nối thành công!";
}
?>
