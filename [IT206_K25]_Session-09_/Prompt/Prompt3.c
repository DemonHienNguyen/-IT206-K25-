// ============================================
// CHUONG TRINH QUIZ GAME - PROMPT3.C (TOI UU)
// ============================================
// Cac cai tien:
// - Tranh lap code
// - Dung ham thay cho code viet truc tiep trong main
// - Dat ten bien ro rang
// - Chuan hoa style code C
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================
// KHAI BAO HANG SO
// ============================================
#define TOTAL_QUESTIONS 15
#define QUESTIONS_TO_PLAY 5
#define MAX_NAME_LENGTH 50
#define MAX_QUESTION_LENGTH 256
#define MAX_OPTION_LENGTH 100
#define MAX_LINE_LENGTH 100
#define RESULT_FILE "quiz_results.txt"
#define NUM_OPTIONS 4

// ============================================
// KHAI BAO STRUCT
// ============================================
typedef struct {
    char question[MAX_QUESTION_LENGTH];
    char options[NUM_OPTIONS][MAX_OPTION_LENGTH];
    char correct_answer;
} Question;

// ============================================
// KHAI BAO HAM (FUNCTION PROTOTYPES)
// ============================================
void init_random_seed(void);
void init_questions(Question questions[]);
void get_player_name(char player_name[]);
int is_duplicate(const int chosen[], int count, int value);
void select_random_questions(const int total_questions, int chosen[], int num_to_select);
void display_question(const Question *q);
char get_user_answer(void);
int check_answer(char user_answer, char correct_answer);
void play_quiz(const Question questions[], const int chosen[], int *score);
void display_result(const char player_name[], int score);
int save_result_to_file(const char player_name[], int score);
void display_leaderboard(void);
void print_separator(const char *title);

// ============================================
// HAM MAIN
// ============================================
int main(void) {
    Question questions[TOTAL_QUESTIONS];
    int chosen_questions[QUESTIONS_TO_PLAY];
    char player_name[MAX_NAME_LENGTH];
    int score = 0;
    
    // Khoi tao
    init_random_seed();
    init_questions(questions);
    get_player_name(player_name);
    
    // Chon cau hoi ngau nhien
    select_random_questions(TOTAL_QUESTIONS, chosen_questions, QUESTIONS_TO_PLAY);
    
    // Choi quiz
    print_separator("Quiz Game");
    play_quiz(questions, chosen_questions, &score);
    
    // Hien thi ket qua
    display_result(player_name, score);
    
    // Luu ket qua vao file
    save_result_to_file(player_name, score);
    
    // Hien thi bang xep hang
    display_leaderboard();
    
    return 0;
}

// ============================================
// DINH NGHIA CAC HAM
// ============================================

/**
 * Khoi tao bo sinh so ngau nhien bang thoi gian hien tai
 */
void init_random_seed(void) {
    srand((unsigned int)time(NULL));
}

/**
 * Khoi tao danh sach cau hoi
 * @param questions Mang luu danh sach cau hoi
 */
void init_questions(Question questions[]) {
    Question question_list[TOTAL_QUESTIONS] = {
        {"Thu do cua Viet Nam la gi?", 
         {"Ha Noi", "Ho Chi Minh", "Da Nang", "Hue"}, 
         'A'},
        {"Ngon ngu nao dung de viet he dieu hanh Linux?", 
         {"Python", "C", "Java", "Pascal"}, 
         'B'},
        {"Ai la nguoi phat minh ra dien?", 
         {"Newton", "Einstein", "Edison", "Faraday"}, 
         'D'},
        {"Song nao dai nhat the gioi?", 
         {"Amazon", "Nile", "Mekong", "Yangtze"}, 
         'B'},
        {"Trai dat quay quanh gi?", 
         {"Mat troi", "Mat trang", "Sao Hoa", "Sao Kim"}, 
         'A'},
        {"Quoc gia dong dan nhat the gioi?", 
         {"An Do", "Trung Quoc", "My", "Nga"}, 
         'B'},
        {"Ngon ngu nao pho bien nhat the gioi?", 
         {"Tieng Anh", "Tieng Trung", "Tieng Tay Ban Nha", "Tieng Phap"}, 
         'B'},
        {"Ai la tac gia Truyen Kieu?", 
         {"Nguyen Du", "Nguyen Trai", "Xuan Dieu", "To Huu"}, 
         'A'},
        {"He dieu hanh Windows do cong ty nao phat trien?", 
         {"Apple", "Google", "Microsoft", "IBM"}, 
         'C'},
        {"So Pi xap xi bang?", 
         {"3.14", "2.71", "1.41", "1.61"}, 
         'A'},
        {"Thu do cua nuoc My la gi?", 
         {"New York", "Los Angeles", "Washington D.C.", "Chicago"}, 
         'C'},
        {"Ngon ngu lap trinh Python duoc phat minh vao nam nao?", 
         {"1989", "1995", "2000", "2005"}, 
         'A'},
        {"Hanh tinh nao gan mat troi nhat?", 
         {"Sao Thuy", "Sao Kim", "Trai Dat", "Sao Hoa"}, 
         'A'},
        {"Bien nao lon nhat the gioi?", 
         {"Thai Binh Duong", "Dai Tay Duong", "An Do Duong", "Bac Bang Duong"}, 
         'A'},
        {"Ngon ngu lap trinh C duoc phat trien boi ai?", 
         {"Dennis Ritchie", "Bjarne Stroustrup", "James Gosling", "Guido van Rossum"}, 
         'A'}
    };
    
    // Sao chep vao mang questions
    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        questions[i] = question_list[i];
    }
}

