#include <iostream>
#include <fstream> // memanggil header untuk bisa mengupdate database

using namespace std;
#include "db.txt" //memanggil database

int nasabahIndex; // variable untuk menyimpan indeks nasabah saat ini
const int totalNasabah = 5;
const string kartuATM[5] = {"BCA", "BJB", "BRI", "BTN", "BNI"}; // kartu atm yang tersedia di EL-KBMN
const int penarikanDana[4] = {50000, 100000, 500000, 1000000};

// function tipe data void;
void head();

void cekSaldo();

// function tipe data boolean
bool checkSandi(int kartu, int count = 1);

// function tipe data integer
int pilihTransaksi();
int pilihanLainnya();
int displayMenuDana(string jenisTransaksi);

// function tipe data string
string gantiPin();
string transferSaldo();
string kalkulasiSaldo(int tarikSaldo, int jenisTransaksi, int noRekIndex = -1);

int main()
{
    int kartu;
    // Welcoming pengguna
    head(); // memanggil header

    // Memasukkan kartu ATM berdasarkan keinginan nasabah
    cout << "\t\t\tEL-KBMN menerima berbagai kartu: " << endl;
    cout << "\t\t\t1. BCA\t\t\t2. BJB\n\t\t\t3. BRI\t\t\t4. BTN\n\t\t\t\t   5. BNI" << endl;
    cout << "\t\tMasukkan kartu ATM berdasarkan nomor di atas: ";

    // Program berakhir ketika ATM tidak valid
    if (!(cin >> kartu) || kartu > 5 || kartu <= 0)
    {
        cout << endl
             << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t   Kartu ATM yang anda masukkan tidak valid\n";
        cout << "\t\t==============================================\n";
        return 1;
    };

    char repeat;
    do
    {
        // menjanlankan function checkSandi
        // nasabah memasukkan sandi
        // program berakhir ketika sandi tidak valid
        if (!checkSandi(kartu) || nasabah[nasabahIndex].isBlocked)
        {
            cout << endl
                 << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t         Kartu ATM Anda Telah Diblokir.\n";
            cout << "\t\t==============================================\n\n";
            break;
        };

        system("cls"); // system akan menghapus semua isi terminal
        head();        // memanggil header //menampilkan header dari atm el-kbmn

        string output; // menyimpan pesan teks dari setiap transaksi

        int transaksiNumber = pilihTransaksi(); // memilih transaksi
        switch (transaksiNumber)
        {
        case 1: // Opsi 1 adalah ketika nasabah memilih tarik saldo
            output = kalkulasiSaldo(displayMenuDana("penarikan"), 2);
            break;
        case 2: // Opsi 2 adalah ketika nasabah memilih transfer
            output = transferSaldo();
            break;
        case 3:                                      // Opsi 3 adalah ketika nasabah memilih pilihan lainnya
            int transaksiLainnya = pilihanLainnya(); // nasabah memilih transaksi lanjutan
            switch (transaksiLainnya)
            {
            case 1: // Opsi 1 adalah ketika nasabah memilih cek saldo
                cekSaldo();
                break;
            case 2: // Opsi 2 adalah ketika nasabah memilih ganti sandi
                output = gantiPin();
                break;
            case 3: // Opsi 3 adalah ketika nasabah memilih setor tunai
                output = kalkulasiSaldo(displayMenuDana("untuk disetor "), 3);
                break;
            }
            break;
        }

        cout << endl
             << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t\t   " << output << endl;
        cout << "\t\t==============================================\n";

        cout << "\t\tApakah ingin melakukan transaksi lagi [y/n]: ";
        cin >> repeat;

    } while (repeat == 'y'); // jika nasabah memilih y, maka program akan diulang, selain itu program akan berakhir

    system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
    system("cls");   // system akan menghapus semua isi terminal
    head();          // memanggil header

    cout << "\t\t  " << "Terima Kasih Telah Menggunakan ATM EL-KBMN";
    cout << endl
         << endl;
    cout << "\t\t==============================================\n";
    cout << "\t\t\t\t" << "PROGRAM BERAKHIR" << endl;
    cout << "\t\t==============================================\n";

    system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
    return 0;
}

