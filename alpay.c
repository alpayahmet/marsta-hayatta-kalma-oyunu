#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>



int saglik, enerji, oksijen;
int su, yedekParca, modulHasari;
int kilitMuhurlu = 0;

int gun = 1;
int tur = 0;

int oyunBitti = 0;
int kazanildi = 0;
int cikisYapildi = 0;

int firtinaSuresi;
int firtinaHasari;
int kesifEsigi;
int yaralanmaEsigi;

char komut;
char zorluk;



void sinirlariKontrolEt() {

    if (saglik < 0) saglik = 0;
    if (saglik > 100) saglik = 100;

    if (enerji < 0) enerji = 0;
    if (enerji > 100) enerji = 100;

    if (oksijen < 0) oksijen = 0;
    if (oksijen > 100) oksijen = 100;

    if (modulHasari < 0) modulHasari = 0;
    if (modulHasari > 100) modulHasari = 100;

    if (su < 0) su = 0;
    if (yedekParca < 0) yedekParca = 0;
}



void oyunSonuKontrol() {

    sinirlariKontrolEt();

    if (saglik <= 0 || oksijen <= 0) {
        oyunBitti = 1;
        kazanildi = 0;
        printf("\nHAYAT DESTEK SISTEMI BASARISIZ!\n");
    }

    if (gun >= 15 && oyunBitti == 0) {
        oyunBitti = 1;
        kazanildi = 1;
        printf("\nKURTARMA EKIBI MARS'A ULASTI!\n");
    }
}



void durumRaporu() {

    printf("\n========== DURUM RAPORU ==========\n");

    printf("Gun          : %d\n", gun);
    printf("Tur          : %d\n", tur);
    printf("Saglik       : %d\n", saglik);
    printf("Enerji       : %d\n", enerji);
    printf("Oksijen      : %d\n", oksijen);
    printf("Su           : %d\n", su);
    printf("Yedek Parca  : %d\n", yedekParca);
    printf("Modul Hasari : %d\n", modulHasari);

    printf("Hava Kilidi  : %s\n",
           kilitMuhurlu ? "Muhurlu" : "Acik");

    printf("\nKRITIK UYARILAR:\n");

    if (oksijen < 25)
        printf("UYARI: Oksijen kritik!\n");

    if (saglik < 30)
        printf("UYARI: Saglik kritik!\n");

    if (enerji < 20)
        printf("UYARI: Enerji kritik!\n");

    if (su < 10)
        printf("UYARI: Su kritik!\n");

    if (modulHasari > 70)
        printf("UYARI: Modul hasari kritik!\n");

    if (oksijen >= 25 && saglik >= 30 &&
        enerji >= 20 && su >= 10 &&
        modulHasari <= 70) {

        printf("TUM SISTEMLER NORMAL.\n");
    }

    printf("==================================\n");
}



void zamanIlerle() {

    tur++;

    printf("\nTur: %d\n", tur);

    if (tur % 3 == 0) {

        gun++;

        printf("\nYENI GUN: %d\n", gun);

        oksijen -= 8;

        printf("Gun basinda 8 oksijen tuketildi.\n");

        if (modulHasari > 70) {
            saglik -= 5;
            printf("Modul hasari nedeniyle 5 saglik kaybedildi.\n");
        }
    }

    sinirlariKontrolEt();
    oyunSonuKontrol();
}



void zorlukSecimi() {

    do {

        printf("\n========== ZORLUK ==========\n");
        printf("K - Kolay\n");
        printf("N - Normal\n");
        printf("Z - Zor\n");
        printf("Seciminiz: ");

        scanf(" %c", &zorluk);
        zorluk = toupper((unsigned char)zorluk);

        switch (zorluk) {

            case 'K':

                saglik = 100;
                enerji = 100;
                oksijen = 100;
                su = 60;
                yedekParca = 8;
                modulHasari = 0;

                firtinaSuresi = 3;
                firtinaHasari = 5;
                kesifEsigi = 60;
                yaralanmaEsigi = 10;

                break;

            case 'N':

                saglik = 90;
                enerji = 90;
                oksijen = 90;
                su = 40;
                yedekParca = 5;
                modulHasari = 10;

                firtinaSuresi = 5;
                firtinaHasari = 10;
                kesifEsigi = 45;
                yaralanmaEsigi = 20;

                break;

            case 'Z':

                saglik = 75;
                enerji = 80;
                oksijen = 80;
                su = 25;
                yedekParca = 3;
                modulHasari = 20;

                firtinaSuresi = 7;
                firtinaHasari = 15;
                kesifEsigi = 30;
                yaralanmaEsigi = 35;

                break;

            default:

                printf("Gecersiz zorluk! Tekrar giriniz.\n");
                break;
        }

    } while (zorluk != 'K' &&
             zorluk != 'N' &&
             zorluk != 'Z');

}



