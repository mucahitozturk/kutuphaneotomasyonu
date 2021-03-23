#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct kutuphane
{
	int ogrenciNo;
	char adi[25];
	int  kitapNo;
	char kitapAdi[50];
	char kitapAlTar[10];
} *kayit;

void kayitEkle(FILE *);
void kayitSil(FILE *);
FILE *kutup;
void kayitListele(FILE *);
void kayitAra(FILE *);

int main()
{
	char secenek;
	printf("KUTUPHANE OTOMASTON SISTEMI\n");
    printf("1-Kayit Ekle\n");
    printf("2-Kayit Listele\n");
	printf("3-Kayit Sil\n");
	printf("4-Kayit Ara\n");
    printf("5-Cikis\n");
    printf("Hangi Islemi Yapmak Istiyorsun:");
    scanf("%s",&secenek);

    			switch(secenek)
    			{
    			case '1':
    			    kayitEkle(kutup);
    			    break;
    			case '2':
    			    kayitListele(kutup);
                    break;
				case '3':
				    kayitSil(kutup);
                    break;
				case '4':
				    kayitAra(kutup);
                    break;
				case '5':
				exit(0);
    			default:
    			    printf("HATALI TUSLAMA YAPTINIZ");
    			    system("cls");
    			    main();
    			}
		fclose(kutup);
}

void kayitEkle(FILE *kutup) //yeni kayýt fonksiyonu
{
	int ogrenciBilgi;
	struct kutuphane kutBilgi={0,"","",0,"",""};
	kutup =(struct kutBilgi*) calloc(600,sizeof(kutBilgi));//bellekte yer ayýrýldý

	if(kutup==NULL)
    {
            kutup=fopen("kutuphane.txt","w");
    }
	else
	{
	kutup=fopen("kutuphane.txt","r+");
	printf("/////  Ogrenci Numarsini Ekleyin //// \n");
	scanf("%d",&ogrenciBilgi);//ogrenci numarasi aliniyor
	fseek(kutup,(ogrenciBilgi)*sizeof(struct kutuphane),SEEK_SET);//imleci basa getiriyor
	fread(&kutBilgi,sizeof(struct kutuphane),1,kutup);


	if(kutBilgi.ogrenciNo ==ogrenciBilgi){
		printf("%d nolu ogrenci zaten mevcut\n ",ogrenciBilgi);
	}
	else
	{
		printf("--> Uyenin Adini Soyadini Giriniz:\n");
		scanf("%s",kutBilgi.adi);
		printf("--> Alinan Kitabin Numarasini Giriniz:\n");
		scanf("%d",&kutBilgi.kitapNo);
		printf("--> Alinan Kitabin Adini Giriniz:\n");
		scanf("%s",kutBilgi.kitapAdi);
		printf("--> Kitabin Alinma Tarihi Giriniz:\n");
		scanf("%s",kutBilgi.kitapAlTar);
		kutBilgi.ogrenciNo=ogrenciBilgi;
		fseek(kutup,(ogrenciBilgi-1)*sizeof(struct kutuphane),SEEK_SET);
		fwrite(&kutBilgi,sizeof(struct kutuphane),1,kutup);
	}
	}
	fclose(kutup);
	system("cls");
	main();
}
void kayitListele(FILE *kutup)
{
	struct kutuphane kutBilgi = {0,"","",0,"",""};
	char secenek;
	kutup=fopen("kutuphane.txt","r");
	if(kutup==NULL)
	{
		printf("Dosya bulunamadi\n");
	}
	else
	{
		printf("Ogrenci No Adi Soyadi Kitap No Kitap Adi Kitap Alinma Tarihi\n");
		while(!feof(kutup))
		{
			fread(&kutBilgi,sizeof(struct kutuphane),1,kutup);
			if(kutBilgi.ogrenciNo != 0)
			{
				printf("%d |",kutBilgi.ogrenciNo);
				printf("%s |",kutBilgi.adi);
				printf("%d |",kutBilgi.kitapNo);
				printf("%s |",kutBilgi.kitapAdi);
				printf("%s |\n",kutBilgi.kitapAlTar);
			}
		}
	}
	fclose(kutup);
	printf("Baska Islem Yapmak Istermisiniz(E veya H):");
	scanf("%s",&secenek);
	switch(secenek)
	{
		case 'E':
		system("cls");
		main();
		case 'H':
		exit(0);
	}
	getchar();
}
void kayitSil(FILE *kutup)
{
	struct kutuphane kutBilgi, bosOgrenci = {0,"","",0,"",""};
	int ogrenciNo;
	kutup=fopen("kutuphane.txt","r+");
		if(kutup==NULL)
		{
			printf("Dosya bulunamadi\n");
		}
		else
		{
		printf("Silinecek Ogrenci Numarasini Giriniz:");
		scanf("%d",&ogrenciNo);
		fseek(kutup,(ogrenciNo-1)*sizeof(struct kutuphane),SEEK_SET);
		fread(&kutBilgi,sizeof(struct kutuphane),1,kutup);
		if(kutBilgi.ogrenciNo!=0)
			{
			fseek(kutup,(ogrenciNo-1)*sizeof(struct kutuphane),SEEK_SET);
			fwrite(&bosOgrenci,sizeof(struct kutuphane),1,kutup);
			}
		else
		{
			printf("Silmek Istediginiz %d Numarali Ogrenci Bulunamadi",ogrenciNo);
		}
		}
	fclose(kutup);
	main();
}

	void kayitAra(FILE *kutup)
{
    char ogrenciAdi[25];
    int denetleyici = 0;
    char Secim111;
    kutup=fopen("kutuphane.txt","r");
	if (kutup == NULL)
	{
		printf("Dosya bulunamadi!\n");
	}
	else
	{
		system("cls");
		printf("********************************************************************************************************");
		printf("\n\t\t\t\t  KAYIT ARAMA\n");
		printf("********************************************************************************************************\n\n");
		system("cls");
        printf("Aradiginiz ogrencinin adini giriniz:");}
        gets(ogrenciAdi); // scanf ile almýyor burda gets ile alýyor
        printf("\n");
        rewind(kutup);
                while(!feof(kutup))
				{
					if (strcmp(kutup, ogrenciAdi)==0)//Aranan isimle karþýlaþtýrma yaptýrýp doðruysa ekrana yazýdýrýyoruz.
					{
						printf("Ogrenci Bilgileri\n");
						printf("--------------\n");
						printf("Ogrenci Adi:  %s\n", kutup);
						denetleyici = 1;
					}
				}
				if (denetleyici == 0)
				{
					printf("\nBu isimde bir ogrenci kutuphanede kayitli degil!\n\n");
				}

	printf("\n");//Ýþleme devam edip etmeyeceði sorgulandmýþtýr.
	printf("Arama islemine devam etmek icin (A/a) tusuna basiniz\n");
	printf("Menuye donmek icin (M/m) tusuna basiniz \n");
	printf("Cikis  yapmak icin (C/c) tusuna basiniz\n\n");
	printf("Tercihiniz: ");
    scanf("%c", &Secim111); system("cls");
	if (Secim111 == 'a' || Secim111== 'A')
	{
		main();
	}
	/*else if (Secim111 == 'm' || Secim111 == 'M')
	{
		sayac++;
		main();
	}*/
	else if (Secim111 == 'c' || Secim111 == 'C')
	{
		exit(1);
	}
	else
	{
		printf("\nYanlis secim yaptiniz!Lutfen belirtilen tuslari kullaniniz\n");
		exit(1);
	}
}

