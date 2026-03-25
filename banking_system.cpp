#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Hesap {
    string isim;
    string sifre;
    double bakiye;
};

void menuGoster() {
    cout << "\n=== BANKA SISTEMI ===" << endl;
    cout << "1. Hesap Olustur" << endl;
    cout << "2. Giris Yap" << endl;
    cout << "3. Para Yatir" << endl;
    cout << "4. Para Cek" << endl;
    cout << "5. Bakiye Sorgula" << endl;
    cout << "6. Cikis" << endl;
    cout << "Seciminiz: ";
}

void hesapOlustur(Hesap hesaplar[], int &hesapSayisi) {
    if(hesapSayisi >= 10) {
        cout << "Maksimum hesap sayisina ulasildi!" << endl;
        return;
    }
    cout << "\n=== HESAP OLUSTUR ===" << endl;
    cout << "Isim: ";
    cin >> hesaplar[hesapSayisi].isim;
    cout << "Sifre: ";
    cin >> hesaplar[hesapSayisi].sifre;
    cout << "Baslangic bakiyesi: ";
    cin >> hesaplar[hesapSayisi].bakiye;
    hesapSayisi++;
    cout << "Hesap basariyla olusturuldu!" << endl;
}

int girisYap(Hesap hesaplar[], int hesapSayisi) {
    string isim, sifre;
    cout << "\n=== GIRIS YAP ===" << endl;
    cout << "Isim: ";
    cin >> isim;
    cout << "Sifre: ";
    cin >> sifre;
    for(int i = 0; i < hesapSayisi; i++) {
        if(hesaplar[i].isim == isim && hesaplar[i].sifre == sifre) {
            cout << "Giris basarili! Hosgeldin " << isim << endl;
            return i;
        }
    }
    cout << "Hatali isim veya sifre!" << endl;
    return -1;
}

void paraYatir(Hesap hesaplar[], int hesapSayisi) {
    int index = girisYap(hesaplar, hesapSayisi);
    if(index == -1) return;
    double miktar;
    cout << "Yatirmak istediginiz miktar: ";
    cin >> miktar;
    if(miktar <= 0) {
        cout << "Gecersiz miktar!" << endl;
        return;
    }
    hesaplar[index].bakiye += miktar;
    cout << miktar << " TL yatirildi. Yeni bakiye: " << hesaplar[index].bakiye << " TL" << endl;
}

void paraCek(Hesap hesaplar[], int hesapSayisi) {
    int index = girisYap(hesaplar, hesapSayisi);
    if(index == -1) return;

    cout << "\n1. Belirli bir miktar cek" << endl;
    cout << "2. Tum parayi cek" << endl;
    cout << "Seciminiz: ";

    int secim;
    cin >> secim;

    if(secim == 1) {
        double miktar;
        cout << "Cekmek istediginiz miktar: ";
        cin >> miktar;
        if(miktar <= 0) {
            cout << "Gecersiz miktar!" << endl;
            return;
        }
        if(miktar > hesaplar[index].bakiye) {
            cout << "Yetersiz bakiye!" << endl;
            return;
        }
        hesaplar[index].bakiye -= miktar;
        cout << miktar << " TL cekildi. Yeni bakiye: " << hesaplar[index].bakiye << " TL" << endl;

    } else if(secim == 2) {
        double tumBakiye = hesaplar[index].bakiye;
        if(tumBakiye <= 0) {
            cout << "Hesabinizda para bulunmuyor!" << endl;
            return;
        }
        hesaplar[index].bakiye = 0;
        cout << tumBakiye << " TL cekildi. Bakiyeniz sifirlandi." << endl;

    } else {
        cout << "Gecersiz secim!" << endl;
    }
}

void bakiyeSorgula(Hesap hesaplar[], int hesapSayisi) {
    int index = girisYap(hesaplar, hesapSayisi);
    if(index == -1) return;
    cout << "Bakiyeniz: " << hesaplar[index].bakiye << " TL" << endl;
}

void dosyayaKaydet(Hesap hesaplar[], int hesapSayisi) {
    ofstream dosya("hesaplar.txt");
    for(int i = 0; i < hesapSayisi; i++) {
        dosya << hesaplar[i].isim << endl;
        dosya << hesaplar[i].sifre << endl;
        dosya << hesaplar[i].bakiye << endl;
    }
    dosya.close();
    cout << "Veriler kaydedildi!" << endl;
}

void dosyadanYukle(Hesap hesaplar[], int &hesapSayisi) {
    ifstream dosya("hesaplar.txt");
    if(!dosya) {
        cout << "Kayitli veri bulunamadi." << endl;
        return;
    }
    hesapSayisi = 0;
    while(dosya >> hesaplar[hesapSayisi].isim
               >> hesaplar[hesapSayisi].sifre
               >> hesaplar[hesapSayisi].bakiye) {
        hesapSayisi++;
    }
    dosya.close();
    cout << "Veriler yuklendi! " << hesapSayisi << " hesap bulundu." << endl;
}

int main() {
    Hesap hesaplar[10];
    int hesapSayisi = 0;
    int secim;

    dosyadanYukle(hesaplar, hesapSayisi);

    do {
        menuGoster();
        cin >> secim;

        switch(secim) {
            case 1:
                hesapOlustur(hesaplar, hesapSayisi);
                dosyayaKaydet(hesaplar, hesapSayisi);
                break;
            case 2:
                girisYap(hesaplar, hesapSayisi);
                break;
            case 3:
                paraYatir(hesaplar, hesapSayisi);
                dosyayaKaydet(hesaplar, hesapSayisi);
                break;
            case 4:
                paraCek(hesaplar, hesapSayisi);
                dosyayaKaydet(hesaplar, hesapSayisi);
                break;
            case 5:
                bakiyeSorgula(hesaplar, hesapSayisi);
                break;
            case 6:
                cout << "Cikiliyor..." << endl;
                break;
            default:
                cout << "Gecersiz secim!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                break;
        }
    } while(secim != 6);

    return 0;
}
