<?php
    include 'config.php';
    $jarak = $_GET['jarak'];
    // Menampilkan jarak di web
    $query = "UPDATE tb_led SET jarak = $jarak WHERE id=1";
    $koneksi->query($query);
    
    // Mengontrol LED melalui website
    $query = "SELECT red FROM tb_led WHERE id = 1";
    $result = $koneksi->query($query);
    $row = mysqli_fetch_assoc($result);
    if($row['red'] == "on"){
        echo "on";
    }else {
        echo "off";
    }
?>
