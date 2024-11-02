#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 5

struct Barang
{
    char no[3];
    char nama[25];
    int harga;
};

struct Pembelian
{
    char no[3];
    int jumlah;
};

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void tampilkanMenu(struct Barang items[], int maxItems)
{
    clearScreen();
    printf("Selamat datang di Toko Skensa\n");
    printf("Silahkan pilih barang yang Anda inginkan:\n");
    printf("-----------------------------------------\n");
    printf("| %-4s| %-15s| %-15s|\n", "No", "Nama Barang", "Harga");
    printf("-----------------------------------------\n");

    int i;
    for (i = 0; i < maxItems; i++)
    {
        printf("| %-4s| %-15s| Rp.%-12d|\n", items[i].no, items[i].nama, items[i].harga);
    }

    printf("-----------------------------------------\n");
    printf("11. Input Barang\n");
    printf("99. Struk Pembayaran\n");
    printf("55. Reset Pilihan\n");
    printf("00. Keluar\n");
    printf("-----------------------------------------\n");
    printf("Inputkan pilihan yang anda inginkan : ");
}

void swap(struct Pembelian *a, struct Pembelian *b){
    struct Pembelian temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(struct Pembelian arr[], int n){
    int i, j;
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(arr[j].jumlah < arr[j+1].jumlah){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int main()
{
    struct Barang items[MAX_ITEMS] = {
        {"1", "Buku Tulis", 5000},
        {"2", "Pensil", 2000},
        {"3", "Penghapus", 1000},
        {"4", "Penggaris", 1000},
        {"5", "Bujur Sangkar", 500}};

    int pilihan;

    struct Pembelian keranjang[MAX_ITEMS];
    int jumlah;
    int jumlahItemDiKeranjang = 0;
    char tambahLagi;
    char noBarang[3];

    int uangBayar, totalBayar, totalDiskon, totalHarga, kembalian;

    time_t strukId = time(0);
    
    char tgl[30];
    time_t y = time(0);
    strncpy(tgl, ctime(&y), 29);
    tgl[29] = '\n';

    while (1)
    {
        tampilkanMenu(items, MAX_ITEMS);
        scanf("%d", &pilihan);
        fflush(stdin);

        switch (pilihan)
        {
        case 11:
            do
            {
                printf("\nMasukkan no barang : ");
                fgets(noBarang, 3, stdin);
                fflush(stdin);

                noBarang[strcspn(noBarang, "\n")] = 0;
                printf("Masukkan jumlah : ");
                scanf("%d", &jumlah);
                fflush(stdin);

                int i;
                int found = 0;
                for (i = 0; i < jumlahItemDiKeranjang; i++)
                {
                    if (strcmp(keranjang[i].no, noBarang) == 0)
                    {
                        keranjang[i].jumlah += jumlah;
                        found = 1;
                        break;
                    }
                }

                if (!found)
                {
                    for (i = 0; i < MAX_ITEMS; i++)
                    {
                        if (strcmp(items[i].no, noBarang) == 0)
                        {
                            struct Pembelian pembelian;
                            strcpy(pembelian.no, noBarang);
                            pembelian.jumlah = jumlah;
                            keranjang[jumlahItemDiKeranjang++] = pembelian;
                            found = 1;
                            break;
                        }
                    }

                    if (!found)
                    {
                        printf("\nBarang tidak tersedia");
                        getchar();
                        getchar();
                    }
                }
                printf("Ingin tambah lagi? (Y/n) ");
                tambahLagi = getchar();
                fflush(stdin);

            } while (tambahLagi == 'Y' || tambahLagi == 'y');
            break;
        case 99:
            clearScreen();
            
            bubbleSort(keranjang, jumlahItemDiKeranjang);
            
            printf("Toko SKENSA\n;");
            printf("Jl. HOS Cokroaminoto No. 84, Denpasar\n");
            printf("Bali\n");
            printf("Telp : 0816285791\n");
            printf("ID Struk :  %d\n", strukId);
            printf("==============================================================================\n");
            printf("%-20s%-15s%-15s%-10s\n", "Nama Barang", "Harga", "Total", "Diskon");
            printf("==============================================================================\n");

            int i;
            for (i = 0; i < jumlahItemDiKeranjang; i++)
            {
                int hargaItem = 0, diskonItem = 0, jumlahItem = keranjang[i].jumlah;

                char namaJumlahBarang[30];

                int j;
                for (j = 0; j < MAX_ITEMS; j++)
                {
                    if (strcmp(keranjang[i].no, items[j].no) == 0)
                    {
                        hargaItem = items[j].harga * jumlahItem;

                        if (jumlahItem > 5)
                        {
                            diskonItem = hargaItem * 15 / 100;
                        }
                        else if (jumlahItem > 3)
                        {
                            diskonItem = hargaItem * 10 / 100;
                        }

                        sprintf(namaJumlahBarang, "%d x %s", jumlahItem, items[j].nama);

                        printf("%-20s%-15d%-15d%-10d\n", namaJumlahBarang, items[j].harga, hargaItem, diskonItem);
                        break;
                    }
                }
                totalHarga += hargaItem;
                totalDiskon += diskonItem;
            }

            totalBayar = totalHarga - totalDiskon;
            printf("==============================================================================\n");
            printf("Total Harga  = Rp.%d,-\n", totalHarga);
            printf("Total Diskon = Rp.%d,-\n", totalDiskon);
            printf("Total Bayar  = Rp.%d,-\n", totalBayar);
            printf("==============================================================================\n");
            printf("Masukkan uang bayar: ");
            scanf("%d", &uangBayar);

            if (uangBayar < totalBayar)
            {
                printf("\nMaaf uanh anda kurang !!");
                getchar();
            }
            else
            {
                kembalian = uangBayar - totalBayar;
                printf("Kembalian : Rp.%d,-\n", kembalian);
                printf("=============================================================================");

                char filename[50];

                time_t now;
                struct tm *tm_now;

                time(&now);
                tm_now = localtime(&now);

                strftime(filename, sizeof(filename), "struk_%Y%m%d_%H%M%S.txt", tm_now);

                FILE *fp = fopen(filename, "w");
                if (fp == NULL)
                {
                    printf("Gagal membuat struk");
                }

                fprintf(fp, "Toko SKENSA\n");
                fprintf(fp, "Jl. HOS Cokroaminoto No. 84, Denpasar\n");
                fprintf(fp, "Bali\n");
                fprintf(fp, "Telp : 0816285791\n");
                fprintf(fp, "ID Struk :  %d\n", strukId);
                fprintf(fp, "==============================================================================\n");
                fprintf(fp, "%-20s%-15s%-15s%-10s\n", "Nama Barang", "Harga", "Total", "Diskon");
                fprintf(fp, "==============================================================================\n");

                int k;
                for (k = 0; k < jumlahItemDiKeranjang; k++)
                {
                    int hargaItem = 0, diskonItem = 0, jumlahItem = keranjang[k].jumlah;

                    char namaJumlahBarang[30];

                    int m;
                    for (m = 0; m < MAX_ITEMS; m++)
                    {
                        if (strcmp(keranjang[k].no, items[m].no) == 0)
                        {
                            hargaItem = items[m].harga * jumlahItem;

                            if (jumlahItem > 5)
                            {
                                diskonItem = hargaItem * 15 / 100;
                            }
                            else if (jumlahItem > 3)
                            {
                                diskonItem = hargaItem * 10 / 100;
                            }

                            sprintf(namaJumlahBarang, "%d x %s", jumlahItem, items[m].nama);

                            fprintf(fp, "%-20s%-15d%-15d%-10d\n", namaJumlahBarang, items[m].harga, hargaItem, diskonItem);
                            break;
                        }
                    }
                }

                fprintf(fp, "==============================================================================\n");
                fprintf(fp, "Total Harga  = Rp.%d,-\n", totalHarga);
                fprintf(fp, "Total Diskon = Rp.%d,-\n", totalDiskon);
                fprintf(fp, "Total Bayar  = Rp.%d,-\n", totalBayar);
                fprintf(fp, "==============================================================================\n");
                fprintf(fp, "Uang Bayar  = Rp.%d,-\n", uangBayar);
                fprintf(fp, "Kembalian = Rp.%d,-\n", kembalian);
                
                fprintf(fp, "==============================================================================\n");
                fprintf(fp, "Waktu/Tgl : %s", tgl);
                fprintf(fp, "==============================================================================\n");

                fclose(fp);
                
                printf("%s berhasil dibuat", filename);
                
                totalBayar = 0;
                totalHarga = 0;
                totalDiskon = 0;
                jumlahItemDiKeranjang = 0;
            }
            getchar();
            getchar();
            break;
            case 55:
             totalBayar = 0;
                totalHarga = 0;
                totalDiskon = 0;
                jumlahItemDiKeranjang = 0;
            break;
        }
    }
    return 0;
}l
