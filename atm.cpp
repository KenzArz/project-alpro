#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#include "db.txt"

const string endTask = "program berakhir";
const int totalNasabah = 5;
const string kartuATM[4] = {"BCA", "BRI", "BTN", "BNI"};
const int penarikanDana[4] = {50000, 100000, 500000, 1000000};
int nasabahIndex;

// bool checkKartu(int kartu);
void head();
bool checkSandi(int kartu, int count = 1);
int pilihTransaksi();
int displayMenuDana(string jenisTransfer);
string kalkulasiSaldo(int tarikSaldo, int jenisTransfer, int noRekIndex = -1);
string transferSaldo();
int pilihanLainnya();
void cekSaldo();
string gantiPin();

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
        cout << "\t\t   Kartu ATM yang anda masukkan tidak valid\n";
        cout << "\n\t\t\t      " << endTask;
        return 1;
    };    

    // Menjanlankan function checkSandi
    // User memasukkan sandi
    // Program berakhir ketika sandi tidak valid
    if(!checkSandi(kartu) || nasabah[nasabahIndex].isBlocked) {
        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t       Kartu ATM Anda Telah Diblokir.\n";
        cout << "\t\t==============================================\n\n";
        cout << endTask << endl;
        system("pause");
        return 1;
    };

    cout << nasabah[nasabahIndex].isBlocked;
    
    char repeat;
    do
    {
        system("cls");
        head();

        repeat = 0;
        string output;

        int transaksiNumber = pilihTransaksi();
        if(transaksiNumber == 1) {
            output =  kalkulasiSaldo(displayMenuDana("penarikan"), 2);
        }
        else if(transaksiNumber == 2) {
           output =  transferSaldo();
        }
        else if(transaksiNumber == 3) {
            int transaksiLainnya = pilihanLainnya();
            if(transaksiLainnya == 1) {
                cekSaldo();
            }
            else if(transaksiLainnya == 2) {
                output = gantiPin();
            }
            else if(transaksiLainnya == 3) {
                output = kalkulasiSaldo(displayMenuDana("untuk disetor "), 3);
            }
        }

        cout << endl << endl;
        cout << "\t\t==============================================\n";
        cout << "\t\t\t   " << output << endl;
        cout << "\t\t==============================================\n";

        cout << "\t\tApakah ingin melakukan transaksi lagi [y/n]: ";
        cin >> repeat;
        
    } while (repeat == 'y');

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
    if(count == 3 && !isValidSandi) {
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

int displayMenuDana(string jenisTransfer) {
    int tarikSaldo;
    cout << "\t\t\t1. Rp.50.000 \t2. Rp.100.000 \n\t\t\t3. Rp.500.000 \t4. Rp.1.000.000 \n";
    cout << "\t\t==============================================\n";
    
    cout << "\t\tSilahkan pilih jumlah " << jenisTransfer << ": ";
    cin >> tarikSaldo;
    return tarikSaldo - 1;
}

// kalkulasi saldo
// parameter jenisTransfer untuk jenis transfer yang akan dilakukan
// parameter isTransfer berisi 1 atau 0, 0 = dikurang, 1 = ditambah berdasarkan index nasabah yang akan ditransferr
string kalkulasiSaldo(int tarikSaldo, int jenisTransfer, int noRekIndex) {
    if(!(nasabah[nasabahIndex].saldo >= penarikanDana[tarikSaldo]) && jenisTransfer != 3) {
        return "Saldo anda tidak mencukupi.";
    }
    
    switch (jenisTransfer)
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
    cout << endl << endl;
    
    system("cls");
    head();
    if(rekeningTujuan == nasabah[nasabahIndex].noRekening) { 
        cout <<  "Anda tidak bisa melakukan transfer menggunakan no rekening anda sendiri.\n\n";
        return transferSaldo();
    }
    
    for (int i = 0; i < totalNasabah; i++) {
        if(nasabah[i].noRekening == rekeningTujuan) {
            isValidRekeningIndex = i;
        }
    }
    if(isValidRekeningIndex >= 0) return kalkulasiSaldo(displayMenuDana("untuk ditransfer"), 1, isValidRekeningIndex);
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
        cout << "\n\t\t1. Cek Saldo\n\t\t2. Ganti Sandi\n\t\t3. Setor Tunai\n";
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
