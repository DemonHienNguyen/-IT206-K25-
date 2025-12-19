#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_QUESTIONS 10
#define QUESTIONS_TO_PLAY 5

// Khai bao struct Question
typedef struct {
    char question[256];
    char options[4][100];
    char correctAnswer; // 'A', 'B', 'C', 'D'
} Question;

// Ham hien thi cau hoi
void askQuestion(Question q, int *score) {
    char answer;
    printf("\n%s\n", q.question);
    printf("A. %s\n", q.options[0]);
    printf("B. %s\n", q.options[1]);
    printf("C. %s\n", q.options[2]);
    printf("D. %s\n", q.options[3]);
    printf("Nhap dap an (A-D): ");
    scanf(" %c", &answer);

    if (answer == q.correctAnswer) {
        printf("Dung roi!\n");
        (*score)++;
    } else {
        printf("Sai roi! Dap an dung la %c\n", q.correctAnswer);
    }
}

int main() {
    srand(time(NULL));
    char playerName[50];
    int score = 0;

    // Nhap ten nguoi choi
    printf("Nhap ten cua ban: ");
    fgets(playerName, sizeof(playerName), stdin);
    playerName[strcspn(playerName, "\n")] = 0; // Xoa ky tu xuong dong

    // Danh sach cau hoi
    Question questions[TOTAL_QUESTIONS] = {
        {"Thu do cua Viet Nam la gi?", {"Ha Noi", "Ho Chi Minh", "Da Nang", "Hue"}, 'A'},
        {"Ngon ngu nao dung de viet he dieu hanh Linux?", {"Python", "C", "Java", "Pascal"}, 'B'},
        {"Ai la nguoi phat minh ra dien?", {"Newton", "Einstein", "Edison", "Faraday"}, 'D'},
        {"Song nao dai nhat the gioi?", {"Amazon", "Nile", "Mekong", "Yangtze"}, 'B'},
        {"Trai dat quay quanh gi?", {"Mat troi", "Mat trang", "Sao Hoa", "Sao Kim"}, 'A'},
        {"Quoc gia dong dan nhat the gioi?", {"An Do", "Trung Quoc", "My", "Nga"}, 'B'},
        {"Ngon ngu nao pho bien nhat the gioi?", {"Tieng Anh", "Tieng Trung", "Tieng Tay Ban Nha", "Tieng Phap"}, 'B'},
        {"Ai la tac gia Truyen Kieu?", {"Nguyen Du", "Nguyen Trai", "Xuan Dieu", "To Huu"}, 'A'},
        {"He dieu hanh Windows do cong ty nao phat trien?", {"Apple", "Google", "Microsoft", "IBM"}, 'C'},
        {"So Pi xap xi bang?", {"3.14", "2.71", "1.41", "1.61"}, 'A'}
    };

    // Chon ngau nhien 5 cau hoi
    int chosen[QUESTIONS_TO_PLAY];
    for (int i = 0; i < QUESTIONS_TO_PLAY; i++) {
        int r;
        do {
            r = rand() % TOTAL_QUESTIONS;
            int duplicate = 0;
            for (int j = 0; j < i; j++) {
                if (chosen[j] == r) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) {
                chosen[i] = r;
                break;
            }
        } while (1);
    }

    // Hien thi cau hoi va tinh diem
    printf("\n===== Quiz Game =====\n");
    for (int i = 0; i < QUESTIONS_TO_PLAY; i++) {
        askQuestion(questions[chosen[i]], &score);
    }

    // Ket qua
    printf("\n%s, ban dat %d/%d diem.\n", playerName, score, QUESTIONS_TO_PLAY);

    // Luu vao file
    FILE *f = fopen("quiz_results.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s: %d/%d\n", playerName, score, QUESTIONS_TO_PLAY);
        fclose(f);
    } else {
        printf("Khong the mo file de luu ket qua.\n");
    }

    // Hien thi bang xep hang
    printf("\n===== Bang xep hang =====\n");
    f = fopen("quiz_results.txt", "r");
    if (f != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);
        }
        fclose(f);
    } else {
        printf("Khong the mo file de doc ket qua.\n");
    }

    return 0;
}
