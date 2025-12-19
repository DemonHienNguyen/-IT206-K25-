// ============================================
// CHUONG TRINH QUIZ GAME - PROMPT2.C
// ============================================
// Chuong trinh tro choi trac nghiem voi cac tinh nang:
// - Co it nhat 10 cau hoi trong kho
// - Chon ngau nhien 5 cau de choi
// - Nhap ten nguoi choi
// - Luu ten va diem vao file text
// ============================================

#include <stdio.h>      // Thu vien cho cac ham nhap/xuat: printf, scanf, fgets, FILE
#include <stdlib.h>     // Thu vien cho cac ham tien ich: rand, srand, malloc
#include <string.h>     // Thu vien cho cac ham xu ly chuoi: strcspn, strlen
#include <time.h>       // Thu vien cho ham time() de khoi tao so ngau nhien

#define TOTAL_QUESTIONS 15  // So luong cau hoi toi da trong kho (it nhat 10, o day la 15)
#define QUESTIONS_TO_PLAY 5 // So cau hoi se duoc chon ngau nhien de choi

// ============================================
// KHAI BAO STRUCT QUESTION
// ============================================
// Struct nay dung de luu tru thong tin cua mot cau hoi trac nghiem
typedef struct {
    char question[256];        // Mang ky tu luu cau hoi (toi da 255 ky tu + ky tu ket thuc)
    char options[4][100];      // Mang 2 chieu luu 4 lua chon A, B, C, D (moi lua chon toi da 99 ky tu)
    char correctAnswer;        // Ky tu luu dap an dung ('A', 'B', 'C', hoac 'D')
} Question;

// ============================================
// HAM HIEN THI CAU HOI VA NHAN DAP AN
// ============================================
// Tham so:
//   q: Bien kieu Question chua thong tin cau hoi
//   score: Con tro den bien diem so (dung de tang diem khi tra loi dung)
void askQuestion(Question q, int *score) {
    char answer;  // Bien luu dap an nguoi choi nhap vao
    
    // Hien thi cau hoi ra man hinh
    printf("\n%s\n", q.question);
    
    // Hien thi 4 lua chon A, B, C, D
    printf("A. %s\n", q.options[0]);  // Hien thi lua chon A (phan tu dau tien trong mang)
    printf("B. %s\n", q.options[1]);  // Hien thi lua chon B (phan tu thu hai)
    printf("C. %s\n", q.options[2]);  // Hien thi lua chon C (phan tu thu ba)
    printf("D. %s\n", q.options[3]);  // Hien thi lua chon D (phan tu thu tu)
    
    // Yeu cau nguoi choi nhap dap an
    printf("Nhap dap an (A-D): ");
    // Doc mot ky tu tu ban phim (dau cach truoc %c de bo qua ky tu xuong dong con lai)
    scanf(" %c", &answer);
    
    // Kiem tra dap an
    if (answer == q.correctAnswer) {  // Neu dap an dung
        printf("Dung roi!\n");       // Hien thi thong bao dung
        (*score)++;                   // Tang diem len 1 (dung con tro de thay doi bien score trong main)
    } else {                          // Neu dap an sai
        printf("Sai roi! Dap an dung la %c\n", q.correctAnswer);  // Hien thi dap an dung
    }
}

