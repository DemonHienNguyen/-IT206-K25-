#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Khai b�o struct Student
typedef struct {
    int id;              
    char name[50];      
    int age;             
    float gpa;           
}Student;

void removeBuffer(){
	 int c;
	 while((c = getchar()) != '\n' && c != EOF);
}

void removeNewLine(char *a){
	size_t len = strlen(a);
	a[len-1] = '\0';
	
}
void addStudent(Student stu[], int *size){
	const int COUNT = 5; 
	
	for(int i = *size; i < *size + COUNT; i++){ 
		printf("Thong tin cua sinh vien thu %d\n", i - *size + 1);
		
		printf("Nhap Id: "); 
		scanf("%d", &stu[i].id);
		removeBuffer();
		
		printf("Nhap ten: ");
		fgets(stu[i].name, sizeof(stu[i].name), stdin);
		removeNewLine(stu[i].name);
		
		printf("Nhap tuoi: ");
		scanf("%d", &stu[i].age);
		removeBuffer();
		
	
		printf("Nhap GPA [0-4.0]: ");
		while(1){ 
			scanf("%f", &stu[i].gpa);
			if(stu[i].gpa >= 0 && stu[i].gpa <= 4.0) break; 
			printf("Loi! GPA phai trong [0-4.0]. Nhap lai: "); 
		}
		removeBuffer();
	}
	*size += COUNT; 
	printf("Nhap thong tin thanh cong!\n");
}
void saveToFile(Student stu[], int n){
	FILE *f = fopen("students.txt", "w"); 
	if(f == NULL){
		printf("Loi! Khong the mo file\n"); 
		exit(1);
	}
	fprintf(f, "%-5s %-15s %-5s %-6s\n", "ID", "Name", "Age", "GPA");
	fprintf(f, "----------------------------------------\n");
	for(int i = 0; i < n; i++){ 
		fprintf(f, "%-5d %-15s %-5d %-6.2f\n", stu[i].id, stu[i].name, stu[i].age, stu[i].gpa); 
	}
	printf("Da luu danh sach sinh vien vao file students.txt\n");
	fclose(f);
}

/**
 * Ghi danh sach sinh vien vao file voi ten file duoc chi dinh
 * 
 * Tham so:
 *   - filename: Ten file can ghi (vi du: "classA.txt")
 *   - stu[]: Mang danh sach sinh vien
 *   - n: So luong sinh vien
 */
void saveToFileWithName(char filename[], Student stu[], int n){
	// Buoc 1: Mo file de ghi (mode "w" = write, ghi de file cu neu co)
	FILE *f = fopen(filename, "w"); 
	
	// Buoc 2: Kiem tra xem co mo file thanh cong khong
	if(f == NULL){
		printf("Loi! Khong the mo file %s de ghi\n", filename); 
		exit(1); // Thoat chuong trinh neu khong mo duoc file
	}
	
	// Buoc 3: Ghi tieu de vao file
	fprintf(f, "%-5s %-15s %-5s %-6s\n", "ID", "Name", "Age", "GPA");
	fprintf(f, "----------------------------------------\n");
	
	// Buoc 4: Ghi tung sinh vien vao file
	for(int i = 0; i < n; i++){ 
		fprintf(f, "%-5d %-15s %-5d %-6.2f\n", 
		        stu[i].id, stu[i].name, stu[i].age, stu[i].gpa); 
	}
	
	// Buoc 5: Thong bao da ghi thanh cong
	printf("Da luu danh sach sinh vien vao file %s\n", filename);
	
	// Buoc 6: Dong file lai de dam bao du lieu duoc ghi vao dia
	fclose(f);
}

/**
 * Doc danh sach sinh vien tu file voi ten file do nguoi dung nhap
 * 
 * Tham so:
 *   - filename: Ten file can doc (do nguoi dung nhap)
 *   - stu[]: Mang de luu danh sach sinh vien doc duoc
 *   - n: Con tro toi bien luu so luong sinh vien (se duoc cap nhat)
 */
