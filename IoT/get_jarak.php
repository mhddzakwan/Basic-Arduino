<?php
include 'config.php';

// Ambil nilai jarak dari database
$query = "SELECT jarak FROM tb_led WHERE id=1";
$result = $koneksi->query($query);
$row = mysqli_fetch_assoc($result);

// Output jarak
echo $row['jarak'];
?>
