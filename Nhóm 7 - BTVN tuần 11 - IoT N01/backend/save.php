<?php
include 'connect.php'; // Kết nối tới MySQL

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $data = $_POST['data'];
    $values = explode(',', $data); // Phân tách giá trị bằng dấu phẩy

    if (count($values) == 6) {
        $id = intval($values[0]);
        $ls1 = intval($values[1]);
        $ls2 = intval($values[2]);
        $hc1 = intval($values[3]);
        $hc2 = intval($values[4]);
        $time = intval($values[5]);

        // Lưu vào cơ sở dữ liệu
        $sql = "INSERT INTO your_table (id, ls1, ls2, hc1, hc2, time) VALUES ($id, $ls1, $ls2, $hc1, $hc2, $time)";
        if ($conn->query($sql) === TRUE) {
            echo "Lưu dữ liệu thành công!";
        } else {
            echo "Lỗi: " . $sql . "<br>" . $conn->error;
        }
    } else {
        echo "Dữ liệu không hợp lệ!";
    }
} else {
    echo "Chỉ hỗ trợ phương thức POST!";
}
?>
