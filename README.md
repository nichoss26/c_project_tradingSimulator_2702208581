# c_project_tradingSimulator_2702208581

Projek ini adalah simulasi trading berbasis candlestick chart yang dibuat dalam bahasa C. Program ini berjalan di terminal dan menggunakan ASCII art untuk menampilkan grafik pergerakan harga. Pengguna bisa mendaftar akun, login, melakukan simulasi trading dengan membuka posisi long atau short, menetapkan take profit dan stop loss, lalu melihat hasilnya apakah untung atau rugi berdasarkan pergerakan harga selanjutnya.

Saat pengguna login, sistem akan membaca data akun dari file `user.txt`. Setiap akun memiliki username, email, password, dan saldo uang virtual. Setelah berhasil login, pengguna bisa memilih menu untuk mulai trading, melihat histori trading sebelumnya, membaca panduan, atau logout.

Simulasi candle dibuat berdasarkan harga open sebelumnya, dengan nilai close, highest, dan lowest yang diacak berdasarkan probabilitas tertentu agar menyerupai kondisi pasar. Setiap candle baru akan muncul saat user memilih “Next Day”. Grafik candlestick digambar secara horizontal di terminal, dengan warna merah dan hijau untuk menandai harga naik atau turun.

Untuk melakukan trading, user harus memasukkan sejumlah nilai sebagai “value”, lalu menentukan posisi (harga entry), take profit, dan stop loss. Jika harga bergerak dan menyentuh TP atau SL, posisi akan otomatis tertutup dan sistem menghitung reward atau kerugian. Reward ditambahkan atau dikurangkan dari saldo pengguna. Semua histori trading akan disimpan secara lokal dan bisa dilihat kembali dari menu “Trade History”.

Struktur data yang digunakan mencakup:
* **Linked list** untuk menyimpan candle dan histori trading
* **Hash table** untuk menyimpan data pengguna berdasarkan username
* File handling untuk menyimpan dan membaca data akun dari file

Program ini sepenuhnya berbasis terminal Windows, menggunakan library `windows.h` untuk efek fullscreen dan `conio.h` untuk input karakter dengan masker password.

Semua data user disimpan dalam file teks `user.txt` dengan format:

```
username#email#password#saldo
```
