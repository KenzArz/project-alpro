#include <iostream>
#include <fstream>

using namespace std;
#include "db.txt"

int nasabahIndex;
const int totalNasabah = 5;
const string kartuATM[4] = {"BCA", "BRI", "BTN", "BNI"};
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

int main(){
    int kartu;
    // Welcoming pengguna
    head();

    // Memasukkan kartu ATM berdasarkan keinginan user
    cout << "\t\t\tEL-KBMN menerima berbagai kartu: " << endl;
    cout << "\t\t\t1. BCA\t\t\t2. BRI\n\t\t\t3. BTN\t\t\t4. BNI" << endl;
    cout << "\t\tMasukkan kartu ATM berdasarkan nomor di atas: ";

    // Program berakhir ketika ATM tidak valid
    if(!(cin >> kartu) || kartu > 4) {
        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t   Kartu ATM yang anda masukkan tidak valid\n";
        cout << "\t\t==============================================\n";
        return 1;
    };
    
    char repeat;
    do
    {
        // Menjanlankan function checkSandi
        // User memasukkan sandi
        // Program berakhir ketika sandi tidak valid
        if(!checkSandi(kartu) || nasabah[nasabahIndex].isBlocked) {
            cout << endl << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t         Kartu ATM Anda Telah Diblokir.\n";
            cout << "\t\t==============================================\n\n";
            continue;
        };

        system("cls"); //terminal "dibersihkan"
        head(); //menampilkan header dari atm el-kbmn

        string output;

        int transaksiNumber = pilihTransaksi();
        switch (transaksiNumber) {
        case 1:
            output = kalkulasiSaldo(displayMenuDana("penarikan"), 2);
            break;
        case 2:
            output = transferSaldo();
            break;
        case 3:
            int transaksiLainnya = pilihanLainnya();
            switch (transaksiLainnya) {
            case 1:
                cekSaldo();
                break;
            case 2:
                output = gantiPin();
                break;
            case 3:
                output = kalkulasiSaldo(displayMenuDana("untuk disetor "), 3);
                break;
            }
            break;
        }

        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t\t   " << output << endl;
        cout << "\t\t==============================================\n";

        cout << "\t\tApakah ingin melakukan transaksi lagi [y/n]: ";
        cin >> repeat;
        
    } while (repeat == 'y');

    system("pause");
    system("cls");
    head();
    
    cout << "\t\t  " << "Terima Kasih Telah Menggunakan ATM EL-KBMN";
    cout << endl << endl;
    cout << "\t\t==============================================\n";
    cout << "\t\t\t\t" << "PROGRAM BERAKHIR" << endl;
    cout << "\t\t==============================================\n";

    system("pause");
    return 0;
}

void head() {
    cout << endl << endl << endl;
    cout << "\t\t==============================================" << endl;
    cout << "\t\t                 ATM EL-KBMN" << endl;
    cout << "\t\t==============================================" << endl << endl;
}

void updateDatabaseFile() {
    ofstream dbFile("db.txt");

    dbFile << "struct Nasabah {\n";
    dbFile << "    string nama;\n";
    dbFile << "    string kartu;\n";
    dbFile << "    string pin;\n";
    dbFile << "    string noRekening;\n";
    dbFile << "    long saldo;\n";
    dbFile << "    bool isBlocked;\n";
    dbFile << "};\n\n";
    dbFile << "Nasabah nasabah[5] = {\n";

    for (int i = 0; i < totalNasabah; i++) {
        dbFile << "    {\n";
        dbFile << "        \"" << nasabah[i].nama << "\",\n";
        dbFile << "        \"" << nasabah[i].kartu << "\",\n";
        dbFile << "        \"" << nasabah[i].pin << "\",\n";
        dbFile << "        \"" << nasabah[i].noRekening << "\",\n";
        dbFile << "        " << nasabah[i].saldo << ",\n";
        dbFile << "        " << nasabah[i].isBlocked << "\n";
        dbFile << "    }" << (i < totalNasabah - 1 ? "," : "") << "\n";
    }
    dbFile << "};\n";
    dbFile.close();
}

bool checkSandi(int kartu, int count) {
    string sandi;

    system("cls");
    head();
    
    cout << "\t\t\tSilahkan masukkan kata sandi:\n\t\t\t\t    ";
    getline(cin >> ws, sandi);

    bool isValidSandi = false;
    for(int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].pin == sandi && kartuATM[kartu - 1] == nasabah[i].kartu) {
            isValidSandi = true;
            nasabahIndex = i;
        }
    }

    if(!isValidSandi && count < 3) {
        count++;
        
        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t     Sandi yang anda masukkan tidak valid\n";
        cout << "\t\t==============================================\n\n";

        system("pause");
        return checkSandi(kartu, count);
    }
    else if(count == 3 && !isValidSandi) {
        nasabah[nasabahIndex].isBlocked = true;
        updateDatabaseFile();
    }

    return isValidSandi;
}

int pilihTransaksi() {
    int transaksiNumber;
    do
    {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "\t\t1. Tarik Saldo\n\t\t2. Transfer\n\t\t3. Lainya\n";
        cout << "\t\t==============================================\n";

        cout << "\t\tSilahkan pilih transaksi: ";
        if(!(cin >> transaksiNumber) ||transaksiNumber > 3) {
            cout << endl << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  Transaksi yang ada pilih tidak tersedia\n";
            cout << "\t\t==============================================\n";
            system("pause");
        }
        system("cls");
        head();
    } while (transaksiNumber > 3 || cin.fail());

    return transaksiNumber;
}

