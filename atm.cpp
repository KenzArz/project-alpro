#include <iostream>
#include <string>
using namespace std;
#include "db.cpp"

const string endTask = "program berakhir...";
const int totalNasabah = 5;
const string kartuATM[4] = {"BCA", "BRI", "BTN", "BJB"};
const int penarikanDana[4] = {50000, 100000, 500000, 1000000};
Nasabah biodata_nasabah;

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
    cout << "BCA (1)\nBRI (2)\nBTN (3)\nBJB (4)" << endl;
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
        cout << "\nSandi yang anda masukkan tidak valid\n";
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

        cout << "\nyes (1)\nno (0)\n";
        cout << "Apakah ingin melakukan transaksi lagi?: ";
        if(!(cin >> repeat)) {

        }

    } while (repeat == 1);

    return 0;
}

bool checkSandi(int kartu, string sandi, int count) {
    bool isValidSandi = false;
    for(int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].pin == sandi && kartuATM[kartu - 1] == nasabah[i].kartu) {
            isValidSandi = true;
            biodata_nasabah = nasabah[i];
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
        cout << "\nTarik Saldo (1)\nTransfer (2)\nLainya (3)\n";
        cout << "Silahkan pilih transaksi: ";
        if(!(cin >> transaksiNumber) ||transaksiNumber > 3) {
            cout << "Transaksi yang ada pilih tidak tersedia, coba lagi!\n\n";
        }
    } while (transaksiNumber > 3 || cin.fail());
    return transaksiNumber;
}

int penarikanSaldo() {
    int tarikSaldo;
    cout << "\nRp.50.000 (1) \tRp.100.000 (2)\nRp.500.000 (3) \tRp.1.000.000 (4)\n";
    cout << "Silahkan pilih jumlah penarikkan: ";
    cin >> tarikSaldo;

    if(!(biodata_nasabah.saldo >= penarikanDana[tarikSaldo - 1])) {
        cout << "Saldo anda tidak mencukupi.";
        return 1;
    }
    cout <<  "\nSaldo sebelum ditarik: " << biodata_nasabah.saldo << endl;
    biodata_nasabah.saldo -= penarikanDana[tarikSaldo - 1];
    cout << "Saldo sesudah ditarik: " << biodata_nasabah.saldo << endl;
    return 0;
    
}