void readFromFile(char filename[], Student stu[], int *n){
	// Buoc 1: Mo file de doc (mode "r" = read)
	FILE *f = fopen(filename, "r"); 
	
	// Buoc 2: Kiem tra xem co mo file thanh cong khong
	if(f == NULL){
		printf("Loi! Khong the mo file %s de doc\n", filename); 
		printf("Vui long kiem tra lai ten file hoac file chua duoc tao!\n");
		exit(1); // Thoat chuong trinh neu khong mo duoc file
	}
	
	// Buoc 3: Dat so luong sinh vien ve 0 (bat dau doc tu dau)
	*n = 0; 
	
	// Buoc 4: Bo qua 2 dong dau tien (dong tieu de va dong gach ngang)
	char temp[200]; 
	fgets(temp, sizeof(temp), f); // Doc dong tieu de "ID Name Age GPA"
	fgets(temp, sizeof(temp), f); // Doc dong gach ngang "--------"
	
	// Buoc 5: Doc tung dong du lieu sinh vien
	char line[200];
	while(fgets(line, sizeof(line), f) != NULL){ // Doc den khi het file
		// Parse du lieu tu dong: ID, ten, tuoi, GPA
		if(sscanf(line, "%d %49s %d %f", &stu[*n].id, stu[*n].name, 
		          &stu[*n].age, &stu[*n].gpa) == 4){
			// Xoa khoang trang thua o cuoi ten (neu co)
			int len = strlen(stu[*n].name);
			while(len > 0 && stu[*n].name[len-1] == ' '){
				stu[*n].name[--len] = '\0'; 
			}
			(*n)++; // Tang so luong sinh vien sau moi lan doc thanh cong
		}
	}
	
	// Buoc 6: Thong bao so luong sinh vien doc duoc
	printf("Da doc thanh cong %d sinh vien tu file %s\n", *n, filename);
	
	// Buoc 7: Dong file lai
	fclose(f); 
}
void showStu(Student stu[], int *n){
	FILE *f = fopen("students.txt", "r"); 
	if(f == NULL){
		printf("Loi! Khong the mo file\n"); 
		exit(1);
	}
	*n = 0; 
	char temp[200]; 
	fgets(temp, sizeof(temp), f); 
	fgets(temp, sizeof(temp), f); 
	
	char line[200];
	while(fgets(line, sizeof(line), f) != NULL){ 
		if(sscanf(line, "%d %49s %d %f", &stu[*n].id, stu[*n].name, &stu[*n].age, &stu[*n].gpa) == 4){
			int len = strlen(stu[*n].name);
			while(len > 0 && stu[*n].name[len-1] == ' '){
				stu[*n].name[--len] = '\0'; 
			}
			(*n)++; 
		}
	}
	fclose(f); 
}

/**
 * Tim kiem sinh vien trong danh sach theo ma ID
 * 
 * Muc dich: Ham nay cho phep nguoi dung nhap vao ma ID va tim kiem 
 *           sinh vien co ID tuong ung trong mang. Neu tim thay, 
 *           se in ra day du thong tin cua sinh vien do.
 * 
 * Tham so dau vao:
 *   - stu[]: Mang chua danh sach cac sinh vien (Student)
 *   - n: So luong sinh vien hien co trong mang (int)
 * 
 * Gia tri tra ve:
 *   - Khong tra ve gia tri nao (void)
 *   - In ra man hinh thong tin sinh vien neu tim thay
 *   - In ra thong bao "Khong tim thay sinh vien" neu khong tim thay
 */
void findStudentById(Student stu[], int n) {
    int findId;
    printf("Nhap ID can tim: ");
    scanf("%d", &findId);
    removeBuffer(); // Xoa buffer sau khi nhap ID
    
    for (int i = 0; i < n; i++) {
        if (stu[i].id == findId) {
            printf("\nThong tin sinh vien tim thay:\n");
            printf("ID   : %d\n", stu[i].id);
            printf("Ten  : %s\n", stu[i].name);
            printf("Tuoi : %d\n", stu[i].age);
            printf("GPA  : %.2f\n", stu[i].gpa);
            return; // Thoat ham ngay khi tim thay
        }
    }
    
    // Neu chay het vong lap ma khong tim thay
    printf("Khong tim thay sinh vien\n");
}