// header
void head()
{
    cout << endl
         << endl
         << endl;
    cout << "\t\t==============================================" << endl;
    cout << "\t\t                 ATM EL-KBMN" << endl;
    cout << "\t\t==============================================" << endl
         << endl;
};

// untuk mengupdate database yang ada di file db.txt
void updateDatabaseFile()
{
    ofstream dbFile("db.txt"); // membuka file db.txt

    // melakukan overwrite ke db.txt, jadi teks yang ada di db.txt akan ditimpa
    dbFile << "struct Nasabah {\n";
    dbFile << "    string nama;\n";
    dbFile << "    string kartu;\n";
    dbFile << "    string pin;\n";
    dbFile << "    string noRekening;\n";
    dbFile << "    long saldo;\n";
    dbFile << "    bool isBlocked;\n";
    dbFile << "};\n\n";
    dbFile << "Nasabah nasabah[5] = {\n";

    // Looping digunakan untuk menuliskan data dari nasabah-nasabah yang ada
    for (int i = 0; i < totalNasabah; i++)
    {
        dbFile << "    {\n";                                            // kurung kurawal pembuka
        dbFile << "        \"" << nasabah[i].nama << "\",\n";           // menuliskan nama nasabah dengan indeks ke-i
        dbFile << "        \"" << nasabah[i].kartu << "\",\n";          // menuliskan karu nasabah dengan indeks ke-i
        dbFile << "        \"" << nasabah[i].pin << "\",\n";            // menuliskan pin nasabah dengan indeks ke-i
        dbFile << "        \"" << nasabah[i].noRekening << "\",\n";     // menuliskan NoRek nasabah dengan indeks ke-i
        dbFile << "        " << nasabah[i].saldo << ",\n";              // menuliskan saldo nasabah dengan indeks ke-i
        dbFile << "        " << nasabah[i].isBlocked << "\n";           // menuliskan apakah nasabah dengan indeks ke-i diblokir atau tidak
        dbFile << "    }" << (i < totalNasabah - 1 ? "," : "") << "\n"; // kurung kurawal penutup dengan tambahan, jika i kurang dari total nasabah yang ada maka akan ditambahkan koma dibelakang kurung kurawal, sebaliknya akan ditambahkan string kosong
    }
    dbFile << "};\n";
    dbFile.close(); // menutup file db.txt
}

// Untuk mengecek sandi nasabah
bool checkSandi(int kartu, int count)
{
    string sandi; // mendeklarasikan variable sandi dengan tipe data string

    system("cls"); // system akan menghapus semua isi terminal
    head();        // memanggil header

    cout << "\t\t\tSilahkan masukkan kata sandi:\n\t\t\t\t    ";
    getline(cin >> ws, sandi); // memasukkan inputan nasabah ke variable sandi, ws digunakan untuk menghilangkan whitespace agar kode tidak error

    bool isValidSandi = false;

    // melakukan looping untuk mengecek kata sandi dan kartu yang sesuai dengan apa yang sudah dimasukkan nasabah
    for (int i = 0; i < totalNasabah; i++)
    {
        if (kartuATM[kartu - 1] == nasabah[i].kartu)
        {
            nasabahIndex = i;

            if (nasabah[i].pin == sandi)
            {
                isValidSandi = true;
                break; // keluar dari looping secara paksa
            }
        }
    }

    // melakukan pengecekan jika sandi nasabah tidak ada yang sesuai dan percobaan yang dilakukan kurang dari sama dengan 3
    if (!isValidSandi && count < 3)
    {
        count++;

        cout << endl
             << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t     Sandi yang anda masukkan tidak valid\n";
        cout << "\t\t==============================================\n\n";

        system("pause");                 // system akan berhenti sampai nasabah memencet sembarang tombol
        return checkSandi(kartu, count); // fungsi akan memanggil dirinya sendiri, dengan nilai count yang sudah ditambah 1
    }

    // jika percobaan memasukkan sandi sebanyak 3 kali masih salah, maka kartu nasabah akan diblock
    else if (count == 3 && !isValidSandi)
    {
        nasabah[nasabahIndex].isBlocked = true;
        updateDatabaseFile();
    }

    return isValidSandi;
}

