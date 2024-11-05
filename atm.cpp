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
bool checkSandi(int kartu, string sandi, int count=1);
int pilihTransaksi();
int penarikanSaldo();

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
            penarikanSaldo();
        }
        else if(transaksiNumber == 2) {

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

void updateDatabaseFile() {
    ofstream dbFile("db.cpp");  // Membuka file db.cpp untuk ditulis ulang

    if (!dbFile.is_open()) {
        cerr << "Error: Program tidak dapat memperbaharui data\n";
        return;
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
}

int penarikanSaldo() {
    int tarikSaldo;
    cout << "\n1. Rp.50.000 \t2. Rp.100.000 \n3. Rp.500.000 \t4. Rp.1.000.000 \n";
    
    cout << "Silahkan pilih jumlah penarikkan: ";
    cin >> tarikSaldo;

    if(!(nasabah[nasabahIndex].saldo >= penarikanDana[tarikSaldo - 1])) {
        cout << "\nSaldo anda tidak mencukupi.\n";
        return 1;
    }
    nasabah[nasabahIndex].saldo -= penarikanDana[tarikSaldo - 1];
    updateDatabaseFile();
    cout << "\nTransaksi Berhasil.\n";
    return 0;
}