/**
 * Them sinh vien moi vao danh sach
 * 
 * Muc dich: Ham nay cho phep nguoi dung nhap thong tin sinh vien moi
 *           va them vao danh sach. Ham se kiem tra xem ID da ton tai
 *           chua, neu trung ID thi se khong them vao.
 * 
 * Tham so dau vao:
 *   - stu[]: Mang chua danh sach cac sinh vien (Student)
 *   - n: Con tro toi bien luu so luong sinh vien (int*)
 *        - Truoc khi goi: chua so luong hien tai
 *        - Sau khi goi: se duoc cap nhat neu them thanh cong
 *   - maxSize: So luong toi da sinh vien co the luu trong mang
 * 
 * Gia tri tra ve:
 *   - Khong tra ve gia tri (void)
 *   - In ra man hinh ket qua: thanh cong hoac ID da ton tai
 */
void addNewStudent(Student stu[], int *n, int maxSize){
	// Kiem tra danh sach da day chua
	if(*n >= maxSize){
		printf("Danh sach da day! Khong the them sinh vien moi.\n");
		return; // Thoat ham neu danh sach da day
	}
	
	// Khai bao bien de luu thong tin sinh vien moi
	Student newStudent;
	
	printf("\n=== THEM SINH VIEN MOI ===\n");
	
	// Nhap ID va kiem tra trung lap
	printf("Nhap ID: ");
	scanf("%d", &newStudent.id);
	removeBuffer();
	
	// Kiem tra ID da ton tai chua
	for(int i = 0; i < *n; i++){
		if(stu[i].id == newStudent.id){
			printf("Loi! ID %d da ton tai trong danh sach.\n", newStudent.id);
			printf("Khong the them sinh vien vi ID bi trung!\n");
			return; // Thoat ham neu ID trung
		}
	}
	
	// Nhap ten sinh vien
	printf("Nhap ten: ");
	fgets(newStudent.name, sizeof(newStudent.name), stdin);
	removeNewLine(newStudent.name);
	
	// Nhap tuoi sinh vien
	printf("Nhap tuoi: ");
	scanf("%d", &newStudent.age);
	removeBuffer();
	
	// Nhap GPA va kiem tra hop le
	printf("Nhap GPA [0-4.0]: ");
	while(1){
		scanf("%f", &newStudent.gpa);
		if(newStudent.gpa >= 0 && newStudent.gpa <= 4.0){
			break; // Thoat vong lap neu GPA hop le
		}
		printf("Loi! GPA phai trong [0-4.0]. Nhap lai: ");
	}
	removeBuffer();
	
	// Them sinh vien moi vao cuoi danh sach
	stu[*n] = newStudent;
	(*n)++; // Tang so luong sinh vien len 1
	
	printf("Them sinh vien thanh cong! So luong sinh vien hien tai: %d\n", *n);
}

/**
 * Xoa sinh vien khoi danh sach theo ID
 * 
 * Muc dich: Ham nay cho phep nguoi dung nhap ID va xoa sinh vien
 *           co ID tuong ung khoi danh sach. Neu khong tim thay ID,
 *           se thong bao loi.
 * 
 * Tham so dau vao:
 *   - stu[]: Mang chua danh sach cac sinh vien (Student)
 *   - n: Con tro toi bien luu so luong sinh vien (int*)
 *        - Truoc khi goi: chua so luong hien tai
 *        - Sau khi goi: se duoc giam di 1 neu xoa thanh cong
 * 
 * Gia tri tra ve:
 *   - Khong tra ve gia tri (void)
 *   - In ra man hinh ket qua: thanh cong hoac khong tim thay ID
 */
