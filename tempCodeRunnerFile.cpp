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