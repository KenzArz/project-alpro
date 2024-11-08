#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#include "db.txt"

const string endTask = "program berakhir...";
const int totalNasabah = 5;
const string kartuATM[4] = {"BCA", "BRI", "BTN", "BNI"};
const int penarikanDana[4] = {50000, 100000, 500000, 1000000};
int nasabahIndex;

// bool checkKartu(int kartu);
bool checkSandi(int kartu, string sandi, int count = 1);
int pilihTransaksi();
string kalkulasiSaldo(string jenisTransfer, int isTransfer = -1);
string transferSaldo();
int pilihanLainnya();
void cekSaldo();
void gantiPin();

int main(){
    int kartu;
    string sandi;

    // Welcoming pengguna
    cout << "==============================" << endl;
    cout << "Selamat Datang di ATM EL-KBMN" << endl;
    cout << "==============================" << endl << endl;

    // Memasukkan kartu ATM berdasarkan keinginan user
    cout << "Kartu ATM yang Tersedia di EL-KBMN: " << endl;
    cout << "1. BCA\n2. BRI\n3. BTN\n4. BNI" << endl;
    cout << "Silahkan masukkan kartu ATM anda berdasarkan nomor di atas: ";

    // Program berakhir ketika ATM tidak valid
    if(!(cin >> kartu) || kartu > 4) {
        cout << "\nKartu ATM yang anda masukkan tidak valid\n";
        cout << endTask;
        return 1;
    };

    cout << "Silahkan masukkan kata sandi: ";
    cin >> sandi;
    

    // Program berakhir ketika sandi tidak valid
    if(!checkSandi(kartu, sandi)) {
        cout << "\nSandi yang anda masukkan tidak valid.\n";
        cout << endTask;
        return 1;
    };
    
    int repeat;
    do
    {
        repeat = 0;
        int transaksiNumber = pilihTransaksi();
        if(transaksiNumber == 1) {
            cout << kalkulasiSaldo("penarikan");
        }
        else if(transaksiNumber == 2) {
           cout << transferSaldo();
        }
        else if(transaksiNumber == 3) {
            int transaksiLainnya = pilihanLainnya();
            if(transaksiLainnya == 1) {
                cekSaldo();
            }
            else if(transaksiLainnya == 2) {
                gantiPin();
            }
        }

        cout << "\n1. yes\n2. no\n";
        cout << "Apakah ingin melakukan transaksi lagi?: ";
        cin >> repeat;
        
    } while (repeat == 1);

    return 0;
}

bool checkSandi(int kartu, string sandi, int count) {
    bool isValidSandi = false;
    for(int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].pin == sandi && kartuATM[kartu - 1] == nasabah[i].kartu) {
            isValidSandi = true;
            nasabahIndex = i;
        }
    }
    if(!isValidSandi && count < 3) {
        count++;
        cout << "\nSandi yang anda masukkan tidak valid, coba lagi!: ";
        cin >> sandi;
        return checkSandi(kartu, sandi, count);
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
        cout << "\n1. Tarik Saldo\n2. Transfer\n3. Lainya\n";
        cout << "Silahkan pilih transaksi: ";
        if(!(cin >> transaksiNumber) ||transaksiNumber > 3) {
            cout << "Transaksi yang ada pilih tidak tersedia, coba lagi!\n\n";
        }
    } while (transaksiNumber > 3 || cin.fail());
    return transaksiNumber;
}

bool updateDatabaseFile() {
    ofstream dbFile("db.txt");

    if (!dbFile.is_open()) {
        return false;
    }

    dbFile << "struct Nasabah {\n";
    dbFile << "    string nama;\n";
    dbFile << "    string kartu;\n";
    dbFile << "    string pin;\n";
    dbFile << "    string noRekening;\n";
    dbFile << "    long saldo;\n";
    dbFile << "};\n\n";
    dbFile << "Nasabah nasabah[5] = {\n";

    for (int i = 0; i < totalNasabah; i++) {
        dbFile << "    {\n";
        dbFile << "        \"" << nasabah[i].nama << "\",\n";
        dbFile << "        \"" << nasabah[i].kartu << "\",\n";
        dbFile << "        \"" << nasabah[i].pin << "\",\n";
        dbFile << "        \"" << nasabah[i].noRekening << "\",\n";
        dbFile << "        " << nasabah[i].saldo << "\n";
        dbFile << "    }" << (i < totalNasabah - 1 ? "," : "") << "\n";
    }
    dbFile << "};\n";

    dbFile.close();
    return true;
}

