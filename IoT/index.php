<?php
include 'config.php';

// Mengontrol LED melalui website
if (isset($_POST['toggle_led'])) {
    // Mengambil status red saat ini
    $query = "SELECT red FROM tb_led WHERE id=1";
    $result = $koneksi->query($query);
    $row = mysqli_fetch_assoc($result);
    
    // Mengubah status red
    $new_status = ($row['red'] == "on") ? "off" : "on";
    
    // Update status red di database
    $query = "UPDATE tb_led SET red='$new_status' WHERE id=1";
    $koneksi->query($query);
}

// Ambil status terbaru untuk red
$query = "SELECT red FROM tb_led WHERE id=1";
$result = $koneksi->query($query);
$row = mysqli_fetch_assoc($result);
$red_status = $row['red'];

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kontrol LED dan Jarak</title>
    <script>
        // Fungsi untuk mengambil nilai jarak dari get_jarak.php setiap 2 detik
        function updateJarak() {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', 'get_jarak.php', true);
            xhr.onload = function() {
                if (xhr.status === 200) {
                    // Perbarui nilai jarak pada elemen HTML
                    document.getElementById('jarak').innerText = xhr.responseText + ' cm';
                }
            };
            xhr.send();
        }

        // Memanggil fungsi updateJarak setiap 2 detik
        setInterval(updateJarak, 2000);

        // Memanggil fungsi untuk pertama kali saat halaman dimuat
        window.onload = updateJarak;
    </script>
</head>
<body>
    <h1>Jarak: <span id="jarak">Loading...</span></h1>

    <h2>LED Status: <?php echo $red_status == "on" ? "Menyala" : "Mati"; ?></h2>
    
    <!-- Form untuk toggle LED -->
    <form method="POST" action="">
        <button type="submit" name="toggle_led">
            <?php echo $red_status == "on" ? "Matikan LED" : "Nyalakan LED"; ?>
        </button>
    </form>
    
</body>
</html>
