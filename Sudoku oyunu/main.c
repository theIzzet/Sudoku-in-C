#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

int board[SIZE][SIZE];

void generate_board() {
    srand(time(NULL));
    int temp[SIZE][SIZE] = {0};  // Geçici matris

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }

    for (int i = 0; i < 22; i++) {
        int row, col, num;
        do {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (temp[row][col] != 0);

                //is_valid fonksiyonu kullanılarak, seçilen sayının o hücreye yerleştirilip yerleştirilemeyeceği kontrol edilir.
                // Sayı geçerliyse (is_valid fonksiyonu 1 döndürür), hücreye sayı
                //yerleştirilir ve temp matrisinde ilgili hücre işaretlenir (temp[row][col] = 1)

          do {
           num = rand() % 9 + 1;  //1 ile 9 arasında rastgele bir sayıyı num değişkenine atar
        } while (!is_valid(row, col, num));

        board[row][col] = num;
        temp[row][col] = 1;
    }
}

void print_board() {
    int i, j;


    printf("\n        | |  1    2    3   |  4    5    6   |  7    8    9  |");
    printf("\n       ------------------------------------------------------");
    for (i = 0; i < SIZE; i++) {
        if (i % 3 == 0) {
            printf("\n       ------------------------------------------------------");
        }
        printf("\n    %d   |", i + 1); // Write row number
        for (j = 0; j < SIZE; j++) {
            if (j % 3 == 0) {
                printf(" |");
            }
            if (board[i][j] != 0) {
                printf(" [%d] ", board[i][j]); // Square numbers enclosed in brackets
            } else {
                printf("  %d  ", board[i][j]);
            }
        }
        printf("|");
    }
    printf("\n       ------------------------------------------------------\n");
}


int is_valid(int row, int col, int num) {  //Eğer num değeri geçerliyse, 1 döndürülür; aksi halde 0 döndürülür.
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) {  //Satir kontrol ediyor
            return 0;
        }
        if (board[row][i] == num) {  //Sutun kontrol eder
            return 0;
        }
    }

    int box_row = (row / 3) * 3; //satir indexini belirlemek icin
    int box_col = (col / 3) * 3;
    for (int i = box_row; i < box_row + 3; i++) {
        for (int j = box_col; j < box_col + 3; j++) {  //Küçük karelerin içerisini dolasmak icin
            if (board[i][j] == num) {
                return 0;
            }
        }
    }
    return 1;
}

int add_number(int row, int col, int num) {
    if (board[row][col] != 0) {
        printf("Burada zaten bir sayi var.\n");
        return 0;
    }
    if (is_valid(row, col, num)) {   //is_valid fonk cagir
        board[row][col] = num;
        return 1;
    } else {
        printf("Gecersiz islem.\n");
        return 0;
    }
}

int delete_number(int row, int col) {
    if (board[row][col] == 0) {
        printf("Burada zaten sayi yok.\n");
        return 0;
    } else {
        board[row][col] = 0;
        return 1;
    }
}

void how_play() {
printf("########################################################################################################################");
printf("Sudoku, 9x9 kareli bir izgara uzerinde oynanan bir sayi bulmaca oyunudur. Oyunun amaci, her bir satir, sutun ve 3x3'luk kucuk kareden olusan bolgelerde 1'den 9'a kadar olan sayilari tekil olarak yerlestirmektir.");
printf(" \nIste Sudoku'nun nasil oynandigina dair temel kurallar:\n");

printf("\n1. Sudoku tahtasi, 9x9 karelik bir izgara seklindedir. Bu izgara, 9 adet 3x3'luk kucuk kareden olusur. Bazi kareler,    baslangicta oyuna dahil edilmis sayilarla doldurulmustur.\n");

printf("\n2. Oyuna baslarken, bos kalan kareleri doldurmaniz gerekmektedir. Her bir karenin, 1 ile 9 arasinda bir sayiyla doldurulmasi gerekmektedir.\n");

printf("\n3. Her bir satirda ve sutunda, 1'den 9'a kadar olan sayilar yalnizca bir kez kullanilmalidir. Ayni sekilde, her bir     3x3'luk kucuk karede de 1'den 9'a kadar olan sayilar yalnizca bir kez kullanilmalidir.\n");

printf("\n4. Oyuna baslarken, bazi kareler zaten doldurulmus olabilir. Bu sayilar, oyuncuya baslangic noktasi olarak sunulur ve  dogru cozum yolunda bir rehberlik saglar.\n");

printf("\n5. Sudoku cozumlemek, mantik ve problem cozme becerileri gerektirir. Her bir kareyi doldururken, o karenin satirinda,   sutununda ve 3x3'luk kucuk karesinde henuz");
printf("kullanilmamis olan bir sayi secmelisiniz.\n");
printf("\n6.Sudoku oyunu,tamamen mantiga dayali bir bulmaca oldugundan,herhangi bir sayiyi atamadan once tahtadaki diger sayilari ve kisitlamalari");
printf(" dikkatlice degerlendirmeniz onemlidir.\n");
printf("\n7. Oyunun amaci, tum kareleri doldurarak her bir sayiyi satirlarda, sutunlarda ve 3x3'luk kucuk karelere tekil olarak   yerlestirmektir.\n");
printf("\nDogru bir sekilde tamamlandiginda, her bir satir, sutun ve kucuk karede 1'den 9'a kadar olan sayilar sadece bir kez bulunacaktir.\n");
printf("\nDevam etmek icin bir tusa basiniz -> ");


}

void save_game() {
    FILE *fp = fopen("sudoku_game.txt", "w");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(fp, "%d ", board[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Oyun kaydedildi.\n");
}

int is_game_completed() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

void play_sudoku() {
    generate_board();
    int choice;
    do {
        print_board();
        printf("MENU\n");
        printf("1-> Sayi Ekle\n");
        printf("2-> Sayi Sil \n");
        printf("3-> Oyun Hakkinda\n");
        printf("4-> Oyunu Kaydet\n");
        printf("0-> Cikis\n\n");
        printf("\nYapmak istediginiz islem -> ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int row, col, num;
                printf("Satir numarasini,sutun numarasini ve eklemek istediginiz sayiyi giriniz:\n");
                scanf("%d %d %d", &row, &col, &num);
                if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE) {
                    row--; // Adjusting row and column to zero-based index
                    col--;
                    if (add_number(row, col, num)) {
                        printf("Istediginiz sayi eklendi.\n");
                    }
                } else {
                    printf("Gecersiz satir ya da sutun.\n");
                }
                break;
            }
            case 2: {
                int row, col;
                printf("Satir ve sutun sayisini giriniz: ");
                scanf("%d %d", &row, &col);
                if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE) {
                    row--; // Adjusting row and column to zero-based index
                    col--;
                    if (delete_number(row, col)) {
                        printf("Sayi silindi.\n");
                    }
                } else {
                    printf("Gecersiz satir ya da sutun.\n");
                }
                break;
            }
            case 3: {
                how_play();
                break;
            }
            case 4: {
                save_game();
                break;
            }
            case 0: {
                printf("Cikiliyor...!\n");
                break;
            }
            default: {
                printf("Gecersiz secim.\n");
                break;
            }
        }

        if (is_game_completed()) {
            printf("Tebrikler! Oyunu basariyla tamamladiniz.\n");
            break;
        }

    } while (choice != 0);
}

int main() {

    play_sudoku();
    return 0;
}