int kesif() {

    int zar, esik;

    if (enerji < 15 || oksijen < 10) {
        printf("Kesif icin yeterli kaynak yok!\n");
        return 0;
    }

    enerji -= 15;
    oksijen -= 10;

    if (enerji > 40 && oksijen > 30)
        esik = kesifEsigi;
    else
        esik = kesifEsigi / 2;

    zar = rand() % 100;

    printf("Zar: %d / Esik: %d -> ", zar, esik);

    if (zar < esik) {

        su += 10;
        printf("10 birim su bulundu!\n");

    }
    else if (zar < esik + 20) {

        yedekParca++;
        printf("1 yedek parca bulundu!\n");

    }
    else {

        printf("Kesif basarisiz!\n");
    }

    zar = rand() % 100;

    printf("Yaralanma zari: %d / Esik: %d -> ",
           zar, yaralanmaEsigi);

    if (zar < yaralanmaEsigi || modulHasari > 70) {

        saglik -= 10;
        printf("10 saglik kaybedildi!\n");

    }
    else {

        printf("Yaralanma yok.\n");
    }

    return 1;
}



int oksijenUret() {

    int miktar;
    int kullanilanSu;
    int uretilenOksijen;

    printf("Kullanilacak su miktari: ");
    scanf("%d", &miktar);

    if (miktar <= 0 || miktar > su) {
        printf("Gecersiz su miktari!\n");
        return 0;
    }

    if (enerji < 5) {
        printf("Yeterli enerji yok!\n");
        return 0;
    }

    kullanilanSu = miktar - (miktar % 2);

    if (kullanilanSu == 0) {
        printf("En az 2 birim su gereklidir!\n");
        return 0;
    }

    uretilenOksijen = (kullanilanSu / 2) * 3;

    if (oksijen + uretilenOksijen > 100) {
        printf("Oksijen kapasitesi yetersiz!\n");
        return 0;
    }

    su -= kullanilanSu;
    oksijen += uretilenOksijen;
    enerji -= 5;

    printf("%d su harcandi.\n", kullanilanSu);
    printf("%d oksijen uretildi.\n", uretilenOksijen);

    return 1;
}



int tamir() {

    if (yedekParca <= 0) {
        printf("Yedek parca yok!\n");
        return 0;
    }

    if (enerji < 15) {
        printf("Tamir icin enerji yetersiz!\n");
        return 0;
    }

    if (modulHasari == 0) {
        printf("Modul zaten saglam!\n");
        return 0;
    }

    if (modulHasari <= 30) {

        modulHasari -= 15;
        yedekParca--;
        enerji -= 15;

        printf("Hafif hasar onarildi.\n");
    }

    else if (modulHasari <= 70) {

        if (yedekParca < 2) {
            printf("Orta hasar icin 2 parca gerekli!\n");
            return 0;
        }

        modulHasari -= 20;
        yedekParca -= 2;
        enerji -= 15;

        printf("Orta hasar onarildi.\n");
    }

    else {

        if (yedekParca < 2) {
            printf("Agir hasar icin 2 parca gerekli!\n");
            return 0;
        }

        modulHasari -= 30;
        yedekParca -= 2;
        enerji -= 15;

        printf("Agir hasar onarildi.\n");
    }

    return 1;
}



int dinlen() {

    if (enerji < 5) {
        printf("Dinlenmek icin enerji yetersiz!\n");
        return 0;
    }

    enerji += 25;
    oksijen -= 5;

    if (oksijen >= 20) {

        if (saglik < 100) {
            saglik += 10;
        }

        printf("Saglik ve enerji yenilendi.\n");
    }

    else {

        saglik -= 10;
        printf("Oksijen dusuk! Saglik kaybedildi.\n");
    }

    return 1;
}



int kumFirtinasi() {

    int zar;
    int hasar;
    int toplamSaglik = 0;
    int toplamOksijen = 0;
    int hasarliTur = 0;

    if (enerji < 10) {
        printf("Firtina icin enerji yetersiz!\n");
        return 0;
    }

    enerji -= 10;

    printf("\nKUM FIRTINASI BASLADI!\n");

    int i;

for (i = 1; i <= firtinaSuresi; i++) {

        printf("\nFirtina turu: %d\n", i);

        zar = rand() % 100;

        printf("Zar: %d / Esik: 25 -> ", zar);

        if (kilitMuhurlu == 1 &&
            zar >= 25 && zar < 50) {

            printf("Kilit muhurlu, sizinti engellendi!\n");
            continue;
        }

        if (zar < 25) {

            saglik -= 10;
            toplamSaglik += 10;
            hasarliTur++;

            printf("10 saglik kaybedildi.\n");
        }

        else if (zar < 50) {

            oksijen -= 10;
            toplamOksijen += 10;
            hasarliTur++;

            printf("10 oksijen kaybedildi.\n");
        }

        else if (zar < 75) {

            hasar = firtinaHasari;

            if (i % 2 == 0) {
                hasar *= 2;
                printf("Cift tur! Hasar iki katina cikti.\n");
            }

            modulHasari += hasar;
            hasarliTur++;

            printf("%d modul hasari olustu.\n", hasar);
        }

        else {

            printf("Firtinadan korunuldu.\n");
        }

        sinirlariKontrolEt();

        if (saglik <= 0 || oksijen <= 0) {
            printf("Kritik durum! Firtina durduruldu.\n");
            break;
        }
    }

    printf("\n========== FIRTINA OZETI ==========\n");
    printf("Hasarli tur sayisi: %d\n", hasarliTur);
    printf("Kaybedilen saglik: %d\n", toplamSaglik);
    printf("Kaybedilen oksijen: %d\n", toplamOksijen);
    printf("===================================\n");

    return 1;
}



