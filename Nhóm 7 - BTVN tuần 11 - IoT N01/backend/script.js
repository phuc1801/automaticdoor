// script.js
function loadData() {
    $.ajax({
        url: "index.php",  // URL lấy dữ liệu từ PHP
        method: "GET",      // Phương thức GET để lấy dữ liệu
        success: function(data) {
            var rows = JSON.parse(data); // Chuyển dữ liệu JSON thành mảng
            var tableBody = $("#data-table tbody");
            tableBody.empty(); // Xóa dữ liệu cũ trong bảng

            // Thêm dữ liệu mới vào bảng
            rows.forEach(function(row) {
                var tr = $("<tr>");
                tr.append("<td>" + row.id + "</td>");
                tr.append("<td>" + row.ls1 + "</td>");
                tr.append("<td>" + row.ls2 + "</td>");
                tr.append("<td>" + row.hc1 + "</td>");
                tr.append("<td>" + row.hc2 + "</td>");
                tr.append("<td>" + row.time + "</td>");
                tr.append("<td>" + row.status + "</td>");
                tableBody.append(tr);
            });
        }
    });
}

// Tải dữ liệu ngay khi trang được tải và tự động cập nhật mỗi 5 giây
$(document).ready(function() {
    loadData();  // Gọi hàm tải dữ liệu ngay lập tức
    setInterval(loadData, 5000);  // Tải lại dữ liệu mỗi 5 giây
});
