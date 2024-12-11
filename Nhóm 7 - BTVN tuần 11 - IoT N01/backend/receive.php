<?php
include 'connect.php'; 

// Kiểm tra nếu yêu cầu là POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST['data'])) {
        // Nhận dữ liệu từ ESP8266
        $data = $_POST['data'];

        // Kiểm tra nếu có dữ liệu
        if (!empty($data)) {
            // Phân tách dữ liệu (các giá trị cách nhau bằng khoảng trắng)
            $data_parts = explode(" ", $data);

            // Kiểm tra nếu dữ liệu có đủ 4 phần
            if (count($data_parts) == 4) {
                $rls1 = $data_parts[0];
                $rls2 = $data_parts[1];
                $ds1 = $data_parts[2];
                $ds2 = $data_parts[3];

                // Thêm dữ liệu vào database
                $sql = "INSERT INTO info (ls1, ls2, hc1, hc2, time) VALUES ('$rls1', '$rls2', '$ds1', '$ds2', NOW())";

                if ($conn->query($sql) === TRUE) {
                    echo "New record created successfully";
                } else {
                    echo "Error: " . $sql . "<br>" . $conn->error;
                }
            } else {
                echo "Invalid data format";
            }
        } else {
            echo "No data received!";
        }
    } else {
        echo "No 'data' field in POST request!";
    }
} else {
    echo "Invalid request method!";
}
?>