int havaKilidi() {

    char sifre;
    char giris;
    int deneme = 0;

    if (kilitMuhurlu == 1) {
        printf("Hava kilidi zaten muhurlu!\n");
        return 0;
    }

    if (enerji < 15) {
        printf("Sifre sistemi icin enerji yetersiz!\n");
        return 0;
    }

    sifre = 'A' + (gun % 26);

    printf("\nHAVA KILIDI SIFRE SISTEMI\n");
    printf("Ipucu: A harfinden bugunun gun sayisi kadar ilerle.\n");

    do {

        printf("Sifreyi giriniz: ");
        scanf(" %c", &giris);

        giris = toupper((unsigned char)giris);

        deneme++;

        if (giris != sifre) {

            enerji -= 5;

            if (giris < sifre)
                printf("Ileri git!\n");
            else
                printf("Geri git!\n");
        }

        else {

            kilitMuhurlu = 1;
            printf("Hava kilidi basariyla muhurlendi!\n");
        }

    } while (giris != sifre && deneme < 3);

    if (kilitMuhurlu == 0) {

        modulHasari += 20;
        printf("Uc deneme basarisiz! Modul hasari artti.\n");
    }

    return 1;
}



void sonucRaporu() {

    int puan;

    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n========================================\n");
    printf("       MARS KOLONISI SONUC RAPORU\n");
    printf("========================================\n");

    if (kazanildi)
        printf("SONUC: KAZANDINIZ! KURTARMA EKIBI GELDI.\n");

    else if (cikisYapildi)
        printf("SONUC: OYUNDAN CIKIS YAPTINIZ.\n");

    else
        printf("SONUC: KAYBETTINIZ.\n");

    printf("----------------------------------------\n");

    printf("Gun             : %d\n", gun);
    printf("Toplam Tur      : %d\n", tur);
    printf("Saglik          : %d\n", saglik);
    printf("Enerji          : %d\n", enerji);
    printf("Oksijen         : %d\n", oksijen);
    printf("Su              : %d\n", su);
    printf("Yedek Parca     : %d\n", yedekParca);
    printf("Modul Hasari    : %d\n", modulHasari);
    printf("Hava Kilidi     : %s\n",
           kilitMuhurlu ? "Muhurlu" : "Acik");

    printf("----------------------------------------\n");
    printf("PUAN: %d\n", puan);
    printf("========================================\n");
}



int main() {

    int komutBasarili;

    srand(time(NULL));

    printf("========================================\n");
    printf("   MARS KOLONISI YASAM DESTEK SIMULATORU\n");
    printf("========================================\n");

    printf("Mars'ta tek basinasiniz.\n");
    printf("Kurtarma ekibi gelene kadar 15 gun hayatta kalin!\n");

    zorlukSecimi();

    printf("\nBaslangic degerleri yuklendi.\n");

    durumRaporu();

    do {

        if (oyunBitti)
            break;

        printf("\n========================================\n");
        printf("Gun: %d | Tur: %d\n", gun, tur);
        printf("========================================\n");

        printf("G - Kesif\n");
        printf("O - Oksijen uret\n");
        printf("T - Tamir\n");
        printf("D - Durum raporu\n");
        printf("U - Dinlen\n");
        printf("K - Kum firtinasi\n");
        printf("H - Hava kilidi sifresi\n");
        printf("Q - Cikis\n");

        printf("\nKomut: ");
        scanf(" %c", &komut);

        komut = toupper((unsigned char)komut);

        komutBasarili = 0;

        switch (komut) {

            case 'G':
            case 'g':

                komutBasarili = kesif();
                break;

            case 'O':
            case 'o':

                komutBasarili = oksijenUret();
                break;

            case 'T':
            case 't':

                komutBasarili = tamir();
                break;

            case 'D':
            case 'd':

                durumRaporu();
                break;

            case 'U':
            case 'u':

                komutBasarili = dinlen();
                break;

            case 'K':
            case 'k':

                komutBasarili = kumFirtinasi();
                break;

            case 'H':
            case 'h':

                komutBasarili = havaKilidi();
                break;

            case 'Q':
            case 'q':

                cikisYapildi = 1;
                oyunBitti = 1;

                printf("Simulasyondan cikiliyor...\n");
                break;

            default:

                printf("Gecersiz komut! Tur harcanmadi.\n");
                break;
        }

        if (komutBasarili == 1) {

            sinirlariKontrolEt();

            oyunSonuKontrol();

            if (!oyunBitti) {
                zamanIlerle();
            }
        }

    } while (!oyunBitti);

    sonucRaporu();

    return 0;
}
