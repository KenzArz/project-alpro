#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#include "db.cpp"

const string endTask = "program berakhir...";
const int totalNasabah = 5;
const string kartuATM[4] = {"BCA", "BRI", "BTN", "BJB"};
const int penarikanDana[4] = {50000, 100000, 500000, 1000000};
int nasabahIndex;

// bool checkKartu(int kartu);
bool checkSandi(int kartu, string sandi, int count = 1);
int pilihTransaksi();
string kalkulasiSaldo(string jenisTransfer, int kalkulasi);
string transferSaldo();

int main(){
    int kartu;
    string sandi;

    // Welcoming pengguna
    cout << "==============================" << endl;
    cout << "Selamat Datang di ATM EL-KBMN" << endl;
    cout << "==============================" << endl << endl;

    // Memasukkan kartu ATM berdasarkan keinginan user
    cout << "Kartu ATM yang Tersedia di EL-KBMN: " << endl;
    cout << "1. BCA\n2. BRI\n3. BTN\n4. BJB" << endl;
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
            cout << kalkulasiSaldo("penarikan", 0);
        }
        else if(transaksiNumber == 2) {
           transferSaldo();
        }
        else if(transaksiNumber == 3) {
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
    ofstream dbFile("db.cpp");

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
    
    if(isTransfer) nasabah[isTransfer].saldo += penarikanDana[tarikSaldo - 1];
    nasabah[nasabahIndex].saldo -= penarikanDana[tarikSaldo - 1];

    if (!updateDatabaseFile()) return "\nTransaksi gagal.\n";
    return "\nTransaksi Berhasil.\n";;
}

string transferSaldo() {
    string rekeningTujuan;
    string message;
    cout << "Masukkan No Rekening tujuan: ";
    getline(cin >> ws, rekeningTujuan);
    
    
    for (int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].noRekening == rekeningTujuan) {
            message = kalkulasiSaldo("untuk ditransfer", i);
        }
    }
    return message;
}