int displayMenuDana(string jenisTransaksi) {
    int tarikSaldo;
    cout << "\t\t\t1. Rp.50.000 \t2. Rp.100.000 \n\t\t\t3. Rp.500.000 \t4. Rp.1.000.000 \n";
    cout << "\t\t==============================================\n";
    
    cout << "\t\tSilahkan pilih jumlah " << jenisTransaksi << ": ";
    if(!(cin >> tarikSaldo) || tarikSaldo > 4) {
        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t  Pilihan yang anda masukkan tidak tersedia\n";
        cout << "\t\t==============================================\n";

        system("pause");
        system("cls");
        head();

        cin.clear();
        cin.ignore(1000, '\n');
        return displayMenuDana(jenisTransaksi);
    };
    return tarikSaldo - 1;
}

// kalkulasi saldo
// parameter jenisTransaksi untuk jenis transfer yang akan dilakukan
string kalkulasiSaldo(int tarikSaldo, int jenisTransaksi, int noRekIndex) {
    if(!(nasabah[nasabahIndex].saldo >= penarikanDana[tarikSaldo]) && jenisTransaksi != 3) {
        return "Saldo anda tidak mencukupi.";
    }
    
    switch (jenisTransaksi)
    {
    case 1:
        nasabah[noRekIndex].saldo += penarikanDana[tarikSaldo];
    case 2:
        nasabah[nasabahIndex].saldo -= penarikanDana[tarikSaldo];
        break;
    case 3:
        nasabah[nasabahIndex].saldo += penarikanDana[tarikSaldo];
    }
    updateDatabaseFile();
    return "    Transaksi Berhasil.";
}

string transferSaldo() {
    string rekeningTujuan;
    int isValidRekeningIndex = -1;
    
    cout << "\t\t\tMasukkan No Rekening tujuan:\n\t\t\t\t  ";
    getline(cin >> ws, rekeningTujuan);

    if(rekeningTujuan == nasabah[nasabahIndex].noRekening) { 
        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\tAnda tidak bisa melakukan transfer menggunakan\n\t\t\t      No.Rek anda sendiri\n";
        cout << "\t\t==============================================\n";
        
        system("pause");
        system("cls");
        head();
        return transferSaldo();
    }
    
    for (int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].noRekening == rekeningTujuan) {
            isValidRekeningIndex = i;
        }
    }
    if(isValidRekeningIndex >= 0) {
        system("cls");
        head();
        return kalkulasiSaldo(displayMenuDana("untuk ditransfer"), 1, isValidRekeningIndex);
    };

    cout << endl << endl;
    cout << "\t\t==============================================\n";
    cout << "\t\tNo rekening yang anda masukkan tidak tersedia\n\t\t\tpastikan No Rekening sudah benar!\n";
    cout << "\t\t==============================================\n";

    system("pause");
    system("cls");
    head();

    return transferSaldo();
}

int pilihanLainnya() {
    int transaksiNumber;

    do
    {
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "\t\t1. Cek Saldo\n\t\t2. Ganti Sandi\n\t\t3. Setor Tunai\n";
        cout << "\t\t==============================================\n";
        
        cout << "\t\tSilahkan pilih transaksi: ";
        if(!(cin >> transaksiNumber) || transaksiNumber > 3) {
            cout << endl << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  Transaksi yang ada pilih tidak tersedia\n";
            cout << "\t\t==============================================\n";
            system("pause");
        }
        
        system("cls");
        head();
    } while (transaksiNumber > 3 || cin.fail());

    return transaksiNumber;
}

void cekSaldo() {
    cout << "\t\t\tNama: \t\t" << nasabah[nasabahIndex].nama << endl;
    cout << "\t\t\tNO. Rekening: \t" << nasabah[nasabahIndex].noRekening << endl;
    cout << "\t\t\tKartu ATM: \t" << nasabah[nasabahIndex].kartu << endl;
    cout << "\t\t\tSaldo: \t\tRp." << nasabah[nasabahIndex].saldo;
}

string gantiPin() {
    string pinBaru[2];
    string number = "0123456789";
    bool isValidNumber;
    
    do
    {
        cout << "\t\t\t      Masukkan pin baru:\n\t\t\t\t    ";
        getline(cin >> ws, pinBaru[0]);

        if(pinBaru[0].length() != 6) {
            cout << endl << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t          PIN harus berisi 6 angka\n";
            cout << "\t\t==============================================\n";

            system("pause");
            system("cls");
            head();
            continue;
        }
        for(int i = 0; i < pinBaru[0].length(); i ++) {
            isValidNumber = false;
            for(int j = 0; j < number.length(); j++) {
                if(number[j] == pinBaru[0][i]) {
                    isValidNumber = true;
                }
            }
            if(!isValidNumber) {
                cout << endl << endl;
                cout << "\t\t==============================================\n";
                cout << "\t\t           PIN harus berisi angka\n";
                cout << "\t\t==============================================\n";
                
                system("pause");
                system("cls");
                head();
                break;
            }
        }
        if(!isValidNumber) {
            continue;
        }
        
        system("cls");
        head();
        cout << "\t\t\t     Konfirmasi pin baru:\n\t\t\t\t    ";

        getline(cin >> ws, pinBaru[1]);
        if(pinBaru[1] != pinBaru[0]) {
            cout << endl << endl;
            cout << "\t\t==============================================\n";
            cout << "\t\t  PIN yang anda masukkan tidak sesuai\n";
            cout << "\t\t==============================================\n";

            system("pause");
            continue;
        }
        
    } while (pinBaru[0].length() != 6 || !isValidNumber || pinBaru[0] != pinBaru[1]);

    nasabah[nasabahIndex].pin = pinBaru[0];
    updateDatabaseFile();
    
    return "  PIN berhasil diganti.";
};
