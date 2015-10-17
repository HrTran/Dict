#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct xau_s {
	char tu[100];
	char vitri[20];
	char dodai[20];
} XAU;

char *strrev(char *str){ 			/* reverse a string */    
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

XAU xu_ly_xau(char *str) {			/* break the input into 3 parts */
	XAU xuly;
	int i=0, j=0;
	char str_temp[strlen(str)];
	str = strrev(str);
	strncpy(xuly.dodai, str, 20);
	strcpy(str_temp, str);

	for (i=0; i<20; i++){
		if (xuly.dodai[i] == ' '){
			xuly.dodai[i] = '\0';
			j = i; break;
		}
	}
	strrev(xuly.dodai);

	i=0; while(str_temp[j] == ' ' || str_temp[j] == '\t') j++;

	while (str_temp[j] != '\0' && str_temp[j] != ' ' && str_temp[j] != '\t'){
		xuly.vitri[i] = str_temp[j];
		i++;j++;
	} 
	xuly.vitri[i] = '\0';
	strrev(xuly.vitri);

	i=0; while(str_temp[j] == ' ' || str_temp[j] == '\t') j++;

	while (str_temp[j] != '\0'){
		xuly.tu[i] = str_temp[j];
		i++;j++;	
	} 
	xuly.tu[i] = '\0';
	strrev(xuly.tu);

	return xuly;
}

// int main(){
// 	XAU xaubatky;
// 	char str[100] = "Vu Tuan Dat 		ICT58   	 sds";
// 	xaubatky = xu_ly_xau(str);
// 	printf("%s.\n%s.\n%s.\n", xaubatky.tu, xaubatky.vitri, xaubatky.dodai);
// 	return 0;
// }

int lay_chiso (char ch, char *str) {
	int i=0;
	for (i=0; i<strlen(str); i++){
		if (ch == str[i]) return i;
	}
}

long luy_thua (int chiso, int luythua){
	long ketqua=1;
	while (luythua != 0){
		ketqua*=64;
		luythua--;
	}
	return chiso*ketqua;
}

long change_base_10(char *str) {
	char SAMPLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	long ketqua=0;
	long sohang=0;
	int i, n=strlen(str);
	strrev(str);
	for (i=0; i<n; i++){
		sohang = luy_thua(lay_chiso(str[i], SAMPLE), i);
		ketqua += sohang;
	}
	return ketqua;
}

// int main(){
// 	char str[] = "kbpP";
// 	printf("%li\n", change_base_10(str));
// 	return 0;
// }