// ============================================
// HAM MAIN - HAM CHINH CUA CHUONG TRINH
// ============================================
int main() {
    // Khoi tao bo sinh so ngau nhien bang thoi gian hien tai
    // time(NULL) tra ve so giay tu 1/1/1970 den hien tai
    srand(time(NULL));
    
    char playerName[50];  // Mang ky tu luu ten nguoi choi (toi da 49 ky tu + ky tu ket thuc)
    int score = 0;        // Bien luu diem so cua nguoi choi (khoi tao = 0)
    
    // ============================================
    // NHAP TEN NGUOI CHOI
    // ============================================
    printf("Nhap ten cua ban: ");  // Hien thi thong bao yeu cau nhap ten
    // Doc chuoi ky tu tu ban phim (bao gom ca dau cach) va luu vao playerName
    // sizeof(playerName) la kich thuoc toi da co the doc (50 ky tu)
    fgets(playerName, sizeof(playerName), stdin);
    // Xoa ky tu xuong dong '\n' o cuoi chuoi (neu co)
    // strcspn tra ve vi tri cua ky tu '\n' trong chuoi, neu khong co tra ve do dai chuoi
    playerName[strcspn(playerName, "\n")] = 0;
    
    // ============================================
    // KHOI TAO DANH SACH CAU HOI
    // ============================================
    // Mang questions chua TOTAL_QUESTIONS cau hoi (15 cau)
    Question questions[TOTAL_QUESTIONS] = {
        // Cau hoi 1: Ve thu do Viet Nam
        {"Thu do cua Viet Nam la gi?", 
         {"Ha Noi", "Ho Chi Minh", "Da Nang", "Hue"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 2: Ve ngon ngu lap trinh Linux
        {"Ngon ngu nao dung de viet he dieu hanh Linux?", 
         {"Python", "C", "Java", "Pascal"}, 
         'B'},  // Dap an dung la B
        
        // Cau hoi 3: Ve nguoi phat minh ra dien
        {"Ai la nguoi phat minh ra dien?", 
         {"Newton", "Einstein", "Edison", "Faraday"}, 
         'D'},  // Dap an dung la D
        
        // Cau hoi 4: Ve con song dai nhat
        {"Song nao dai nhat the gioi?", 
         {"Amazon", "Nile", "Mekong", "Yangtze"}, 
         'B'},  // Dap an dung la B
        
        // Cau hoi 5: Ve trai dat
        {"Trai dat quay quanh gi?", 
         {"Mat troi", "Mat trang", "Sao Hoa", "Sao Kim"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 6: Ve quoc gia dong dan
        {"Quoc gia dong dan nhat the gioi?", 
         {"An Do", "Trung Quoc", "My", "Nga"}, 
         'B'},  // Dap an dung la B
        
        // Cau hoi 7: Ve ngon ngu pho bien
        {"Ngon ngu nao pho bien nhat the gioi?", 
         {"Tieng Anh", "Tieng Trung", "Tieng Tay Ban Nha", "Tieng Phap"}, 
         'B'},  // Dap an dung la B
        
        // Cau hoi 8: Ve tac gia Truyen Kieu
        {"Ai la tac gia Truyen Kieu?", 
         {"Nguyen Du", "Nguyen Trai", "Xuan Dieu", "To Huu"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 9: Ve Windows
        {"He dieu hanh Windows do cong ty nao phat trien?", 
         {"Apple", "Google", "Microsoft", "IBM"}, 
         'C'},  // Dap an dung la C
        
        // Cau hoi 10: Ve so Pi
        {"So Pi xap xi bang?", 
         {"3.14", "2.71", "1.41", "1.61"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 11: Ve thu do nuoc My (cau hoi moi)
        {"Thu do cua nuoc My la gi?", 
         {"New York", "Los Angeles", "Washington D.C.", "Chicago"}, 
         'C'},  // Dap an dung la C
        
        // Cau hoi 12: Ve ngon ngu Python (cau hoi moi)
        {"Ngon ngu lap trinh Python duoc phat minh vao nam nao?", 
         {"1989", "1995", "2000", "2005"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 13: Ve hanh tinh (cau hoi moi)
        {"Hanh tinh nao gan mat troi nhat?", 
         {"Sao Thuy", "Sao Kim", "Trai Dat", "Sao Hoa"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 14: Ve bien (cau hoi moi)
        {"Bien nao lon nhat the gioi?", 
         {"Thai Binh Duong", "Dai Tay Duong", "An Do Duong", "Bac Bang Duong"}, 
         'A'},  // Dap an dung la A
        
        // Cau hoi 15: Ve ngon ngu C (cau hoi moi)
        {"Ngon ngu lap trinh C duoc phat trien boi ai?", 
         {"Dennis Ritchie", "Bjarne Stroustrup", "James Gosling", "Guido van Rossum"}, 
         'A'}   // Dap an dung la A
    };
    
    // ============================================
    // CHON NGAU NHIEN 5 CAU HOI
    // ============================================
    int chosen[QUESTIONS_TO_PLAY];  // Mang luu chi so cua 5 cau hoi duoc chon
    
    // Vong lap chon 5 cau hoi khong trung nhau
    for (int i = 0; i < QUESTIONS_TO_PLAY; i++) {
        int r;  // Bien luu so ngau nhien
        do {
            // Sinh mot so ngau nhien tu 0 den TOTAL_QUESTIONS - 1
            r = rand() % TOTAL_QUESTIONS;
            int duplicate = 0;  // Co danh dau trung lap (0 = khong trung, 1 = trung)
            
            // Kiem tra xem so r da duoc chon truoc do chua
            for (int j = 0; j < i; j++) {
                if (chosen[j] == r) {  // Neu trung voi cau hoi da chon
                    duplicate = 1;     // Danh dau la trung
                    break;             // Thoat khoi vong lap kiem tra
                }
            }
            
            // Neu khong trung, luu chi so vao mang chosen
            if (!duplicate) {
                chosen[i] = r;  // Luu chi so cau hoi duoc chon
                break;           // Thoat khoi vong lap do-while
            }
        } while (1);  // Lap lai cho den khi tim duoc cau hoi khong trung
    }
    
    // ============================================
    // HIEN THI CAU HOI VA TINH DIEM
    // ============================================
    printf("\n===== Quiz Game =====\n");  // Hien thi tieu de tro choi
    
    // Vong lap hien thi lan luot 5 cau hoi da chon
    for (int i = 0; i < QUESTIONS_TO_PLAY; i++) {
        // Goi ham askQuestion voi cau hoi tai vi tri chosen[i] trong mang questions
        // Truyen con tro &score de ham co the thay doi diem so
        askQuestion(questions[chosen[i]], &score);
    }
    
    // ============================================
    // HIEN THI KET QUA
    // ============================================
    // In ra ten nguoi choi va diem so dat duoc
    printf("\n%s, ban dat %d/%d diem.\n", playerName, score, QUESTIONS_TO_PLAY);
    
    // ============================================
    // LUU TEN VA DIEM VAO FILE TEXT
    // ============================================
    // Mo file quiz_results.txt o che do append (them vao cuoi file)
    // Neu file chua ton tai, se tao file moi
    FILE *f = fopen("quiz_results.txt", "a");
    
    if (f != NULL) {  // Neu mo file thanh cong
        // Ghi ten nguoi choi va diem vao file
        // Format: "Ten: diem/tong_so_cau\n"
        fprintf(f, "%s: %d/%d\n", playerName, score, QUESTIONS_TO_PLAY);
        fclose(f);  // Dong file sau khi ghi xong
    } else {  // Neu khong mo duoc file
        printf("Khong the mo file de luu ket qua.\n");  // Hien thi thong bao loi
    }
    
    // ============================================
    // HIEN THI BANG XEP HANG
    // ============================================
    printf("\n===== Bang xep hang =====\n");  // Hien thi tieu de bang xep hang
    
    // Mo file quiz_results.txt o che do doc (read)
    f = fopen("quiz_results.txt", "r");
    
    if (f != NULL) {  // Neu mo file thanh cong
        char line[100];  // Mang ky tu luu tung dong doc duoc tu file
        
        // Doc tung dong trong file cho den het file
        // fgets tra ve NULL khi het file hoac co loi
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);  // Hien thi dong vua doc ra man hinh
        }
        
        fclose(f);  // Dong file sau khi doc xong
    } else {  // Neu khong mo duoc file
        printf("Khong the mo file de doc ket qua.\n");  // Hien thi thong bao loi
    }
    
    return 0;  // Tra ve 0 de bao hieu chuong trinh chay thanh cong
}