void deleteStudentById(Student stu[], int *n){
	// Kiem tra danh sach co rong khong
	if(*n == 0){
		printf("Danh sach rong! Khong co sinh vien nao de xoa.\n");
		return; // Thoat ham neu danh sach rong
	}
	
	int deleteId;
	printf("\n=== XOA SINH VIEN ===\n");
	printf("Nhap ID can xoa: ");
	scanf("%d", &deleteId);
	removeBuffer();
	
	// Tim vi tri sinh vien co ID can xoa
	int pos = -1; // -1 co nghia la chua tim thay
	for(int i = 0; i < *n; i++){
		if(stu[i].id == deleteId){
			pos = i; // Luu vi tri tim duoc
			break; // Thoat vong lap khi tim thay
		}
	}
	
	// Kiem tra co tim thay khong
	if(pos == -1){
		printf("Khong tim thay sinh vien co ID = %d trong danh sach!\n", deleteId);
		printf("Khong the xoa vi ID khong ton tai.\n");
		return; // Thoat ham neu khong tim thay
	}
	
	// Xoa sinh vien bang cach dich cac phan tu phia sau len truoc
	// Vi du: Mang [A, B, C, D], xoa B (pos=1)
	// Buoc 1: Dich C len vi tri 1 -> [A, C, C, D]
	// Buoc 2: Dich D len vi tri 2 -> [A, C, D, D]
	// Buoc 3: Giam n xuong -> [A, C, D]
	for(int i = pos; i < *n - 1; i++){
		stu[i] = stu[i + 1]; // Dich phan tu sau len vi tri hien tai
	}
	
	(*n)--; // Giam so luong sinh vien di 1
	
	printf("Da xoa thanh cong sinh vien co ID = %d!\n", deleteId);
	printf("So luong sinh vien con lai: %d\n", *n);
}

void printStu(Student stu[], int n){
	printf("%-5s %-15s %-5s %-6s\n", "ID", "Name", "Age", "GPA");
	printf("----------------------------------------\n");
	for (int i = 0; i < n; i++) {
		printf("%-5d %-15s %-5d %-6.2f\n", stu[i].id, stu[i].name, stu[i].age, stu[i].gpa);
	}
}
/**
 * Sap xep danh sach sinh vien theo GPA tang dan (tu thap den cao)
 * Su dung thuat toan Bubble Sort
 * 
 * Giai thich thuat toan Bubble Sort:
 * - So sanh tung cap phan tu canh nhau
 * - Neu phan tu sau nho hon phan tu truoc, thi doi cho chung
 * - Lap lai cho den khi khong con cap nao can doi cho nua
 * - Ten "Bubble" vi phan tu nho nhat "noi bot" len dau danh sach
 * 
 * Tham so:
 *   - stu[]: Mang danh sach sinh vien can sap xep
 *   - n: So luong sinh vien trong mang
 */
void sortStudentsByGPA(Student stu[], int n){
	// Vong lap ngoai: chay (n-1) lan de dam bao sap xep het
	for(int i = 0; i < n - 1; i++){
		// Vong lap trong: so sanh tung cap phan tu canh nhau
		// Sau moi lan i, phan tu lon nhat se "chim" xuong cuoi
		// Nen chi can so sanh den (n-1-i) phan tu
		for(int j = 0; j < n - 1 - i; j++){
			// So sanh GPA cua 2 sinh vien canh nhau
			if(stu[j].gpa > stu[j+1].gpa){
				// Neu GPA truoc > GPA sau, thi doi cho 2 sinh vien
				Student temp = stu[j];     // Luu tam sinh vien truoc
				stu[j] = stu[j+1];         // Gan sinh vien sau vao vi tri truoc
				stu[j+1] = temp;           // Gan sinh vien truoc vao vi tri sau
			}
		}
	}
}


float arverageGPA(Student stu[], int n){
	float sum = 0.0; // Khoi tao sum = 0 de tranh gia tri rac
	
	// Tinh tong GPA cua tat ca sinh vien
	for(int i = 0; i < n; i++){
		sum += stu[i].gpa; // Cong tung GPA vao tong
	}
	
	// Kiem tra neu khong co sinh vien nao thi tra ve 0
	if(n == 0){
		return 0.0; // Tranh chia cho 0
	}
	
	return sum / n; // Tra ve GPA trung binh
}

/**
 * Hien thi menu chuong trinh quan ly sinh vien
 * 
 * Muc dich: In ra man hinh menu voi cac chuc nang co san
 *           de nguoi dung lua chon
 */
