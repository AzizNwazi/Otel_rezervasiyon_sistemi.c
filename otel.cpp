#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ODA_SAYISI 100

typedef struct{ // Müþteri bilgileri
	char *musteriAdi;
	char *musteriSoyadi;
	
	
}musteriBilgileri; 


typedef struct{ // Tarih bilgileri
	int gun;
	int ay;
	int yil;
	
}tarihBilgileri;

typedef struct{ // Oda bilgileri
	int kisiSayisi;
	int odaDurumu;// doluysa 1, boþsa 0
	int odaNumarasi; // 1- 100 arasi
	double fiyatBilgisi;
	
	musteriBilgileri musteri;
	tarihBilgileri girisTarihi;
	tarihBilgileri cikisTarihi;
	
}odaBilgileri;


typedef enum{ // Yetki seviyeleri
	musteri=0,personel=1
	
}yetkiSeviyeleri;


// Fonksiyon prototipleri

int gunFarkiHesapla(tarihBilgileri girisTarihi,tarihBilgileri cikisTarihi){
	
	if(girisTarihi.gun>cikisTarihi.gun){
		cikisTarihi.ay-=1;
		cikisTarihi.gun+=30;
	}
	if(girisTarihi.ay>girisTarihi.ay){
		cikisTarihi.yil-=1;
		cikisTarihi.ay+=12;
	}
	tarihBilgileri tarihFarki;
	tarihFarki.gun=cikisTarihi.gun-girisTarihi.gun;
	tarihFarki.ay=cikisTarihi.ay-girisTarihi.ay;
	tarihFarki.yil=cikisTarihi.yil-girisTarihi.yil;
	
	int gunFarki=tarihFarki.yil*360+tarihFarki.ay*30+tarihFarki.gun;
	return gunFarki;
	
	
}

double fiyatHesaplama(odaBilgileri *odalar,int odaNumarasi){
	
	int gunFarki=gunFarkiHesapla(odalar[odaNumarasi-1].girisTarihi,odalar[odaNumarasi-1].cikisTarihi);
	
	printf("kalacaginiz gun sayisi:%d\n",gunFarki);
	return gunFarki*150*odalar[odaNumarasi-1].kisiSayisi;
	
}



void rezervasyonTemizle(odaBilgileri *odalar,int odaNumarasi){
	odalar[odaNumarasi-1].odaDurumu=0;
	free(odalar[odaNumarasi-1].musteri.musteriAdi);
	free(odalar[odaNumarasi-1].musteri.musteriSoyadi);
	
	printf("%d. odanizin bilgileri temizlendi cikis/iptal islemi tamamlandi. \n",odaNumarasi);
}

void doluOdaBilgileriYazdirma(odaBilgileri *odalar){
	int i;
	for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu!=0){
			printf("------------------------------------------------------\n"
			       "Oda Numarasi: %d\n"
				   "Musteri Adi-Soyadi: %s %s\n"
				   "Kisi Sayisi: %d\n"
				   "Fiyat Bilgisi: %.2lf\n"
				   "Giris Tarihi: %d:%d:%d\n"
				   "Cikis Tarihi: %d:%d:%d\n"
				   ,odalar[i].odaNumarasi
				   ,odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi
				   ,odalar[i].kisiSayisi
				   ,odalar[i].fiyatBilgisi
				   ,odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil
				   ,odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);
		}
	}
	
	
	
}




