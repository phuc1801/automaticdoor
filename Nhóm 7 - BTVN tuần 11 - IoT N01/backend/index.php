<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Thông tin Cửa</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 20px;
        }

        h1 {
            text-align: center;
            color: #333;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        table, th, td {
            border: 1px solid #ddd;
        }

        th {
            background-color: #4CAF50;
            color: white;
            padding: 12px;
            text-align: center;
        }

        td {
            padding: 10px;
            text-align: center;
        }

        tr:nth-child(even) {
            background-color: #f2f2f2;
        }

        tr:hover {
            background-color: #ddd;
        }

        .status {
            font-weight: bold;
        }

        .open {
            color: green;
        }

        .closed {
            color: red;
        }

        .reload-btn {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            cursor: pointer;
            margin: 10px 0;
            display: block;
            margin-left: auto;
            margin-right: auto;
        }

        .reload-btn:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>

    <h1>Danh Sách Thông Tin Cửa</h1>

    <!-- Nút load lại dữ liệu -->
    <button class="reload-btn" onclick="reloadData()">Load lại dữ liệu</button>

    <div id="data-table">
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
    </div>

    <script>
        // Hàm để load lại dữ liệu
        function reloadData() {
            const xhr = new XMLHttpRequest();
            xhr.open('GET', 'load_data.php', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    document.getElementById('data-table').innerHTML = xhr.responseText;
                }
            };
            xhr.send();
        }
    </script>

</body>
</html>
