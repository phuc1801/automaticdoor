<?php
include 'connect.php';

$sql = "SELECT * FROM info ORDER BY time DESC LIMIT 10";
$result = $conn->query($sql);

if ($result === FALSE) {
    die("Lỗi truy vấn: " . $conn->error);
}

if ($result->num_rows > 0) {
    echo "<table>";
    echo "<tr><th>ID</th><th>LS1</th><th>LS2</th><th>HC1</th><th>HC2</th><th>Time</th><th>Status</th></tr>";

    while ($row = $result->fetch_assoc()) {
        // Kiểm tra điều kiện để hiển thị trạng thái cho hc1 và hc2
        $status_hc1 = ($row['hc1'] < 15) ? '<span class="status open">Mở cửa</span>' : '<span class="status closed">Đóng cửa</span>';
        $status_hc2 = ($row['hc2'] < 15) ? '<span class="status open">Mở cửa</span>' : '<span class="status closed">Đóng cửa</span>';

        echo "<tr>
                <td>{$row['id']}</td>
                <td>{$row['ls1']}</td>
                <td>{$row['ls2']}</td>
                <td>{$row['hc1']}</td>
                <td>{$row['hc2']}</td>
                <td>{$row['time']}</td>
                <td>HC1: $status_hc1, HC2: $status_hc2</td>
              </tr>";
    }
    echo "</table>";
} else {
    echo "Không có dữ liệu!";
}
?>