void showMenu(){
	printf("\n========================================\n");
	printf("         STUDENT MANAGER\n");
	printf("========================================\n");
	printf("1. Nhap sinh vien (5 sinh vien)\n");        // Chuc nang: Nhap 5 sinh vien
	printf("2. In danh sach\n");                        // Chuc nang: Hien thi danh sach sinh vien
	printf("3. Ghi file\n");                            // Chuc nang: Luu danh sach vao file students.txt
	printf("4. Doc file\n");                            // Chuc nang: Doc danh sach tu file students.txt
	printf("5. Tim kiem\n");                            // Chuc nang: Tim sinh vien theo ID
	printf("6. Sap xep\n");                             // Chuc nang: Sap xep sinh vien theo GPA tang dan
	printf("7. Them sinh vien\n");                      // Chuc nang: Them 1 sinh vien moi (kiem tra trung ID)
	printf("8. Xoa sinh vien\n");                       // Chuc nang: Xoa sinh vien theo ID
	printf("0. Thoat\n");                               // Chuc nang: Ket thuc chuong trinh
	printf("========================================\n");
	printf("Chon chuc nang: ");
}

/**
 * Khoi tao 10 sinh vien mau de test chuong trinh
 * 
 * Tham so:
 *   - stu[]: Mang de luu danh sach sinh vien
 *   - n: Con tro toi bien luu so luong sinh vien (se duoc cap nhat = 10)
 * 
 * Muc dich: Tao san 10 sinh vien voi ID, ten, tuoi, GPA khac nhau
 *           de nguoi dung co the test ngay cac chuc nang ma khong can nhap tay
 */
void initSampleStudents(Student stu[], int *n){
	// Tao 10 sinh vien mau voi thong tin da co san
	Student sample[10] = {
		{1, "Nguyen Van A", 20, 3.5},
		{2, "Tran Thi B", 19, 3.8},
		{3, "Le Van C", 21, 3.2},
		{4, "Pham Thi D", 20, 2.9},
		{5, "Hoang Van E", 22, 4.0},
		{6, "Vu Thi F", 19, 2.5},
		{7, "Dao Van G", 20, 3.7},
		{8, "Bui Thi H", 21, 3.0},
		{9, "Dinh Van I", 20, 2.8},
		{10, "Ly Thi J", 19, 3.9}
	};
	
	// Sao chep 10 sinh vien mau vao mang chinh
	for(int i = 0; i < 10; i++){
		stu[i] = sample[i];
	}
	
	*n = 10; // Cap nhat so luong sinh vien = 10
	printf("Da khoi tao 10 sinh vien mau de test!\n");
}

/**
 * LUONG CHAY CUA CHUONG TRINH:
 * 
 * 1. KHOI TAO:
 *    - Tao mang list[100] de luu danh sach sinh vien
 *    - Khoi tao size = 0 (chua co sinh vien nao)
 *    - Goi initSampleStudents() de tao 10 sinh vien mau
 * 
 * 2. VONG LAP MENU (lap lai cho den khi chon 0):
 *    - Hien thi menu (showMenu())
 *    - Doc lua chon cua nguoi dung
 *    - Xu ly theo lua chon:
 *      + 1: Nhap 5 sinh vien moi (addStudent)
 *      + 2: In danh sach hien tai (printStu)
 *      + 3: Ghi danh sach vao file students.txt (saveToFile)
 *      + 4: Doc danh sach tu file students.txt (showStu)
 *      + 5: Tim sinh vien theo ID (findStudentById)
 *      + 6: Sap xep theo GPA tang dan (sortStudentsByGPA)
 *      + 7: Them 1 sinh vien moi (addNewStudent) - kiem tra trung ID
 *      + 8: Xoa sinh vien theo ID (deleteStudentById) - kiem tra ID ton tai
 *      + 0: Thoat chuong trinh (break khoi vong lap)
 *    - Neu lua chon khong hop le, thong bao loi
 * 
 * 3. KET THUC:
 *    - In thong bao ket thuc
 *    - Tra ve 0
 */