void yeniMusteriEkleme (odaBilgileri *odalar){
	char musteriAdi[20],   musteriSoyadi[20],   ch;
	int sorgulanacakOda;
	
	printf("lutfen kayit olmak istediginiz odayi giriniz:");
	scanf("%d",&sorgulanacakOda);
	
	if(odalar[sorgulanacakOda-1].odaDurumu!=0){
		printf("Maalesef kayit yaptirmak istediginz oda %d %d %d tarihine kadare doludur.\n"
		, odalar[sorgulanacakOda-1].cikisTarihi.gun
		, odalar[sorgulanacakOda-1].cikisTarihi.ay
		, odalar[sorgulanacakOda-1].cikisTarihi.yil);
		return ;
	}
	odalar[sorgulanacakOda-1].odaNumarasi=sorgulanacakOda;// oda numarasý atandý
	
	printf("lutfen AD ve SOYAD bilgilerini giriniz:");
	scanf("%s %s",&musteriAdi,&musteriSoyadi);
	
	odalar[sorgulanacakOda-1].musteri.musteriAdi=(char*)malloc(sizeof(char)*strlen(musteriAdi)+1);
	odalar[sorgulanacakOda-1].musteri.musteriSoyadi=(char*)malloc(sizeof(char)*strlen(musteriSoyadi)+1);
	
	strcpy(odalar[sorgulanacakOda-1].musteri.musteriAdi,musteriAdi);
	strcpy(odalar[sorgulanacakOda-1].musteri.musteriSoyadi,musteriSoyadi);
	
	printf("lutfen kac kisi olacaginizi giriniz:");
	scanf("%d",&odalar[sorgulanacakOda-1].kisiSayisi);
	
	printf("lutfen giris tarihi bilgisini giriniz gun:ay:yil  :");
	scanf("%d:%d:%d"
	,&odalar[sorgulanacakOda-1].girisTarihi.gun
	,&odalar[sorgulanacakOda-1].girisTarihi.ay
	,&odalar[sorgulanacakOda-1].girisTarihi.yil);
	
	printf("lutfen cikis tarihi bilgisini giriniz gun:ay:yil  :");
	scanf("%d:%d:%d"
	,&odalar[sorgulanacakOda-1].cikisTarihi.gun
	,&odalar[sorgulanacakOda-1].cikisTarihi.ay
	,&odalar[sorgulanacakOda-1].cikisTarihi.yil);
	
	odalar[sorgulanacakOda-1].fiyatBilgisi=fiyatHesaplama(odalar,sorgulanacakOda);
	printf("odemeniz gereken tutar %.2lf\n",odalar[sorgulanacakOda-1].fiyatBilgisi);
	printf("onayliyor musunuz?(e - h)");
	fflush(stdin);
	ch=getchar();
	if(ch=='h'){
		rezervasyonTemizle(odalar,sorgulanacakOda);
		return ;
	}
	printf("%d. oda kayit isleminiz gerceklesti.\n",sorgulanacakOda);
	odalar[sorgulanacakOda-1].odaDurumu=1;//yeni odaniz doldu
}

void odaBilgisiSorgulama(odaBilgileri *odalar,int odaNumarasi){
	if(odalar[odaNumarasi-1].odaDurumu!=0){
		printf("\n%d nolu oda %d:%d:%d tarihine kadar doludur.\n"
		,odaNumarasi
		,odalar[odaNumarasi-1].cikisTarihi.gun
		,odalar[odaNumarasi-1].cikisTarihi.ay
		,odalar[odaNumarasi-1].cikisTarihi.yil);
	}
	else{
		printf("\n%d numarali oda suan bos durumdadir.\n",odaNumarasi);
	}
	
}

void fiyatBilgisiYazdirma(){
	
	int kisiSayisi;
	double toplamTutar=0.0;
	tarihBilgileri girisTarihi,cikisTarihi;
	
	printf("lutfen kac kisi olacaginizi giriniz:");
	scanf("%d",&kisiSayisi);
	
	printf("lutfen giris tarihi bilgisini giriniz gun:ay:yil  :");
	scanf("%d:%d:%d",&girisTarihi.gun, &girisTarihi.ay, &girisTarihi.yil);
	
	printf("lutfen cikis tarihi bilgisini giriniz gun:ay:yil  :");
	scanf("%d:%d:%d",&cikisTarihi.gun, &cikisTarihi.ay, &cikisTarihi.yil);
	
	toplamTutar=gunFarkiHesapla(girisTarihi,cikisTarihi)*150*kisiSayisi;// 1 günlük bir kiþinin ücreti
	printf("Odemeniz gereken tutar: %.2lf\n",toplamTutar);
	
}