// memilih transaksi
int pilihTransaksi()
{
    int transaksiNumber;
    do
    {
        // untuk melihat apakan pada proses peng-inputan data terjadi error
        if (cin.fail())
        {
            cin.clear();            // menghapus status error
            cin.ignore(1000, '\n'); // membersihkan karakter dari buffer input sebanyak 1000 karakter atau hingga ada line baru
        }

        cout << "\t\t1. Tarik Saldo\n\t\t2. Transfer\n\t\t3. Lainya\n";
        cout << "\t\t==============================================\n";

        cout << "\t\tSilahkan pilih transaksi: ";

        // nasabah memilih angka 1 - 3, jika memilih karakter atau angka lebih dari 3 maka akan masuk ke kondisi pilihan tidak tersedia
        if (!(cin >> transaksiNumber) || transaksiNumber > 3 || transaksiNumber <= 0)
        {
            cout << endl
                 << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  Transaksi yang ada pilih tidak tersedia\n";
            cout << "\t\t==============================================\n";
            system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
        }
        system("cls"); // system akan menghapus semua isi terminal
        head();        // memanggil header
    } while (transaksiNumber > 3 || cin.fail() || transaksiNumber <= 0);

    return transaksiNumber;
}

// Untuk menampilkan menu uang transaksi
int displayMenuDana(string jenisTransaksi)
{
    int tarikSaldo;
    cout << "\t\t\t1. Rp.50.000 \t2. Rp.100.000 \n\t\t\t3. Rp.500.000 \t4. Rp.1.000.000 \n";
    cout << "\t\t==============================================\n";

    cout << "\t\tSilahkan pilih jumlah " << jenisTransaksi << ": "; // jenisTransaksi akan diisi tergantung dengan transaksi apa yang sedang diingikan nasabah

    // nasabah memilih angka 1 - 4, jika memilih karakter atau angka lebih dari 4 maka akan masuk ke kondisi pilihan tidak tersedia
    if (!(cin >> tarikSaldo) || tarikSaldo > 4 || tarikSaldo == 0)
    {
        cout << endl
             << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t  Pilihan yang anda masukkan tidak tersedia\n";
        cout << "\t\t==============================================\n";

        system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
        system("cls");   // system akan menghapus semua isi terminal
        head();          // memanggil header

        cin.clear();                            // menghapus status error
        cin.ignore(1000, '\n');                 // membersihkan karakter dari buffer input sebanyak 1000 karakter atau hingga ada line baru
        return displayMenuDana(jenisTransaksi); // menjalankan fungsi dirinya sendiri
    };
    return tarikSaldo - 1; // nilai dari tarikSaldo dikurangi 1 karena mengacu kepada indeks
}

// kalkulasi saldo setiap nasabah melakukan transaksi tertenu
string kalkulasiSaldo(int tarikSaldo, int jenisTransaksi, int noRekIndex)
{
    // jika saldo nasabah saat ini tidak lebih besar dari dana yang dipilih nasabah dan jenisTransaksi bukan setor tunai, maka kondisi saldo tidak mencukupi akan dijalankan
    if (!(nasabah[nasabahIndex].saldo >= penarikanDana[tarikSaldo]) && jenisTransaksi != 3)
    {
        return "Saldo anda tidak mencukupi.";
    }

    switch (jenisTransaksi)
    {
    case 1:                                                     //// Opsi 1 adalah ketika nasabah memilih transfer
        nasabah[noRekIndex].saldo += penarikanDana[tarikSaldo]; // keyword break ditiadakan, agar saldo nasabah saat ini bisa dikalkulasi di kondisi selanjutnya
    case 2:                                                     // Opsi 2 adalah ketika nasabah memilih tarik saldo atau mengurangi saldo setelah melakukan transfer
        nasabah[nasabahIndex].saldo -= penarikanDana[tarikSaldo];
        break;
    case 3: // Opsi 1 adalah ketika nasabah memilih setor tunai
        nasabah[nasabahIndex].saldo += penarikanDana[tarikSaldo];
    }

    updateDatabaseFile(); // fungsi updateDatabaseFile dijalankan untuk memperbaharui database pada db.txt
    return "    Transaksi Berhasil.";
}