int main() {
	Student list[100];           // Mang luu danh sach sinh vien (toi da 100 sinh vien)
	int size = 0;                // So luong sinh vien hien co trong danh sach
	const int MAX_SIZE = 100;    // So luong toi da sinh vien co the luu
	int choice;                  // Bien luu lua chon cua nguoi dung
	
	// KHOI TAO DU LIEU MAU: Tao 10 sinh vien de test
	printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
	initSampleStudents(list, &size);
	printf("Danh sach ban dau co %d sinh vien:\n", size);
	printStu(list, size);
	
	// VONG LAP MENU: Lap lai cho den khi nguoi dung chon 0 (Thoat)
	while(1){
		// Buoc 1: Hien thi menu de nguoi dung lua chon
		showMenu();
		
		// Buoc 2: Doc lua chon cua nguoi dung
		scanf("%d", &choice);
		removeBuffer(); // Xoa buffer sau khi nhap so
		
		// Buoc 3: Xu ly theo lua chon cua nguoi dung
		switch(choice){
			case 1: // Chuc nang 1: Nhap 5 sinh vien
				printf("\n=== CHUC NANG 1: NHAP SINH VIEN ===\n");
				printf("Ban se nhap 5 sinh vien moi vao danh sach.\n");
				addStudent(list, &size); // Goi ham nhap 5 sinh vien
				break;
				
			case 2: // Chuc nang 2: In danh sach sinh vien
				printf("\n=== CHUC NANG 2: IN DANH SACH ===\n");
				if(size == 0){
					printf("Danh sach rong! Chua co sinh vien nao.\n");
				} else {
					printf("Danh sach hien co %d sinh vien:\n", size);
					printStu(list, size); // In danh sach ra man hinh
				}
				break;
				
			case 3: // Chuc nang 3: Ghi danh sach vao file
				printf("\n=== CHUC NANG 3: GHI FILE ===\n");
				if(size == 0){
					printf("Danh sach rong! Khong co gi de luu.\n");
				} else {
					saveToFile(list, size); // Luu danh sach vao file students.txt
				}
				break;
				
			case 4: // Chuc nang 4: Doc danh sach tu file
				printf("\n=== CHUC NANG 4: DOC FILE ===\n");
				printf("Dang doc du lieu tu file students.txt...\n");
				showStu(list, &size); // Doc danh sach tu file students.txt
				printf("\nDa doc xong! Danh sach hien co %d sinh vien:\n", size);
				printStu(list, size);
				break;
				
			case 5: // Chuc nang 5: Tim kiem sinh vien theo ID
				printf("\n=== CHUC NANG 5: TIM KIEM ===\n");
				if(size == 0){
					printf("Danh sach rong! Khong co sinh vien nao de tim.\n");
				} else {
					findStudentById(list, size); // Tim va hien thi thong tin sinh vien
				}
				break;
				
			case 6: // Chuc nang 6: Sap xep sinh vien theo GPA tang dan
				printf("\n=== CHUC NANG 6: SAP XEP ===\n");
				if(size == 0){
					printf("Danh sach rong! Khong co gi de sap xep.\n");
				} else {
					printf("Danh sach truoc khi sap xep:\n");
					printStu(list, size);
					sortStudentsByGPA(list, size); // Sap xep theo GPA tang dan
					printf("\nDanh sach sau khi sap xep (GPA tang dan):\n");
					printStu(list, size);
				}
				break;
				
			case 7: // Chuc nang 7: Them 1 sinh vien moi
				printf("\n=== CHUC NANG 7: THEM SINH VIEN ===\n");
				addNewStudent(list, &size, MAX_SIZE); // Them 1 sinh vien (kiem tra trung ID)
				break;
				
			case 8: // Chuc nang 8: Xoa sinh vien theo ID
				printf("\n=== CHUC NANG 8: XOA SINH VIEN ===\n");
				if(size == 0){
					printf("Danh sach rong! Khong co sinh vien nao de xoa.\n");
				} else {
					deleteStudentById(list, &size); // Xoa sinh vien theo ID
				}
				break;
				
			case 0: // Chuc nang 0: Thoat chuong trinh
				printf("\n=== THOAT CHUONG TRINH ===\n");
				printf("Cam on ban da su dung chuong trinh!\n");
				printf("Hen gap lai!\n");
				return 0; // Thoat ham main(), ket thuc chuong trinh
				
			default: // Neu lua chon khong hop le (khong phai 0-8)
				printf("\nLoi! Lua chon khong hop le.\n");
				printf("Vui long chon tu 0 den 8.\n");
				break;
		}
	}
	
	return 0;
}