void yedekKayitAlma(odaBilgileri *odalar){
	int i;
	FILE *otelKayitlari=fopen("otelKayitlari.txt","a");
	if(otelKayitlari==NULL){
		fprintf(stderr,"yedek kayit alinirken bir hala olustu.");
		exit(1);
	}
	for(i=0;i<ODA_SAYISI;i++){
		if(odalar[i].odaDurumu!=0){
			fprintf(otelKayitlari,"------------------------------------------------------\n");
			fprintf(otelKayitlari,"Oda Numarasi: %d\n",odalar[i].odaNumarasi);
			fprintf(otelKayitlari,"Musteri Adi-Soyadi: %s %s\n",odalar[i].musteri.musteriAdi,odalar[i].musteri.musteriSoyadi);
			fprintf(otelKayitlari,"Kisi Sayisi: %d\n",odalar[i].kisiSayisi);
			fprintf(otelKayitlari,"Fiyat Bilgisi: %.2lf\n",odalar[i].fiyatBilgisi);
			fprintf(otelKayitlari,"Giris Tarihi: %d:%d:%d\n",odalar[i].girisTarihi.gun,odalar[i].girisTarihi.ay,odalar[i].girisTarihi.yil);
			fprintf(otelKayitlari,"Cikis Tarihi: %d:%d:%d\n",odalar[i].cikisTarihi.gun,odalar[i].cikisTarihi.ay,odalar[i].cikisTarihi.yil);
		}
	}
	fclose(otelKayitlari);
}

// Oda dizisini dinamik olarak oluþtur

int main(){
	int belirlenenSifre=123,kullaniciSifre , odaNumarasi;
	yetkiSeviyeleri kullaniciYetkisi;
	odaBilgileri *odaDizisi;
	odaDizisi=(odaBilgileri*)calloc(ODA_SAYISI,sizeof(odaBilgileri));// dinamik þekilde oluþturduk
	
	printf("\t\t\t Otel rezervasyon sistemine hos geldiniz.\n");
	printf("Lutfen burada calisyorsaniz sifreyi giriniz:");
	scanf("%d",&kullaniciSifre);
	
	char ch;

	// Kullanýcý yetkisini belirle
	if(kullaniciSifre==belirlenenSifre){
		kullaniciYetkisi=personel;
	}else{
		kullaniciYetkisi=musteri;
	}
	do{
		printf("\n"
		       "1.Yeni musteri girisi yapmak \n"
		       "2.Oda bilgisi goruntulemek \n"
			   "3.Dolu oda bilgilerini goruntulemek \n"
			   "4.Fiyat sorgusu yapmak \n"
			   "5.Musteri cikis islemi gerceklestirmek \n"
			   "6.Sistemden cikis yapmak \n"
			   "\n");
			   getchar();
			   ch=getchar();
			   switch(ch){
			   	
			   	case '1':
			   		if(kullaniciYetkisi==personel){
			   			yeniMusteriEkleme(odaDizisi);
					   }else {
					   	printf("\nBu alan sadece calisanlar tarafindan kullanilabilir.\n");
					   }
			   		break;
			
			   	case '2':
			   		printf("Lutfen sorgulancak olan odanin numarasini giriniz: ");
			   		scanf("%d",&odaNumarasi);
			   		odaBilgisiSorgulama(odaDizisi,odaNumarasi);
			   		break;
			   		
			   		
			   	case '3':
			   		if(kullaniciYetkisi==personel){
			   			doluOdaBilgileriYazdirma(odaDizisi);
					   }else {
					   	printf("\nBu alan sadece calisanlar tarafindan kullanilabilir.\n");
					   }
			   		break;
			   		
			   		
			   	case '4':
			   		fiyatBilgisiYazdirma();
			   		break;
			   		
			   		
			   	case '5':
			   		if(kullaniciYetkisi==personel){
			   			printf("Cikis yapmak istediginiz oda numarasini giriniz:");
			   			scanf("%d",&odaNumarasi);
			   			rezervasyonTemizle(odaDizisi,odaNumarasi);
					   }else {
					   	printf("\nBu alan sadece calisanlar tarafindan kullanilabilir.\n");
					   }
			   		break;
			   		
			   		
			   	case '6':
			   		yedekKayitAlma(odaDizisi);
			   		break;
			   		
			   		
			   	default:
			   		printf("Gecersiz secim!\n");
			   		break;
		}
	}while(ch!='6');
	
	
	return 0;
}