string transferSaldo()
{
    string rekeningTujuan;
    int isValidRekeningIndex = -1;

    cout << "\t\t\tMasukkan No Rekening tujuan:\n\t\t\t\t  ";
    getline(cin >> ws, rekeningTujuan); // memasukkan inputan nasabah ke variable rekeningTujuan, ws digunakan untuk menghilangkan whitespace agar kode tidak error

    // jika nilai rekeningTujuan sama dengan noRekening nasabah saat ini, maka akan masuk ke kondisi tidak bisa mentransfer ke noRek sendiri
    if (rekeningTujuan == nasabah[nasabahIndex].noRekening)
    {
        cout << endl
             << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\tAnda tidak bisa melakukan transfer menggunakan\n\t\t\t      No.Rek anda sendiri\n";
        cout << "\t\t==============================================\n";

        system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
        system("cls");   // system akan menghapus semua isi terminal
        head();          // memanggil header
        return transferSaldo();
    }

    // looping dilakukan untuk mencari no rekening yang sesuai
    for (int i = 0; i < totalNasabah; i++)
    {
        if (nasabah[i].noRekening == rekeningTujuan)
        {
            isValidRekeningIndex = i; // jika sudah ketemu, maka indeks ke-i yang sesuai akan dimasukkan ke variable isValidRekeningIndex
        }
    }

    // jika isValidRekeningIndex nilai lebih besar sama dengan 0, maka akan masuk ke kondisi pengkalkulasian saldo
    if (isValidRekeningIndex >= 0)
    {
        system("cls"); // system akan menghapus semua isi terminal
        head();        // memanggil header
        return kalkulasiSaldo(displayMenuDana("untuk ditransfer"), 1, isValidRekeningIndex);
    };

    // Jika isValidRekeningIndex masih bernilai -1, maka rekeningTujuan tidak terdaftar di database
    cout << endl
         << endl;
    cout << "\t\t==============================================\n";
    cout << "\t\tNo rekening yang anda masukkan tidak tersedia\n\t\t\tpastikan No Rekening sudah benar!\n";
    cout << "\t\t==============================================\n";

    system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
    system("cls");   // system akan menghapus semua isi terminal
    head();          // memanggil header

    return transferSaldo(); // menjalankan kembali fungsi transferSaldo
}

int pilihanLainnya()
{
    int transaksiNumber;

    do
    {
        // untuk melihat apakan pada proses peng-inputan data terjadi error
        if (cin.fail())
        {
            cin.clear();            // menghapus status error
            cin.ignore(1000, '\n'); // membersihkan karakter dari buffer input sebanyak 1000 karakter atau hingga ada line baru
        }

        cout << "\t\t1. Cek Saldo\n\t\t2. Ganti Sandi\n\t\t3. Setor Tunai\n";
        cout << "\t\t==============================================\n";

        cout << "\t\tSilahkan pilih transaksi: ";

        // nasabah memilih angka 1 - 3, jika memilih karakter atau angka lebih dari 3 maka akan masuk ke kondisi pilihan tidak tersedia
        if (!(cin >> transaksiNumber) || transaksiNumber > 3 || transaksiNumber <= 0)
        {
            cout << endl
                 << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  Transaksi yang ada pilih tidak tersedia\n";
            cout << "\t\t==============================================\n";
            system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
        }

        system("cls"); // system akan menghapus semua isi terminal
        head();        // memanggil header
    } while (transaksiNumber > 3 || cin.fail() || transaksiNumber <= 0);

    return transaksiNumber;
}

