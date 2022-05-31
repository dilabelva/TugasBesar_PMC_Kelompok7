# TugasBesar_PMC_Kelompok7

- **Latar Belakang**

Minimisasi _logic boolean algebra_ diperlukan untuk memperkecil ukuran sebuah rangkaian, sehingga kecepatan akan meningkat dan konsumsi power rangkaian menjadi semakin optimal. Terdapat dua buah metode yang dapat digunakan untuk melakukan minimisasi _logic boolean algebra_, yakni metode Karnaugh Map (K-Map) dan metode Quine-McCluskey (Metode Tabular). Melalui metode tabular, keterbatasan metode karnaugh map terkait jumlah variabel yang dapat di-_input_-kan (minimal dua dan maksimal lima variabel), dapat teratasi, karena sifat metode tabular yang dapat menerima variabel dalam jumlah tak terbatas. Selain itu, dikarenakan metode karnaugh map lebih banyak memanfaatkan visual manusia daripada metode tabular, metode karnaugh map akan lebih sulit untuk diimplementasikan dalam sebuah kode program. Karena alasan-alasan tersebut, kami pun memilih metode tabular untuk dibahas dan diimplementasikan dalam _**Tugas Besar Eksplorasi Algoritma Minimisasi Logic EL2008 - Pemecahan Masalah dengan C**_ untuk _**Kelompok 7**_.

- **Metode Quine-McCluskey (Metode Tabular)**

Tujuan utama yang ingin dicapai dalam metode tabular adalah untuk menemukan seluruh _price implicants_ kemudian memanfaatkannya untuk mencari _essential prime implicants_ dari fungsi-fungsi yang di-_input_-kan (minterm). Dalam perjalanannya demi mencapai tujuan utama tersebut, dilakukan setidaknya **empat buah tahapan**, yakni iterasi 1, iterasi 2, iterasi 3, dan pembuatan tabel _prime implicants_, _essential prime implicants_, serta hasil akhir. 

Pada kode program yang telah disusun, _**input**_ akan berupa **banyaknya minterm yang akan diminimisasi** (dalam range 1 s.d. 16 berbentuk integer) dan **bentuk desimal dari minterm-minterm tersebut** (dalam range 0 s.d. 15 berbentuk integer) sesuai jumlah banyaknya minterm yang telah di-_input_-kan. Pada akhir keberjalanan, _**output**_ yang akan disajikan kepada pengguna adalah **tabel hasil iterasi 1**, **iterasi 2**, **iterasi 3** (jika diperlukan), **tabel _prime implicants_**, serta **_boolean expression_ yang telah disederhanakan**. Program ini memanfaatkan 18 fungsi lain di luar main() function, yakni tambahMinterm(int), buatNode(int), gabungMinterm(), print(), printTabel(), buatNodePair(node*, node*), isiBiner(node*, node*, node*), initTable(), ifPairingPossible(node*, node*), ifMintermPresentInImplicant(int, int), tambahPair(node*, node*), tambahTabel(), analisisTabel(), konversiBiner(int), cariMax(int*), jumlahImplicants(int, int), dan hapusMinterm(int). 

- **Kelebihan dan Kekurangan Program**

a. Kelebihan : tersedianya tampilan bentuk tabel dari hasil iterasi 1, 2, 3 (jika diperlukan), dan _prime implicants_, sehingga memungkinkan pengguna menganalisis setiap tahapan dari metode tabular. 

b. Kekurangan : keterbatasan input yang dapat dimasukkan. Jumlah banyaknya minterm yang dapat dimasukkan terbatas dalam range 1 s.d. 16 dan bentuk desimal dari minterm terkait yang dapat dimasukkan terbatas dalam range 0 s.d. 15.

- **Contoh _Input_ dan _Output_**

**a. _Test Case 1_** : _test case_ dengan adanya validasi input terlebih dahulu pada awal pemasukan
![2299187](https://user-images.githubusercontent.com/82191748/171211123-c58afb8e-5281-45d5-9a5e-a488a3a4059d.jpg)

**b. _Test Case 2_** : _test case_ dengan dua kali iterasi
![2299188](https://user-images.githubusercontent.com/82191748/171211151-4abedd90-31b6-466e-a959-27e2f103d7de.jpg)

**c. _Test Case 3_** : _test case_ dengan tiga kali iterasi
![2299185](https://user-images.githubusercontent.com/82191748/171210345-76da627e-3c1d-453f-b0af-198099b4488f.jpg)