// kalkulasi saldo
// parameter jenisTransfer untuk jenis transfer yang akan dilakukan
// parameter isTransfer berisi 1 atau 0, 0 = dikurang, 1 = ditambah berdasarkan index nasabah yang akan ditransferr
string kalkulasiSaldo(string jenisTransfer, int isTransfer) {
    int tarikSaldo;
    cout << "\n1. Rp.50.000 \t2. Rp.100.000 \n3. Rp.500.000 \t4. Rp.1.000.000 \n";
    
    cout << "Silahkan pilih jumlah " << jenisTransfer << ": ";
    cin >> tarikSaldo;
    if(!(nasabah[nasabahIndex].saldo >= penarikanDana[tarikSaldo - 1])) {
        return "\nSaldo anda tidak mencukupi.\n";
    }
    
    if(isTransfer >= 0) nasabah[isTransfer].saldo += penarikanDana[tarikSaldo - 1];
    nasabah[nasabahIndex].saldo -= penarikanDana[tarikSaldo - 1];

    if (!updateDatabaseFile()) return "\nTransaksi gagal.\n";
    return "\nTransaksi Berhasil.\n";;
}

string transferSaldo() {
    string rekeningTujuan;
    int isValidRekeningIndex = -1;
    cout << "Masukkan No Rekening tujuan: ";
    getline(cin >> ws, rekeningTujuan);
    
    if(rekeningTujuan == nasabah[nasabahIndex].noRekening) { 
        cout <<  "Anda tidak bisa melakukan transfer menggunakan no rekening anda sendiri.\n\n";
        return transferSaldo();
    }
    
    for (int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].noRekening == rekeningTujuan) {
            isValidRekeningIndex = i;
        }
    }
    if(isValidRekeningIndex >= 0) return kalkulasiSaldo("untuk ditransfer", isValidRekeningIndex);
    cout << "No rekening yang anda masukkan tidak tersedia, pastikan No Rekening sudah benar!\n\n";
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
        cout << "\n1. Cek Saldo\n2. Ganti Sandi\n";
        cout << "Silahkan pilih transaksi: ";
        if(!(cin >> transaksiNumber) ||transaksiNumber > 2) {
            cout << "Transaksi yang ada pilih tidak tersedia, coba lagi!\n\n";
        }
    } while (transaksiNumber > 2 || cin.fail());
    return transaksiNumber;
}

void cekSaldo() {
    cout << "\nNama: \t\t" << nasabah[nasabahIndex].nama << endl;
    cout << "NO. Rekening: \t" << nasabah[nasabahIndex].noRekening << endl;
    cout << "Kartu ATM: \t" << nasabah[nasabahIndex].kartu << endl;
    cout << "Saldo: \t\tRp." << nasabah[nasabahIndex].saldo << endl;
}

void gantiPin() {
    string pinBaru[2];
    string number = "0123456789";
    bool isValidNumber;
    do
    {
        cout << "\nMasukkan pin baru: ";
        getline(cin >> ws, pinBaru[0]);
        if(pinBaru[0].length() != 6) {
            cout << "PIN harus berisi 6 angka\n";
            continue;
        }
        for(int i = 0; i < pinBaru[0].length(); i ++) {
            isValidNumber = false;
            for(int j = 0; j < number.length(); j++) {
                if(number[j] == pinBaru[0][i]) {
                    isValidNumber = true;
                }
            }
        }
        if(!isValidNumber) {
            cout << "PIN harus berisi angka\n";
            continue;
        }
        
        cout << "Konfirmasi pin baru: ";
        getline(cin >> ws, pinBaru[1]);
        if(pinBaru[1] != pinBaru[0]) {
            cout << "PIN yang anda masukkan tidak sesuai, coba lagi!\n";
            continue;
        }
        
    } while (pinBaru[0].length() != 6 || !isValidNumber || pinBaru[0] != pinBaru[1]);
    nasabah[nasabahIndex].pin = pinBaru[0];
    if (!updateDatabaseFile()) cout <<  "\nPIN gagal diganti.\n";
    cout <<  "\nPIN berhasil diganti.\n";
    
};