// menampilkan biodata nasabah saat ini beserta dengan saldonya
void cekSaldo()
{
    cout << "\t\t\tNama: \t\t" << nasabah[nasabahIndex].nama << endl;             // menampilkan nama nasabah saat ini
    cout << "\t\t\tNO. Rekening: \t" << nasabah[nasabahIndex].noRekening << endl; // menampilkan No Rekening nasabah saat ini
    cout << "\t\t\tKartu ATM: \t" << nasabah[nasabahIndex].kartu << endl;         // menampilkan kartu yang digunakan nasabah saat ini
    cout << "\t\t\tSaldo: \t\tRp." << nasabah[nasabahIndex].saldo;                // menampilkan saldo nasabah saat ini
}

string gantiPin()
{
    string pinBaru[2];            // membuat array yang dapat menampung 2 nilai string
    string number = "0123456789"; // variable yang diisi dengan angka kari 0-9
    bool isValidNumber;           // variable yang akan menyimpan nilai true or false

    do
    {
        cout << "\t\t\t      Masukkan pin baru:\n\t\t\t\t    ";
        getline(cin >> ws, pinBaru[0]); // memasukkan inputan nasabah ke variable pinBaru indeks ke 0, ws digunakan untuk menghilangkan whitespace agar kode tidak error

        // jika pinBaru indeks ke 0 panjangnya tidak sama dengan 6, maka akan masuk kondisi error
        if (pinBaru[0].length() != 6)
        {
            cout << endl
                 << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t          PIN harus berisi 6 angka\n";
            cout << "\t\t==============================================\n";

            system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
            system("cls");   // system akan menghapus semua isi terminal
            head();          // memanggil header
            continue;
        }

        // looping dijalankan untuk mengecek setiap karakter pada pinBaru indeks ke 0 apakah terdaftar di variable number
        for (int i = 0; i < pinBaru[0].length(); i++)
        {
            isValidNumber = false;

            // looping dijalankan untuk mengecek setiap karakter pada number sama dengan karakter pinBaru indeks ke 0
            for (int j = 0; j < number.length(); j++)
            {
                if (number[j] == pinBaru[0][i])
                {
                    isValidNumber = true; // jika terdapat karakter yang sama maka variable isValidNumber bernilai true
                    break;
                }
            }

            // jika isValidNumber masih berni
            if (!isValidNumber)
            {
                cout << endl
                     << endl;
                cout << "\t\t==============================================\n";
                cout << "\t\t           PIN harus berisi angka\n";
                cout << "\t\t==============================================\n";

                system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
                system("cls");   // system akan menghapus semua isi terminal
                head();          // memanggil header
                break;           // akan langsung keluar dari for loop
            }
        }

        // jika isValidNumber bernilai false, maka program akan melakukan looping dari awal lagi
        if (!isValidNumber)
        {
            continue; // keyword continue membuat program langsung masuk ke while dan akan diperiksa
        }

        system("cls"); // system akan menghapus semua isi terminal
        head();        // memanggil header
        cout << "\t\t\t     Konfirmasi pin baru:\n\t\t\t\t    ";

        getline(cin >> ws, pinBaru[1]); //// memasukkan inputan nasabah ke variable pinBaru indeks ke 1, ws digunakan untuk menghilangkan whitespace agar kode tidak error

        // melakukan pengecekan apakah pinBaru indeks ke 0 sama dengan pinBaru indeks ke 1, jika tidak maka program akan error
        if (pinBaru[1] != pinBaru[0])
        {
            cout << endl
                 << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  PIN yang anda masukkan tidak sesuai\n";
            cout << "\t\t==============================================\n";

            system("pause"); // system akan berhenti sampai nasabah memencet sembarang tombol
            system("cls");   // system akan menghapus semua isi terminal
            head();          // memanggil header
        }

    } while (pinBaru[0].length() != 6 || !isValidNumber || pinBaru[0] != pinBaru[1]);

    nasabah[nasabahIndex].pin = pinBaru[0]; // menganti pin nasabah saat ini dengan yang baru
    updateDatabaseFile();

    return "  PIN berhasil diganti.";
};