/**
 * Nhap ten nguoi choi tu ban phim
 * @param player_name Mang ky tu de luu ten
 */
void get_player_name(char player_name[]) {
    printf("Nhap ten cua ban: ");
    fgets(player_name, MAX_NAME_LENGTH, stdin);
    // Xoa ky tu xuong dong '\n' neu co
    player_name[strcspn(player_name, "\n")] = '\0';
}

/**
 * Kiem tra xem mot gia tri da ton tai trong mang chua
 * @param chosen Mang chua cac gia tri da chon
 * @param count So luong phan tu da co trong mang
 * @param value Gia tri can kiem tra
 * @return 1 neu trung, 0 neu khong trung
 */
int is_duplicate(const int chosen[], int count, int value) {
    for (int i = 0; i < count; i++) {
        if (chosen[i] == value) {
            return 1;  // Trung lap
        }
    }
    return 0;  // Khong trung
}

/**
 * Chon ngau nhien cac cau hoi khong trung nhau
 * @param total_questions Tong so cau hoi co san
 * @param chosen Mang luu chi so cau hoi duoc chon
 * @param num_to_select So luong cau hoi can chon
 */
void select_random_questions(const int total_questions, int chosen[], int num_to_select) {
    for (int i = 0; i < num_to_select; i++) {
        int random_index;
        do {
            random_index = rand() % total_questions;
        } while (is_duplicate(chosen, i, random_index));
        
        chosen[i] = random_index;
    }
}

/**
 * Hien thi cau hoi va cac lua chon ra man hinh
 * @param q Con tro den cau hoi can hien thi
 */
void display_question(const Question *q) {
    printf("\n%s\n", q->question);
    for (int i = 0; i < NUM_OPTIONS; i++) {
        printf("%c. %s\n", 'A' + i, q->options[i]);
    }
}

/**
 * Nhan dap an tu nguoi choi
 * @return Ky tu dap an ('A', 'B', 'C', hoac 'D')
 */
char get_user_answer(void) {
    char answer;
    printf("Nhap dap an (A-D): ");
    scanf(" %c", &answer);
    return answer;
}

/**
 * Kiem tra dap an cua nguoi choi
 * @param user_answer Dap an nguoi choi nhap
 * @param correct_answer Dap an dung
 * @return 1 neu dung, 0 neu sai
 */
int check_answer(char user_answer, char correct_answer) {
    if (user_answer == correct_answer) {
        printf("Dung roi!\n");
        return 1;
    } else {
        printf("Sai roi! Dap an dung la %c\n", correct_answer);
        return 0;
    }
}

/**
 * Chay tro choi quiz
 * @param questions Mang chua tat ca cau hoi
 * @param chosen Mang chi so cau hoi duoc chon
 * @param score Con tro den bien diem so
 */
void play_quiz(const Question questions[], const int chosen[], int *score) {
    for (int i = 0; i < QUESTIONS_TO_PLAY; i++) {
        int question_index = chosen[i];
        display_question(&questions[question_index]);
        
        char user_answer = get_user_answer();
        if (check_answer(user_answer, questions[question_index].correct_answer)) {
            (*score)++;
        }
    }
}

/**
 * Hien thi ket qua cua nguoi choi
 * @param player_name Ten nguoi choi
 * @param score Diem so dat duoc
 */
void display_result(const char player_name[], int score) {
    printf("\n%s, ban dat %d/%d diem.\n", player_name, score, QUESTIONS_TO_PLAY);
}

/**
 * Luu ket qua vao file
 * @param player_name Ten nguoi choi
 * @param score Diem so dat duoc
 * @return 1 neu thanh cong, 0 neu that bai
 */
int save_result_to_file(const char player_name[], int score) {
    FILE *file = fopen(RESULT_FILE, "a");
    
    if (file == NULL) {
        printf("Khong the mo file de luu ket qua.\n");
        return 0;
    }
    
    fprintf(file, "%s: %d/%d\n", player_name, score, QUESTIONS_TO_PLAY);
    fclose(file);
    return 1;
}

/**
 * Hien thi bang xep hang tu file
 */
void display_leaderboard(void) {
    print_separator("Bang xep hang");
    
    FILE *file = fopen(RESULT_FILE, "r");
    
    if (file == NULL) {
        printf("Khong the mo file de doc ket qua.\n");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    
    fclose(file);
}

/**
 * Hien thi tieu de co ke gach ngan
 * @param title Tieu de can hien thi
 */
void print_separator(const char *title) {
    printf("\n===== %s =====\n", title);
}

